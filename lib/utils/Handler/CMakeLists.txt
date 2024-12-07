add_library(Handler Handler.cpp Handler.hpp)

target_link_libraries(Handler PUBLIC
    Commands
    Manager
    Field
    WorkWithString
    Response
)

target_include_directories(Handler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/utils
    ${PROJECT_SOURCE_DIR}/lib/utils/Handler
)

add_subdirectory(Commands)