MITK_CREATE_MODULE(Qt4Qt5TestModule
               QT4_MODULES QtCore # we want something in the Qt 4 case
               QT5_MODULES Qt5Core # we want something else in the Qt 5 case
               SUBPROJECTS MITK-CoreUI
)

add_subdirectory(Testing)
