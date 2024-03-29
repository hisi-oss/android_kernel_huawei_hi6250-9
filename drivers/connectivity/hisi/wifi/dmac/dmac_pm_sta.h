

#ifndef __DMAC_PM_STA_H__
#define __DMAC_PM_STA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ??????????????
*****************************************************************************/

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PM_STA_H
/*****************************************************************************
  2 ??????
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
extern 	oal_uint8 dmac_psm_check_hw_txq_state(oal_void);
extern oal_uint8 dmac_psm_check_txrx_state(oal_void);
extern oal_void  dmac_psm_recover_start_dma(oal_uint8 *puc_ch0,oal_uint8 *puc_ch1,oal_uint8 *puc_ch2);
extern oal_uint8 dmac_psm_clean_state (oal_void);
extern oal_void dmac_psm_save_start_dma (oal_uint8* puc_ch0,oal_uint8* puc_ch1,oal_uint8* puc_ch2);
extern oal_uint8 dmac_psm_save_ps_state (oal_void);
extern oal_uint8 dmac_psm_recover_powerdown(oal_uint8 uc_dmach0,oal_uint8 uc_dmach1,oal_uint8 uc_dmach2);
extern oal_uint8 dmac_psm_recover_no_powerdown (oal_void);
extern oal_uint8 dmac_psm_cbb_stopwork (oal_void);
extern oal_void dmac_psm_rf_sleep(oal_uint8 uc_restore_reg);
extern oal_void dmac_psm_rf_awake (oal_uint8 uc_restore_reg);
extern oal_void dmac_psm_sync_tsf_to_sta(oal_void);
extern oal_void dmac_psm_sync_tsf_to_ap(oal_void);
extern oal_uint8 dmac_psm_is_fake_queues_empty(oal_void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_pm_sta.h */
