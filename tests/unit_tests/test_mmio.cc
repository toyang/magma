// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "magma_util/macros.h"
#include "mock/mock_mmio.h"
#include "gtest/gtest.h"

static void test_mmio(magma::PlatformMmio* mmio, magma::PlatformMmio::CachePolicy cache_policy)
{
    // Verify we can write to and read from the mmio space.
    {
        uint32_t expected = 0xdeadbeef;
        mmio->Write32(expected, 0);
        uint32_t val = mmio->Read32(0);
        EXPECT_EQ(val, expected);

        mmio->Write32(expected, mmio->size() - sizeof(uint32_t));
        val = mmio->Read32(mmio->size() - sizeof(uint32_t));
        EXPECT_EQ(val, expected);
    }

    {
        uint64_t expected = 0xabcddeadbeef1234;
        mmio->Write64(expected, 0);
        uint64_t val = mmio->Read64(0);
        EXPECT_EQ(val, expected);

        mmio->Write64(expected, mmio->size() - sizeof(uint64_t));
        val = mmio->Read64(mmio->size() - sizeof(uint64_t));
        EXPECT_EQ(val, expected);
    }
}

TEST(MagmaUtil, PlatformMmio)
{
    test_mmio(std::unique_ptr<MockMmio>(MockMmio::Create(8)).get(),
              magma::PlatformMmio::CACHE_POLICY_CACHED);
    test_mmio(std::unique_ptr<MockMmio>(MockMmio::Create(16)).get(),
              magma::PlatformMmio::CACHE_POLICY_UNCACHED);
    test_mmio(std::unique_ptr<MockMmio>(MockMmio::Create(64)).get(),
              magma::PlatformMmio::CACHE_POLICY_UNCACHED_DEVICE);
    test_mmio(std::unique_ptr<MockMmio>(MockMmio::Create(1024)).get(),
              magma::PlatformMmio::CACHE_POLICY_WRITE_COMBINING);
}