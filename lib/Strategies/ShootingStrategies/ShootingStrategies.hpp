#pragma once

#include <utility>
#include <memory>

#include <GameSettings.hpp>

#include <Response.hpp>

namespace BattleShipGame {
    class ShootingStrategy {
    protected:
        GameSettings gameSettings_;
        int countOfKills_ = 0;
        bool isWaitResult_ = false;
        int result_ = 0; // 0 - miss, 1 - hit, 2 - kill
    public:
        virtual ~ShootingStrategy() = default;

        int GetCountOfKills() const;
        void InitSettings(GameSettings settings);
        Response SetResult(std::string result);

        virtual Response Shot() = 0;
        virtual Response Clear() = 0;

        virtual std::unique_ptr<ShootingStrategy> Clone() const = 0;
    };
}