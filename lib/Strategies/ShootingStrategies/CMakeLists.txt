add_library(ShootingStrategies ShootingStrategies.cpp ShootingStrategies.hpp)

target_include_directories(ShootingStrategies PUBLIC ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(CustomShooting)
add_subdirectory(OrderedShooting)