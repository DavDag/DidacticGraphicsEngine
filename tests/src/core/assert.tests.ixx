module;
#include <gtest/gtest.h>
#include <gmock/gmock.h>
export module engine.core.assert.tests;

import engine.core.assert;

namespace engine::core::assert
{
    TEST(EngineCoreAssert, AssertionShouldAbortOnConditionNotMet)
    {
        // Intercept std::err
        std::stringstream bufferCErr;
        std::streambuf* oldCErr = std::cerr.rdbuf(bufferCErr.rdbuf());

        EXPECT_THROW(
            Assert(false, "This should abort <always>"),
            AssertException
        );
#ifndef NDEBUG
        EXPECT_THROW(
            DebugAssert(false, "This should abort <debug>"),
            AssertException
        );
#endif // !NDEBUG

        // Ensure output to std::err
        EXPECT_THAT(bufferCErr.str(), ::testing::HasSubstr("This should abort <always>"));
#ifndef NDEBUG
        EXPECT_THAT(bufferCErr.str(), ::testing::HasSubstr("This should abort <debug>"));
#endif // !NDEBUG

        // Restore std::err
        std::cerr.rdbuf(oldCErr);
    }

    TEST(EngineCoreAssert, AssertionShouldNotAbortOnConditionMet)
    {
        // Intercept std::err
        std::stringstream bufferCErr;
        std::streambuf* oldCErr = std::cerr.rdbuf(bufferCErr.rdbuf());

        EXPECT_NO_THROW(
            Assert(true, "This should not abort <always>")
        );
#ifndef NDEBUG
        EXPECT_NO_THROW(
            DebugAssert(true, "This should not abort <debug>")
        );
#endif // !NDEBUG

        // Ensure no output to std::err
        EXPECT_THAT(bufferCErr.str(), ::testing::IsEmpty());

        // Restore std::err
        std::cerr.rdbuf(oldCErr);
    }

    TEST(EngineCoreAssert, AssertionExceptionShouldContainMessage)
    {
        // Intercept std::err
        const std::stringstream bufferCErr;
        std::streambuf* oldCErr = std::cerr.rdbuf(bufferCErr.rdbuf());

        try
        {
            Assert(false, "This should abort <always>");
        }
        catch (const AssertException& e)
        {
            EXPECT_THAT(e.what(), ::testing::HasSubstr("This should abort <always>"));
        }

#ifndef NDEBUG
        try
        {
            DebugAssert(false, "This should abort <debug>");
        }
        catch (const AssertException& e)
        {
            EXPECT_THAT(e.what(), ::testing::HasSubstr("This should abort <debug>"));
        }
#endif // !NDEBUG

        // Restore std::err
        std::cerr.rdbuf(oldCErr);
    }
} // namespace engine::core::assert
