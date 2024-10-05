module;
#include <string>
#include <iostream>
#include <source_location>
export module engine.core.assert;

import engine.core.types;
import engine.core.log;

export
class AssertException final : public std::exception
{
public:
    explicit AssertException(const std::string& message) : _msg(message)
    {
    }

    const char* what() const noexcept override
    {
        return _msg.c_str();
    }

private:
    const std::string _msg;
};

export
void Assert(
    const bool condition,
    const std::string& msg,
    std::ostream& out = std::cerr,
    const std::source_location& loc = std::source_location::current()
)
{
    if (!condition)
    {
        FLogError<const std::string&>(out, "Assertion Failed: {}", msg, loc);
        throw AssertException(std::format("Assertion Failed: {}", msg));
    }
}

export
void DebugAssert(
    const bool condition,
    const std::string& msg,
    std::ostream& out = std::cerr,
    const std::source_location& loc = std::source_location::current()
)
{
#ifndef NDEBUG
    if (!condition)
    {
        FLogError<const std::string&>(out, "DebugAssertion Failed: {}", msg, loc);
        throw AssertException(std::format("DebugAssertion Failed: {}", msg));
    }
#endif // NDEBUG
}
