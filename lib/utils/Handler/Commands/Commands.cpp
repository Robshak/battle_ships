#include "Commands.hpp"
#include <Manager/Manager.hpp>

namespace BattleShipGame {
    void CommandPing::execute(std::vector<std::string> args, Manager& manager) {
        std::cout << "pong\n";
    }

    void CommandExit::execute(std::vector<std::string> args, Manager& manager) {
        std::cout << "ok\n";
        exit(0);
    }

    void CommandCreate::execute(std::vector<std::string> args, Manager& manager) {
        for (int i = 1; i < args.size(); i++) {
            std::cout << args[i] << ' ';
        }
        std::cout << "\nok\n";
    }

    void CommandStart::execute(std::vector<std::string> args, Manager& manager) {
        Response res = manager.StartGame();
        std::cout << res.ResponseMessage() << "\n";
    }


    void CommandDump::execute(std::vector<std::string> args, Manager& manager) {
        Response res = FileManager::WriteField(manager.GetField(), args[1]);
        std::cout << res.ResponseMessage() << "\n";
    }

    void CommandLoad::execute(std::vector<std::string> args, Manager& manager) {
        Response res = FileManager::ReadField(manager.GetField(), args[1]);
        std::cout << res.ResponseMessage() << "\n";
    }

    void CommandMatrix::execute(std::vector<std::string> args, Manager& manager) {
        Response res = FileManager::WriteFieldMatrix(manager.GetField(), args[1]);
        std::cout << res.ResponseMessage() << "\n";
    }
}