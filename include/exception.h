// By notchcamo.

#pragma once

#include <exception>
#include <string>
#include <utility>

/**
 * Namespace for custom exceptions.
 */
namespace mathod::exception {
    class DivisionByZeroException final : public std::exception {
    private:
        std::string msg;

    public:
        explicit DivisionByZeroException(std::string str = "Division by zero.") : msg(std::move(str)) {}
        const char* what() const noexcept override { return msg.c_str(); }
    };
} // namespace mathod::exception.
