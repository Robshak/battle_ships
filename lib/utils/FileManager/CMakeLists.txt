add_library(FileManager FileManager.cpp FileManager.hpp)

target_link_libraries(FileManager PUBLIC
    Field
    Ship
    Response
    GameSettings
)

target_include_directories(FileManager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)