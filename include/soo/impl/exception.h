// By notchcamo.

#pragma once

#include <exception>
#include <string>
#include <utility>

/**
 * @brief Namespace for custom exceptions.
 */
namespace soo::exception
{
    class DivisionByZero final : public std::exception
    {
    private:
        std::string msg;

    public:
        explicit DivisionByZero(std::string str = "Division by zero.") : msg(std::move(str)) {}
        const char* what() const noexcept override { return msg.c_str(); }
    };
} // namespace soo::exception.
