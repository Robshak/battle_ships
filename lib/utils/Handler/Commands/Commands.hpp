#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <FileManager/FileManager.hpp>

#include <Response/Response.hpp>

namespace BattleShipGame {
    class Manager; // Forward declaration

    class Command {
    public:
        virtual ~Command() = default;
        virtual void execute(std::vector<std::string> args, Manager& manager) = 0;
    };

    class CommandPing : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandExit : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandCreate : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandStart : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override;
    };


    class CommandDump : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandLoad : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandMatrix : public Command {
    public:
        void execute(std::vector<std::string> args, Manager& manager) override;
    };
}
