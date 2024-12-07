add_library(Error Error.cpp Error.hpp)

target_include_directories(Error PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)