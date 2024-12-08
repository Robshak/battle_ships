#include "Response.hpp"

namespace BattleShipGame {
    Response::Response(int code, Error error) : code_(code), error_(error) {}
    Response::Response(int code, std::string message) : code_(code) {
        if (code == 200) {
            data_ = message;
        } else {
            error_ = Error(message);
        }
    }

    void Response::SetCode(int code) { code_ = code; }
    void Response::SetData(std::string data) { data_ = data; }
    void Response::SetError(Error error) { error_ = error; }
    void Response::SetError(std::string message) { error_ = Error(message); }

    bool Response::IsOk() const { return code_ == 200; }
    int Response::StatusCode() const { return code_; }

    std::string Response::ResponseMessage() const {
        if (code_ == 200) {
            if (data_ != "") {
                return data_;
            }
            return "ok";
        }

        std::string res = "status code: ";
        res += std::to_string(code_);
        res += '\n';
        res += error_.GetMessage();
        return res;
    }
}