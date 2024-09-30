module;
#include <gtest/gtest.h>
export module main.tests;

import engine.core.tests;
import engine.math.tests;

export
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}