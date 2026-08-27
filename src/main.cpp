#include <QApplication>
#include <QMessageBox>

#include <exception>

#include "MainWindow.h"
#include "engine/CContainerFBD.h"
#include "engine/CFBDBuilder.h"
#include "engine/CSimEngine.h"

/**
 * @brief Entry point of FBD Simulator.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return QApplication execution code.
 *
 * Dummy config.txt format example:
 * # Sampling period in milliseconds
 * SAMPLING 100
 * # Blocks: BLOCK <Type> <Name> [params...]
 * BLOCK Const const1 2.5
 * BLOCK PeriodicGenerator gen1 1.0 0.5
 * BLOCK AddSub sum1 ++
 * BLOCK Gain gain1 3.0
 * BLOCK Integrator int1
 * BLOCK FileWrite sink1 output.csv
 * # Connections: CONNECT <SrcBlock> <SrcOutIdx> <DstBlock> <DstInIdx>
 * CONNECT const1 0 sum1 0
 * CONNECT gen1 0 sum1 1
 * CONNECT sum1 0 gain1 0
 * CONNECT gain1 0 int1 0
 * CONNECT int1 0 sink1 0
 */
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    CContainerFBD container;
    CSimEngine engine(&container);
    CFBDBuilder builder(&container);

    try {
        builder.configureFBDFromFile("config.txt");
    } catch (const std::exception& ex) {
        QMessageBox::critical(nullptr, "Configuration Error", ex.what());
        return 1;
    }

    MainWindow w(&container, &engine);
    w.resize(900, 500);
    w.show();

    return app.exec();
}
