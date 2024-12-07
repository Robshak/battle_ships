#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include <Handler.hpp>
#include <Field.hpp>
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
        Manager() {
            shootingStrategies_["ordered"] = std::make_unique<OrderedShooting>();
            shootingStrategies_["custom"] = std::make_unique<CustomShooting>();

            gameSettings_ = GameSettings();
            gameState_ = GameState();
            handler_ = Handler();
            field_ = Field();
        };
        ~Manager() = default;

        bool Run() {
            handler_.Run(*this);

            return true;
        }

        Field& GetField() { return field_; }
        ShootingStrategy& GetShootingStrategy() { return *shootingStrategy_; }
        Response IsGameStarted() { return Response(200, gameState_.isGameStarted ? "yes" : "no"); }
        Response IsGameFinished() {
            if (!gameState_.isGameFinished) {
                return Response(400, "Game is not finished");
            }

            if (gameState_.isGameFinished) {
                return Response(200, "yes");
            }

            return Response(200, "no");
        }
        Response IsWin() {
            if (!gameState_.isGameStarted) {
                return Response(400, "Game is not started");
            }

            if (gameState_.isLose) {
                return Response(200, "no");
            }

            return Response(200, "yes");
        }
        Response IsLose() {
            if (!gameState_.isGameStarted) {
                return Response(400, "Game is not started");
            }

            if (gameState_.isLose) {
                return Response(200, "yes");
            }

            return Response(200, "no");
        }

        Response Ping() {
            return Response(200, "pong");
        }
        Response SetWidth(int width) {
            if (gameState_.isGameStarted) {
                return Response(400, "Game is already started");
            }

            if (width < 1) {
                return Response(400, "Invalid width: " + std::to_string(width));
            }

            gameSettings_.width = width;

            return Response(200, "ok");
        }
        Response SetHeight(int height) {
            if (gameState_.isGameStarted) {
                return Response(400, "Game is already started");
            }

            if (height < 1) {
                return Response(400, "Invalid height: " + std::to_string(height));
            }

            gameSettings_.height = height;

            return Response(200, "ok");
        }
        Response SetCountOfShips(int size, int count) {
            if (gameState_.isGameStarted) {
                return Response(400, "Game is already started");
            }

            if (size < 1 || count < 1) {
                return Response(400, "Invalid size or count: " + std::to_string(size) + " " + std::to_string(count));
            }

            gameSettings_.countOfShips[size - 1] = count;

            return Response(200, "ok");
        }
        Response SetRole(std::string role) {
            if (gameState_.isGameStarted) {
                return Response(400, "Game is already started");
            }

            if (role == "master") {
                gameSettings_.role = GameSettings::Role::Master;
                return Response(200, "ok");
            }
            if (role == "slave") {
                gameSettings_.role = GameSettings::Role::Slave;
                return Response(200, "ok");
            }
            
            return Response(400, "Unknown role: " + role);
        }
        Response SetShootingStrategy(std::string strategy) {
            if (gameState_.isGameStarted) {
                return Response(400, "Game is already started");
            }

            if (shootingStrategies_.find(strategy) == shootingStrategies_.end()) {
                return Response(400, "Unknown strategy: " + strategy);
            }

            shootingStrategy_ = shootingStrategies_[strategy]->Clone();

            return Response(200, "ok");
        }

        Response StartGame() {
            if (gameState_.isGameStarted) {
                return Response(400, "Game is already started");
            }
            if (field_.GetCountOfAliveShips() == 0) {
                return Response(400, "No ships on the field");
            }
            if (!shootingStrategy_) {
                return Response(400, "No shooting strategy");
            }

            if (gameSettings_.role == GameSettings::Role::Master) {
                // TODO
            }

            gameState_.isGameStarted = true;
            return Response(200, "ok");
        }

        Response StopGame() {
            if (!gameState_.isGameStarted) {
                return Response(400, "Game is not started");
            }

            gameState_.isGameStarted = false;

            return Response(200, "ok");
        }
    };
}