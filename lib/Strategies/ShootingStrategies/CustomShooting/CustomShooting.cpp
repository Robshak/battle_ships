#include "CustomShooting.hpp"

namespace BattleShipGame {
    std::pair<long long, long long> CustomShooting::CreateShot() {
        long long x = template_[currentIndex_].first + currentX_;
        long long y = template_[currentIndex_].second + currentY_;

        long long lastX = currentX_ + templateWidth_ - 1;

        currentIndex_++;
        if (currentIndex_ == template_.size()) {
            currentIndex_ = 0;
            if (lastX + temaplateSpace_ + templateWidth_ < gameSettings_.width) {
                currentX_ += temaplateSpace_ + templateWidth_;
            } else {
                currentX_ = 0;
                currentY_ += temaplateSpace_ + templateHeight_;
                if (currentY_ + templateHeight_ > gameSettings_.height) {
                    currentY_ = 0;
                }
            }
        }

        return std::make_pair(x, y);
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