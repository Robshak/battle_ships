#pragma once

#include <string>

#include <Error/Error.hpp>

namespace BattleShipGame {
    class Response {
    private:
        int code_;
        Error error_;
    public:
        Response() = default;
        Response(int code, Error error);
        ~Response() = default;

        void SetCode(int code) { code_ = code; }
        void SetError(Error error) { error_ = error; }
        void SetError(std::string message) { error_ = Error(message); }

        bool IsOk() const { return code_ == 200; }
        int StatusCode() const { return code_; }
        std::string ResponseMessage() const;
    };
}