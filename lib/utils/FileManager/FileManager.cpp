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

Response FileManager::WriteShipMatrix(const Field& field,
                                      const std::string& path) {
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

Response FileManager::WriteShotMatrix(ShootingStrategy& strategy,
                                      const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        return Response(500, "Can't open file for writing: " + path);
    }

    if (strategy.GetShots().size() == 0) {
        file.close();
        return Response(200, "ok");
    }

    for (int j = 0; j < strategy.GetShots()[0].size(); j++) {
        for (int i = 0; i < strategy.GetShots().size(); i++) {
            if (strategy.GetShots()[i][j]) {
                file << 'X' << ' ';
            } else {
                file << '.' << ' ';
            }
        }
        file << '\n';
    }

    file.close();

    return Response(200, "ok");
}

Response FileManager::ReadShotMatrix(
    std::vector<std::pair<int64_t, int64_t>>& coords, const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return Response(500, "Can't open file for writing: " + path);
    }

    std::vector<std::string> shots;
    std::string buffer;
    while (std::getline(file, buffer)) {
        shots.push_back(buffer);
    }

    for (int64_t j = 0; j < shots.size(); j++) {
        for (int64_t i = 0; i < shots[j].size(); i += 2) {
            if (shots[j][i] == 'X') {
                coords.push_back({i / 2, j});
            }
        }
    }

    file.close();

    return Response(200, "ok");
}
}  // namespace BattleShipGame