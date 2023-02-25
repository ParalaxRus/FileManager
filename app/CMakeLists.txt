find_package(Boost 1.74 REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(filemanager)
target_sources(filemanager PRIVATE main.cpp parser.cpp parser.h)
target_link_libraries(filemanager LINK_PUBLIC common)
target_link_libraries(filemanager LINK_PUBLIC ${Boost_LIBRARIES})

install(TARGETS filemanager
    COMPONENT linapp
    RUNTIME DESTINATION "/home/"
    LIBRARY DESTINATION "/home/"
    DESTINATION "/home/"
)