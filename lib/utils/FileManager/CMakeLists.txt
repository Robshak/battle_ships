add_library(FileManager FileManager.cpp FileManager.hpp)

target_link_libraries(FileManager PUBLIC
Field)

target_include_directories(FileManager PUBLIC ${PROJECT_SOURCE_DIR}/lib)