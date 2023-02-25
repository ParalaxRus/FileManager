add_library(common SHARED command.cpp filemanager.cpp)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS common
    LIBRARY DESTINATION "/usr/lib/"
    PUBLIC_HEADER DESTINATION "include"
)