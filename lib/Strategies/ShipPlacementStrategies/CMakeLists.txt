add_library(ShipPlacementStrategies ShipPlacementStrategies.cpp ShipPlacementStrategies.hpp)

target_link_libraries(ShipPlacementStrategies PUBLIC
    Field
    Response
    GameSettings
)

target_include_directories(ShipPlacementStrategies PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)