#pragma once
#include <random>

namespace BattleShipGame {
    class Ship {
    private:
        long long x_;
        long long y_;
        int size_;
        bool isHorizontal_;

        char cellsState_;
        bool isAlive_;
    public:
        Ship();
        Ship(long long x, long long y, int size, char orientation);
        ~Ship() = default;

        long long GetX() const { return x_; };
        long long GetY() const { return y_; };
        int GetSize() const { return size_; };
        bool IsAlive() const { return isAlive_; };
        bool IsHorizontal() const { return isHorizontal_; };

        int Shot(long long x, long long y); // 0 - missed, 1 - hit, 2 - killed
    };
}