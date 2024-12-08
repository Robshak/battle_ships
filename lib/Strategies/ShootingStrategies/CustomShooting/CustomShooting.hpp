#pragma once

#include <string>
#include <vector>

#include <ShootingStrategies.hpp>
#include <GameSettings.hpp>

namespace BattleShipGame {
    class CustomShooting : public ShootingStrategy {
    private:
        int currentIndex_ = 0;
        std::vector<std::pair<long long, long long>> template_ = {
            {1, 0},
            {2, 0},
            {0, 1},
            {0, 2},
            {0, 3},
            {1, 4},
            {2, 4},

            {5, 1},
            {5, 2},
            {5, 3},
            {4, 2},
            {6, 2},

            {9, 1},
            {9, 2},
            {9, 3},
            {8, 2},
            {10, 2},
        };
        long long  currentX_ = 0;
        long long  currentY_ = 0;

        long long templateWidth_ = 11;
        long long templateHeight_ = 5;
        long long temaplateSpace_ = 2;
    public:
        std::pair<long long, long long> CreateShot() override;
        Response Clear() override;

        std::unique_ptr<ShootingStrategy> Clone() const override;
    };
}