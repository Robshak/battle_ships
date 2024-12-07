add_library(Commands Commands.cpp Commands.hpp)

target_link_libraries(Commands PUBLIC
    Manager
    FileManager
    Field
    Response
)

target_include_directories(Commands PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)