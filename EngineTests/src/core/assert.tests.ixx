module;
#include <gtest/gtest.h>
export module engine.core.assert.tests;

import engine.core.assert;

TEST(EngineCoreAssert, Assertions) {
	EXPECT_DEATH(Assert(false, "This should abort in Release & Debug"), "Assertion failed");
	EXPECT_DEBUG_DEATH(DebugAssert(false, "This should abort in Debug"), "Assertion failed");

	EXPECT_EXIT({
		Assert(true, "This should not abort");
		exit(0);
	}, ::testing::ExitedWithCode(0), "");
	EXPECT_EXIT({
		DebugAssert(true, "This should not abort");
		exit(0);
	}, ::testing::ExitedWithCode(0), "");
}
