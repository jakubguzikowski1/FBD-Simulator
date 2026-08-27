#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include <string>

#include <QMainWindow>

class CContainerFBD;
class CSimEngine;
class QLabel;
class QTimer;
class QComboBox;
class QDoubleSpinBox;
class QSpinBox;

/**
 * @brief Main application window for controlling and monitoring simulation.
 */
class MainWindow : public QMainWindow {
public:
    /**
     * @brief Constructs window with injected simulation dependencies.
     * @param container Simulation model container.
     * @param engine Simulation engine.
     * @param parent Parent widget.
     */
    explicit MainWindow(CContainerFBD* container, CSimEngine* engine, QWidget* parent = nullptr);

    /**
     * @brief Destroys main window.
     */
    ~MainWindow() override;

private:
    /**
     * @brief Builds and wires GUI widgets.
     */
    void setupUi();

    /**
     * @brief Refreshes labels with current simulation state.
     */
    void refreshMonitoring();

    /**
     * @brief Updates block selection combo values.
     */
    void refreshBlockSelector();

    /**
     * @brief Handles start button click.
     */
    void onStart();

    /**
     * @brief Handles pause button click.
     */
    void onPause();

    /**
     * @brief Handles stop button click.
     */
    void onStop();

    /**
     * @brief Handles single-step button click.
     */
    void onStep();

    /**
     * @brief Handles periodic timer tick.
     */
    void onTimerTick();

    /**
     * @brief Applies parameter value to selected block.
     */
    void onApplyParameter();

    /**
     * @brief Injected simulation container pointer.
     */
    CContainerFBD* m_container{nullptr};

    /**
     * @brief Injected simulation engine pointer.
     */
    CSimEngine* m_engine{nullptr};

    /**
     * @brief Timer driving real-time simulation ticks.
     */
    QTimer* m_timer{nullptr};

    /**
     * @brief Sampling-time editor in milliseconds.
     */
    QSpinBox* m_samplingSpin{nullptr};

    /**
     * @brief Maximum-steps editor.
     */
    QSpinBox* m_maxStepsSpin{nullptr};

    /**
     * @brief Label for current simulation step.
     */
    QLabel* m_stepLabel{nullptr};

    /**
     * @brief Label for current simulation time.
     */
    QLabel* m_timeLabel{nullptr};

    /**
     * @brief Block-name selector for parameter editing.
     */
    QComboBox* m_blockSelector{nullptr};

    /**
     * @brief Parameter value editor.
     */
    QDoubleSpinBox* m_paramSpin{nullptr};

    /**
     * @brief Map of monitored block output labels by name.
     */
    std::map<std::string, QLabel*> m_outputLabels;
};

#endif  // MAINWINDOW_H
