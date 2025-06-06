#include "Field.hpp"

namespace BattleShipGame {
Field::Field(int height, int width) : height_(height), width_(width) {}

int Field::GetHeight() const { return height_; }
int Field::GetWidth() const { return width_; }
bool Field::IsLoaded() const { return isLoaded_; }
int Field::GetCountOfAliveShips() const { return ships_.size(); }
std::vector<Ship> Field::GetShips() const {
    std::vector<Ship> res;

    for (auto ship : ships_) {
        res.push_back(ship.second);
    }

    return res;
}

void Field::SetLoaded(bool isLoaded) { isLoaded_ = isLoaded; }
void Field::SetWidth(int width) { width_ = width; }
void Field::SetHeight(int height) { height_ = height; }
void Field::SetSize(int width, int height) {
    width_ = width;
    height_ = height;
}

Response Field::AddShip(int64_t x, int64_t y, int size, char orientation) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        std::string errorString = "Invalid coordinates\n";
        errorString += "Size of field: " + std::to_string(width_) + "x" +
                       std::to_string(height_) + "\n";
        errorString += "Coordinates of ship: (" + std::to_string(x) + ", " +
                       std::to_string(y) + ")\n";

        return Response(401, errorString);
    }

    if (orientation == 'h') {
        if (0 <= x && x + size - 1 < width_) {
            Response isAvailable;
            for (int i = x; i < x + size; i++) {
                isAvailable = isAvailableCell(i, y, x, y);
                if (!isAvailable.IsOk()) {
                    return isAvailable;
                }
            }

            ships_[{x, y}] = Ship(x, y, size, orientation);
            return Response(200, "ok");
        }
    } else {
        if (0 <= y && y + size - 1 < height_) {
            Response isAvailable;
            for (int i = y; i < y + size; i++) {
                isAvailable = isAvailableCell(x, i, x, y);
                if (!isAvailable.IsOk()) {
                    return isAvailable;
                }
            }

            ships_[{x, y}] = Ship(x, y, size, orientation);
            return Response(200, "ok");
        }
    }

    std::string errorString = "";
    errorString += "The ship cannot fit in the field due to its size. ";
    errorString += "Try changing its position or size.\n";
    errorString += "Coordinates of ship: (" + std::to_string(x) + ", " +
                   std::to_string(y) + ")";
    return Response(400, errorString);
}

bool Field::CheckCell(int64_t x, int64_t y) const {
    return FindShip(x, y).first != -1;
}

Response Field::AddShip(Ship ship) {
    int64_t x = ship.GetX();
    int64_t y = ship.GetY();
    int size = ship.GetSize();
    char orientation = ship.GetDirection();

    return AddShip(x, y, size, orientation);
}

Response Field::Shot(int64_t x, int64_t y) {
    std::pair<int64_t, int64_t> shipCoord = FindShip(x, y);
    if (shipCoord.first == -1) {
        return Response(200, "miss");
    }

    Response res = ships_[shipCoord].Shot(x, y);

    if (!ships_[shipCoord].IsAlive()) {
        ships_.erase(shipCoord);
    }

    return res;
}

std::pair<int64_t, int64_t> Field::FindShip(int64_t x, int64_t y) const {
    for (int i = x - 3; i <= x; i++) {
        if (ships_.find({i, y}) != ships_.end()) {
            Ship ship = ships_.at({i, y});
            if (ship.GetX() <= x && x <= ship.GetX() + ship.GetSize() - 1 &&
                ship.GetDirection() == 'h') {
                return {i, y};
            }
        }
    }

    for (int i = y - 3; i <= y; i++) {
        if (ships_.find({x, i}) != ships_.end()) {
            Ship ship = ships_.at({x, i});
            if (ship.GetY() <= y && y <= ship.GetY() + ship.GetSize() - 1 &&
                ship.GetDirection() == 'v') {
                return {x, i};
            }
        }
    }

    return {-1, -1};
}

Response Field::isAvailableCell(int64_t x, int64_t y, int64_t xShip,
                                int64_t yShip) const {
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (FindShip(i, j).first != -1) {
                std::string errorString = "";
                errorString +=
                    "The ship cannot be placed because it overlaps with "
                    "another ship. ";
                errorString += "Please adjust its position\n";
                errorString += "Coordinates of ship: (" +
                               std::to_string(xShip) + ", " +
                               std::to_string(yShip) + ")";
                return Response(400, errorString);
            }
        }
    }

    return Response(200, "ok");
}

void Field::Clear() {
    isLoaded_ = false;
    height_ = 0;
    width_ = 0;
    ships_.clear();
}

void Field::DeleteShips() { ships_.clear(); }
}  // namespace BattleShipGame