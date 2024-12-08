#pragma once

#include <random>

#include <Response.hpp>

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

        long long GetX() const;
        long long GetY() const;
        int GetSize() const;
        bool IsAlive() const;
        char GetDirection() const;

        Response Shot(long long x, long long y);
    };
}