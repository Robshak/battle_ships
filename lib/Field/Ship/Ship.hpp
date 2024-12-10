#pragma once

#include <random>

#include <Response.hpp>

namespace BattleShipGame {
class Ship {
   private:
    int64_t x_;
    int64_t y_;
    int size_;
    bool isHorizontal_;

    char cellsState_;
    bool isAlive_;

   public:
    Ship();
    Ship(int64_t x, int64_t y, int size, char orientation);
    ~Ship() = default;

    int64_t GetX() const;
    int64_t GetY() const;
    int GetSize() const;
    bool IsAlive() const;
    char GetDirection() const;

    Response Shot(int64_t x, int64_t y);
};
}  // namespace BattleShipGame