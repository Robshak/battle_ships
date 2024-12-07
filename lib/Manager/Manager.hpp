#pragma once

#include <vector>

#include <utils/Handler/Handler.hpp>
#include <Field/Field.hpp>

#include <Response/Response.hpp>

namespace BattleShipGame {
    class Manager {
    private:
        struct GameState {
            bool isGameStarted;
            bool isGameFinished;
            bool isLose;
        };

        struct GameSettings {
            enum Role {
                Master,
                Slave
            };

            int width;
            int height;

            std::vector<int> countOfShips = std::vector<int>(4, 0);

            Role role;
        };

        GameSettings gameSettings_;
        GameState gameState_;
        Handler handler_;
        Field field_;
    public:
        Manager() = default;
        ~Manager() = default;

        bool Run() {
            handler_.Run(*this);

            return !gameState_.isGameFinished;
        }

        Field& GetField() { return field_; }

        bool SetRole(std::string role) {
            if(role == "master") {
                gameSettings_.role = GameSettings::Role::Master;
                return true;
            }
            if(role == "slave") {
                gameSettings_.role = GameSettings::Role::Slave;
                return true;
            }

            return false;
        }

        Response StartGame() {
            Response res;

            if (gameState_.isGameStarted) {
                res.SetCode(400);
                res.SetError("Game is already started");
                return res;
            }
            if (field_.GetCountOfAliveShips() == 0) {
                res.SetCode(400);
                res.SetError("Field is empty");
                return res;
            }

            //FIX

            gameState_.isGameStarted = true;
            res.SetCode(200);
            return res;
        }
    };
}