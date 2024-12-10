#include "Commands.hpp"

#include <Manager.hpp>

namespace BattleShipGame {
Response CommandPing::execute(std::vector<std::string> args, Manager& manager) {
    return manager.Ping();
}

Response CommandCreate::execute(std::vector<std::string> args,
                                Manager& manager) {
    if (args.size() < 2) {
        return Response(400, "Too few arguments");
    }

    return manager.SetRole(args[1]);
}

Response CommandExit::execute(std::vector<std::string> args, Manager& manager) {
    return manager.KillManager();
}

Response CommandStart::execute(std::vector<std::string> args,
                               Manager& manager) {
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
        return manager.SetWidth(std::strtoll(args[2].c_str(), nullptr, 10));
    } else if (args[1] == "height") {
        if (args.size() < 3) {
            return Response(400, "Too few arguments");
        }
        return manager.SetHeight(std::strtoll(args[2].c_str(), nullptr, 10));
    } else if (args[1] == "count") {
        if (args.size() < 4) {
            return Response(400, "Too few arguments");
        }
        return manager.SetCountOfShips(
            std::strtoll(args[2].c_str(), nullptr, 10),
            std::strtoll(args[2].c_str(), nullptr, 10));
    } else if (args[1] == "strategy") {
        if (args.size() < 3) {
            return Response(400, "Too few arguments");
        }
        std::vector<std::string> subArgs(args.begin() + 3, args.end());
        return manager.SetShootingStrategy(args[2], subArgs);
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
        int sizeOfShip = std::strtoll(args[2].c_str(), nullptr, 10);

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
    }

    return manager.Shot(std::strtoll(args[2].c_str(), nullptr, 10),
                        std::strtoll(args[2].c_str(), nullptr, 10));
}

Response CommandFinished::execute(std::vector<std::string> args,
                                  Manager& manager) {
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

Response CommandMatrix::execute(std::vector<std::string> args,
                                Manager& manager) {
    if (args.size() < 3) {
        return Response(400, "Too few arguments");
    }

    if (args[1] == "ship") {
        return manager.ShipsToMatrix(args[2]);
    } else if (args[1] == "shot") {
        return manager.ShotsToMatrix(args[2]);
    }

    return Response(400, "Unknown command: matrix " + args[1]);
}

Response CommandTest::execute(std::vector<std::string> args, Manager& manager) {
    if (args.size() < 2) {
        return Response(400, "Too few arguments");
    }

    if (args[1] == "shot") {
        if (args.size() < 3) {
            return Response(400, "Too few arguments");
        }
        return manager.TestShot(std::strtoll(args[2].c_str(), nullptr, 10));
    }

    return Response(400, "Unknown command: test " + args[1]);
}
}  // namespace BattleShipGame