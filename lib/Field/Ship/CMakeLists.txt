add_library(Ship Ship.cpp Ship.hpp)

target_link_libraries(Ship PUBLIC
    Response
)

target_include_directories(Ship PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)