#pragma once

#include <string>
#include <memory>
#include <iostream>

#include <ShootingStrategies.hpp>
#include <GameSettings.hpp>

namespace BattleShipGame {
    class OrderedShooting : public ShootingStrategy {
    private:
        int currentIndex_ = 0;
    public:
        std::pair<long long, long long> CreateShot() override;
        Response Clear() override;

        std::unique_ptr<ShootingStrategy> Clone() const override;
    };
}