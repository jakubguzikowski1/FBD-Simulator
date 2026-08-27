cmake_minimum_required(VERSION 3.16)

project(FBDSimulator
    VERSION 1.0.0
    DESCRIPTION "Function Block Diagram (FBD) discrete-time simulator with Qt 6 GUI"
    LANGUAGES CXX
)

# ----- Language / tooling -----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)

# Export compile_commands.json for clangd / IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----- Dependencies -----
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ----- Sources -----
set(FBD_SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/io/CConnection.cpp
    src/io/CInput.cpp
    src/io/COutput.cpp
    src/blocks/CFunctionBlockBase.cpp
    src/blocks/CSourceBase.cpp
    src/blocks/CProcessingBlock.cpp
    src/blocks/CSinkBase.cpp
    src/blocks/CConst.cpp
    src/blocks/CPeriodicGenerator.cpp
    src/blocks/CFileRead.cpp
    src/blocks/CGain.cpp
    src/blocks/CAddSub.cpp
    src/blocks/CIntegrator.cpp
    src/blocks/CFileWrite.cpp
    src/engine/CContainerFBD.cpp
    src/engine/CFBDBuilder.cpp
    src/engine/CSimEngine.cpp
)

set(FBD_HEADERS
    src/MainWindow.h
    src/core/DataTypes.h
    src/interfaces/ICConnection.h
    src/interfaces/ICFunctionBlock.h
    src/interfaces/ICInput.h
    src/interfaces/ICOutput.h
    src/io/CConnection.h
    src/io/CInput.h
    src/io/COutput.h
    src/blocks/CFunctionBlockBase.h
    src/blocks/CSourceBase.h
    src/blocks/CProcessingBlock.h
    src/blocks/CSinkBase.h
    src/blocks/CConst.h
    src/blocks/CPeriodicGenerator.h
    src/blocks/CFileRead.h
    src/blocks/CGain.h
    src/blocks/CAddSub.h
    src/blocks/CIntegrator.h
    src/blocks/CFileWrite.h
    src/engine/CContainerFBD.h
    src/engine/CFBDBuilder.h
    src/engine/CSimEngine.h
)

add_executable(FBDSimulator
    ${FBD_SOURCES}
    ${FBD_HEADERS}
)

target_include_directories(FBDSimulator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(FBDSimulator
    PRIVATE
        Qt6::Widgets
)

# Friendly output name
set_target_properties(FBDSimulator PROPERTIES
    OUTPUT_NAME "FBDSimulator"
    WIN32_EXECUTABLE FALSE
)

# Copy sample config next to the binary for convenient local runs
add_custom_command(TARGET FBDSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/config.txt
        $<TARGET_FILE_DIR:FBDSimulator>/config.txt
    COMMENT "Copying config.txt next to FBDSimulator"
)

install(TARGETS FBDSimulator RUNTIME DESTINATION bin)
install(FILES config.txt DESTINATION bin)
