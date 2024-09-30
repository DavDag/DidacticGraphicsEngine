export module engine.core.assert;

import engine.core.types;
import engine.core.log;

export
inline void Assert(
	bool condition,
	const std::string& msg,
	std::ostream& out = std::cerr,
	const std::source_location& loc = std::source_location::current()
) {
	if (!condition) {
		FLogError<const std::string&>(out, "Assertion failed: {}", msg, loc);
		std::abort(); // Abort the program, enabling a debugger to catch the error & inspect the stack
	}
}

export
inline void DebugAssert(
	bool condition,
	const std::string& msg,
	std::ostream& out = std::cerr,
	const std::source_location& loc = std::source_location::current()
) {
#ifndef NDEBUG
	if (!condition) {
		FLogError<const std::string&>(out, "Assertion failed: {}", msg, loc);
		std::abort(); // Abort the program, enabling a debugger to catch the error & inspect the stack
	}
#endif // NDEBUG
}
