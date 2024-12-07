#pragma once

#include <string>
#include <fstream>

#include <Field.hpp>
#include <Ship.hpp>

#include <Response.hpp>

namespace BattleShipGame {
    class FileManager {
    public:
        static Response WriteField(const Field& field, const std::string& path);
        static Response ReadField(Field& field, const std::string& path);

        static Response WriteFieldMatrix(const Field& field, const std::string& path);
    };
}