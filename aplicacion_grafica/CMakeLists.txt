cmake_minimum_required(VERSION 3.19)
project(aplicacion_grafica LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Charts)

qt_standard_project_setup()

qt_add_executable(aplicacion_grafica
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    csvreader.h CSVReader.cpp
    datasample.h
    temperaturecalculator.h temperaturecalculator.cpp
)

target_link_libraries(aplicacion_grafica
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
)

install(TARGETS aplicacion_grafica
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET aplicacion_grafica
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
