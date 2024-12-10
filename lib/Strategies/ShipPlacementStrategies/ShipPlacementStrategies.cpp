#include "ShipPlacementStrategies.hpp"

namespace BattleShipGame {
Response ShipPlacementStrategies::StrategyGreedyRandom(
    Field& field, GameSettings& gameSettings) {
    int currentSize = 0;
    int countOfPostedShips = 0;
    int countOfFail = 0;

    const int maximumCountOfFail = 100000;

    while (countOfFail < maximumCountOfFail) {
        if (countOfPostedShips >= gameSettings.countOfShips[currentSize]) {
            currentSize++;
            countOfPostedShips = 0;

            if (currentSize == 4) {
                return Response(200, "ok");
            }
            continue;
        }

        int orientation = rand() % 2;
        int x = rand() % gameSettings.width;
        int y = rand() % gameSettings.height;
        int size = currentSize + 1;
        Ship ship;

        if (orientation == 0) {
            ship = Ship(x, y, size, 'h');
        } else {
            ship = Ship(x, y, size, 'v');
        }

        Response checkAddition = field.AddShip(ship);
        if (checkAddition.IsOk()) {
            countOfPostedShips++;
        } else {
            countOfFail++;
        }
    }

    return Response(500, "Sorry, I can't place all ships");
}

Response ShipPlacementStrategies::ApplyStrategy(Field& field,
                                                GameSettings& gameSettings,
                                                std::string strategy) {
    if (strategy == "greedy_random") {
        return StrategyGreedyRandom(field, gameSettings);
    } else {
        return Response(400, "Unknown strategy: " + strategy);
    }
}
}  // namespace BattleShipGame