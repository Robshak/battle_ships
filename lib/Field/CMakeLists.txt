add_library(Field Field.cpp Field.hpp)

target_link_libraries(Field PUBLIC
    Ship
    Response
)

target_include_directories(Field PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/utils
)

add_subdirectory(Ship)