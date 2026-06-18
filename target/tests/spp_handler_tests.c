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

#include "../spp_handler.h"
#include "../i3c_debug_handler.h"

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

ssize_t __wrap_receive_i3c(SPP_Handler* state, i3c_cmd* cmd)
{
    return (ssize_t)mock();
}

STATUS __wrap_send_i3c_action(SPP_Handler* state, i3c_cmd* cmd)
{
    return (STATUS)mock();
}

STATUS __wrap_send_i3c_opcode(SPP_Handler* state, i3c_cmd* cmd)
{
    return (STATUS)mock();
}

STATUS __wrap_send_i3c_cmd(SPP_Handler* state, i3c_cmd* cmd)
{
    return (STATUS)mock();
}

// Tests

void SPPHandler_null_config_returns_null_test(void** state)
{
    (void)state;
    assert_null(SPPHandler(NULL));
}

void spp_initialize_null_returns_err_test(void** state)
{
    (void)state;
    assert_int_equal(ST_ERR, spp_initialize(NULL));
}

void spp_deinitialize_null_returns_err_test(void** state)
{
    (void)state;
    assert_int_equal(ST_ERR, spp_deinitialize(NULL));
}

int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(SPPHandler_null_config_returns_null_test),
        cmocka_unit_test(spp_initialize_null_returns_err_test),
        cmocka_unit_test(spp_deinitialize_null_returns_err_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
