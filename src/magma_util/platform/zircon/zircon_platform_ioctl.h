// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef _ZIRCON_PLATFORM_CONNECTION_H_
#define _ZIRCON_PLATFORM_CONNECTION_H_

#include "zircon/device/ioctl-wrapper.h"
#include "zircon/device/ioctl.h"

#define IOCTL_MAGMA_CONNECT IOCTL(IOCTL_KIND_GET_HANDLE, IOCTL_FAMILY_GPU, 1)
#define IOCTL_MAGMA_QUERY IOCTL(IOCTL_KIND_DEFAULT, IOCTL_FAMILY_GPU, 2)
#define IOCTL_MAGMA_DUMP_STATUS IOCTL(IOCTL_KIND_DEFAULT, IOCTL_FAMILY_GPU, 3)
#define IOCTL_MAGMA_TEST_RESTART IOCTL(IOCTL_KIND_DEFAULT, IOCTL_FAMILY_GPU, 4)
#define IOCTL_MAGMA_DISPLAY_GET_SIZE IOCTL(IOCTL_KIND_DEFAULT, IOCTL_FAMILY_GPU, 5)

#endif // _ZIRCON_PLATFORM_CONNECTION_H_
