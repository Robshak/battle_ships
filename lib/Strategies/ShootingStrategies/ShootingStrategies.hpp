#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <GameSettings.hpp>
#include <Response.hpp>

namespace BattleShipGame {
class ShootingStrategy {
   protected:
    GameSettings gameSettings_;
    std::vector<std::string> args_;
    int countOfKills_ = 0;
    bool isWaitResult_ = false;
    int result_ = 0;  // 0 - miss, 1 - hit, 2 - kill

    std::vector<std::vector<bool>> shots_;

   public:
    virtual ~ShootingStrategy() = default;

    int GetCountOfKills() const;
    std::vector<std::vector<bool>>& GetShots();
    void InitSettings(GameSettings settings);
    void SetArguments(std::vector<std::string> args);
    Response SetResult(std::string result);

    Response Shot();

    virtual bool StrategyIsPossible() const = 0;
    Response Clear();
    virtual std::unique_ptr<ShootingStrategy> Clone() const = 0;

   private:
    virtual std::pair<int64_t, int64_t> CreateShot() = 0;
    virtual void ApplyArguments() = 0;

    virtual Response ClearImpl() = 0;
};
}  // namespace BattleShipGame