cmake_minimum_required(VERSION 3.7.0)
project(flugs_framework VERSION 0.9.50)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

include(FeatureSummary)
include(InstallDirs)
include(CMakeSettings)
include(CompilerSettings)
include(GenerateHeaders)
include(Library)
include(Plugin)
include(Test)

set(REQUIRED_QT_VERSION 5.7.1)
find_package(Qt5Core    ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)
find_package(Qt5Network ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

message( STATUS "${PROJECT_NAME} ${PROJECT_VERSION} will be built for install into ${INSTALL_PREFIX}" )

add_subdirectory(3rdparty)
add_subdirectory(src)

add_library(other_files_target EXCLUDE_FROM_ALL
  .clang-format
  .gitignore
  LICENSE
  Makefile

  scripts/codingstyle.sh
  scripts/cppcheck.sh
  scripts/pmd-cpd.sh
  scripts/sloccount.sh
)

feature_summary(WHAT ALL)
