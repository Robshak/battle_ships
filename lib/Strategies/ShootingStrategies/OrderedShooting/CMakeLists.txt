add_library(OrderedShooting OrderedShooting.cpp OrderedShooting.hpp)

target_link_libraries(OrderedShooting PUBLIC
ShootingStrategies)

target_include_directories(OrderedShooting PUBLIC ${PROJECT_SOURCE_DIR}/lib)