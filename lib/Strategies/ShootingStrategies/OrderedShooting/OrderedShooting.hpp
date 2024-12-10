#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <GameSettings.hpp>
#include <ShootingStrategies.hpp>

namespace BattleShipGame {
class OrderedShooting : public ShootingStrategy {
   private:
    int currentIndex_ = 0;

   public:
    bool StrategyIsPossible() const override;
    Response Clear() override;

    std::unique_ptr<ShootingStrategy> Clone() const override;

   private:
    std::pair<long long, long long> CreateShot() override;
    void ApplyArguments() override;
};
}  // namespace BattleShipGame