add_library(Manager Manager.cpp Manager.hpp)

target_link_libraries(Manager PUBLIC
    GameSettings
    Field
    Handler
    ShipPlacementStrategies
    CustomShooting
    OrderedShooting
    Response
)

target_include_directories(Manager PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)