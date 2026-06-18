/*
Copyright (c) 2026, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>
#include "logging.h"

#include "../i3c_handler.h"

// Wraps
void __wrap_ASD_log(ASD_LogLevel level, ASD_LogStream stream,
                    ASD_LogOption option, const char* format, ...)
{
}

void __wrap_ASD_log_buffer(ASD_LogLevel level, ASD_LogStream stream,
                           ASD_LogOption option, const unsigned char* ptr,
                           size_t len, const char* prefixPtr)
{
}

Dbus_Handle* __wrap_dbus_helper(void)
{
    return (Dbus_Handle*)mock();
}

STATUS __wrap_dbus_initialize(Dbus_Handle* state)
{
    return (STATUS)mock();
}

STATUS __wrap_dbus_deinitialize(Dbus_Handle* state)
{
    return (STATUS)mock();
}

STATUS __wrap_dbus_rel_i3c_ownership(Dbus_Handle* dbus, int token)
{
    return (STATUS)mock();
}

STATUS __wrap_dbus_req_i3c_ownership(Dbus_Handle* dbus, int* token)
{
    return (STATUS)mock();
}

STATUS __wrap_dbus_read_i3c_ownership(Dbus_Handle* dbus, bool* owned)
{
    return (STATUS)mock();
}

int __wrap_sd_bus_get_fd(sd_bus* bus)
{
    return (int)mock();
}

// Tests

void I3CHandler_null_config_returns_null_test(void** state)
{
    (void)state;
    assert_null(I3CHandler(NULL));
}

void i3c_initialize_null_returns_err_test(void** state)
{
    (void)state;
    assert_int_equal(ST_ERR, i3c_initialize(NULL));
}

void i3c_deinitialize_null_returns_err_test(void** state)
{
    (void)state;
    assert_int_equal(ST_ERR, i3c_deinitialize(NULL));
}

int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(I3CHandler_null_config_returns_null_test),
        cmocka_unit_test(i3c_initialize_null_returns_err_test),
        cmocka_unit_test(i3c_deinitialize_null_returns_err_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
