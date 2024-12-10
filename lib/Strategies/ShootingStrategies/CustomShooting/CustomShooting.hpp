#pragma once

#include <string>
#include <vector>

#include <FileManager.hpp>
#include <GameSettings.hpp>
#include <ShootingStrategies.hpp>

namespace BattleShipGame {
class CustomShooting : public ShootingStrategy {
   private:
    int currentIndex_ = 0;
    std::vector<std::pair<int64_t, int64_t>> template_ = {};
    int64_t templateWidth_ = 0;
    int64_t templateHeight_ = 0;

    std::vector<std::pair<int64_t, int64_t>> baseTemplate_ = {
        {1, 0}, {2, 0}, {0, 1}, {0, 2}, {0, 3},  {1, 4}, {2, 4},

        {5, 1}, {5, 2}, {5, 3}, {4, 2}, {6, 2},

        {9, 1}, {9, 2}, {9, 3}, {8, 2}, {10, 2},
    };
    int64_t baseTemplateWidth_ = 11;
    int64_t baseTemplateHeight_ = 5;

    int64_t currentX_ = 0;
    int64_t currentY_ = 0;

    int64_t temaplateSpace_ = 2;

   public:
    bool StrategyIsPossible() const override;

    std::unique_ptr<ShootingStrategy> Clone() const override;

   private:
    std::pair<int64_t, int64_t> CreateShot() override;
    void ApplyArguments() override;
    Response ClearImpl() override;
};
}  // namespace BattleShipGame