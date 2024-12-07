#pragma once

#include <string>
#include <fstream>

#include <Field/Field.hpp>
#include <Field/Ship/Ship.hpp>

#include <Response/Response.hpp>

namespace BattleShipGame {
    class FileManager {
    public:
        static Response WriteField(const Field& field, const std::string& path);
        static Response ReadField(Field& field, const std::string& path);

        static Response WriteFieldMatrix(const Field& field, const std::string& path);
    };
}