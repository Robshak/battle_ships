#pragma once

#include <unordered_map>
#include <memory>
#include <iostream>
#include <string>
#include <functional>

#include "./Commands/Commands.hpp"
#include <Manager/Manager.hpp>

#include <WorkWithString/WorkWithString.hpp>

namespace BattleShipGame {
    class Manager; // Forward declaration

    class Handler {
    private:
        std::unordered_map<std::string, std::unique_ptr<Command>> commands_;
    public:
        Handler() {
            commands_["ping"] = std::make_unique<CommandPing>();
            commands_["exit"] = std::make_unique<CommandExit>();
            commands_["create"] = std::make_unique<CommandCreate>();
        }

        void Run(Manager& manager) {
            std::string inputString, cmd;
            std::getline(std::cin, inputString);

            std::vector<std::string> splitString = SplitString(inputString, ' ');
            cmd = splitString[0];

            auto it = commands_.find(cmd);
            if (it != commands_.end()) {
                it->second->execute(splitString, manager);
            } else {
                std::cout << "Unknown command\n";
            }
        }
    };
}