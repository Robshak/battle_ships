#include "OrderedShooting.hpp"

namespace BattleShipGame {
    std::pair<long long, long long> OrderedShooting::CreateShot() {
        long long x = currentIndex_ % gameSettings_.width;
        long long y = currentIndex_ / gameSettings_.width;

        currentIndex_++;
        isWaitResult_ = true;

        return std::make_pair(x, y);
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