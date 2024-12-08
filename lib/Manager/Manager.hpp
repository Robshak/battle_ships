#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include <Handler.hpp>
#include <Field.hpp>
#include <FileManager.hpp>

#include <GameSettings.hpp>

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
    public:
        Manager();
        ~Manager() = default;

        bool Run();

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
        Response Shot(long long x, long long y);
        Response SetResult(std::string result);

        Response WriteField(const std::string path) const;
        Response ReadField(const std::string path);
        Response FieldToMatrix(const std::string path) const;

        Response StartGame();
        Response StopGame();
        Response FinishGame(bool isWin);
    private:
        int GetCountOfShips() const;
    };
}