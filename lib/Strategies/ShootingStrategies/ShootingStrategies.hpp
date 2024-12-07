#pragma once

#include <utility>
#include <memory>

#include <GameSettings.hpp>

#include <Response.hpp>

namespace BattleShipGame {
    class ShootingStrategy {
    protected:
        GameSettings gameSettings_;
        bool isWaitResult_;
        int result_; // 0 - miss, 1 - hit, 2 - kill
    public:
        virtual ~ShootingStrategy() = default;
        virtual void InitSettings(GameSettings settings) = 0;
        virtual Response SetResult(std::string result) = 0;
        virtual Response Shot() = 0;

        virtual std::unique_ptr<ShootingStrategy> Clone() const = 0;
    };
}