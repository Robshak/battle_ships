#pragma once

#include <map>
#include <vector>

#include <Response.hpp>
#include <Ship.hpp>

namespace BattleShipGame {
class Field {
   private:
    bool isLoaded_ = false;

    int height_;
    int width_;

    std::map<std::pair<int64_t, int64_t>, Ship> ships_;

   public:
    Field(int height = 0, int width = 0);
    ~Field() = default;

    int GetHeight() const;
    int GetWidth() const;
    bool IsLoaded() const;
    int GetCountOfAliveShips() const;
    std::vector<Ship> GetShips() const;

    void SetLoaded(bool isLoaded);
    void SetHeight(int height);
    void SetWidth(int width);
    void SetSize(int height, int width);

    Response AddShip(int64_t x, int64_t y, int size, char orientation);
    Response AddShip(Ship ship);

    Response Shot(int64_t x, int64_t y);

    bool CheckCell(int64_t x, int64_t y) const;

    void Clear();
    void DeleteShips();

   private:
    // (-1, -1) - no ship, (x, y) - ship
    std::pair<int64_t, int64_t> FindShip(int64_t x, int64_t y) const;
    Response isAvailableCell(int64_t x, int64_t y, int64_t xShip,
                             int64_t yShip) const;
};
}  // namespace BattleShipGame