#include "ShootingStrategies.hpp"

namespace BattleShipGame {
int ShootingStrategy::GetCountOfKills() const { return countOfKills_; }
std::vector<std::vector<bool>>& ShootingStrategy::GetShots() { return shots_; }

void ShootingStrategy::InitSettings(GameSettings settings) {
    gameSettings_ = settings;
    ApplyArguments();

    shots_.resize(gameSettings_.height,
                  std::vector<bool>(gameSettings_.width, false));
}

void ShootingStrategy::SetArguments(std::vector<std::string> args) {
    args_ = args;
}

Response ShootingStrategy::SetResult(std::string result) {
    if (!isWaitResult_) {
        return Response(400, "Result already set");
    }

    Response res;

    if (result == "miss") {
        result_ = 0;
        res = Response(200, "ok");
    } else if (result == "hit") {
        result_ = 1;
        res = Response(200, "ok");
    } else if (result == "kill") {
        result_ = 2;
        countOfKills_++;
        res = Response(200, "ok");
    } else {
        res = Response(400, "Unknown result");
    }

    if (res.IsOk()) {
        isWaitResult_ = false;
    }

    return res;
}

Response ShootingStrategy::Shot() {
    if (isWaitResult_) {
        return Response(400, "Result not set");
    }

    std::pair<int64_t, int64_t> shot = CreateShot();
    int64_t x = shot.first;
    int64_t y = shot.second;

    shots_[x][y] = true;

    isWaitResult_ = true;

    return Response(200, std::to_string(x) + " " + std::to_string(y));
}

Response ShootingStrategy::Clear() {
    result_ = 0;
    countOfKills_ = 0;
    isWaitResult_ = false;
    shots_.clear();
    return ClearImpl();
}
}  // namespace BattleShipGame