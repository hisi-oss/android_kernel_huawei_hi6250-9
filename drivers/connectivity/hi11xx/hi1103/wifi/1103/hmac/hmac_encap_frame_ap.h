

#ifndef __HMAC_ENCAP_FRAME_AP_H__
#define __HMAC_ENCAP_FRAME_AP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "hmac_user.h"
#include "hmac_vap.h"

/*****************************************************************************
  2 ??????
*****************************************************************************/
typedef enum
{
    /* ??????????open */
    HMAC_AP_AUTH_SEQ1_OPEN_ANY  = 0,
    /* ??????????wep,?????????? */
    HMAC_AP_AUTH_SEQ1_WEP_NOT_RESEND,
    /* ??????????wep,???????????? */
    HMAC_AP_AUTH_SEQ1_WEP_RESEND,
    /* ??????????open */
    HMAC_AP_AUTH_SEQ3_OPEN_ANY,
    /* ??????????WEP,assoc??????auth comlete */
    HMAC_AP_AUTH_SEQ3_WEP_COMPLETE,
    /* ??????????WEP,assoc??????assoc */
    HMAC_AP_AUTH_SEQ3_WEP_ASSOC,
    /* ?????????? */
    HMAC_AP_AUTH_DUMMY,

    HMAC_AP_AUTH_BUTT
}hmac_ap_auth_process_code_enum;
typedef oal_uint8 hmac_ap_auth_process_code_enum_uint8;

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
typedef struct tag_hmac_auth_rsp_param_stru
{
    /* ????auth request???????????? */
    oal_uint8                               uc_auth_resend;
    /* ??????????wep */
    oal_bool_enum_uint8                     en_is_wep_allowed;
    /* ?????????????? */
    oal_uint16                              us_auth_type;
    /* ????????????????user??????????*/
    mac_user_asoc_state_enum_uint8          en_user_asoc_state;
    oal_uint8                               uc_pad[3];

}hmac_auth_rsp_param_stru;

typedef hmac_ap_auth_process_code_enum_uint8 (*hmac_auth_rsp_fun)(
                                                    mac_vap_stru *pst_mac_vap,\
                                                    hmac_auth_rsp_param_stru *pst_auth_rsp_param, \
                                                    oal_uint8 *puc_code, \
                                                    mac_user_asoc_state_enum_uint8 *pst_usr_ass_stat);

typedef struct tag_hmac_auth_rsp_handle_stru
{
    hmac_auth_rsp_param_stru st_auth_rsp_param;
    hmac_auth_rsp_fun        st_auth_rsp_fun;
}hmac_auth_rsp_handle_stru;
/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

OAL_STATIC OAL_INLINE oal_void hmac_mgmt_encap_chtxt(oal_uint8 *puc_frame,
                                                               oal_uint8 *puc_chtxt,
                                                               oal_uint16 *pus_auth_rsp_len,
                                                               hmac_user_stru *pst_hmac_user_sta)
{
    /* Challenge Text Element                  */
    /* --------------------------------------- */
    /* |Element ID | Length | Challenge Text | */
    /* --------------------------------------- */
    /* | 1         |1       |1 - 253         | */
    /* --------------------------------------- */
    puc_frame[6] = MAC_EID_CHALLENGE;
    puc_frame[7] = WLAN_CHTXT_SIZE;

    /* ??challenge text?????????????? */
    oal_memcopy(&puc_frame[8], puc_chtxt, WLAN_CHTXT_SIZE);

    /* ??????????????Challenge Text Element?????? */
    *pus_auth_rsp_len += (WLAN_CHTXT_SIZE + MAC_IE_HDR_LEN);

    /* ??????????challenge text */
    oal_memcopy(pst_hmac_user_sta->auc_ch_text, &puc_frame[8], WLAN_CHTXT_SIZE);
}

/*****************************************************************************
  10 ????????
*****************************************************************************/

extern oal_uint16  hmac_encap_auth_rsp_etc(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_auth_rsp, oal_netbuf_stru *pst_auth_req, oal_uint8 *puc_chtxt);

#ifdef _PRE_WLAN_FEATURE_11R_AP
extern oal_err_code_enum  hmac_encap_auth_rsp_get_user_idx_etc(mac_vap_stru *pst_mac_vap,
                                                oal_uint8   *puc_mac_addr,
                                                oal_uint8   uc_is_seq1,
                                                oal_uint8   *puc_auth_resend,
                                                oal_uint16  *pus_user_index);
extern oal_uint32 hmac_get_assoc_comeback_time(mac_vap_stru *pst_mac_vap,
                                        hmac_user_stru *pst_hmac_user);
#endif
extern oal_uint32 hmac_mgmt_encap_asoc_rsp_ap_etc(
                    mac_vap_stru                   *pst_mac_ap,
                    oal_uint8                      *puc_sta_addr,
                    oal_uint16                      us_assoc_id,
                    mac_status_code_enum_uint16     en_status_code,
                    oal_uint8                      *puc_asoc_rsp,
                    oal_uint16                      us_type);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_encap_frame_ap.h */
