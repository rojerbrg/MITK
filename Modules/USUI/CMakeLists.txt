MITK_CREATE_MODULE(MitkUSUI
  #SUBPROJECTS MITK-US
  INCLUDE_DIRS Qmitk
  DEPENDS Mitk MitkUS Qmitk QmitkExt
  QT4_MODULES QtGui
  GENERATED_CPP ${TOOL_GUI_CPPS} ${TOOL_CPPS}
)

