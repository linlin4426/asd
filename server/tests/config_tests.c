/*
Copyright (c) 2019, Intel Corporation

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

#include <getopt.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <syslog.h>

#include "config.h"
#include "logging.h"
#include "cmocka.h"

// static char temporary_log_buffer[512];
void __wrap_ASD_log(ASD_LogLevel level, ASD_LogStream stream,
                    ASD_LogOption options, const char* format, ...)
{
    (void)level;
    (void)stream;
    (void)options;
    (void)format;
    // va_list args;
    // va_start(args, format);
    // vsnprintf(temporary_log_buffer, sizeof(temporary_log_buffer), format,
    // args);
    // fprintf(stderr, "%s\n", temporary_log_buffer);
    // va_end(args);
}

void set_config_defaults_failed_test(void** state)
{
    config config_obj;
    bus_options busopt;
    timeout_config tmo_cfg;
    assert_int_equal(set_config_defaults(NULL, NULL, NULL), ST_ERR);
    assert_int_equal(set_config_defaults(NULL, &busopt, &tmo_cfg), ST_ERR);
    assert_int_equal(set_config_defaults(&config_obj, NULL, &tmo_cfg), ST_ERR);
    assert_int_equal(set_config_defaults(&config_obj, &busopt, NULL), ST_ERR);
}

void set_config_defaults_enabled_i2c_test(void** state)
{
    config config_obj;
    bus_options busopt;
    timeout_config tmo_cfg;
    memset(&busopt, 0, sizeof(busopt));
    memset(&tmo_cfg, 0, sizeof(tmo_cfg));
    busopt.enable_i2c = true;
    busopt.bus = 4;
    busopt.bus_config_type[4] = BUS_CONFIG_I2C;

    STATUS status = set_config_defaults(&config_obj, &busopt, &tmo_cfg);
    assert_int_equal(status, ST_OK);
    assert_true(config_obj.buscfg.enable_i2c);
    assert_int_equal(config_obj.buscfg.default_bus, 4);
    for (int i = 0; i < MAX_IxC_BUSES + MAX_SPP_BUSES; i++)
    {
        if (i == 4)
            assert_int_equal(config_obj.buscfg.bus_config_type[i], BUS_CONFIG_I2C);
        else
            assert_int_equal(config_obj.buscfg.bus_config_type[i], BUS_CONFIG_NOT_ALLOWED);
    }
}

int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(set_config_defaults_failed_test),
        cmocka_unit_test(set_config_defaults_enabled_i2c_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
