#include "Ship.hpp"

namespace BattleShipGame {
    Ship::Ship() {
        x_ = rand();
        y_ = rand();
        size_ = rand() % 4 + 1;

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
    Ship::Ship(long long x, long long y, int size, char orientation)
        : x_(x)
        , y_(y)
        , size_(size)
        , isAlive_(true) {
            if (orientation == 'h') {
                isHorizontal_ = true;
            } else {
                isHorizontal_ = false;
            }

            for (int i = 0; i < size; i++) {
                cellsState_ += (1 << i);
            }
        }
    
    long long Ship::GetX() const { return x_; };
    long long Ship::GetY() const { return y_; };
    int Ship::GetSize() const { return size_; };
    bool Ship::IsAlive() const { return isAlive_; };
    bool Ship::IsHorizontal() const { return isHorizontal_; };
    char Ship::GetDirection() const { return isHorizontal_ ? 'h' : 'v'; };
    
    int Ship::Shot(long long x, long long y) {
        if (x == x_ && !isHorizontal_) {
            int index = y - y_;

            if (index < 0 || index >= size_) {
                return 0;
            }

            if ((cellsState_ & (1 << index)) != 0) {
                cellsState_ &= ~(1 << index);
                if (cellsState_ == 0) {
                    isAlive_ = false;
                    return 2;
                }

                return 1;
            }
        } else if (y == y_ && isHorizontal_) {
            int index = x - x_;

            if (index < 0 || index >= size_) {
                return 0;
            }

            if ((cellsState_ & (1 << index)) != 0) {
                cellsState_ &= ~(1 << index);
                if (cellsState_ == 0) {
                    isAlive_ = false;
                    return 2;
                }

                return 1;
            }
        }

        return 0;
    }
}