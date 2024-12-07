#include "Commands.hpp"
#include <Manager.hpp>

namespace BattleShipGame {
    Response CommandPing::execute(std::vector<std::string> args, Manager& manager) {
        return manager.Ping();
    }
    
    Response CommandCreate::execute(std::vector<std::string> args, Manager& manager) {
        if (args.size() < 2) {
            return Response(400, "Too few arguments");
        }

        return manager.SetRole(args[1]);
    }


    Response CommandExit::execute(std::vector<std::string> args, Manager& manager) {
        std::cout << "ok\n";
        exit(0);
    }

    Response CommandStart::execute(std::vector<std::string> args, Manager& manager) {
        return manager.StartGame();
    }

    Response CommandStop::execute(std::vector<std::string> args, Manager& manager) {
        return manager.StopGame();
    }


    Response CommandSet::execute(std::vector<std::string> args, Manager& manager) {
        if (args.size() < 2) {
            return Response(400, "Too few arguments");
        }

        if (args[1] == "width") {
            if (args.size() < 3) {
                return Response(400, "Too few arguments");
            }
            return manager.SetWidth(std::stoi(args[2]));
        } else if (args[1] == "height") {
            if (args.size() < 3) {
                return Response(400, "Too few arguments");
            }
            return manager.SetHeight(std::stoi(args[2]));
        } else if (args[1] == "count") {
            if (args.size() < 4) {
                return Response(400, "Too few arguments");
            }
            return manager.SetCountOfShips(std::stoi(args[2]), std::stoi(args[3]));
        } else if (args[1] == "strategy") {
            if (args.size() < 3) {
                return Response(400, "Too few arguments");
            }
            return manager.SetShootingStrategy(args[2]);
        } else if (args[1] == "result") {
            if (args.size() < 3) {
                return Response(400, "Too few arguments");
            }
            return manager.GetShootingStrategy().SetResult(args[2]);
        }

        return Response(400, "Unknown command: set " + args[1]);
    }

    Response CommandGet::execute(std::vector<std::string> args, Manager& manager) {
        if (args.size() < 2) {
            return Response(400, "Too few arguments");
        }

        if (args[1] == "width") {
            return Response(200, std::to_string(manager.GetField().GetWidth()));
        } else if (args[1] == "height") {
            return Response(200, std::to_string(manager.GetField().GetHeight()));
        } else if (args[1] == "count") {
            if (args.size() < 3) {
                return Response(400, "Too few arguments");
            }
            // return Response(200, std::to_string(manager.GetField().Get(std::stoi(args[2]))));
        }

        return Response(400, "Unknown command: get " + args[1]);
    }

    Response CommandShot::execute(std::vector<std::string> args, Manager& manager) {
        if (args.size() < 3) {
            if (manager.IsGameStarted().ResponseMessage() == "no") {
                return Response(400, "Game is not started");
            }
            return manager.GetShootingStrategy().Shot();
        } else {
            if (manager.IsGameStarted().ResponseMessage() == "no") {
                return Response(400, "Game is not started");
            }
            return manager.GetField().Shot(std::stoi(args[1]), std::stoi(args[2]));
        }
    }


    Response CommandFinished::execute(std::vector<std::string> args, Manager& manager) {
        return manager.IsGameFinished();
    }

    Response CommandWin::execute(std::vector<std::string> args, Manager& manager) {
        return manager.IsWin();
    }

    Response CommandLose::execute(std::vector<std::string> args, Manager& manager) {
        return manager.IsLose();
    }


    Response CommandDump::execute(std::vector<std::string> args, Manager& manager) {
        return FileManager::WriteField(manager.GetField(), args[1]);
    }

    Response CommandLoad::execute(std::vector<std::string> args, Manager& manager) {
        return FileManager::ReadField(manager.GetField(), args[1]);
    }

    Response CommandMatrix::execute(std::vector<std::string> args, Manager& manager) {
        return FileManager::WriteFieldMatrix(manager.GetField(), args[1]);
    }
}