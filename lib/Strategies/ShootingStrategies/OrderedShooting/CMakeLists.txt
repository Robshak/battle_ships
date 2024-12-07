add_library(OrderedShooting OrderedShooting.cpp OrderedShooting.hpp)

target_link_libraries(OrderedShooting PUBLIC
    GameSettings
    ShootingStrategies
    Response
)

target_include_directories(OrderedShooting PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)