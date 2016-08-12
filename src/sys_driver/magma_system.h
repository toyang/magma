// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef _MAGMA_SYSTEM_H_
#define _MAGMA_SYSTEM_H_

#include <msd_defs.h>

class MagmaSystemConnection;

// Opens a device - triggered by a client action. returns null on failure
MagmaSystemConnection* magma_system_open(uint32_t device_handle);
void magma_system_close(MagmaSystemConnection* connection);

// Returns the device id.  0 is an invalid device id.
uint32_t magma_system_get_device_id(MagmaSystemConnection* connection);

bool magma_system_create_context(MagmaSystemConnection* connection, uint32_t* context_id);
bool magma_system_destroy_context(MagmaSystemConnection* connection, uint32_t context_id);

bool magma_system_alloc(MagmaSystemConnection* connection, uint64_t size, uint64_t* size_out,
                        uint32_t* handle_out);
bool magma_system_free(MagmaSystemConnection* connection, uint32_t handle);

bool magma_system_set_tiling_mode(MagmaSystemConnection* connection, uint32_t handle,
                                  uint32_t tiling_mode);

bool magma_system_map(MagmaSystemConnection* connection, uint32_t handle, void** paddr);
bool magma_system_unmap(MagmaSystemConnection* connection, uint32_t handle, void* addr);

bool magma_system_set_domain(MagmaSystemConnection* connection, uint32_t handle, uint32_t read_domains,
                             uint32_t write_domain);

bool magma_system_execute_buffer(MagmaSystemConnection* connection, struct MagmaExecBuffer* execbuffer);

void magma_system_wait_rendering(MagmaSystemConnection* connection, uint32_t handle);

#endif /* _MAGMA_SYSTEM_H_ */