#
# First, set the generator variable
#
IF(NOT CPACK_GENERATOR)
  IF(WIN32)
    FIND_PROGRAM(NSIS_MAKENSIS NAMES makensis
      PATHS [HKEY_LOCAL_MACHINE\\SOFTWARE\\NSIS]
      DOC "Where is makensis.exe located"
      )

    IF(NOT NSIS_MAKENSIS)
      SET(CPACK_GENERATOR ZIP)
    ELSE()
      SET(CPACK_GENERATOR "NSIS;ZIP")
      
    ENDIF(NOT NSIS_MAKENSIS)
  ELSE()
    IF(APPLE)
      SET(CPACK_GENERATOR DragNDrop)
    ELSE()
      SET(CPACK_GENERATOR TGZ)
    ENDIF()
  ENDIF()
ENDIF(NOT CPACK_GENERATOR)

# include required mfc libraries
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_NAME "MITK")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MITK is a medical image processing tool")
SET(CPACK_PACKAGE_VENDOR "German Cancer Research Center (DKFZ)")
SET(CPACK_CREATE_DESKTOP_LINKS "ExtApp")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${MITK_SOURCE_DIR}/MITKCopyright.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${MITK_SOURCE_DIR}/MITKCopyright.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MITK_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MITK_VERSION_MINOR}")

# tell cpack to strip all debug symbols from all files
SET(CPACK_STRIP_FILES ON)

# append revision number if available
IF(MITK_WC_REVISION_HASH)
  STRING(SUBSTRING ${MITK_WC_REVISION_HASH} 0 6 git_hash)
  SET(CPACK_PACKAGE_VERSION_PATCH "${MITK_VERSION_PATCH}_r${git_hash}")
ELSE()
  SET(CPACK_PACKAGE_VERSION_PATCH "${MITK_VERSION_PATCH}")
ENDIF()


