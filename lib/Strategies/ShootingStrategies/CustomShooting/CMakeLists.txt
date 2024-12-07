add_library(CustomShooting CustomShooting.cpp CustomShooting.hpp)

target_link_libraries(CustomShooting PUBLIC
    GameSettings
    ShootingStrategies
    Response
)

target_include_directories(CustomShooting PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)