#include "OrderedShooting.hpp"

namespace BattleShipGame {
    void OrderedShooting::InitSettings(GameSettings settings) {
        gameSettings_ = settings;
        currentIndex_ = 0;
    }

    Response OrderedShooting::SetResult(std::string result) {
        if (!isWaitResult_) {
            return Response(400, "Result already set");
        }

        if (result == "miss") {
            result_ = 0;
            return Response(200, "ok");
        } else if (result == "hit") {
            result_ = 1;
            return Response(200, "ok");
        } else if (result == "kill") {
            result_ = 2;
            return Response(200, "ok");
        }

        return Response(400, "Unknown result");
    }

    Response OrderedShooting::Shot() {
        if (isWaitResult_) {
            return Response(400, "Result not set");
        }

        long long x = currentIndex_ % gameSettings_.width;
        long long y = currentIndex_ / gameSettings_.width;

        currentIndex_++;
        isWaitResult_ = true;

        return Response(200, std::to_string(x) + " " + std::to_string(y));
    }

    std::unique_ptr<ShootingStrategy> OrderedShooting::Clone() const {
        return std::make_unique<OrderedShooting>(*this);
    }
}