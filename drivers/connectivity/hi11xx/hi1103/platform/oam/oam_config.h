

#ifndef __OAM_CONFIG_H__
#define __OAM_CONFIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "oal_ext_if.h"


/*****************************************************************************
  2 ??????
*****************************************************************************/
/* ???????????????????????????????????? */
#define   OAM_CFG_VAL_MAX_LEN       20

/* ??????(=)???? */
#define   OAM_CFG_EQUAL_SIGN_LEN    1

/* '\0'???? */
#define   OAM_CFG_STR_END_SIGN_LEN  1


typedef oal_uint32 (* p_oam_customize_init_func)(oal_void);
/*****************************************************************************
  3 ????????
*****************************************************************************/
/*TBD ??????????BFGIN????*/
/* primID pattern */
enum OM_MSG_MODULEID
{
    OM_WIFI_HOST    = 0x00,
    OM_WIFI         = 0x01,
    OM_BT           = 0x02,
    OM_GNSS         = 0x03,
    OM_FM           = 0x04,
    OM_PF           = 0x05,
    OM_MODULEID_BUTT
};
typedef oal_uint8 oam_msg_moduleid_enum_uint8;

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
typedef struct
{
    p_oam_customize_init_func customize_init[OM_MODULEID_BUTT];       /* ???????????????????? */
}oam_customize_stru;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/
extern oam_customize_stru g_oam_customize_etc;

/*****************************************************************************
  10 ????????
*****************************************************************************/
extern oal_void  oam_register_init_hook_etc(oam_msg_moduleid_enum_uint8 en_moduleid,  p_oam_customize_init_func p_func);
extern oal_int32  oam_cfg_get_one_item_etc(
                                           oal_int8   *pc_cfg_data_buf,
                                           oal_int8   *pc_section,
                                           oal_int8   *pc_key,
                                          oal_int32   *pl_val);

extern oal_int32  oam_cfg_read_file_to_buf_etc(
                                                    oal_int8   *pc_cfg_data_buf,
                                                    oal_uint32  ul_file_size);

extern oal_uint32  oam_cfg_decrypt_all_item_etc(
                                              oal_aes_key_stru *pst_aes_key,
                                              oal_int8         *pc_ciphertext,
                                              oal_int8         *pc_plaintext,
                                              oal_uint32        ul_cipher_len);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_config.h */
