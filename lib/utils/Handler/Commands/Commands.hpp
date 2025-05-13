#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <Manager/Manager.hpp>

namespace BattleShipGame {
    class Manager; // Forward declaration

    class Command {
    public:
        virtual ~Command() = default;
        virtual void execute(std::vector<std::string> args, Manager& manager) = 0;
    };

    class CommandPing : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override {
            std::cout << "pong\n";
        }
    };

    class CommandExit : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override {
            exit(0);
        }
    };

    class CommandCreate : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override {
            for (int i = 1; i < args.size(); i++) {
                std::cout << args[i] << ' ';
            }
            std::cout << '\n';
        }
    };
}
