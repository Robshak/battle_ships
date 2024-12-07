add_library(Response Response.cpp Response.hpp)

target_link_libraries(Response PUBLIC
    Error
)

target_include_directories(Response PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/utils
    ${PROJECT_SOURCE_DIR}/lib/utils/Response
)

add_subdirectory(Error)