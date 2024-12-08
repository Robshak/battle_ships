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
            return manager.SetResult(args[2]);
        }

        return Response(400, "Unknown command: set " + args[1]);
    }

    Response CommandGet::execute(std::vector<std::string> args, Manager& manager) {
        if (args.size() < 2) {
            return Response(400, "Too few arguments");
        }

        if (args[1] == "width") {
            return manager.GetWidth();
        } else if (args[1] == "height") {
            return manager.GetHeight();
        } else if (args[1] == "count") {
            if (args.size() < 3) {
                return Response(400, "Too few arguments");
            }
            int sizeOfShip = std::stoi(args[2]);
            
            if (sizeOfShip > 5 || sizeOfShip < 1) {
                return Response(400, "Invalid size: " + args[2]);
            }

            return manager.GetCountOfShips(sizeOfShip);
        }

        return Response(400, "Unknown command: get " + args[1]);
    }

    Response CommandShot::execute(std::vector<std::string> args, Manager& manager) {
        if (args.size() < 3) {
            return manager.Shot();
        } else {
            return manager.Shot(std::stoi(args[1]), std::stoi(args[2]));
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
        return manager.WriteField(args[1]);
    }

    Response CommandLoad::execute(std::vector<std::string> args, Manager& manager) {
        return manager.ReadField(args[1]);
    }

    Response CommandMatrix::execute(std::vector<std::string> args, Manager& manager) {
        return manager.FieldToMatrix(args[1]);
    }
}