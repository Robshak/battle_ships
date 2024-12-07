#include "FileManager.hpp"

namespace BattleShipGame {
    Response FileManager::WriteField(const Field& field, const std::string& path) {
        Response res;

        std::ofstream file(path);
        if (!file.is_open()) {
            res.SetCode(500);
            res.SetError("Can't open file for writing: " + path);
            return res;
        }

        file << field.GetWidth() << " " << field.GetHeight() << "\n";

        std::vector<Ship> ships = field.GetShips();
        for (const Ship& ship : ships) {
            file << ship.GetSize() << " " << ship.GetDirection() << " "
                << ship.GetX() << " " << ship.GetY() << "\n";
        }

        file.close();

        res.SetCode(200);
        return res;
    }

    Response FileManager::ReadField(Field& field, const std::string& path) {
        Response res;

        std::ifstream file(path);
        if (!file.is_open()) {
            res.SetCode(500);
            res.SetError("Can't open file for reading: " + path);
            return res;
        }

        int width, height;
        file >> width >> height;
        field.Clear();
        field.SetSize(height, width);

        int x, y, size;
        char direction;
        while (file >> size >> direction >> x >> y) {
            Ship ship = Ship(x, y, size, direction);
            Response checkAddition = field.AddShip(ship);
            if (!checkAddition.IsOk()) {
                return checkAddition;
            }
        }

        file.close();

        res.SetCode(200);
        return res;
    }

    Response FileManager::WriteFieldMatrix(const Field& field, const std::string& path) {
        Response res;

        std::ofstream file(path);
        if (!file.is_open()) {
            res.SetCode(500);
            res.SetError("Can't open file for writing: " + path);
            return res;
        }

        for (int j = 0; j < field.GetHeight(); j++) {
            for (int i = 0; i < field.GetWidth(); i++) {
                file << (field.CheckCell(i, j) ? 'X' : '.') << ' ';
            }
            file << '\n';
        }

        file.close();

        res.SetCode(200);
        return res;
    }
}