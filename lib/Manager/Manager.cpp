#include "Manager.hpp"

namespace BattleShipGame {
    Manager::Manager() {
        shootingStrategies_["ordered"] = std::make_unique<OrderedShooting>();
        shootingStrategies_["custom"] = std::make_unique<CustomShooting>();

        gameSettings_ = GameSettings();
        gameState_ = GameState();
        handler_ = Handler();
        field_ = Field();
    };

    bool Manager::Run() {
        handler_.Run(*this);

        return true;
    }

    int Manager::GetCountOfShips() const {
        int res = 0;

        for (int i = 0; i < 4; i++) {
            res += gameSettings_.countOfShips[i];
        }

        return res;
    }

    Response Manager::IsGameStarted() const { return Response(200, gameState_.isGameStarted ? "yes" : "no"); }

    Response Manager::IsGameFinished() const {
        if (!gameState_.isGameStarted) {
            return Response(400, "Game is not started");
        }

        if (gameState_.isGameFinished) {
            return Response(200, "yes");
        }

        return Response(200, "no");
    }

    Response Manager::IsWin() const {
        if (!gameState_.isGameStarted) {
            return Response(400, "Game is not started");
        }
        if (!gameState_.isGameFinished) {
            return Response(400, "Game is not finished");
        }

        if (gameState_.isLose) {
            return Response(200, "no");
        }

        return Response(200, "yes");
    }

    Response Manager::IsLose() const {
        if (!gameState_.isGameStarted) {
            return Response(400, "Game is not started");
        }
        if (!gameState_.isGameFinished) {
            return Response(400, "Game is not finished");
        }

        if (gameState_.isLose) {
            return Response(200, "yes");
        }

        return Response(200, "no");
    }

    Response Manager::Ping() const {
        return Response(200, "pong");
    }

    Response Manager::SetWidth(int width) {
        if (gameState_.isGameStarted) {
            return Response(400, "Game is already started");
        }

        if (width < 1) {
            return Response(400, "Invalid width: " + std::to_string(width));
        }

        gameSettings_.width = width;

        return Response(200, "ok");
    }

    Response Manager::SetHeight(int height) {
        if (gameState_.isGameStarted) {
            return Response(400, "Game is already started");
        }

        if (height < 1) {
            return Response(400, "Invalid height: " + std::to_string(height));
        }

        gameSettings_.height = height;

        return Response(200, "ok");
    }

    Response Manager::SetCountOfShips(int size, int count) {
        if (gameState_.isGameStarted) {
            return Response(400, "Game is already started");
        }

        if (size < 1 || count < 1) {
            return Response(400, "Invalid size or count: " + std::to_string(size) + " " + std::to_string(count));
        }

        gameSettings_.countOfShips[size - 1] = count;

        return Response(200, "ok");
    }

    Response Manager::SetRole(std::string role) {
        if (gameState_.isGameStarted) {
            return Response(400, "Game is already started");
        }

        if (role == "master") {
            gameSettings_.role = GameSettings::Role::Master;
            return Response(200, "ok");
        }
        if (role == "slave") {
            gameSettings_.role = GameSettings::Role::Slave;
            return Response(200, "ok");
        }
        
        return Response(400, "Unknown role: " + role);
    }

    Response Manager::SetShootingStrategy(std::string strategy) {
        if (gameState_.isGameStarted) {
            return Response(400, "Game is already started");
        }

        if (shootingStrategies_.find(strategy) == shootingStrategies_.end()) {
            return Response(400, "Unknown strategy: " + strategy);
        }

        shootingStrategy_ = shootingStrategies_[strategy]->Clone();
        shootingStrategy_->InitSettings(gameSettings_);

        return Response(200, "ok");
    }

    Response Manager::GetWidth() const {
        return Response(200, std::to_string(gameSettings_.width));
    }

    Response Manager::GetHeight() const {
        return Response(200, std::to_string(gameSettings_.height));
    }

    Response Manager::GetCountOfShips(int size) const {
        return Response(200, std::to_string(gameSettings_.countOfShips[size - 1]));
    }

    Response Manager::Shot() {
        if (!gameState_.isGameStarted) {
            return Response(400, "Game is not started");
        }
        if (gameState_.isGameFinished) {
            return Response(400, "Game is finished");
        }

        Response res = shootingStrategy_->Shot();

        return res;
    }

    Response Manager::Shot(long long x, long long y) {
        if (!gameState_.isGameStarted) {
            return Response(400, "Game is not started");
        }
        if (gameState_.isGameFinished) {
            return Response(400, "Game is finished");
        }

        Response res = field_.Shot(x, y);

        if (field_.GetCountOfAliveShips() == 0) {
            FinishGame(false);
        }

        return res;
    }

    Response Manager::SetResult(std::string result) {
        Response res = shootingStrategy_->SetResult(result);
        
        if (shootingStrategy_->GetCountOfKills() == GetCountOfShips()) {
            FinishGame(true);
        }

        return res;
    }

    Response Manager::WriteField(const std::string path) const {
        return FileManager::WriteField(field_, path);
    }

    Response Manager::ReadField(const std::string path) {
        if (gameState_.isGameStarted) {
            return Response(400, "Game is already started");
        }

        Response res = FileManager::ReadField(field_, path, gameSettings_);

        return res;
    }

    Response Manager::FieldToMatrix(const std::string path) const {
        return FileManager::WriteFieldToMatrix(field_, path);
    }

    Response Manager::StartGame() {
        if (gameState_.isGameStarted) {
            return Response(400, "Game is already started");
        }
        if (field_.GetCountOfAliveShips() == 0) {
            return Response(400, "No ships on the field");
        }
        if (!shootingStrategy_) {
            return Response(400, "No shooting strategy");
        }

        if (gameSettings_.role == GameSettings::Role::Master) {
            // TODO
        }

        gameState_.isGameStarted = true;
        return Response(200, "ok");
    }

    Response Manager::StopGame() {
        if (!gameState_.isGameStarted) {
            return Response(400, "Game is not started");
        }

        gameState_.isGameStarted = false;

        return Response(200, "ok");
    }

    Response Manager::FinishGame(bool isWin) {
        gameState_.isGameFinished = true;
        gameState_.isLose = !isWin;

        return Response(200, "ok");
    }
}