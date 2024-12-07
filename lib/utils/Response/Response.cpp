#include "Response.hpp"

namespace BattleShipGame {
    Response::Response(int code, Error error) : code_(code), error_(error) {}

    std::string Response::ResponseMessage() const {
        if (code_ == 200) return "ok";

        std::string res = "status code: ";
        res += std::to_string(code_);
        res += '\n';
        res += error_.GetMessage();
        return res;
    }
}