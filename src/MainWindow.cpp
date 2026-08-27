#include "MainWindow.h"

#include <QString>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "blocks/CConst.h"
#include "blocks/CGain.h"
#include "engine/CContainerFBD.h"
#include "engine/CSimEngine.h"
#include "interfaces/ICFunctionBlock.h"
#include "interfaces/ICOutput.h"

MainWindow::MainWindow(CContainerFBD* container, CSimEngine* engine, QWidget* parent)
    : QMainWindow(parent), m_container(container), m_engine(engine) {
    setupUi();

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    refreshBlockSelector();
    refreshMonitoring();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    setWindowTitle("FBD Simulator");

    QVBoxLayout* rootLayout = new QVBoxLayout(central);

    QGroupBox* controlPanel = new QGroupBox("Control Panel", central);
    QHBoxLayout* controlLayout = new QHBoxLayout(controlPanel);
    QPushButton* startBtn = new QPushButton("Start", controlPanel);
    QPushButton* pauseBtn = new QPushButton("Pause", controlPanel);
    QPushButton* stopBtn = new QPushButton("Stop", controlPanel);
    QPushButton* stepBtn = new QPushButton("Step", controlPanel);
    controlLayout->addWidget(startBtn);
    controlLayout->addWidget(pauseBtn);
    controlLayout->addWidget(stopBtn);
    controlLayout->addWidget(stepBtn);
    rootLayout->addWidget(controlPanel);

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(pauseBtn, &QPushButton::clicked, this, &MainWindow::onPause);
    connect(stopBtn, &QPushButton::clicked, this, &MainWindow::onStop);
    connect(stepBtn, &QPushButton::clicked, this, &MainWindow::onStep);

    QGroupBox* paramPanel = new QGroupBox("Simulation Parameters", central);
    QFormLayout* paramLayout = new QFormLayout(paramPanel);
    m_samplingSpin = new QSpinBox(paramPanel);
    m_samplingSpin->setRange(1, 10000);
    m_samplingSpin->setValue(m_container != nullptr ? static_cast<int>(m_container->getSamplingTime()) : 100);

    m_maxStepsSpin = new QSpinBox(paramPanel);
    m_maxStepsSpin->setRange(1, 10000000);
    m_maxStepsSpin->setValue(1000);
    paramLayout->addRow("Sampling Time [ms]", m_samplingSpin);
    paramLayout->addRow("Max Steps", m_maxStepsSpin);
    rootLayout->addWidget(paramPanel);

    connect(m_samplingSpin, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        if (m_container != nullptr) {
            m_container->setSamplingTime(static_cast<unsigned>(v));
        }
    });
    connect(m_maxStepsSpin, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        if (m_engine != nullptr) {
            m_engine->setMaxSteps(static_cast<unsigned>(v));
        }
    });

    QGroupBox* monitorPanel = new QGroupBox("Monitoring", central);
    QFormLayout* monitorLayout = new QFormLayout(monitorPanel);
    m_stepLabel = new QLabel("0", monitorPanel);
    m_timeLabel = new QLabel("0.000", monitorPanel);
    monitorLayout->addRow("Current Step", m_stepLabel);
    monitorLayout->addRow("Current Time [s]", m_timeLabel);
    rootLayout->addWidget(monitorPanel);

    QGroupBox* dynParamPanel = new QGroupBox("Dynamic Block Parameterization", central);
    QHBoxLayout* dynParamLayout = new QHBoxLayout(dynParamPanel);
    m_blockSelector = new QComboBox(dynParamPanel);
    m_paramSpin = new QDoubleSpinBox(dynParamPanel);
    m_paramSpin->setRange(-1e9, 1e9);
    m_paramSpin->setDecimals(6);
    QPushButton* applyBtn = new QPushButton("Apply", dynParamPanel);
    dynParamLayout->addWidget(m_blockSelector);
    dynParamLayout->addWidget(m_paramSpin);
    dynParamLayout->addWidget(applyBtn);
    rootLayout->addWidget(dynParamPanel);

    connect(applyBtn, &QPushButton::clicked, this, &MainWindow::onApplyParameter);
}

void MainWindow::refreshMonitoring() {
    if (m_engine != nullptr) {
        m_stepLabel->setText(QString::number(m_engine->getCurrentStep()));
        m_timeLabel->setText(QString::number(m_engine->getCurrentTime().getInSeconds(), 'f', 3));
    }

    if (m_container == nullptr) {
        return;
    }

    for (ICFunctionBlock* block : m_container->getBlocks()) {
        if (block == nullptr || block->getOutCount() == 0U) {
            continue;
        }
        if (m_outputLabels.find(block->getName()) == m_outputLabels.end()) {
            if (QGroupBox* monitorBox = findChild<QGroupBox*>("")) {
                (void)monitorBox;
            }
        }
    }

    QGroupBox* monitorPanel = nullptr;
    const QList<QGroupBox*> groups = centralWidget()->findChildren<QGroupBox*>();
    for (QGroupBox* group : groups) {
        if (group->title() == "Monitoring") {
            monitorPanel = group;
            break;
        }
    }

    if (monitorPanel == nullptr) {
        return;
    }

    QFormLayout* monitorLayout = qobject_cast<QFormLayout*>(monitorPanel->layout());
    if (monitorLayout == nullptr) {
        return;
    }

    for (ICFunctionBlock* block : m_container->getBlocks()) {
        if (block == nullptr || block->getOutCount() == 0U) {
            continue;
        }
        QLabel*& lbl = m_outputLabels[block->getName()];
        if (lbl == nullptr) {
            lbl = new QLabel("-", monitorPanel);
            monitorLayout->addRow(QString::fromStdString(block->getName() + " out0"), lbl);
        }
        const SDataSample sample = block->getOutput(0U)->getData();
        if (sample.isOK()) {
            lbl->setText(QString::number(sample.Value, 'f', 6));
        } else {
            lbl->setText("BAD");
        }
    }
}

void MainWindow::refreshBlockSelector() {
    m_blockSelector->clear();
    if (m_container == nullptr) {
        return;
    }

    for (ICFunctionBlock* block : m_container->getBlocks()) {
        if (block != nullptr) {
            m_blockSelector->addItem(QString::fromStdString(block->getName()));
        }
    }
}

void MainWindow::onStart() {
    if (m_container == nullptr || m_engine == nullptr) {
        return;
    }
    m_container->setSamplingTime(static_cast<unsigned>(m_samplingSpin->value()));
    m_engine->setMaxSteps(static_cast<unsigned>(m_maxStepsSpin->value()));
    m_engine->resetSimulation();
    refreshMonitoring();
    m_timer->start();
}

void MainWindow::onPause() {
    if (m_timer != nullptr) {
        m_timer->stop();
    }
}

void MainWindow::onStop() {
    if (m_timer != nullptr) {
        m_timer->stop();
    }
    if (m_engine != nullptr) {
        m_engine->finalizeSimulation();
        m_engine->resetSimulation();
    }
    refreshMonitoring();
}

void MainWindow::onStep() {
    if (m_container == nullptr || m_engine == nullptr) {
        return;
    }

    if (m_engine->getCurrentStep() == 0U && m_engine->getCurrentTime().getInSeconds() == 0.0) {
        m_container->setSamplingTime(static_cast<unsigned>(m_samplingSpin->value()));
        m_engine->setMaxSteps(static_cast<unsigned>(m_maxStepsSpin->value()));
        m_engine->resetSimulation();
    }

    m_engine->doSimStep();
    refreshMonitoring();
}

void MainWindow::onTimerTick() {
    if (m_engine == nullptr) {
        return;
    }
    m_engine->doSimStep();
    refreshMonitoring();
    if (!m_engine->canStep()) {
        m_timer->stop();
        m_engine->finalizeSimulation();
    }
}

void MainWindow::onApplyParameter() {
    if (m_container == nullptr) {
        return;
    }

    const std::string blockName = m_blockSelector->currentText().toStdString();
    ICFunctionBlock* block = m_container->findBlockByName(blockName);
    if (block == nullptr) {
        return;
    }

    const double newValue = m_paramSpin->value();
    if (CConst* constBlock = dynamic_cast<CConst*>(block)) {
        constBlock->setParam(newValue);
    } else if (CGain* gainBlock = dynamic_cast<CGain*>(block)) {
        gainBlock->setParam(newValue);
    }
}
