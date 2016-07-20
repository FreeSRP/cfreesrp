/*
 * C wrapper for libfreesrp
 */


#ifndef CFREESRP_H
#define CFREESRP_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum status
{
    CFREESRP_SUCCESS = 0,
    CFREESRP_ERR = -1,
    CFREESRP_CONNECTION_ERR = -2,
    CFREESRP_ALREADY_INITED = -3,
    CFREESRP_NOT_CONNECTED = -4,
    CFREESRP_FPGA_SKIPPED = -5,
    CFREESRP_INVALID_CMD = -6
} freesrp_status_t;

typedef enum cmd_id
{
    CFREESRP_GET_REGISTER,
    CFREESRP_GET_TX_LO_FREQ,
    CFREESRP_SET_TX_LO_FREQ,
    CFREESRP_GET_TX_SAMP_FREQ,
    CFREESRP_SET_TX_SAMP_FREQ,
    CFREESRP_GET_TX_RF_BANDWIDTH, 
    CFREESRP_SET_TX_RF_BANDWIDTH,
    CFREESRP_GET_TX_ATTENUATION,
    CFREESRP_SET_TX_ATTENUATION,
    CFREESRP_GET_TX_FIR_EN,
    CFREESRP_SET_TX_FIR_EN,
    CFREESRP_GET_RX_LO_FREQ,
    CFREESRP_SET_RX_LO_FREQ,
    CFREESRP_GET_RX_SAMP_FREQ,
    CFREESRP_SET_RX_SAMP_FREQ,
    CFREESRP_GET_RX_RF_BANDWIDTH,
    CFREESRP_SET_RX_RF_BANDWIDTH,
    CFREESRP_GET_RX_GC_MODE,
    CFREESRP_SET_RX_GC_MODE,
    CFREESRP_GET_RX_RF_GAIN,
    CFREESRP_SET_RX_RF_GAIN,
    CFREESRP_GET_RX_FIR_EN,
    CFREESRP_SET_RX_FIR_EN,
    CFREESRP_SET_DATAPATH_EN,
    CFREESRP_GET_FPGA_VERSION,
    CFREESRP_SET_LOOPBACK_EN
} freesrp_cmd_id_t;

typedef enum cmd_err
{
    CFREESRP_CMD_OK = 0,
    CFREESRP_CMD_INVALID_PARAM,
    CFREESRP_CMD_ENSM_ERR
} freesrp_cmd_err_t;

typedef struct version
{
    char *fx3;
    char *fpga;
} freesrp_version_t;

typedef struct sample
{
    int16_t i;
    int16_t q;
} freesrp_sample_t;

freesrp_status_t freesrp_init();
void freesrp_deinit();

bool freesrp_fpga_loaded();
freesrp_status_t freesrp_load_fpga(char *filename);

freesrp_status_t start_rx();
freesrp_status_t stop_rx();

freesrp_status_t start_tx();
freesrp_status_t stop_tx();

bool freesrp_get_rx_sample(freesrp_sample_t *s);
bool freesrp_submit_tx_sample(freesrp_sample_t *s);

freesrp_status_t freesrp_send_cmd(freesrp_cmd_id_t id, double param, freesrp_cmd_err_t *error, double *new_value);

freesrp_status_t freesrp_version(freesrp_version_t *version);

#ifdef __cplusplus
}
#endif

#endif
