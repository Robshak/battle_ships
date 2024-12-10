#pragma once

#include <Field.hpp>
#include <GameSettings.hpp>
#include <Response.hpp>

namespace BattleShipGame {
class ShipPlacementStrategies {
   private:
    static Response StrategyGreedyRandom(Field& field,
                                         GameSettings& gameSettings);

   public:
    static Response ApplyStrategy(Field& field, GameSettings& gameSettings,
                                  std::string strategy);
};
}  // namespace BattleShipGame