/**
 * E32-915T-20D Transceiver Interface, 
 * SX1276 Chip, 915MHz, Tx power 20dB, 3Km, 0.3k~19.2k, SMA-K
 */
#ifndef E32-915T-20D_H_
#define E32-915T-20D_H_

typedef enum {
  RET_SUCCESS = 0,
  RET_ERROR_UNKNOWN,	/* something shouldn't happened */
  RET_NOT_SUPPORT,
  RET_NOT_IMPLEMENT,
  RET_NOT_INITIAL,
  RET_INVALID_PARAM,
  RET_DATA_SIZE_NOT_MATCH,
  RET_BUF_TOO_SMALL,
  RET_TIMEOUT,
  RET_HW_ERROR,
} RET_STATUS;

//-- Operating mode ----------------------
//-- Mode         Val   M0  M1
//-- Normal       0     0   0   UART and wireless channel are open, transparent transmission is on
//-- Wakeup       1     1   0   UART and wireless channel are open, wakeup receiver
//-- Power Saving 2     0   1   UART close, wireless is uner air-awaken mode, 
//-- Sleep        3     1   1
enum MODE_TYPE
{
  MODE_0_NORMAL = 0,
  MODE_1_WAKE_UP,
  MODE_2_POWER_SAVIN,
  MODE_3_SLEEP,
  MODE_INIT = 0xFF
};

//-- mode switching
//-- shall be in the new mode in 1 ms after UART transmission completion, when AUX=1
//-- It is recommended to check AUX pin out status and wait 2ms after AUX outputs high level before switching the mode.

enum SLEEP_MODE_CMD_TYPE
{
  W_CFG_PWR_DWN_SAVE = 0xC0,  //-- C0+5 bytes working parameters
  R_CFG              = 0xC1,  //-- C1+C1+C1 : sent in hexa, get saved parameters
  W_CFG_PWR_DWN_LOSE = 0xC2,  //-- C2+5 bytes working parameters, 6 bytes in total
  R_MODULE_VERSION   = 0xC3,  //-- C3+C3+C3 : sent in hexa, version infoation
  W_RESET_MODULE     = 0xC4   //-- C4+C4+C4 : 
};

//-- default parameters: C0 00 00 1A 17 44
//-- MODEL         : E32-915T20D
//-- Frequency     : 915MHz
//-- Address       : 0x00
//-- Channel       : 0x0F
//-- Air data rate : 2.4kbps
//-- Baud rate     : 9600
//-- Parity        : 8N1
//-- Transmitting power : 100mW

//SPED+
//-- bit 7, 6    : UART_PARITY_TYPE
//-- bit 5, 4, 3 : UART_BPS_TYPE
//-- bit 2, 1, 0 : AIR_BPS_TYPE
enum UART_PARITY_TYPE       //-- UART Parity Bit
{
  UART_PARITY_8N1 = 0x00,  /*no   parity bit one stop, default, or 0x11 */
  UART_PARITY_8O1 = 0x01,  /*odd  parity bit one stop*/
  UART_PARITY_8E1 = 0x02   /*even parity bitone stop*/
};

enum UART_BPS_TYPE          //-- TTL UART baud rate (bps)
{
  UART_BPS_1200 = 0x00,
  UART_BPS_2400 = 0x01,
  UART_BPS_4800 = 0x02,
  UART_BPS_9600 = 0x03, //-- default
  UART_BPS_19200 = 0x04,
  UART_BPS_38400 = 0x05,
  UART_BPS_57600 = 0x06,
  UART_BPS_115200 = 0x07
};

//-- The lower the air data rate, the longer the transmitting distance, 
//-- better anti-interference performance and longer transmitting time.
//-- The air data rate must keep the smae for both communication parties
enum AIR_BPS_TYPE           //-- Air data rate 9bps)
{
  AIR_BPS_300   = 0x00,   /* 0.3k */
  AIR_BPS_1200  = 0x01,   /* 1.2k */
  AIR_BPS_2400  = 0x02,   /* 2.4k, default */
  AIR_BPS_4800  = 0x03,   /* 4.8k */
  AIR_BPS_9600  = 0x04,   /* 9.6k */
  AIR_BPS_19200 = 0x05    /* or 0x06, 0x07, 19.2k */
};
//SPED-

//410~441MHz : 410M + CHAN*1M

//-- 00H~1FH, correspond to 900~931MHz
//-- 4~0, channel (900MHz+CHAN*1MHz), default 0FH (915MHz)
enum AIR_CHAN_TYPE
{
  AIR_CHAN_900M = 0x00,
  AIR_CHAN_915M = 0x0F,
  AIR_CHAN_931M = 0x1F
};

// OPTION+
//-- bit 7 : Fixed transmission enabling bit (similar to MODBUS)
#define TRSM_TT_MODE		0x00	/*Transparent Transmission*/
#define TRSM_FP_MODE		0x01	/*Fixed-point transmission mode*/

//-- bit 6 : IO drive mode (default 1)
#define OD_DRIVE_MODE		0x00  /* TXD, AUX open-collector outputs, TXD open-collector input */
#define PP_DRIVE_MODE		0x01  /* TXD and AUX push-pull outputs, RXD pull-up inputs */

//-- bit 5,4,3 : wireless wake-up time
enum WAKE_UP_TIME_TYPE
{
  WAKE_UP_TIME_250  = 0x00,   /* 250ms (default) */
  WAKE_UP_TIME_500  = 0x01,   /* 500ms */
  WAKE_UP_TIME_750  = 0x02,   /* 750ms */
  WAKE_UP_TIME_1000 = 0x03,   /* 1000ms */
  WAKE_UP_TIME_1250 = 0x04,   /* 1250ms */
  WAKE_UP_TIME_1500 = 0x05,   /* 1500ms */
  WAKE_UP_TIME_1750 = 0x06,   /* 1750ms */ 
  WAKE_UP_TIME_2000 = 0x07    /* 2000ms */
};
//-- bit 2 : FEC switch
#define DISABLE_FEC			0x00  /* turn off FEC */
#define ENABLE_FEC			0x01  /* trurn on FEC, default */

//-- bit 1 : Transmit power (approximation)
enum TSMT_PWR_TYPE
{
  TSMT_PWR_20DB = 0x00,       /* 20dBm, default */
  TSMT_PWR_17DB = 0x01,       /* 17dBm */
  TSMT_PWR_14DB = 0x02,       /* 14dBm */
  TSMT_PWR_10DB = 0x03        /* 10dBm */
};
//OPTION-

#pragma pack(push, 1)
struct SPEDstruct {
  uint8_t air_bps : 3; //bit 0-2
  uint8_t uart_bps: 3; //bit 3-5
  uint8_t uart_fmt: 2; //bit 6-7
};

struct OPTIONstruct {
  uint8_t tsmt_pwr    : 2; //bit 0-1
  uint8_t enFWC       : 1; //bit 2
  uint8_t wakeup_time : 3; //bit 3-5
  uint8_t drive_mode  : 1; //bit 6
  uint8_t trsm_mode   : 1; //bit 7
};

struct CFGstruct {
  uint8_t HEAD;
  uint8_t ADDH;
  uint8_t ADDL;
  struct SPEDstruct   SPED_bits;
  uint8_t CHAN;
  struct OPTIONstruct OPTION_bits;
};

struct MVerstruct {
  uint8_t HEAD;
  uint8_t Model;
  uint8_t Version;
  uint8_t features;
};
#pragma pack(pop)


#define Device_A

#define TIME_OUT_CNT	100
#define MAX_TX_SIZE		58

#define DEVICE_A_ADDR_H 0x05
#define DEVICE_A_ADDR_L 0x01
#define DEVICE_B_ADDR_H 0x05
#define DEVICE_B_ADDR_L 0x02

#endif /* E32-915T-20D_H_ */
