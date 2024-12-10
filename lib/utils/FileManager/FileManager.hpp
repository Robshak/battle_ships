#pragma once

#include <fstream>
#include <string>

#include <Field.hpp>
#include <Ship.hpp>

#include <GameSettings.hpp>
#include <Response.hpp>
#include <ShootingStrategies.hpp>

#include <WorkWithString.hpp>

namespace BattleShipGame {
class FileManager {
   public:
    static Response WriteField(const Field& field, const std::string& path);
    static Response ReadField(Field& field, const std::string& path,
                              GameSettings& gameSettings);

    static Response WriteShipMatrix(const Field& field,
                                    const std::string& path);
    static Response WriteShotMatrix(ShootingStrategy& strategy,
                                    const std::string& path);

    static Response ReadShotMatrix(
        std::vector<std::pair<int64_t, int64_t>>& coords,
        const std::string& path);
};
}  // namespace BattleShipGame