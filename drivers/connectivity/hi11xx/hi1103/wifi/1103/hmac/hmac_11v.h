

#ifndef __HMAC_11V_H__
#define __HMAC_11V_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_mem.h"
#include "mac_vap.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_11V_H

#ifdef _PRE_WLAN_FEATURE_11V_ENABLE

/*****************************************************************************
  2 ??????
*****************************************************************************/
/* ??????????????????800???? ??????????????19(frame boady)+50(url)+ N*(15(neighbor)+3(sub)+12(sub))  ?????????? ???????????????????? */
#define HMAC_MAX_BSS_NEIGHBOR_LIST  20          /* BSS Transition ??????????????????????AP?????????? */

// 11v????????????????????
#define HMAC_11V_WAIT_STATUS_TIMEOUT        5000         // 5000ms
#define HMAC_11V_MAX_URL_LENGTH             50          /* ????URL????????????????????50 */
#define HMAC_11V_TERMINATION_TSF_LENGTH     8           /* termination_tsf?????????????? */
#define HMAC_11V_QUERY_FRAME_BODY_FIX       4           /* query???????????????? */
#define HMAC_11V_REQUEST_FRAME_BODY_FIX     7           /* query???????????????? */
#define HMAC_11V_RESPONSE_FRAME_BODY_FIX    5           /* response???????????????? */
#define HMAC_11V_PERFERMANCE_ELEMENT_LEN    1           /* perfermance ie length */
#define HMAC_11V_TERMINATION_ELEMENT_LEN    10          /* termination ie length */
#define HMAC_11V_TOKEN_MAX_VALUE            255         /* ?????????????????? */
#define HMAC_11V_SUBELEMENT_ID_RESV         0           /* SUBELEMENT???? ID*/


#define HMAC_11V_REQUEST_DISASSOC_TIME_SCAN_ONE_CHANNEL_TIME 100    /*??????????????100ms??????Reject */
#define HMAC_11V_REQUEST_DISASSOC_TIME_SCAN_ALL_CHANNEL_TIME 3000   /*100ms??3s???????????????????? */

/*****************************************************************************
  3 ????????
*****************************************************************************/
/* IEEE Std 802.11-2012 - Table 8-253 */
enum bss_trans_mgmt_status_code {
	WNM_BSS_TM_ACCEPT = 0,
	WNM_BSS_TM_REJECT_UNSPECIFIED = 1,
	WNM_BSS_TM_REJECT_INSUFFICIENT_BEACON = 2,
	WNM_BSS_TM_REJECT_INSUFFICIENT_CAPABITY = 3,
	WNM_BSS_TM_REJECT_UNDESIRED = 4,
	WNM_BSS_TM_REJECT_DELAY_REQUEST = 5,
	WNM_BSS_TM_REJECT_STA_CANDIDATE_LIST_PROVIDED = 6,
	WNM_BSS_TM_REJECT_NO_SUITABLE_CANDIDATES = 7,
	WNM_BSS_TM_REJECT_LEAVING_ESS = 8
};

/*****************************************************************************
  Neighbor Report Element??????????(Subelement)?? ID
  820.11-2012????583????Table 8-115??SubElement IDs
*****************************************************************************/
typedef enum
{
    HMAC_NEIGH_SUB_ID_RESERVED              = 0,
    HMAC_NEIGH_SUB_ID_TFS_INFO,
    HMAC_NEIGH_SUB_ID_COND_COUNTRY,
    HMAC_NEIGH_SUB_ID_BSS_CANDIDATE_PERF,
    HMAC_NEIGH_SUB_ID_TERM_DURATION,

    HMAC_NEIGH_SUB_ID_BUTT
}hmac_neighbor_sub_eid_enum;
typedef oal_uint8 hmac_neighbor_sub_eid_enum_uint8;


/*****************************************************************************
  4 STRUCT????
*****************************************************************************/
/* Subelement BSS Transition Termination Duration */
struct hmac_bss_term_duration
{
    oal_uint8       uc_sub_ie_id;                                               /* subelement ID????ID????0 ???????????????? */
    oal_uint8       auc_termination_tsf[HMAC_11V_TERMINATION_TSF_LENGTH];       /* BSS????????: TSF */
    oal_uint16      us_duration_min;                                            /* BSS???????? time: ???? */
    oal_uint8       uc_resv;                                                    /* ???????????? */
}__OAL_DECLARE_PACKED;
typedef struct hmac_bss_term_duration  hmac_bss_term_duration_stru;

/* ????BSS????????Neighbor Report IE?????? ??????????????subelement 3 4 ??????????subelement */
struct hmac_neighbor_bss_info
{
    oal_uint8       auc_mac_addr[WLAN_MAC_ADDR_LEN];                      /* BSSID MAC???? */
    oal_uint8       uc_opt_class;                                         /* Operation Class */
    oal_uint8       uc_chl_num;                                           /* Channel number */
    oal_uint8       uc_phy_type;                                          /* PHY type */
    oal_uint8       uc_candidate_perf;                                    /* perference data BSSID?????? */
    oal_uint16      us_resv;                                              /* ?????????? */
    oal_bssid_infomation_stru   st_bssid_info;                       /* BSSID information */
    hmac_bss_term_duration_stru st_term_duration;                   /* ??????Termination duration */
}__OAL_DECLARE_PACKED;
typedef struct hmac_neighbor_bss_info  hmac_neighbor_bss_info_stru;

struct hmac_bsst_req_mode
{
    oal_uint8   bit_candidate_list_include:1,                   /* ????????????AP???? */
                bit_abridged:1,                                 /* 1:????????????????????????AP????????????0 */
                bit_bss_disassoc_imminent:1,                    /* ????????????STA ??0 ??????????????FF FF */
                bit_termination_include:1,                      /* BSS????????  ??0??????????????BSS Termination Duration???? */
                bit_ess_disassoc_imminent:1,                    /* EES???????? */
                bit_rev:3;
}__OAL_DECLARE_PACKED;
typedef struct hmac_bsst_req_mode  hmac_bsst_req_mode_stru;

/* bss transition request?????????????? */
struct hmac_bsst_req_info
{
    oal_uint8               uc_validity_interval;                              /* ???????????????? TBTTs */
    oal_uint16              us_disassoc_time;                                  /* AP??????STA???? TBTTs */
    oal_uint8               *puc_session_url;                                  /* ?????????????? ??????????100?????? */
    hmac_bsst_req_mode_stru st_request_mode;                                   /* request mode */
    oal_uint8               uc_bss_list_num;
    oal_uint8               uc_resv;                                           /* 4???????? */
    hmac_neighbor_bss_info_stru *pst_neighbor_bss_list;                        /* bss list?????? ??????????????50?? */
    hmac_bss_term_duration_stru st_term_duration;                              /* ??????Termination duration */
}__OAL_DECLARE_PACKED;
typedef struct hmac_bsst_req_info  hmac_bsst_req_info_stru;

/* bss transition response?????????????? */
struct hmac_bsst_rsp_info
{
    oal_uint8       uc_status_code;                         /* ?????? ???????????? */
    oal_uint8       uc_termination_delay;                   /* ????AP????????????:???? */
    oal_uint8       auc_target_bss_addr[WLAN_MAC_ADDR_LEN]; /* ??????????????BSSID */
    oal_uint8       uc_chl_num;                             /* Channel number */
    oal_uint8       uc_bss_list_num;                        /* bss list????????????????50?? */
    oal_int8        c_rssi;                                 /* ????????AP??RSSI????Candiate AP??RSSI */
    oal_uint8       us_resv;                                /* ?????????? */
    hmac_neighbor_bss_info_stru *pst_neighbor_bss_list;
}__OAL_DECLARE_PACKED;
typedef struct hmac_bsst_rsp_info  hmac_bsst_rsp_info_stru;

/*****************************************************************************
  5 ????????????
*****************************************************************************/


/*****************************************************************************
  6 ??????????
*****************************************************************************/


/*****************************************************************************
  7 ????????
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
/* ??Neighbor Report IE???????????????????????? */
extern hmac_neighbor_bss_info_stru * hmac_get_neighbor_ie(oal_uint8 *puc_data, oal_uint16 us_len, oal_uint8 *pst_bss_num);
/* STA ????AP??????bss transition request frame */
extern oal_uint32  hmac_rx_bsst_req_action(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_netbuf);
/* STA ????bss transition response frame */
extern oal_uint16  hmac_encap_bsst_rsp_action(hmac_vap_stru *pst_hmac_vap,
                                              hmac_user_stru *pst_hmac_user,
                                              hmac_bsst_rsp_info_stru *pst_bsst_rsp_info,
                                              oal_netbuf_stru *pst_buffer);
/* STA ????bss transition response frame */
//extern oal_uint32  hmac_tx_bsst_rsp_action(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user, hmac_bsst_rsp_info_stru *pst_bsst_rsp_info);
extern oal_uint32 hmac_tx_bsst_rsp_action(void *pst_void1, void *pst_void2, void *pst_void3);

extern oal_uint32 hmac_11v_roam_scan_check(hmac_vap_stru *pst_hmac_vap);

#endif /*_PRE_WLAN_FEATURE_11V_ENABLE*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_11v.h */
