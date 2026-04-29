cmake_minimum_required(VERSION 3.19)
project(Resolution LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Resolution
    WIN32 MACOSX_BUNDLE
    main.cpp
    Resolution.cpp
    Resolution.h
    Resolution.ui
    Fichier.h Fichier.cpp
    Chaine.h Chaine.cpp
)

target_link_libraries(Resolution
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Resolution
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Resolution
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
