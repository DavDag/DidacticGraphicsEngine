export module engine.core.log;

import engine.core.types;

// 
// Log functions
// 

// 
// You can use these functions to log messages to the console
// 
// Ex.
// LogDebug("Hello, World!");
// LogInfo("The solution to the problem is: {}", 42);
// 
// 
// You can even log to a file by passing a std::ofstream object
// 
// Ex.
// std::ofstream file("log.txt");
// FLogDebug(file, "Hello, World!");
// FLogInfo(file, "The solution to the problem is: {}", 42);
// 

// 
// Internal implementation
// 

template<bool C, int L> requires(L >= 0 && L < 4)
constexpr inline const char* __LogPrefix() noexcept {
    if constexpr (C) {
        if constexpr (L == 0) return "\033[1;30m[d] ";
        else if constexpr (L == 1) return "\033[1;37m[i] ";
        else if constexpr (L == 2) return "\033[1;33m[w] ";
        else if constexpr (L == 3) return "\033[1;31m[e] ";
    }
    else {
        if constexpr (L == 0) return "[d] ";
        else if constexpr (L == 1) return "[i] ";
        else if constexpr (L == 2) return "[w] ";
        else if constexpr (L == 3) return "[e] ";
    }
    return "cannot happen";
}

template<bool C, int L> requires(L >= 0 && L < 4)
constexpr inline const char* __LogSuffix() noexcept {
	if constexpr (C) {
		return "\033[0m";
	}
	else {
		return "";
	}
}

template<bool C, int L, typename... Args> requires(L >= 0 && L < 4)
constexpr inline void __Log(
    std::ostream& out,
    const std::source_location& src,
    const std::string& message,
    Args&&... args
) {
    constexpr const char* prefix = __LogPrefix<C, L>();
	constexpr const char* suffix = __LogSuffix<C, L>();
	const std::string file_name = src.file_name();
    out
        << prefix
        << std::format(
            "{:<24.24}:{:<3}",
            file_name.substr(file_name.size() < 24 ? 0 : file_name.size() - 24),
            src.line()
            // src.column()
            // src.function_name()
        )
        << " >>> "
        << std::vformat(message, std::make_format_args(args...))
        << suffix
        << std::endl // TODO: May improve this by not flushing every time
        ;
}

// 
// Structs to enable logging with a simple syntax
// 

export
template<typename... Args>
struct FLogDebug {
    FLogDebug(
        std::ostream& out,
        const std::string& message,
        Args&&... args,
        const std::source_location& src = std::source_location::current()
    ) {
#ifndef NDEBUG
        __Log<false, 0>(out, src, message, args...);
#endif // NDEBUG
    }
};

export
template<typename... Args>
struct LogDebug {
    LogDebug(
        const std::string& message,
        Args&&... args,
        const std::source_location& src = std::source_location::current()
    ) {
#ifndef NDEBUG
        __Log<true, 0>(std::cout, src, message, args...);
#endif // NDEBUG
    }
};

export
template<typename... Args>
struct FLogInfo {
    FLogInfo(
        std::ostream& out,
        const std::string& message,
        Args&&... args,
        const std::source_location& src = std::source_location::current()
    ) {
        __Log<false, 1>(out, src, message, args...);
    }
};

export
template<typename... Args>
struct LogInfo {
	LogInfo(
		const std::string& message,
		Args&&... args,
		const std::source_location& src = std::source_location::current()
	) {
        __Log<true, 1>(std::cout, src, message, args...);
	}
};

export
template<typename... Args>
struct FLogWarning {
    FLogWarning(
        std::ostream& out,
        const std::string& message,
        Args&&... args,
        const std::source_location& src = std::source_location::current()
    ) {
        __Log<false, 2>(out, src, message, args...);
    }
};

export
template<typename... Args>
struct LogWarning {
	LogWarning(
		const std::string& message,
		Args&&... args,
		const std::source_location& src = std::source_location::current()
	) {
        __Log<true, 2>(std::cout, src, message, args...);
	}
};

export
template<typename... Args>
struct FLogError {
    FLogError(
        std::ostream& out,
        const std::string& message,
        Args&&... args,
        const std::source_location& src = std::source_location::current()
    ) {
        __Log<false, 3>(out, src, message, args...);
    }
};

export
template<typename... Args>
struct LogError {
	LogError(
		const std::string& message,
		Args&&... args,
		const std::source_location& src = std::source_location::current()
	) {
        __Log<true, 3>(std::cerr, src, message, args...);
	}
};

// Deduction guide:
// Makes it possible to use the class without specifying the template arguments
// in this case, the std::source_location is deduced from the last argument

template<typename... Args>
FLogDebug(std::ostream& out, const std::string& s, Args&&...) -> FLogDebug<Args... >;

template<typename... Args>
LogDebug(const std::string& s, Args&&...) -> LogDebug<Args... >;

template<typename... Args>
FLogInfo(std::ostream& out, const std::string& s, Args&&...) -> FLogInfo<Args... >;

template<typename... Args>
LogInfo(const std::string& s, Args&&...) -> LogInfo<Args... >;

template<typename... Args>
FLogWarning(std::ostream& out, const std::string& s, Args&&...) -> FLogWarning<Args... >;

template<typename... Args>
LogWarning(const std::string& s, Args&&...) -> LogWarning<Args... >;

template<typename... Args>
FLogError(std::ostream& out, const std::string& s, Args&&...) -> FLogError<Args... >;

template<typename... Args>
LogError(const std::string& s, Args&&...) -> LogError<Args... >;
