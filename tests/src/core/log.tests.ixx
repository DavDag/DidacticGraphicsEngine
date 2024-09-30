module;
#include <gtest/gtest.h>
#include <gmock/gmock.h>
export module engine.core.log.tests;

import engine.core.log;

namespace engine::core::log {

TEST(EngineCoreLog, StandardLogShouldOutputToStdOut) {
	// Intercept std::cout & std::cerr
	std::stringstream bufferCOut;
	std::stringstream bufferCErr;
	std::streambuf* oldCOut = std::cout.rdbuf(bufferCOut.rdbuf());
	std::streambuf* oldCErr = std::cerr.rdbuf(bufferCErr.rdbuf());

	// Logging
	LogDebug("Debug message");
	LogInfo("Info message");
	LogWarning("Warning message");

	// Restore std::cout & std::cerr
	std::cout.rdbuf(oldCOut);
	std::cerr.rdbuf(oldCErr);

	// Check the output
	EXPECT_THAT(bufferCErr.str(), ::testing::IsEmpty());
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("Debug message"));
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("Info message"));
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("Warning message"));
}

TEST(EngineCoreLog, StandardLogShouldOutputToStdErr) {
	// Intercept std::cout & std::cerr
	std::stringstream bufferCOut;
	std::stringstream bufferCErr;
	std::streambuf* oldCOut = std::cout.rdbuf(bufferCOut.rdbuf());
	std::streambuf* oldCErr = std::cerr.rdbuf(bufferCErr.rdbuf());

	// Logging
	LogError("Error message");

	// Restore std::cout & std::cerr
	std::cout.rdbuf(oldCOut);
	std::cerr.rdbuf(oldCErr);

	// Check the output
	EXPECT_THAT(bufferCOut.str(), ::testing::IsEmpty());
	EXPECT_THAT(bufferCErr.str(), ::testing::HasSubstr("Error message"));
}

TEST(EngineCoreLog, FileLogShouldOutputToFileOnly) {
	// Intercept std::cout & std::cerr
	std::stringstream bufferCOut;
	std::stringstream bufferCErr;
	std::streambuf* oldCOut = std::cout.rdbuf(bufferCOut.rdbuf());
	std::streambuf* oldCErr = std::cerr.rdbuf(bufferCErr.rdbuf());

	// Create tmp "file" for logging (in memory string)
	std::stringstream fakeFileBuffer;

	// Log to file
	FLogDebug(fakeFileBuffer, "Debug message");
	FLogInfo(fakeFileBuffer, "Info message");
	FLogWarning(fakeFileBuffer, "Warning message");
	FLogError(fakeFileBuffer, "Error message");

	// Restore std::cout & std::cerr
	std::cout.rdbuf(oldCOut);
	std::cerr.rdbuf(oldCErr);

	// Check the output
	EXPECT_THAT(bufferCOut.str(), ::testing::IsEmpty());
	EXPECT_THAT(bufferCErr.str(), ::testing::IsEmpty());
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("Debug message"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("Info message"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("Warning message"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("Error message"));
}

TEST(EngineCoreLog, LogShouldHaveVariadicArguments) {
	// Intercept std::cout & std::cerr
	std::stringstream bufferCOut;
	std::stringstream bufferCErr;
	std::streambuf* oldCOut = std::cout.rdbuf(bufferCOut.rdbuf());
	std::streambuf* oldCErr = std::cerr.rdbuf(bufferCErr.rdbuf());

	// Logging (1 argument)
	LogDebug("Debug message: <{}>", 42);
	LogInfo("Info message: <{}>", "Hello, World!");
	LogWarning("Warning message: <{}>", 3.14f);
	LogError("Error message: <{}>", 'X');

	// Logging (2 arguments)
	LogDebug("Debug message: <{}, {}>", 42, "Hello, World!");
	LogInfo("Info message: <{}, {}>", "Hello, World!", 3.14f);
	LogWarning("Warning message: <{}, {}>", 3.14f, 'X');
	LogError("Error message: <{}, {}>", 'X', 42);

	// Restore std::cout & std::cerr
	std::cout.rdbuf(oldCOut);
	std::cerr.rdbuf(oldCErr);

	// Check the output
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("<42>"));
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("<Hello, World!>"));
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("<3.14>"));
	EXPECT_THAT(bufferCErr.str(), ::testing::HasSubstr("<X>"));
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("<42, Hello, World!>"));
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("<Hello, World!, 3.14>"));
	EXPECT_THAT(bufferCOut.str(), ::testing::HasSubstr("<3.14, X>"));
	EXPECT_THAT(bufferCErr.str(), ::testing::HasSubstr("<X, 42>"));
}

TEST(EngineCoreLog, FileLogShouldHaveVariadicArguments) {
	// Intercept std::cout & std::cerr
	std::stringstream bufferCOut;
	std::stringstream bufferCErr;
	std::streambuf* oldCOut = std::cout.rdbuf(bufferCOut.rdbuf());
	std::streambuf* oldCErr = std::cerr.rdbuf(bufferCErr.rdbuf());

	// Create tmp "file" for logging (in memory string)
	std::stringstream fakeFileBuffer;

	// Logging (1 argument)
	FLogDebug(fakeFileBuffer, "Debug message: <{}>", 42);
	FLogInfo(fakeFileBuffer, "Info message: <{}>", "Hello, World!");
	FLogWarning(fakeFileBuffer, "Warning message: <{}>", 3.14f);
	FLogError(fakeFileBuffer, "Error message: <{}>", 'X');

	// Logging (2 arguments)
	FLogDebug(fakeFileBuffer, "Debug message: <{}, {}>", 42, "Hello, World!");
	FLogInfo(fakeFileBuffer, "Info message: <{}, {}>", "Hello, World!", 3.14f);
	FLogWarning(fakeFileBuffer, "Warning message: <{}, {}>", 3.14f, 'X');
	FLogError(fakeFileBuffer, "Error message: <{}, {}>", 'X', 42);

	// Restore std::cout & std::cerr
	std::cout.rdbuf(oldCOut);
	std::cerr.rdbuf(oldCErr);

	// Check the output
	EXPECT_THAT(bufferCOut.str(), ::testing::IsEmpty());
	EXPECT_THAT(bufferCErr.str(), ::testing::IsEmpty());
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("<42>"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("<Hello, World!>"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("<3.14>"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("<X>"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("<42, Hello, World!>"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("<Hello, World!, 3.14>"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("<3.14, X>"));
	EXPECT_THAT(fakeFileBuffer.str(), ::testing::HasSubstr("<X, 42>"));
}

} // namespace engine::core::log
