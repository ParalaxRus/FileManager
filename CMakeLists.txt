cmake_minimum_required(VERSION 3.15)
project(FileManagerPrj VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(common)
add_subdirectory(app)

ENABLE_TESTING()
add_subdirectory(tests)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "eugeneb")
INCLUDE(CPack)