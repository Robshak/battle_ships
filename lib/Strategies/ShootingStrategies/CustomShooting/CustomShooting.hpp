#pragma once

#include <string>

#include <ShootingStrategies.hpp>
#include <GameSettings.hpp>

namespace BattleShipGame {
    class CustomShooting : public ShootingStrategy {
    private:
        int currentIndex_ = 0;
    public:
        void InitSettings(GameSettings settings) override;
        Response SetResult(std::string result) override;
        Response Shot() override;

        std::unique_ptr<ShootingStrategy> Clone() const override;
    };
}