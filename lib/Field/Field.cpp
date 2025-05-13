#include "Field.hpp"

namespace BattleShipGame {
    Field::Field(int height, int width)
            : height_(height)
            , width_(width) {}

    bool Field::AddShip(long long x, long long y, int size, char orientation) {
        if (0 <= x && x + size - 1 < width_ && 0 <= y && y + size - 1 < height_) {
            ships_[{x, y}] = Ship(x, y, size, orientation);
            return true;
        }

        return false;
    }

    int Field::Shot(long long x, long long y) {
            for (int i = x - 3; i <= x; i++) {
                if (ships_.find({i, y}) != ships_.end()) {
                    int res = ships_[{i, y}].Shot(x, y);
                    if (res == 1) {
                        return res;
                    } else if (res == 2) {
                        ships_.erase({i, y});
                        return res;
                    }
                }
            }

            for (int i = y - 3; i <= y; i++) {
                if (ships_.find({x, i}) != ships_.end()) {
                    int res = ships_[{x, i}].Shot(x, y);
                    if (res == 1) {
                        return res;
                    } else if (res == 2) {
                        ships_.erase({x, i});
                        return res;
                    }
                }
            }

            return 0;
        }
}