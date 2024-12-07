add_library(FileManager FileManager.cpp FileManager.hpp)

target_link_libraries(FileManager PUBLIC
    Field
    Ship
    Response
)

target_include_directories(FileManager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib
    # ${PROJECT_SOURCE_DIR}/lib/Field
    ${PROJECT_SOURCE_DIR}/lib/utils
)