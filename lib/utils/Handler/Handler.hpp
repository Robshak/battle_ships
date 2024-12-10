#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <Commands.hpp>
#include <WorkWithString.hpp>

namespace BattleShipGame {
class Manager;

class Handler {
   private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands_;

   public:
    Handler();

    void Run(Manager& manager);
};
}  // namespace BattleShipGame