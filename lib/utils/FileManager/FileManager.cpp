#include "FileManager.hpp"

namespace BattleShipGame {
    Response FileManager::WriteField(const Field& field, const std::string& path) {
        std::ofstream file(path);
        if (!file.is_open()) {
            return Response(500, "Can't open file for writing: " + path);
        }

        file << field.GetWidth() << " " << field.GetHeight() << "\n";

        std::vector<Ship> ships = field.GetShips();
        for (const Ship& ship : ships) {
            file << ship.GetSize() << " " << ship.GetDirection() << " "
                << ship.GetX() << " " << ship.GetY() << "\n";
        }

        file.close();

        return Response(200, "ok");
    }

    Response FileManager::ReadField(Field& field, const std::string& path,
                                    GameSettings& gameSettings) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return Response(500, "Can't open file for reading: " + path);
        }

        int width, height;
        file >> width >> height;
        field.Clear();
        field.SetSize(height, width);
        gameSettings.width = width;
        gameSettings.height = height;

        int x, y, size;
        char direction;
        while (file >> size >> direction >> x >> y) {
            Ship ship = Ship(x, y, size, direction);
            Response checkAddition = field.AddShip(ship);
            if (!checkAddition.IsOk()) {
                return checkAddition;
            }

            gameSettings.countOfShips[size - 1]++;
        }

        field.SetLoaded(true);

        file.close();

        return Response(200, "ok");
    }

    Response FileManager::WriteFieldToMatrix(const Field& field, const std::string& path) {
        std::ofstream file(path);
        if (!file.is_open()) {
            return Response(500, "Can't open file for writing: " + path);
        }

        for (int j = 0; j < field.GetHeight(); j++) {
            for (int i = 0; i < field.GetWidth(); i++) {
                file << (field.CheckCell(i, j) ? 'X' : '.') << ' ';
            }
            file << '\n';
        }

        file.close();

        return Response(200, "ok");
    }
}