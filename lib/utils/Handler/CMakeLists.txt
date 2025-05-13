add_library(Handler Handler.cpp Handler.hpp Commands/Commands.hpp)

target_link_libraries(Handler PUBLIC
Manager
Field
WorkWithString)

target_include_directories(Handler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/utils
)