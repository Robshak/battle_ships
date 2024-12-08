#include "CustomShooting.hpp"

namespace BattleShipGame {
    Response CustomShooting::Shot() {
        if (isWaitResult_) {
            return Response(400, "Result not set");
        }

        long long x = currentIndex_ % gameSettings_.width;
        long long y = currentIndex_ / gameSettings_.width;

        currentIndex_++;
        isWaitResult_ = true;

        return Response(200, std::to_string(x) + " " + std::to_string(y));
    }

    Response CustomShooting::Clear() {
        currentIndex_ = 0;
        isWaitResult_ = false;
        return Response(200, "ok");
    }

    std::unique_ptr<ShootingStrategy> CustomShooting::Clone() const {
        return std::make_unique<CustomShooting>(*this);
    }
}