#pragma once

#include <string>

#include <Error/Error.hpp>

namespace BattleShipGame {
class Response {
   private:
    int code_;
    Error error_;
    std::string data_;

   public:
    Response() = default;
    Response(int code, Error error);
    Response(int code, std::string error);
    ~Response() = default;

    void SetCode(int code);
    void SetData(std::string data);
    void SetError(Error error);
    void SetError(std::string message);

    bool IsOk() const;
    int StatusCode() const;
    std::string ResponseMessage() const;
};
}  // namespace BattleShipGame