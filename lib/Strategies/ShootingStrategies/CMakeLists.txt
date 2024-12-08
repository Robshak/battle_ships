add_library(ShootingStrategies ShootingStrategies.cpp ShootingStrategies.hpp)

target_link_libraries(ShootingStrategies PUBLIC
    GameSettings
    Response
)

target_include_directories(ShootingStrategies PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/Structures/GameSettings
)

add_subdirectory(CustomShooting)
add_subdirectory(OrderedShooting)