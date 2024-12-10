#pragma once

#include <vector>

namespace BattleShipGame {
struct GameSettings {
    enum Role { Unknown, Master, Slave };

    int width;
    int height;

    std::vector<int> countOfShips = std::vector<int>(4, 0);

    Role role = Role::Unknown;
};
}  // namespace BattleShipGame