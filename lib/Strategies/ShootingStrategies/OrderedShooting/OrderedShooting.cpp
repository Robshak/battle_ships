#include "OrderedShooting.hpp"

namespace BattleShipGame {
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

    Response OrderedShooting::Clear() {
        currentIndex_ = 0;
        isWaitResult_ = false;
        return Response(200, "ok");
    }

    std::unique_ptr<ShootingStrategy> OrderedShooting::Clone() const {
        return std::make_unique<OrderedShooting>(*this);
    }
}