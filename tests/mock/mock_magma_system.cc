// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "magma_system.h"
#include "magma_util/dlog.h"

magma_system_connection* magma_system_open(uint32_t device_handle)
{
    return new magma_system_connection();
}

void magma_system_close(magma_system_connection* connection) { delete connection; }

// Returns the device id.  0 is an invalid device id.
uint32_t magma_system_get_device_id(magma_system_connection* connection) { return 0; }

uint32_t next_context_id;
bool magma_system_create_context(magma_system_connection* connection, uint32_t* context_id_out)
{
    *context_id_out = next_context_id++;
    return true;
}

bool magma_system_destroy_context(magma_system_connection* connection, uint32_t context_id)
{
    return true;
}

uint32_t next_handle;
bool magma_system_alloc(magma_system_connection* connection, uint64_t size, uint64_t* size_out,
                        uint32_t* handle_out)
{
    *size_out = size;
    *handle_out = next_handle++;
    return true;
}

bool magma_system_free(magma_system_connection* connection, uint32_t handle) { return true; }

bool magma_system_set_tiling_mode(magma_system_connection* connection, uint32_t handle,
                                  uint32_t tiling_mode)
{
    return true;
}

bool magma_system_map(magma_system_connection* connection, uint32_t handle, void** paddr)
{
    return true;
}

bool magma_system_unmap(magma_system_connection* connection, uint32_t handle, void* addr)
{
    return true;
}

bool magma_system_set_domain(magma_system_connection* connection, uint32_t handle,
                             uint32_t read_domains, uint32_t write_domain)
{
    return true;
}

bool magma_system_submit_command_buffer(struct magma_system_connection* connection,
                                        struct magma_system_command_buffer* command_buffer,
                                        uint32_t context_id)
{
    return true;
}

void magma_system_wait_rendering(magma_system_connection* connection, uint32_t handle)
{
    DLOG("TODO: magma_system_wait_rendering");
}