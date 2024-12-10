#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include <Handler.hpp>
#include <Field.hpp>
#include <FileManager.hpp>

#include <GameSettings.hpp>

#include <ShipPlacementStrategies.hpp>
#include <ShootingStrategies.hpp>
#include <OrderedShooting.hpp>
#include <CustomShooting.hpp>

#include <Response.hpp>

namespace BattleShipGame {
    class Manager {
    private:
        struct GameState {
            bool isGameStarted = false;
            bool isGameFinished = false;
            bool isLose = false;
        };
        std::unordered_map<std::string, std::unique_ptr<ShootingStrategy>> shootingStrategies_;

        std::unique_ptr<ShootingStrategy> shootingStrategy_ = nullptr;
        GameSettings gameSettings_;
        GameState gameState_;
        Handler handler_;
        Field field_;

        bool isAlive = true;
    public:
        Manager();
        ~Manager() = default;

        bool Run();
        Response KillManager();

        Response IsGameStarted() const;
        Response IsGameFinished() const;
        Response IsWin() const;
        Response IsLose() const;

        Response Ping() const;

        Response SetWidth(int width);
        Response SetHeight(int height);
        Response SetCountOfShips(int size, int count);

        Response SetRole(std::string role);
        Response SetShootingStrategy(std::string strategy);

        Response GetWidth() const;
        Response GetHeight() const;
        Response GetCountOfShips(int size) const;

        Response Shot();
        Response Shot(int64_t x, int64_t y);
        Response SetResult(std::string result);

        Response WriteField(const std::string path) const;
        Response ReadField(const std::string path);
        Response ShipsToMatrix(const std::string path) const;
        Response ShotsToMatrix(const std::string path) const;

        Response StartGame();
        Response StopGame();
        Response FinishGame(bool isWin);
    private:
        int GetCountOfShips() const;
    };
}