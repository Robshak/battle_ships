#include "Handler.hpp"

#include <Manager.hpp>

namespace BattleShipGame {
Handler::Handler() {
    commands_["ping"] = std::make_unique<CommandPing>();
    commands_["create"] = std::make_unique<CommandCreate>();
    commands_["exit"] = std::make_unique<CommandExit>();
    commands_["start"] = std::make_unique<CommandStart>();
    commands_["stop"] = std::make_unique<CommandStop>();

    commands_["set"] = std::make_unique<CommandSet>();
    commands_["get"] = std::make_unique<CommandGet>();

    commands_["shot"] = std::make_unique<CommandShot>();

    commands_["finished"] = std::make_unique<CommandFinished>();
    commands_["win"] = std::make_unique<CommandWin>();
    commands_["lose"] = std::make_unique<CommandLose>();

    commands_["dump"] = std::make_unique<CommandDump>();
    commands_["load"] = std::make_unique<CommandLoad>();
    commands_["matrix"] = std::make_unique<CommandMatrix>();

    commands_["test"] = std::make_unique<CommandTest>();
}

void Handler::Run(Manager& manager) {
    std::string inputString, cmd;
    std::getline(std::cin, inputString);

    std::vector<std::string> splitString = SplitString(inputString, ' ');
    if (splitString.size() == 0) {
        return;
    }
    cmd = splitString[0];

    auto it = commands_.find(cmd);
    if (it != commands_.end()) {
        std::cout << it->second->execute(splitString, manager).ResponseMessage()
                  << "\n";
    } else {
        std::cout << "Unknown command\n";
    }
}
}  // namespace BattleShipGame