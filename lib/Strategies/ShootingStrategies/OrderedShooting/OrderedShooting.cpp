#include "OrderedShooting.hpp"

namespace BattleShipGame {
std::pair<int64_t, int64_t> OrderedShooting::CreateShot() {
    int64_t x = currentIndex_ % gameSettings_.width;
    int64_t y = currentIndex_ / gameSettings_.width;

    currentIndex_++;
    isWaitResult_ = true;

    return std::make_pair(x, y);
}

void OrderedShooting::ApplyArguments() { return; }

bool OrderedShooting::StrategyIsPossible() const { return true; }

Response OrderedShooting::ClearImpl() {
    currentIndex_ = 0;
    isWaitResult_ = false;
    return Response(200, "ok");
}

std::unique_ptr<ShootingStrategy> OrderedShooting::Clone() const {
    return std::make_unique<OrderedShooting>(*this);
}
}  // namespace BattleShipGame