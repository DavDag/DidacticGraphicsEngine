module;
#include <gtest/gtest.h>
export module engine.core.types.tests;

import engine.core.types;

namespace engine::core::types {
TEST(EngineCoreTypes, TypeSizingRespectNaming) {
	// Basic types
	EXPECT_EQ(sizeof(i8), 1);
	EXPECT_EQ(sizeof(i16), 2);
	EXPECT_EQ(sizeof(i32), 4);
	EXPECT_EQ(sizeof(i64), 8);
	EXPECT_EQ(sizeof(u8), 1);
	EXPECT_EQ(sizeof(u16), 2);
	EXPECT_EQ(sizeof(u32), 4);
	EXPECT_EQ(sizeof(u64), 8);
	EXPECT_EQ(sizeof(f32), 4);
	EXPECT_EQ(sizeof(f64), 8);

	// Special types
	EXPECT_EQ(sizeof(byte), 1);
	EXPECT_EQ(sizeof(size), 8);
}

TEST(EngineCoreTypes, ValidTypeLimits) {
	// Basic Types
	EXPECT_EQ(I8_MIN, -128);
	EXPECT_EQ(I8_MAX, 127);
	EXPECT_EQ(I16_MIN, -32768);
	EXPECT_EQ(I16_MAX, 32767);
	EXPECT_EQ(I32_MIN, -2147483648);
	EXPECT_EQ(I32_MAX, 2147483647);
	EXPECT_EQ(I64_MIN, -9223372036854775808);
	EXPECT_EQ(I64_MAX, 9223372036854775807);
	EXPECT_EQ(U8_MIN, 0);
	EXPECT_EQ(U8_MAX, 255);
	EXPECT_EQ(U16_MIN, 0);
	EXPECT_EQ(U16_MAX, 65535);
	EXPECT_EQ(U32_MIN, 0);
	EXPECT_EQ(U32_MAX, 4294967295);
	EXPECT_EQ(U64_MIN, 0);
	EXPECT_EQ(U64_MAX, 18446744073709551615);
	EXPECT_FLOAT_EQ(F32_MIN, 1.1754944e-38f);
	EXPECT_FLOAT_EQ(F32_MAX, 3.4028235e+38f);
	EXPECT_DOUBLE_EQ(F64_MIN, 2.2250738585072014e-308);
	EXPECT_DOUBLE_EQ(F64_MAX, 1.7976931348623157e+308);

	// Special Types
	EXPECT_EQ(BYTE_MIN, 0);
	EXPECT_EQ(BYTE_MAX, 255);
	EXPECT_EQ(SIZE_MIN, 0);
	EXPECT_EQ(SIZE_MAX, 18446744073709551615);
}

TEST(EngineCoreTypes, TypeEpsilonInRange) {
	EXPECT_LT(F32_EPSILON, 1e-4f); // 0.0001
	EXPECT_GT(F32_EPSILON, 1e-8f); // 0.00000001
	EXPECT_LT(F64_EPSILON, 1e-9);  // 0.000000001
	EXPECT_GT(F64_EPSILON, 1e-15); // 0.000000000000001
}

} // namespace engine::core::types
