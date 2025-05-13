#pragma once

#include <vector>

#include<utils/Handler/Handler.hpp>
#include<Field/Field.hpp>


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

            std::vector<int> shipsWithSize1;
            std::vector<int> shipsWithSize2;
            std::vector<int> shipsWithSize3;
            std::vector<int> shipsWithSize4;

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
    };
}