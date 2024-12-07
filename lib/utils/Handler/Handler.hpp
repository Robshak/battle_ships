#pragma once

#include <unordered_map>
#include <memory>
#include <iostream>
#include <string>
#include <functional>

#include <Commands/Commands.hpp>

#include <WorkWithString/WorkWithString.hpp>
#include <Error/Error.hpp>

namespace BattleShipGame {
    class Manager; // Forward declaration

    class Handler {
    private:
        std::unordered_map<std::string, std::unique_ptr<Command>> commands_;
    public:
        Handler();

        void Run(Manager& manager);
    };
}