/*
 * Stubs for functions called by asd_msg.c that are not part of
 * the asd_msg_tests build. These provide link-time resolution
 * without pulling in the full implementation source files.
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include "asd_common.h"
#include "logging.h"
#include "../i3c_handler.h"
#include "../spp_handler.h"
#include "../vprobe_handler.h"
#include "../target_handler.h"
#include "../asd_msg.h"
#include "asd_server_interface.h"
#include "../i2c_handler.h"

/* Handler constructors - return malloc'd dummies so asd_msg_free can free them */
I3C_Handler* I3CHandler(bus_config* config)
{
    (void)config;
    return (I3C_Handler*)malloc(sizeof(I3C_Handler));
}

SPP_Handler* SPPHandler(bus_config* config)
{
    (void)config;
    return (SPP_Handler*)malloc(sizeof(SPP_Handler));
}

vProbe_Handler* vProbeHandler(void)
{
    return (vProbe_Handler*)malloc(sizeof(vProbe_Handler));
}

STATUS vProbe_deinitialize(vProbe_Handler* state)
{
    (void)state;
    return ST_OK;
}

STATUS vProbe_initialize(vProbe_Handler* state)
{
    (void)state;
    return ST_OK;
}

/* Bus flock functions */
extern STATUS FLOCK_RESULT[];
extern int flock_cmd_index;
int flock_cmd_index = 0;

STATUS i2c_bus_flock(I2C_Handler* state, uint8_t bus, int op)
{
    (void)state; (void)bus; (void)op;
    return FLOCK_RESULT[flock_cmd_index++] == 0 ? ST_OK : ST_ERR;
}

STATUS i3c_bus_flock(I3C_Handler* state, uint8_t bus, int op)
{
    (void)state; (void)bus; (void)op;
    return ST_OK;
}

STATUS spp_bus_flock(SPP_Handler* state, uint8_t bus, int op)
{
    (void)state; (void)bus; (void)op;
    return ST_OK;
}

/* I3C functions */
STATUS i3c_initialize(I3C_Handler* state)
{
    (void)state;
    return ST_OK;
}

STATUS i3c_deinitialize(I3C_Handler* state)
{
    (void)state;
    return ST_OK;
}

STATUS i3c_bus_select(I3C_Handler* state, uint8_t bus)
{
    (void)state; (void)bus;
    return ST_OK;
}

STATUS i3c_set_sclk(I3C_Handler* state, uint16_t sclk)
{
    (void)state; (void)sclk;
    return ST_OK;
}

STATUS i3c_read_write(I3C_Handler* state, void* msg_set)
{
    (void)state; (void)msg_set;
    return ST_OK;
}

/* SPP functions */
STATUS spp_initialize(SPP_Handler* state)
{
    (void)state;
    return ST_OK;
}

STATUS spp_deinitialize(SPP_Handler* state)
{
    (void)state;
    return ST_OK;
}

STATUS spp_device_select(SPP_Handler* state, uint8_t dev)
{
    (void)state; (void)dev;
    return ST_OK;
}

STATUS spp_send(SPP_Handler* state, uint16_t size, uint8_t* write_buffer)
{
    (void)state; (void)size; (void)write_buffer;
    return ST_OK;
}

STATUS spp_receive(SPP_Handler* state, uint16_t* size, uint8_t* read_buffer)
{
    (void)state; (void)size; (void)read_buffer;
    return ST_OK;
}

STATUS spp_send_cmd(SPP_Handler* state, spp_command_t cmd, uint16_t size,
                    uint8_t* write_buffer)
{
    (void)state; (void)cmd; (void)size; (void)write_buffer;
    return ST_OK;
}

STATUS spp_send_receive_cmd(SPP_Handler* state, spp_command_t cmd,
                            uint16_t wsize, uint8_t* write_buffer,
                            const uint16_t* rsize, uint8_t* read_buffer)
{
    (void)state; (void)cmd; (void)wsize; (void)write_buffer;
    (void)rsize; (void)read_buffer;
    return ST_OK;
}

STATUS spp_set_sim_data_cmd(SPP_Handler* state, uint16_t size,
                            uint8_t* read_buffer)
{
    (void)state; (void)size; (void)read_buffer;
    return ST_OK;
}

STATUS spp_bus_select(SPP_Handler* state, uint8_t bus)
{
    (void)state; (void)bus;
    return ST_OK;
}

STATUS spp_set_sclk(SPP_Handler* state, uint16_t sclk)
{
    (void)state; (void)sclk;
    return ST_OK;
}

STATUS spp_bus_get_device_map(SPP_Handler* state, uint32_t* device_mask)
{
    (void)state; (void)device_mask;
    return ST_OK;
}

/* Target SPP functions */
STATUS target_get_spp_fds(Target_Control_Handle* state, struct pollfd* fds,
                          int* num_fds)
{
    (void)state; (void)fds; (void)num_fds;
    return ST_OK;
}

bool check_spp_auto_cmd_event(ASD_EVENT event, ASD_EVENT_DATA event_data)
{
    (void)event; (void)event_data;
    return false;
}

bool check_spp_prdy_event(ASD_EVENT event, ASD_EVENT_DATA event_data)
{
    (void)event; (void)event_data;
    return false;
}

STATUS on_power_event(Target_Control_Handle* state, ASD_EVENT* event)
{
    (void)state; (void)event;
    return ST_OK;
}

STATUS on_power2_event(Target_Control_Handle* state, ASD_EVENT* event)
{
    (void)state; (void)event;
    return ST_OK;
}

void target_chain_select_delay(Target_Control_Handle* state)
{
    (void)state;
}

/* vProbe / disconnect */
STATUS disconnect(SPP_Handler* state)
{
    (void)state;
    return ST_OK;
}

/* ASD API server functions - bridge to test infrastructure */
extern struct asd_message msg_sent;
extern STATUS FakeSendFunctionResult;
extern unsigned char FakeReadFunctionBuffer[];
extern int FakeReadFunctionNumBytesPerRead;
extern int FakeReadFunctionNumBytesReadIndex;
extern bool FakeReadFunctionDataPending;
extern STATUS FakeReadFunctionResult;

size_t asd_api_server_read(unsigned char* buffer, size_t length, void* opt)
{
    (void)opt;
    size_t number_to_provide = length;
    if (FakeReadFunctionResult != ST_OK)
        return 0;
    if (FakeReadFunctionNumBytesPerRead >= 0)
        number_to_provide = (size_t)FakeReadFunctionNumBytesPerRead;
    if (number_to_provide > length)
        number_to_provide = length;
    for (size_t i = 0; i < number_to_provide; i++)
        ((unsigned char*)buffer)[i] =
            FakeReadFunctionBuffer[FakeReadFunctionNumBytesReadIndex + i];
    FakeReadFunctionNumBytesReadIndex += (int)number_to_provide;
    return number_to_provide;
}

size_t asd_api_server_write(void* buffer, size_t length, void* opt)
{
    (void)opt;
    /* Always capture the message for test inspection */
    memcpy(&msg_sent.header, buffer, sizeof(struct message_header));
    if (length > sizeof(struct message_header))
        memcpy(msg_sent.buffer,
               (unsigned char*)buffer + sizeof(struct message_header),
               length - sizeof(struct message_header));
    if (FakeSendFunctionResult != ST_OK)
        return 0;
    return length;
}

STATUS asd_api_server_ioctl(void* input, void* output, unsigned int cmd)
{
    (void)input;
    if (cmd == IOCTL_SERVER_IS_DATA_PENDING && output)
    {
        *(bool*)output = FakeReadFunctionDataPending;
    }
    return ST_OK;
}

/* Remote logging functions */
bool is_auto_sync_remote_logging_enabled(void)
{
    return false;
}

ASD_LogLevel convert_remote_log_level(uint8_t remote_level)
{
    (void)remote_level;
    return ASD_LogLevel_Off;
}

ASD_LogStream get_auto_sync_remote_logging_streams(void)
{
    return ASD_LogStream_None;
}

void ASD_update_log_settings(ASD_LogLevel level, ASD_LogStream stream)
{
    (void)level; (void)stream;
}

/* flock_i2c - called from test file, delegates to dev_flock */
extern STATUS dev_flock(uint8_t bus, int op);
STATUS flock_i2c(ASD_MSG* state, int op)
{
    return dev_flock(state->buscfg->default_bus, op);
}
