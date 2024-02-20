/*
 * rnic_adapter.h
 */

#ifndef RNIC_ADAPTER_H
#define RNIC_ADAPTER_H

#include <linux/list.h>
#include <linux/skbuff.h>

#define TRANSMIT_SHIFT	(10)
#define TRANSMIT_BUFFER_SIZE	(1UL << TRANSMIT_SHIFT)
#define TRANSMIT_MAX_SIZE     ((1UL << TRANSMIT_SHIFT)  - 4)
#define SDIO_SLAVE_ETH_F_BIT            0x20	/* bit[5] of TranHi is for First Segment Indicator */
#define SDIO_SLAVE_ETH_M_BIT            0x10	/* bit[4] of TranHi is for More Segment Indicator */

#define SDIO_HEAD_SIZE          (5)
#define SEND_BLOCK_SIZE        (512  - 4)
#define SDIO_HEAD_MAX_INDEX         (SDIO_HEAD_SIZE - 1)
#define DATA_CHANEL_ID          (15)

struct rnic_buf_in_packet {
	struct list_head node;
	unsigned char id;
	struct sk_buff *buffer;
};

struct sdio_read_func {
	unsigned char ucPDNId;
	unsigned long (*cbp_read_buff) (unsigned char ucPDNId,
					struct sk_buff *pstData);
};

typedef unsigned long (*RCV_C_DL_DATA_FUNC) (unsigned char ucPDNId,
					     struct sk_buff *pstData);

/* It is defined in Balong RNIC driver, The struct of the Config, the lenth of this Struct is 8.
typedef struct
{
    RNIC_MODEM_TYPE_ENUM_UINT8          enModemType;
    unsigned char                       ucRmNetId;
    unsigned short                      usModemId;
    unsigned char                       ucPdnId;
    unsigned char                       ucRabId;
    RNIC_RMNET_STATUS_ENUM_UINT8        enRmnetStatus;
    RNIC_IP_TYPE_ENUM_UINT8             enIpType;
}RNIC_RMNET_CONFIG_STRU;
*/

/*Copy from balong RNIC*/
enum RNIC_RESULT_ENUM {
	RNIC_OK = 0,		/* ???????? */
	RNIC_NOTSTARTED = 1,	/* ?????? */
	RNIC_INPROGRESS = 2,	/* ?????? */
	RNIC_PERM = 3,
	RNIC_NOENT = 4,
	RNIC_IO = 5,
	RNIC_NXIO = 6,
	RNIC_NOMEM = 7,		/* ???????????? */
	RNIC_BUSY = 8,		/* RNIC?????????? */
	RNIC_NODEV = 9,		/* ?????? */
	RNIC_INVAL = 10,	/* ???????? */
	RNIC_NOTSUPP = 11,	/* ?????????? */
	RNIC_TIMEDOUT = 12,	/* ???? */
	RNIC_SUSPENDED = 13,	/* ???? */
	RNIC_UNKNOWN = 14,	/* ???????? */
	RNIC_TEST_FAILED = 15,	/* ???????? */
	RNIC_STATE = 16,	/* ???????? */
	RNIC_STALLED = 17,	/* ???? */
	RNIC_PARAM = 18,	/* ???????? */
	RNIC_ABORTED = 19,	/* ???????? */
	RNIC_SHORT = 20,	/* ???????? */
	RNIC_EXPIRED = 21,	/* ???? */

	RNIC_ADDR_INVALID = 22,	/* ???????????? */
	RNIC_OUT_RANGE = 23,	/* ?????????????? */
	RNIC_ERROR = 0xff,	/* RNIC???????? */
	RNIC_BUTT
};

typedef struct RnicDataFrame {
	struct list_head list_head_node;
	unsigned int list_size;
	spinlock_t slock;
	struct mutex m_mutex;
	wait_queue_head_t wait;
} tRnicDataFrame;

void rnic_read_packet(unsigned char *buffer, unsigned int datalen,
		      unsigned char tranHi);
void rnic_txrx_init(void);

#endif
