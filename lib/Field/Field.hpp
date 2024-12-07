#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <Ship.hpp>

#include <Response.hpp>

namespace BattleShipGame {
    class Field {
    private:
        bool isLoaded_ = false;

        int height_;
        int width_;

        std::map<std::pair<long long, long long>, Ship> ships_;
    public:
        Field(int height = 0, int width = 0);
        ~Field() = default;

        int GetHeight() const;
        int GetWidth() const;
        bool IsLoaded() const;
        int GetCountOfAliveShips() const;
        std::vector<Ship> GetShips() const;

        void SetHeight(int height);
        void SetWidth(int width);
        void SetSize(int height, int width);

        Response AddShip(long long x, long long y, int size, char orientation);
        Response AddShip(Ship ship);
        
        Response Shot(long long x, long long y);

        bool CheckCell(long long x, long long y) const;

        void Clear();
    private:
        // (-1, -1) - no ship, (x, y) - ship
        std::pair<long long, long long> FindShip(long long x, long long y) const;
        Response isAvailableCell(long long x, long long y,
                                 long long xShip, long long yShip) const;
    };
}