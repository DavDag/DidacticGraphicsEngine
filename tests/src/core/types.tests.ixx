module;
#include <gtest/gtest.h>
export module engine.core.types.tests;

import engine.core.types;

namespace engine::core::types
{
    // Type sizes are checked using static_asserts
    // Type properties are checked using static_asserts
    // Constants are computed using std::numeric_limits

    TEST(EngineCoreTypes, IsNanCorrectlyReportNanValues)
    {
        // Normal values
        EXPECT_FALSE(IsNan(0.0));
        EXPECT_FALSE(IsNan(0.0f));
        EXPECT_FALSE(IsNan(-2.1));
        EXPECT_FALSE(IsNan(-2.1f));
        EXPECT_FALSE(IsNan(5.7));
        EXPECT_FALSE(IsNan(5.7f));

        // Infinity
        EXPECT_FALSE(IsNan(std::numeric_limits<f32>::infinity()));
        EXPECT_FALSE(IsNan(std::numeric_limits<f64>::infinity()));
        EXPECT_FALSE(IsNan(-std::numeric_limits<f32>::infinity()));
        EXPECT_FALSE(IsNan(-std::numeric_limits<f64>::infinity()));

        // Quiet NaNs
        auto qnanf32 = std::numeric_limits<f32>::quiet_NaN();
        auto qnanf64 = std::numeric_limits<f64>::quiet_NaN();
        EXPECT_TRUE(IsNan(qnanf32));
        EXPECT_TRUE(IsNan(qnanf64));

        // Signaling NaNs
        auto snanf32 = std::numeric_limits<f32>::signaling_NaN();
        auto snanf64 = std::numeric_limits<f64>::signaling_NaN();
        EXPECT_TRUE(IsNan(snanf32));
        EXPECT_TRUE(IsNan(snanf64));

        // Limits
        EXPECT_FALSE(IsNan(F32_MIN));
        EXPECT_FALSE(IsNan(F64_MIN));
        EXPECT_FALSE(IsNan(F32_MAX));
        EXPECT_FALSE(IsNan(F64_MAX));
        EXPECT_FALSE(IsNan(F32_EPSILON));
        EXPECT_FALSE(IsNan(F64_EPSILON));

        // Integers
        EXPECT_FALSE(IsNan(0));
        EXPECT_FALSE(IsNan(7));
        EXPECT_FALSE(IsNan(-19));
    }
} // namespace engine::core::types
