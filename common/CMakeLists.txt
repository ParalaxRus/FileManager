#find_package(Boost 1.74 REQUIRED COMPONENTS program_options filesystem)
#include_directories(${Boost_INCLUDE_DIRS})

add_library(common SHARED command.cpp filemanager.cpp)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(common LINK_PUBLIC ${Boost_LIBRARIES})