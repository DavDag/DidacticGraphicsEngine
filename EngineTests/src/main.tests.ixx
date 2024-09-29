module;
#include <gtest/gtest.h>
export module engine.tests;

import core.tests;
import math.tests;

export
int main(int argc, char** argv) {
	RUN_ALL_TESTS();
	return 0;
}