#include "Handler.hpp"
#include <Manager/Manager.hpp>

namespace BattleShipGame {
    Handler::Handler() {
        commands_["ping"] = std::make_unique<CommandPing>();
        commands_["exit"] = std::make_unique<CommandExit>();
        commands_["create"] = std::make_unique<CommandCreate>();
        commands_["start"] = std::make_unique<CommandStart>();

        commands_["dump"] = std::make_unique<CommandDump>();
        commands_["load"] = std::make_unique<CommandLoad>();
        commands_["matrix"] = std::make_unique<CommandMatrix>();
    }

    void Handler::Run(Manager& manager) {
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
}