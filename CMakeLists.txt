cmake_minimum_required(VERSION 3.10)
project(tqdmcpp VERSION 1.0.0 LANGUAGES CXX)

# Set standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Interface library for header-only
add_library(tqdmcpp INTERFACE)
target_include_directories(tqdmcpp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
add_library(tqdmcpp::tqdmcpp ALIAS tqdmcpp)
set_target_properties(tqdmcpp PROPERTIES EXPORT_NAME tqdmcpp)

# Example target
add_executable(examples examples/examples.cpp)
target_link_libraries(examples PRIVATE tqdmcpp)

# Install targets
include(GNUInstallDirs)

install(TARGETS tqdmcpp EXPORT tqdmcpp-targets)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT tqdmcpp-targets
    FILE tqdmcpp-targets.cmake
    NAMESPACE tqdmcpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tqdmcpp)

# Generate and install config files
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/tqdmcppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tqdmcppConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/tqdmcppConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tqdmcpp
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/tqdmcppConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/tqdmcppConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tqdmcpp)
