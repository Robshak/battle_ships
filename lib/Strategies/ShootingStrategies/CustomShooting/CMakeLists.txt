add_library(CustomShooting CustomShooting.cpp CustomShooting.hpp)

target_link_libraries(CustomShooting PUBLIC
ShootingStrategies)

target_include_directories(CustomShooting PUBLIC ${PROJECT_SOURCE_DIR}/lib)