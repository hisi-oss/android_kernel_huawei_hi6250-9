

#ifndef __PLATFORM_SPEC_1151_H__
#define __PLATFORM_SPEC_1151_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_types.h"

/*****************************************************************************
  2 ??????
*****************************************************************************/
/*****************************************************************************
  1.1.1 ????spec
*****************************************************************************/
/* ???????? */
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
/* hi1151V100H */
#define WLAN_CHIP_VERSION_HI1151V100H           0x11510100
#else
/* hi1151V100H */
#define WLAN_CHIP_VERSION_HI1151V100H           0x11510100
#endif
/* hi1151V100L */
#define WLAN_CHIP_VERSION_HI1151V100L           0x11510102

/*????Host??Device??????????????1151??????????????????????????????????????????????????*/
#define IS_HOST 1
#define IS_DEVICE 1

/*****************************************************************************
  1.1.2 ??Core????spec
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    #define WLAN_FRW_MAX_NUM_CORES          2   /* CORE?????? */
#else
    #define WLAN_FRW_MAX_NUM_CORES          1
#endif

/*****************************************************************************
  2.1 WLAN??????????spec
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DOUBLE_CHIP
#define WLAN_CHIP_MAX_NUM_PER_BOARD                 2              /* ??????board??chip???? */
#else
#define WLAN_CHIP_MAX_NUM_PER_BOARD                 1              /* ??????board??chip???? */
#endif

/* ????????????2G chip id??0??5G chip id??1 */
#define WLAN_CHIP_PCIE0_ID                          0
#define WLAN_CHIP_PCIE1_ID                          1

// ??????2G??????????????????:????CHIP ID??band??????????????????
#ifdef _PRE_WLAN_FEATURE_SINGLE_CHIP_SINGLE_BAND
#define WLAN_SINGLE_CHIP_ID 0
#define WLAN_SINGLE_CHIP_SINGLE_BAND_WORK_BAND   WLAN_BAND_2G
#endif

#define WLAN_DEVICE_MAX_NUM_PER_CHIP                1                       /* ????chip????device????????????????????????8?? */
#define WLAN_SERVICE_DEVICE_MAX_NUM_PER_CHIP        WLAN_DEVICE_MAX_NUM_PER_CHIP /* ????chip????????device?????????? */

/* ????BOARD????????????device?? */
#define WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC            (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP)

/* ????BOARD????????????????device???? */
#define WLAN_SERVICE_DEVICE_SUPPORT_MAX_NUM_SPEC    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_SERVICE_DEVICE_MAX_NUM_PER_CHIP)


#ifdef _PRE_WLAN_PRODUCT_1151V200
#if(_PRE_TARGET_PRODUCT_TYPE_5630HERA == _PRE_CONFIG_TARGET_PRODUCT)
#define WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE      3   /* AP????????5630??????????????????AP????*/
#define WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE     1    /* STA?????? */
#else
#define WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE      16   /* AP????????????????WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE????*/
#define WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE     3    /* STA?????? */
#endif
#else
#define WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE      4   /* AP????????????????WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE????*/
#define WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE     1   /* STA?????? */
#endif

#define WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE      1   /* ????VAP????,????????device???? */
#ifdef _PRE_WLAN_PRODUCT_1151V200
#if(_PRE_TARGET_PRODUCT_TYPE_5630HERA == _PRE_CONFIG_TARGET_PRODUCT)
#define WLAN_AP_STA_COEXIST_VAP_NUM             4   /* ap sta??????vap???? 1??STA 3??AP */
#else
#define WLAN_AP_STA_COEXIST_VAP_NUM             19   /* ap sta??????vap???? 3??STA 16??AP */
#endif
#else
#define WLAN_AP_STA_COEXIST_VAP_NUM             5    /* ap sta??????vap???? 1??STA 4??AP */
#endif

/* PROXY STA??????VAP?????????? */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define WLAN_PROXY_STA_MAX_NUM_PER_DEVICE             15   /* PROXY STA?????? */
#else
#define WLAN_PROXY_STA_MAX_NUM_PER_DEVICE             0    /* PROXY STA????????0 */
#endif

/* ????device????????????????VAP???? */
#define WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE    (WLAN_PROXY_STA_MAX_NUM_PER_DEVICE + WLAN_AP_STA_COEXIST_VAP_NUM)        /* ????VAP???? */

/* ????device????????????VAP???? */
#define WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT      (WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE) /* 21??:4??ap,1??sta,15??proxysta,1??????vap */

/* ????BOARD????????????VAP???? */
#define WLAN_VAP_SUPPORT_MAX_NUM_LIMIT      (WLAN_SERVICE_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT)  /* device????*21??:1??ap,1??sta,15??proxysta,1??????vap */

/* ????BOARD??????????????VAP?????? */
#define WLAN_SERVICE_VAP_SUPPORT_MAX_NUM_LIMIT    (WLAN_SERVICE_DEVICE_SUPPORT_MAX_NUM_SPEC * (WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT - WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE)) /* device????*20??:4??ap,1??sta,15??proxysta */

/* ??????????????????????: WLAN_ASSOC_USER_MAX_NUM????g_us_assoc_max_user??WLAN_ACTIVE_USER_MAX_NUM????g_us_active_max_user */
/* ?????????????????? */
#ifdef _PRE_WLAN_FEATURE_USER_EXTEND
#define WLAN_ASSOC_USER_MAX_NUM       128    /* ?????????????????? */
#else
#define WLAN_ASSOC_USER_MAX_NUM       32     /* ?????????????????? */
#endif

/* ?????????????????? */
#define WLAN_ACTIVE_USER_MAX_NUM      32

/* ???????????????? */
#define WLAN_ACTIVE_USER_IDX_BMAP_LEN       ((WLAN_ACTIVE_USER_MAX_NUM + 7)>> 3)
 /* ???????????????? */
#define WLAN_ASSOC_USER_IDX_BMAP_LEN       ((WLAN_ASSOC_USER_MAX_NUM + 7)>> 3)
 /* ????????RA LUT IDX */
#define WLAN_INVALID_RA_LUT_IDX             WLAN_ACTIVE_USER_MAX_NUM

/* ??????????????????????????????????????; ????????????MAC_RES_XXX(????????RES_XXX)????????????????????WLAN_ASSOC_USER_MAX_NUM??g_us_assoc_max_user */
/* ????????:????????????oal oam hal??????????????????????????????????mac res????????????????????board user???????????????????????????????? */
/*board?????????????? = 1??CHIP???????????????????? * board??????CHIP????*/
#define WLAN_ASOC_USER_MAX_NUM_LIMIT       (WLAN_ASSOC_USER_MAX_NUM * WLAN_CHIP_MAX_NUM_PER_BOARD)

/* board?????????? */
#define WLAN_MULTI_USER_MAX_NUM_LIMIT      (WLAN_SERVICE_VAP_SUPPORT_MAX_NUM_LIMIT)

/*board?????????? = ?????????????? + ???????????? */
#define WLAN_USER_MAX_USER_LIMIT           (WLAN_ASOC_USER_MAX_NUM_LIMIT + WLAN_MULTI_USER_MAX_NUM_LIMIT)

/* alg????????????,????user index, 1151 user????active + noactive user????????assoc id??index */
#define WLAN_ALG_ASOC_USER_NUM_LIMIT       (WLAN_USER_MAX_USER_LIMIT)

/*****************************************************************************
  2.2 WLAN??????????spec
*****************************************************************************/

/*****************************************************************************
  2.3 oam??????spec
*****************************************************************************/
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) || (_PRE_OS_VERSION_WINDOWS == _PRE_OS_VERSION))
#define WLAN_OAM_FILE_PATH      "C:\\OAM.log"                   /* WIN32??WINDOWS??,LOG?????????????????? */
#elif ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION))
#define WLAN_OAM_FILE_PATH      "\\home\\oam.log"               /* LINUX??????????,LOG?????????????????? */
#endif

/*****************************************************************************
  2.4 mem??????spec
*****************************************************************************/
/*****************************************************************************
  2.4.1
*****************************************************************************/

#define WLAN_MEM_MAX_BYTE_LEN               (32100 + 1)   /* ???????????????????? */
#define WLAN_MEM_MAX_SUBPOOL_NUM            8             /* ???????????????????????? */
#define WLAN_MEM_MAX_USERS_NUM              4             /* ?????????????????????????? */

/*****************************************************************************
  2.4.2 ????????????????????????
*****************************************************************************/
#if (_PRE_TARGET_PRODUCT_TYPE_ONT == _PRE_CONFIG_TARGET_PRODUCT)
#define WLAN_TID_MPDU_NUM_BIT               11
#else
#define WLAN_TID_MPDU_NUM_BIT               10
#endif
/* ????device????TID??????MPDU??????????????1024???????????????????????????? */
#define WLAN_TID_MPDU_NUM_LIMIT             (1 << WLAN_TID_MPDU_NUM_BIT)

#ifdef _PRE_WLAN_PRODUCT_1151V200
#define WLAN_MEM_SHARED_RX_DSCR_SIZE        88             /*??????????????????????????????????????????????????????????*/
#else
#define WLAN_MEM_SHARED_RX_DSCR_SIZE        64
#endif
#define WLAN_MEM_SHARED_RX_DSCR_CNT         (576 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ????512(????????????) + 64(????????????) */ /* ????! ??????????????????????oal_mem.c????OAL_MEM_BLK_TOTAL_CNT */
#define WLAN_MEM_SHARED_TX_DSCR_SIZE1       128            /*??????????????????????????????????????????????????????????*/
#define WLAN_MEM_SHARED_TX_DSCR_CNT1        ((WLAN_TID_MPDU_NUM_LIMIT * 2) * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ??????????512 */
#define WLAN_MEM_SHARED_TX_DSCR_SIZE2       256                          /*??????????????????????????????????????????????????????????*/
#if (_PRE_TARGET_PRODUCT_TYPE_ONT == _PRE_CONFIG_TARGET_PRODUCT)
#define WLAN_MEM_SHARED_TX_DSCR_CNT2        (1024 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#else
#define WLAN_MEM_SHARED_TX_DSCR_CNT2        (256 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ????amsdu???????? */
#endif

/*****************************************************************************
  2.4.3 ????????????????????????
*****************************************************************************/
#define WLAN_MEM_SHARED_MGMT_PKT_SIZE1      1300
#ifdef _PRE_WLAN_PRODUCT_1151V200
#define WLAN_MEM_SHARED_MGMT_PKT_CNT1       (WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE * 2 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* 16??AP */
#else
#define WLAN_MEM_SHARED_MGMT_PKT_CNT1       (8 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#endif

/*****************************************************************************
  2.4.4 ????????????????????????
*****************************************************************************/
#define WLAN_MEM_SHARED_DATA_PKT_SIZE       44              /* 80211mac???????? */
#define WLAN_MEM_SHARED_DATA_PKT_CNT        ((256 + 1024) * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* skb(??????????????) + ??????????????(??????????????) 768 */

/*****************************************************************************
  2.4.5 ??????????????????
*****************************************************************************/
#define WLAN_MEM_LOCAL_SIZE1                32

#ifdef _PRE_WLAN_FEATURE_USER_EXTEND
#define WLAN_MEM_LOCAL_CNT1                 (2320 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* 1024(128*8)??dmac_alg_tid_stru + 1024??alg_tid_entry_stru + 5??????????(NON_RESET_ERR)*/
#else
#define WLAN_MEM_LOCAL_CNT1                 (580 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* 256(32*8)??dmac_alg_tid_stru + 256??alg_tid_entry_stru + 5??????????(NON_RESET_ERR)*/
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define WLAN_MEM_LOCAL_SIZE2                140

#ifdef _PRE_WLAN_FEATURE_USER_EXTEND
#define WLAN_MEM_LOCAL_CNT2                 (1200 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* 200(????) */    /* 128????????>76*96=7296bytes????+200?? */
#else
#define WLAN_MEM_LOCAL_CNT2                 (800 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* 200(????) */
#endif  /* #ifdef _PRE_WLAN_FEATURE_USER_EXTEND */
#else
#define WLAN_MEM_LOCAL_SIZE2                100                                /* proxysta??????????800?????????????????????????????????????????? */
#ifdef _PRE_WLAN_FEATURE_USER_EXTEND
#define WLAN_MEM_LOCAL_CNT2                 (1200 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ??????????????????????(CCA????????????????????76????????)?????????????????????????? */
#else
#define WLAN_MEM_LOCAL_CNT2                 (800 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ??????????????????????(CCA????????????????????76????????)?????????????????????????? */
#endif /* #ifdef _PRE_WLAN_FEATURE_USER_EXTEND */
#endif

#define WLAN_MEM_LOCAL_SIZE3                260             /* ????hmac_vap_cfg_priv_stru??????VAP???? + ???????? 14 *?? */
#define WLAN_MEM_LOCAL_CNT3                 (WLAN_VAP_SUPPORT_MAX_NUM_LIMIT + 580)   /* ????????????????????????????32???????????????????????? */

#define WLAN_MEM_LOCAL_SIZE4                500

#ifdef _PRE_WLAN_FEATURE_USER_EXTEND
#define WLAN_MEM_LOCAL_CNT4                 (550 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)  /* 64????????????????????????????????alg_smartant_per_user_info_stru???????????? */
#else
#define WLAN_MEM_LOCAL_CNT4                 (350 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)  /* 64????????????????????????????????alg_smartant_per_user_info_stru???????????? */
#endif

#define WLAN_MEM_LOCAL_SIZE5                2200

#ifdef _PRE_WLAN_FEATURE_USER_EXTEND
#define WLAN_MEM_LOCAL_CNT5                 (180 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ????(TPC/autorate??)??????????????????(??????????????????????) */
#else
#define WLAN_MEM_LOCAL_CNT5                 (120 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ????(TPC/autorate??)??????????????????(??????????????????????) */
#endif

#define WLAN_MEM_LOCAL_SIZE6                9500           /* autorate */
#define WLAN_MEM_LOCAL_CNT6                 (64 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /*  */


/*****************************************************************************
  2.4.6 ????????????????
*****************************************************************************/
#define WLAN_MEM_EVENT_SIZE1                64              /* ????: ????????????????4????IPC?????? */
#define WLAN_MEM_EVENT_CNT1                 (180 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#ifdef _PRE_WLAN_FEATURE_11R_AP
#define WLAN_MEM_EVENT_SIZE2                556              /* 11r????ie????530???????????????????? */
#else
#define WLAN_MEM_EVENT_SIZE2                528              /* ????: ????????????????4????IPC?????? */
#endif
#define WLAN_MEM_EVENT_CNT2                 6               /*hmac_main_init????mac_chip_stru????????*/

#define WLAN_WPS_IE_MAX_SIZE                WLAN_MEM_EVENT_SIZE2 - 32   /* 32?????????????????????? */
#ifdef _PRE_WLAN_FEATURE_HILINK
#define WLAN_OKC_IE_MAX_SIZE                WLAN_MEM_EVENT_SIZE2 - 32   /* 32?????????????????????? */
#endif
/*****************************************************************************
  2.4.7 ??????????
*****************************************************************************/


/*****************************************************************************
  2.4.8 MIB??????  TBD :??????????????????????????????????????
*****************************************************************************/
#define WLAN_MEM_MIB_SIZE1                  32000           /* mib?????????? */
#define WLAN_MEM_MIB_CNT1                   ((WLAN_VAP_SUPPORT_MAX_NUM_LIMIT - 1) * 2)    /* ????VAP????MIB */

/*****************************************************************************
  2.4.9 netbuf??????  TBD :??????????????????????????????????????
*****************************************************************************/
#define WLAN_MEM_NETBUF_SIZE1               0       /* ??????SKB */
#define WLAN_MEM_NETBUF_CNT1                (192 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ????????????AMSDU????????????MSDU????????????netbuf */

#ifndef _PRE_WLAN_PHY_PERFORMANCE
#define WLAN_MEM_NETBUF_SIZE2               1600    /* 1500 + WLAN_MAX_FRAME_HEADER_LEN(36) + WLAN_HDR_FCS_LENGTH(4) + (????????????,????????????????(20)) */
#define WLAN_MEM_NETBUF_CNT2                (512 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)      /* ????192(??????????) + 32(??????????) + 32(??????????) */
                                                        /* ????????wlan2wlan????????????????????????x2 */
#define WLAN_MEM_NETBUF_SIZE3               2500    /* ??????????????????skb */
#define WLAN_MEM_NETBUF_CNT3                (32 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)       /* ???????????????????? */

#else
#define WLAN_MEM_NETBUF_SIZE2               5100
#define WLAN_MEM_NETBUF_CNT2                (512 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)

#define WLAN_MEM_NETBUF_SIZE3               5100    /* ??????????????????skb */
#define WLAN_MEM_NETBUF_CNT3                (32 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)       /* ???????????????????? */
#endif


#define WLAN_MEM_NETBUF_ALIGN               4       /* netbuf???? */
#define WLAN_MEM_ETH_HEADER_LEN             14      /* ?????????????? */

#define WLAN_LARGE_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE2 /* NETBUF?????????????????????????????? */
#define WLAN_MGMT_NETBUF_SIZE         WLAN_MEM_NETBUF_SIZE2 /* NETBUF?????????????????? ?? ???????????? */
#define WLAN_SHORT_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE2 /* NETBUF???????????????? ?????????????? */
#define WLAN_MAX_NETBUF_SIZE          WLAN_LARGE_NETBUF_SIZE /* netbuf?????????????? + payload */
#define WLAN_SMGMT_NETBUF_SIZE        WLAN_MGMT_NETBUF_SIZE  /* NETBUF???????????????????? ?? ???????????? */

/*****************************************************************************
  2.4.9.1 sdt netbuf??????
*****************************************************************************/

/*  sdt??????????????????????netbuf??????????????????????????????????????????send????
    ??????????????????Payload??????
*/
/************************* sdt report msg format*********************************/
/* NETLINK_HEAD     | SDT_MSG_HEAD  | Payload    | SDT_MSG_TAIL  |    pad       */
/* ---------------------------------------------------------------------------- */
/* NLMSG_HDRLEN     |    8Byte      |     ...    |   1Byte       |    ...       */
/********************************************************************************/
#define WLAN_SDT_SKB_HEADROOM_LEN       8
#define WLAN_SDT_SKB_TAILROOM_LEN       1
#define WLAN_SDT_SKB_RESERVE_LEN        (WLAN_SDT_SKB_HEADROOM_LEN + WLAN_SDT_SKB_TAILROOM_LEN)

/*
    SDT??????????????SDT??????????????????
*/
#define WLAN_MEM_SDT_NETBUF_PAYLOAD1            37          //????????????
#define WLAN_MEM_SDT_NETBUF_PAYLOAD2            100
#define WLAN_MEM_SDT_NETBUF_PAYLOAD3            512
#define WLAN_MEM_SDT_NETBUF_PAYLOAD4            1600

#define WLAN_SDT_NETBUF_MAX_PAYLOAD             WLAN_MEM_SDT_NETBUF_PAYLOAD4

#define WLAN_MEM_SDT_NETBUF_SIZE1       (WLAN_MEM_SDT_NETBUF_PAYLOAD1 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE1_CNT   (250 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#define WLAN_MEM_SDT_NETBUF_SIZE2       (WLAN_MEM_SDT_NETBUF_PAYLOAD2 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE2_CNT   (250 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#define WLAN_MEM_SDT_NETBUF_SIZE3       (WLAN_MEM_SDT_NETBUF_PAYLOAD3 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE3_CNT   (250 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#define WLAN_MEM_SDT_NETBUF_SIZE4       (WLAN_MEM_SDT_NETBUF_PAYLOAD4 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE4_CNT   (256 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)

#define WLAN_SDT_MSG_FLT_HIGH_THD           800
#define WLAN_SDT_MSG_QUEUE_MAX_LEN          (WLAN_MEM_SDT_NETBUF_SIZE1_CNT + \
                                                 WLAN_MEM_SDT_NETBUF_SIZE2_CNT + \
                                                 WLAN_MEM_SDT_NETBUF_SIZE3_CNT + \
                                                 WLAN_MEM_SDT_NETBUF_SIZE4_CNT - 6)  /* ????????????????????????????1000 */

/*****************************************************************************
  2.4.10 RF??????????
*****************************************************************************/

/*****************************************************************************
  2.4.11 TCP ACK????
*****************************************************************************/
#define DEFAULT_TX_TCP_ACK_OPT_ENABLE (OAL_FALSE)
#define DEFAULT_RX_TCP_ACK_OPT_ENABLE (OAL_FALSE)
#define DEFAULT_TX_TCP_ACK_THRESHOLD (1) /*????????ack ??????*/
#define DEFAULT_RX_TCP_ACK_THRESHOLD (1) /*????????ack ??????*/


/*****************************************************************************
  2.5 frw??????spec
*****************************************************************************/

/******************************************************************************
    ??????????????????
    ????: ????????????????????????????????????2??????????
*******************************************************************************/

#define FRW_EVENT_MAX_NUM_QUEUES    (FRW_EVENT_TYPE_BUTT * WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)

#define WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    /* ????????       ????????   ??????????????????????????   ???????????????? */  \
    /* HIGH_PRIO */     {   1,               32,                      0, 0}, \
    /* HOST_CRX */      {   1,               64,                      1, 0}, \
    /* HOST_DRX */      {   1,               64,                      1, 0}, \
    /* HOST_CTX */      {   1,               64,                      1, 0}, \
    /* HOST_SDT */      {   1,               64,                      1, 0}, \
    /* WLAN_CRX */      {   1,               64,                      1, 0}, \
    /* WLAN_DRX */      {   1,               64,                      0, 0}, \
    /* WLAN_CTX */      {   1,               64,                      1, 0}, \
    /* WLAN_DTX */      {   1,               64,                      0, 0}, \
    /* WLAN_TX_COMP */  {   1,               64,                      0, 0}, \
    /* TBTT */          {   1,               64,                      1, 0}, \
    /* TIMEOUT */       {   1,                2,                      1, 0}, \
    /* HMAC MISC */     {   1,               64,                      1, 0}, \
    /* DMAC MISC */     {   1,               64,                      0, 0},
#ifdef _PRE_WLAN_FEATURE_DOUBLE_CHIP /* ???????????????? */

#define WLAN_FRW_EVENT_CFG_TABLE \
  { \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
  }
#else /* ?????????? */
#ifdef _PRE_WLAN_PRODUCT_1151V200
#define WLAN_FRW_EVENT_CFG_TABLE \
  { \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
  }
#else
#define WLAN_FRW_EVENT_CFG_TABLE \
  { \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
  }
#endif
#endif

/*****************************************************************************
  2.8.0 ????OS????
*****************************************************************************/

/*****************************************************************************
  2.9 DFT
*****************************************************************************/
/*****************************************************************************
  2.9.0 ????
*****************************************************************************/
/*****************************************************************************
  2.9.15 WiFi????????????
*****************************************************************************/



/*****************************************************************************
  3 ????????
*****************************************************************************/


/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/



/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
#endif /* #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* #ifndef __PLATFORM_SPEC_1151_H__ */




