#include "Ship.hpp"

namespace BattleShipGame {
Ship::Ship() {
    x_ = rand();
    y_ = rand();
    size_ = rand() % 4 + 1;
    cellsState_ = 0;

    int orientation = rand() % 2;
    if (orientation == 0) {
        isHorizontal_ = true;
    } else {
        isHorizontal_ = false;
    }

    for (int i = 0; i < size_; i++) {
        cellsState_ += (1 << i);
    }

    isAlive_ = true;
};

Ship::Ship(int64_t x, int64_t y, int size, char orientation)
    : x_(x), y_(y), size_(size), isAlive_(true) {
    if (orientation == 'h') {
        isHorizontal_ = true;
    } else {
        isHorizontal_ = false;
    }
    cellsState_ = 0;

    for (int i = 0; i < size; i++) {
        cellsState_ += (1 << i);
    }
}

int64_t Ship::GetX() const { return x_; };
int64_t Ship::GetY() const { return y_; };
int Ship::GetSize() const { return size_; };
bool Ship::IsAlive() const { return isAlive_; };
char Ship::GetDirection() const { return isHorizontal_ ? 'h' : 'v'; };

Response Ship::Shot(int64_t x, int64_t y) {
    if (x == x_ && !isHorizontal_) {
        int index = y - y_;

        if (index < 0 || index >= size_) {
            return Response(200, "miss");
        }

        if ((cellsState_ & (1 << index)) != 0) {
            cellsState_ &= ~(1 << index);
            if (cellsState_ == 0) {
                isAlive_ = false;
                return Response(200, "kill");
            }

            return Response(200, "hit");
        }
    } else if (y == y_ && isHorizontal_) {
        int index = x - x_;

        if (index < 0 || index >= size_) {
            return Response(200, "miss");
        }

        if ((cellsState_ & (1 << index)) != 0) {
            cellsState_ &= ~(1 << index);
            if (cellsState_ == 0) {
                isAlive_ = false;
                return Response(200, "kill");
            }

            return Response(200, "hit");
        }
    }

    return Response(200, "miss");
}
}  // namespace BattleShipGame