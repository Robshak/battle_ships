#pragma once

#include <string>
#include <fstream>

#include <Field.hpp>
#include <Ship.hpp>
#include <GameSettings.hpp>
#include <ShootingStrategies.hpp>

#include <Response.hpp>

namespace BattleShipGame {
    class FileManager {
    public:
        static Response WriteField(const Field& field, const std::string& path);
        static Response ReadField(Field& field, const std::string& path,
                                  GameSettings& gameSettings);

        static Response WriteShipMatrix(const Field& field, const std::string& path);
        static Response WriteShotMatrix(ShootingStrategy& strategy, const std::string& path);
    };
}