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
    if (!isAlive) {
        return false;
    }
    handler_.Run(*this);

    return true;
}

Response Manager::KillManager() {
    isAlive = false;
    return Response(200, "ok");
}

int Manager::GetCountOfShips() const {
    int res = 0;

    for (int i = 0; i < 4; i++) {
        res += gameSettings_.countOfShips[i];
    }

    return res;
}

Response Manager::IsGameStarted() const {
    return Response(200, gameState_.isGameStarted ? "yes" : "no");
}

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

Response Manager::Ping() const { return Response(200, "pong"); }

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
        return Response(400, "Invalid size or count: " + std::to_string(size) +
                                 " " + std::to_string(count));
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

        gameSettings_.width = 15;
        gameSettings_.height = 15;
        gameSettings_.countOfShips[0] = 4;
        gameSettings_.countOfShips[1] = 3;
        gameSettings_.countOfShips[2] = 2;
        gameSettings_.countOfShips[3] = 1;

        return Response(200, "ok");
    }
    if (role == "slave") {
        gameSettings_.role = GameSettings::Role::Slave;
        return Response(200, "ok");
    }

    return Response(400, "Unknown role: " + role);
}

Response Manager::SetShootingStrategy(std::string strategy,
                                      std::vector<std::string> args) {
    if (gameState_.isGameStarted) {
        return Response(400, "Game is already started");
    }
    if (shootingStrategies_.find(strategy) == shootingStrategies_.end()) {
        return Response(400, "Unknown strategy: " + strategy);
    }

    shootingStrategy_ = shootingStrategies_[strategy]->Clone();
    shootingStrategy_->SetArguments(args);

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
    if (!gameState_.isGameStarted) {
        return Response(400, "Game is not started");
    }
    if (gameState_.isGameFinished) {
        return Response(400, "Game is finished");
    }

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

Response Manager::ShipsToMatrix(const std::string path) const {
    return FileManager::WriteShipMatrix(field_, path);
}

Response Manager::ShotsToMatrix(const std::string path) const {
    if (shootingStrategy_ == nullptr) {
        return Response(400, "No shots yet");
    }
    return FileManager::WriteShotMatrix(*shootingStrategy_, path);
}

Response Manager::StartGame() {
    if (gameState_.isGameStarted) {
        return Response(400, "Game is already started");
    }
    if (gameSettings_.role == GameSettings::Role::Unknown) {
        return Response(400, "Role is not set");
    }
    if (GetCountOfShips() == 0) {
        return Response(400, "Field is empty");
    }

    if (!shootingStrategy_) {
        SetShootingStrategy("custom", {});
    }
    shootingStrategy_->InitSettings(gameSettings_);
    if (!shootingStrategy_->StrategyIsPossible()) {
        shootingStrategy_ = shootingStrategies_["ordered"]->Clone();
        shootingStrategy_->InitSettings(gameSettings_);
    }

    if (field_.IsLoaded()) {
        gameState_.isGameStarted = true;
        return Response(200, "ok");
    }

    field_.SetSize(gameSettings_.width, gameSettings_.height);
    Response res = ShipPlacementStrategies::ApplyStrategy(field_, gameSettings_,
                                                          "greedy_random");
    if (res.IsOk()) {
        gameState_.isGameStarted = true;
    }
    return res;
}

Response Manager::StopGame() {
    if (!gameState_.isGameStarted) {
        return Response(400, "Game is not started");
    }

    field_.DeleteShips();
    shootingStrategy_->Clear();
    gameState_.isGameStarted = false;

    return Response(200, "ok");
}

Response Manager::FinishGame(bool isWin) {
    gameState_.isGameFinished = true;
    gameState_.isLose = !isWin;

    return Response(200, "ok");
}

Response Manager::TestShot(int64_t count) {
    if (!gameState_.isGameStarted) {
        return Response(400, "Game is not started");
    }

    for (int i = 0; i < count; i++) {
        Shot();
        SetResult("miss");
    }

    return Response(200, "ok");
}
}  // namespace BattleShipGame