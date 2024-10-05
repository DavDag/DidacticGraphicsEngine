module;
#include <gtest/gtest.h>
#include <gmock/gmock.h>
export module engine.core.assert.tests;

import engine.core.assert;

namespace engine::core::assert {

TEST(EngineCoreAssert, AssertionShouldAbortOnConditionNotMet) {
	// https://google.github.io/googletest/reference/assertions.html#death
	EXPECT_DEATH(Assert(false, "This should abort in Release & Debug"), ::testing::HasSubstr("Assertion Failed"));
	EXPECT_DEBUG_DEATH(DebugAssert(false, "This should abort in Debug"), ::testing::HasSubstr("Assertion Failed"));
}

TEST(EngineCoreAssert, AssertionShouldNotAbortOnConditionMet) {
	// To assert no abrupt exit, we use EXPECT_EXIT and check the exit code
	// https://google.github.io/googletest/reference/assertions.html#EXPECT_EXIT
	EXPECT_EXIT({
		Assert(true, "This should not abort");
		exit(0);
	}, ::testing::ExitedWithCode(0), "");
	EXPECT_EXIT({
		DebugAssert(true, "This should not abort");
		exit(0);
	}, ::testing::ExitedWithCode(0), "");
}

} // namespace engine::core::assert
