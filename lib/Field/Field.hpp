#pragma once
#include <map>

#include "Ship/Ship.hpp"

namespace BattleShipGame {
    class Field {
    private:
        int height_;
        int width_;

        std::map<std::pair<long long, long long>, Ship> ships_;
    public:
        Field(int height = 0, int width = 0);
        ~Field() = default;

        int GetCountOfAliveShips() const { return ships_.size(); }

        bool AddShip(long long x, long long y, int size, char orientation);
        int Shot(long long x, long long y); // 0 - missed, 1 - hit, 2 - killed
    };
}