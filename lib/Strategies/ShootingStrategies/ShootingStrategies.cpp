#include "ShootingStrategies.hpp"

namespace BattleShipGame {
    int ShootingStrategy::GetCountOfKills() const { return countOfKills_; }

    void ShootingStrategy::InitSettings(GameSettings settings) {
        gameSettings_ = settings;
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
}