#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <FileManager.hpp>

#include <Response.hpp>

namespace BattleShipGame {
    class Manager; // Forward declaration

    class Command {
    public:
        virtual ~Command() = default;
        virtual Response execute(std::vector<std::string> args, Manager& manager) = 0;
    };


    class CommandPing : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandCreate : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandExit : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };
    class CommandStart : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };
    class CommandStop : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandSet : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };
    class CommandGet : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandShot : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandFinished : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };
    class CommandWin : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };
    class CommandLose : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };

    class CommandDump : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };
    class CommandLoad : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };
    class CommandMatrix : public Command {
    public:
        Response execute(std::vector<std::string> args, Manager& manager) override;
    };
}
