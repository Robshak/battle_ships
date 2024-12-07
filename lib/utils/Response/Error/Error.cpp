#include "Error.hpp"

namespace BattleShipGame {
    std::string Error::GetMessage() const { 
        std::string res;
        
        res += "Error: ";
        res += message_;

        return res;
    }
}