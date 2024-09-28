export module core.assert;

import core.types;
import core.log;

export
constexpr inline void DebugAssert(bool condition, const std::string& msg, const std::source_location& loc = std::source_location::current()) {
#ifndef NDEBUG
	if (!condition) {
		LogError(msg, loc);
		std::abort(); // Abort the program, enabling a debugger to catch the error & inspect the stack
	}
#endif // NDEBUG
}
