#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <Response.hpp>

namespace BattleShipGame {
class Manager;

class Command {
   public:
    virtual ~Command() = default;
    virtual Response execute(std::vector<std::string> args,
                             Manager& manager) = 0;
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

class CommandTest : public Command {
   public:
    Response execute(std::vector<std::string> args, Manager& manager) override;
};
}  // namespace BattleShipGame
