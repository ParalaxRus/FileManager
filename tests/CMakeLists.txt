add_executable(unittests)
target_sources(unittests PRIVATE main.cpp commandtests.cpp filemanagertests.cpp)
target_link_libraries(unittests LINK_PUBLIC common)

find_package(Boost 1.74 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(unittests LINK_PUBLIC ${Boost_LIBRARIES})

add_test(tests unittests)

