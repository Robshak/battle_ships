add_library(Field Field.cpp Field.hpp)

target_link_libraries(Field PUBLIC
Ship)

target_include_directories(Field PUBLIC ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(Ship)