#pragma once

#include <vector>
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

        std::vector<std::vector<bool>> shots_;
    public:
        virtual ~ShootingStrategy() = default;

        int GetCountOfKills() const;
        std::vector<std::vector<bool>>& GetShots();
        void InitSettings(GameSettings settings);
        Response SetResult(std::string result);

        Response Shot();

        virtual Response Clear() = 0;
        virtual std::unique_ptr<ShootingStrategy> Clone() const = 0;
    private:
        virtual std::pair<long long, long long> CreateShot() = 0;
    };
}