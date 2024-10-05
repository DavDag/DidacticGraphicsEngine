module;
#include <gtest/gtest.h>
#include <gmock/gmock.h>
export module engine.math.vec2.tests;

import engine.core;
import engine.math.vec2;

namespace engine::math::vec2 {

	template<typename T>
	class EngineMathVec2GenericTest : public testing::Test {};

	using AllVec2Types = ::testing::Types<
		Vec2i8, Vec2i16, Vec2i32, Vec2i64,
		Vec2u8, Vec2u16, Vec2u32, Vec2u64,
		Vec2f32, Vec2f64
	>;
	TYPED_TEST_SUITE(EngineMathVec2GenericTest, AllVec2Types);

	TYPED_TEST(EngineMathVec2GenericTest, Constructors) {
		using ValueType = decltype(TypeParam::x);

		// Default constructor
		TypeParam v_def;
		EXPECT_EQ(0, v_def.x);
		EXPECT_EQ(0, v_def.y);

		// Value constructor
		TypeParam v_val((ValueType)1, (ValueType)2);
		EXPECT_EQ((ValueType)1, v_val.x);
		EXPECT_EQ((ValueType)2, v_val.y);

		// Copy constructor
		TypeParam v_copy1((ValueType)1, (ValueType)2);
		TypeParam v_copy2(v_copy1);
		EXPECT_EQ((ValueType)1, v_copy2.x);
		EXPECT_EQ((ValueType)2, v_copy2.y);

		// Assignment operator
		TypeParam v_ass1((ValueType)1, (ValueType)2);
		TypeParam v_ass2;
		v_ass2 = v_ass1;
		EXPECT_EQ((ValueType)1, v_ass2.x);
		EXPECT_EQ((ValueType)2, v_ass2.y);
	}

	TEST(EngineMathVec2F32SpecialCaseTest, ConstructorWithNaNsShouldThrow) {
		// Quiet NaNs
		auto qnan = std::numeric_limits<f32>::quiet_NaN();
		EXPECT_DEBUG_DEATH({ Vec2f32(qnan, 0); }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(0, qnan); }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(qnan, qnan); }, ".*");

		// Signaling NaNs
		auto snan = std::numeric_limits<f32>::signaling_NaN();
		EXPECT_DEBUG_DEATH({ Vec2f32(snan, 0); }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(0, snan); }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(snan, snan); }, ".*");

		// Dividing 0 by 0
		EXPECT_DEBUG_DEATH({ Vec2f32(0, 0) / 0; }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(0, 1) / 0; }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(1, 0) / 0; }, ".*");

		// Multiplying 0 by infinity
		auto inf = std::numeric_limits<f32>::infinity();
		EXPECT_DEBUG_DEATH({ Vec2f32(0, 0) * inf; }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(0, 1) * inf; }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(1, 0) * inf; }, ".*");

		// Multiplying infinity by 0
		EXPECT_DEBUG_DEATH({ Vec2f32(inf, 0) * 0; }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(0, inf) * 0; }, ".*");
		EXPECT_DEBUG_DEATH({ Vec2f32(inf, inf) * 0; }, ".*");

		// Squaring negative numbers
		// No usecases for Vec2
	}

	TYPED_TEST(EngineMathVec2GenericTest, LogicOperators) {
		using ValueType = decltype(TypeParam::x);

		TypeParam va_12((ValueType)1, (ValueType)2);
		TypeParam vb_12((ValueType)1, (ValueType)2);
		TypeParam va_21((ValueType)2, (ValueType)1);
		TypeParam vb_21((ValueType)2, (ValueType)1);

		// Equality operator
		EXPECT_TRUE(va_12 == vb_12);
		EXPECT_TRUE(vb_12 == va_12);
		EXPECT_FALSE(va_12 == vb_21);
		EXPECT_FALSE(vb_12 == va_21);

		// Inequality operator
		EXPECT_FALSE(va_12 != vb_12);
		EXPECT_FALSE(vb_12 != va_12);
		EXPECT_TRUE(va_12 != vb_21);
		EXPECT_TRUE(vb_12 != va_21);
	}

	TYPED_TEST(EngineMathVec2GenericTest, IndexOperator) {
		using ValueType = decltype(TypeParam::x);

		// Index operator
		TypeParam v1((ValueType)1, (ValueType)2);
		EXPECT_EQ((ValueType)1, v1[0]);
		EXPECT_EQ((ValueType)2, v1[1]);
		EXPECT_DEBUG_DEATH(v1[-1], ".*");
		EXPECT_DEBUG_DEATH(v1[2], ".*");

		// Const index operator
		const TypeParam v2((ValueType)1, (ValueType)2);
		EXPECT_EQ((ValueType)1, v2[0]);
		EXPECT_EQ((ValueType)2, v2[1]);
		EXPECT_DEBUG_DEATH(v2[-1], ".*");
		EXPECT_DEBUG_DEATH(v2[2], ".*");
	}

	TYPED_TEST(EngineMathVec2GenericTest, UtilityMethods) {
		using ValueType = decltype(TypeParam::x);

		// hasNaNs
		// Cannot test since it will abort the program
		// In any case, its already tested indirectly in other tests

		// minComponent
		TypeParam v_min1((ValueType)1, (ValueType)2);
		TypeParam v_min2((ValueType)2, (ValueType)1);
		EXPECT_EQ((ValueType)1, v_min1.minComponent());
		EXPECT_EQ((ValueType)1, v_min2.minComponent());
		if constexpr (std::is_signed_v<ValueType>) {
			TypeParam v_min3((ValueType)1, (ValueType)-2);
			EXPECT_EQ((ValueType)-2, v_min3.minComponent());
		}
		if constexpr (std::is_floating_point_v<ValueType>) {
			TypeParam v_min4((ValueType)1.0, (ValueType)1.1);
			EXPECT_EQ((ValueType)1.0, v_min4.minComponent());
		}

		// maxComponent
		TypeParam v_max1((ValueType)1, (ValueType)2);
		TypeParam v_max2((ValueType)2, (ValueType)1);
		EXPECT_EQ((ValueType)2, v_max1.maxComponent());
		EXPECT_EQ((ValueType)2, v_max2.maxComponent());
		if constexpr (std::is_signed_v<ValueType>) {
			TypeParam v_max3((ValueType)1, (ValueType)-2);
			EXPECT_EQ((ValueType)1, v_max3.maxComponent());
		}
		if constexpr (std::is_floating_point_v<ValueType>) {
			TypeParam v_max4((ValueType)1.0, (ValueType)1.1);
			EXPECT_EQ((ValueType)1.1, v_max4.maxComponent());
		}

		// Exclude for unsigned types
		if constexpr (std::is_signed_v<ValueType>) {
			// negated
			TypeParam v_negA((ValueType)1, (ValueType)2);
			TypeParam v_negB = v_negA.negated();
			EXPECT_EQ((ValueType)1, v_negA.x);
			EXPECT_EQ((ValueType)2, v_negA.y);
			EXPECT_EQ((ValueType)-1, v_negB.x);
			EXPECT_EQ((ValueType)-2, v_negB.y);

			// negate
			TypeParam v_negC((ValueType)1, (ValueType)2);
			TypeParam v_negD = v_negC.negate();
			EXPECT_EQ((ValueType)-1, v_negC.x);
			EXPECT_EQ((ValueType)-2, v_negC.y);
			EXPECT_EQ((ValueType)-1, v_negD.x);
			EXPECT_EQ((ValueType)-2, v_negD.y);
		}
		else {
			// For unsigned types, negating fallbacks to the same value (by design)

			// negated
			TypeParam v_negA((ValueType)1, (ValueType)2);
			TypeParam v_negB = v_negA.negated();
			EXPECT_EQ((ValueType)1, v_negA.x);
			EXPECT_EQ((ValueType)2, v_negA.y);
			EXPECT_EQ((ValueType)1, v_negB.x);
			EXPECT_EQ((ValueType)2, v_negB.y);

			// negate
			TypeParam v_negC((ValueType)1, (ValueType)2);
			TypeParam v_negD = v_negC.negate();
			EXPECT_EQ((ValueType)1, v_negC.x);
			EXPECT_EQ((ValueType)2, v_negC.y);
			EXPECT_EQ((ValueType)1, v_negD.x);
			EXPECT_EQ((ValueType)2, v_negD.y);
		}
	}

	/*
	TYPED_TEST(EngineMathVec2GenericTest, AlgebraOperations) {
		using ValueType = decltype(TypeParam::x);
	}
	*/

} // namespace engine::math::vec2
