#pragma once

#include <string>

namespace BattleShipGame {
class Error {
   private:
    std::string message_;

   public:
    Error() = default;
    Error(std::string message) : message_(message) {}
    ~Error() = default;

    std::string GetMessage() const;
};
}  // namespace BattleShipGame