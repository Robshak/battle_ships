add_library(ShootingStrategies INTERFACE)

target_link_libraries(ShootingStrategies INTERFACE
    GameSettings
    Response
)

target_include_directories(ShootingStrategies INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/Structures/GameSettings
)

add_subdirectory(CustomShooting)
add_subdirectory(OrderedShooting)