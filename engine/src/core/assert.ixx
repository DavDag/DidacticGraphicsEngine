module;
#include <cstdint>
#include <cmath>
#include <string>
#include <iostream>
#include <source_location>
export module engine.core.assert;

import engine.core.types;
import engine.core.log;

export
void Assert(
	const bool condition,
	const std::string& msg,
	std::ostream& out = std::cerr,
	const std::source_location& loc = std::source_location::current()
) {
	if (!condition) {
		FLogError<const std::string&>(out,  "Assertion Failed: {}", msg, loc);
		std::abort(); // Abort the program, enabling a debugger to catch the error & inspect the stack
	}
}

export
void DebugAssert(
	const bool condition,
	const std::string& msg,
	std::ostream& out = std::cerr,
	const std::source_location& loc = std::source_location::current()
) {
#ifndef NDEBUG
	if (!condition) {
		FLogError<const std::string&>(out,  "Assertion Failed: {}", msg, loc);
		std::abort(); // Abort the program, enabling a debugger to catch the error & inspect the stack
	}
#endif // NDEBUG
}
