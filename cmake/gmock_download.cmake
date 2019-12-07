include (ExternalProject)

ExternalProject_Add(googletestlocal
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           release-1.10.0
  BUILD_IN_SOURCE   1
  DOWNLOAD_DIR      ${CMAKE_SOURCE_DIR}/external
  SOURCE_DIR        ${CMAKE_SOURCE_DIR}/external/googletest
  INSTALL_COMMAND   ""
  )