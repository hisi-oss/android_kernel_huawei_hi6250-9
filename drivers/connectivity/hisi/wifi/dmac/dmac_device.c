
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"

#ifdef _PRE_WLAN_DFT_REG
#include "hal_witp_debug.h"
#endif

#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "mac_vap.h"
#include "dmac_resource.h"
#include "dmac_device.h"
#include "dmac_reset.h"
#include "dmac_blockack.h"
#include "dmac_scan.h"
#include "dmac_alg.h"
#include "dmac_acs.h"
#include "dmac_dfx.h"

#ifdef _PRE_WLAN_DFT_STAT
#include "dmac_dft.h"
#endif

#ifdef _PRE_WLAN_FEATURE_GREEN_AP
#include "dmac_green_ap.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DEVICE_C

oal_bool_enum_uint8 g_rx_filter_frag = OAL_FALSE;

#ifdef _PRE_WLAN_FEATURE_IP_FILTER


OAL_STATIC oal_void dmac_ip_filter_exit(oal_void)
{
    g_st_dmac_board.st_rx_ip_filter.en_state = MAC_RX_IP_FILTER_STOPED;
    g_st_dmac_board.st_rx_ip_filter.uc_btable_size      = 0;
    g_st_dmac_board.st_rx_ip_filter.uc_btable_items_num = 0;

    OAL_MEMZERO(g_auc_ip_filter_btable, OAL_SIZEOF(g_auc_ip_filter_btable));
    g_st_dmac_board.st_rx_ip_filter.pst_filter_btable = OAL_PTR_NULL;


    return;
}

OAL_STATIC oal_void dmac_ip_filter_init(oal_void)
{

    /* ?????????????????? */
    g_st_dmac_board.st_rx_ip_filter.en_state = MAC_RX_IP_FILTER_STOPED;
    g_st_dmac_board.st_rx_ip_filter.uc_btable_size      = OAL_SIZEOF(g_auc_ip_filter_btable) / OAL_SIZEOF(mac_ip_filter_item_stru);
    g_st_dmac_board.st_rx_ip_filter.uc_btable_items_num = 0;
    g_st_dmac_board.st_rx_ip_filter.pst_filter_btable   = OAL_PTR_NULL;

    OAL_MEMZERO(g_auc_ip_filter_btable, OAL_SIZEOF(g_auc_ip_filter_btable));
    g_st_dmac_board.st_rx_ip_filter.pst_filter_btable = (mac_ip_filter_item_stru *)g_auc_ip_filter_btable;


    return;
}
#endif //_PRE_WLAN_FEATURE_IP_FILTER


OAL_STATIC oal_void  dmac_free_hd_tx_dscr_queue(hal_to_dmac_device_stru *pst_hal_dev_stru)
{
    oal_uint8                        uc_index;
    hal_tx_dscr_stru                *pst_tx_dscr;
    oal_dlist_head_stru             *pst_hal_dscr_header;
    oal_netbuf_stru                 *pst_buf = OAL_PTR_NULL;


    for (uc_index = 0; uc_index < HAL_TX_QUEUE_NUM; uc_index++)
    {
        pst_hal_dscr_header = &(pst_hal_dev_stru->ast_tx_dscr_queue[uc_index].st_header);

        while(OAL_TRUE != oal_dlist_is_empty(pst_hal_dscr_header))
        {
            pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_hal_dscr_header->pst_next, hal_tx_dscr_stru, st_entry);
            pst_buf = pst_tx_dscr->pst_skb_start_addr;

            oal_dlist_delete_entry(&pst_tx_dscr->st_entry);

            OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);
            dmac_tx_excp_free_netbuf(pst_buf);
        }
    }
}



oal_uint32  dmac_device_exit(mac_board_stru *pst_board, mac_chip_stru *pst_chip, dmac_device_stru *pst_dmac_device)
{
    mac_device_stru   *pst_device;
    oal_uint32         ul_ret;
    hal_to_dmac_device_stru            *pst_hal_dev_stru;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_device_exit::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = pst_dmac_device->pst_device_base_info;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        return OAL_SUCC;
    }

    /* ???????????? */
    dmac_alg_exit(pst_device);

    /* ???????????? */
    //hal_set_machw_tx_suspend(pst_device->pst_device_stru);

    /* ????MAC and PHY */
    //hal_reset_phy_machw(pst_device->pst_device_stru, HAL_RESET_HW_TYPE_ALL, HAL_RESET_MAC_ALL, 1, 1);

    pst_hal_dev_stru = pst_device->pst_device_stru;

    dmac_free_hd_tx_dscr_queue(pst_hal_dev_stru);

#ifdef _PRE_WLAN_FEATURE_PM
    mac_pm_arbiter_destroy(pst_device);
#endif
    pst_device->pst_device_stru = OAL_PTR_NULL;

    /*??????????????*/
    /*?????????????? ???? ????????????*/
#if 0
    ul_ret = pst_board->p_device_destroy_fun(pst_device);
#else
    ul_ret = mac_device_exit(pst_device);
#endif

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_device_exit failed[%d].}", ul_ret);

        return ul_ret;
    }


#ifdef _PRE_SUPPORT_ACS
    /* ????dmac acs */
    dmac_acs_exit(pst_device);
#endif

#ifdef _PRE_WLAN_DFT_REG
        /* ???????????????????? */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_device->st_reg_prd_timer));
#endif

#ifdef _PRE_WLAN_FEATURE_DFR
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

    /* ????pcie?????????????? */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_dmac_device->st_pcie_err_timer));
#endif

	/* ???????????????????????????? */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hal_dev_stru->st_dfr_tx_prot.st_tx_prot_timer));
#endif

#ifdef _PRE_WLAN_FEATURE_GREEN_AP
    /* green ap ???????? */
    dmac_green_ap_exit(pst_device);
#endif

#ifdef _PRE_DEBUG_MODE
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_device->st_exception_report_timer));
#endif

    /* ????keepalive?????? */
    if(OAL_TRUE == pst_device->st_keepalive_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_device->st_keepalive_timer));
    }

#ifdef _PRE_WLAN_DFT_STAT
    if (OAL_TRUE == pst_device->st_dbb_env_param_ctx.st_collect_period_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_device->st_dbb_env_param_ctx.st_collect_period_timer));
    }
#endif

    /* ????????mac device???????????????????????????????????? */
    pst_dmac_device->pst_device_base_info = OAL_PTR_NULL;

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_chip_exit(mac_board_stru *pst_board, mac_chip_stru *pst_chip)
{
    dmac_device_stru  *pst_dmac_device;
    oal_uint32         ul_ret;
    oal_uint8          uc_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_chip || OAL_PTR_NULL == pst_board))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_chip_exit::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_device = 0; uc_device < pst_chip->uc_device_nums; uc_device++)
    {
         pst_dmac_device = dmac_res_get_mac_dev(pst_chip->auc_device_id[uc_device]);

         /* TBD ???????? ???????? */
         dmac_res_free_mac_dev(pst_chip->auc_device_id[uc_device]);

         ul_ret = dmac_device_exit(pst_board, pst_chip, pst_dmac_device);
         if (OAL_SUCC != ul_ret)
         {
             OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_chip_exit::hmac_device_exit failed[%d].}", ul_ret);
             return ul_ret;
         }
    }

    /*????????????*/
    ul_ret = mac_chip_exit(pst_board, pst_chip);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_chip_exit::mac_chip_exit failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


oal_uint32  dmac_board_exit(mac_board_stru *pst_board)
{
    oal_uint8        uc_chip_idx;
    oal_uint32       ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_board))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_board_exit::pst_board null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    while (0 != pst_board->uc_chip_id_bitmap)
    {
        /* ????????????????1????????????????chip?????????? */
        uc_chip_idx = oal_bit_find_first_bit_one_byte(pst_board->uc_chip_id_bitmap);
        if (OAL_UNLIKELY(uc_chip_idx >= WLAN_CHIP_MAX_NUM_PER_BOARD))
        {
            OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_board_exit::invalid uc_chip_idx[%d] uc_chip_id_bitmap=%d.}",
                           uc_chip_idx, pst_board->uc_chip_id_bitmap);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }

        ul_ret = dmac_chip_exit(pst_board, &(pst_board->ast_chip[uc_chip_idx]));
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_board_exit::mac_chip_exit failed[%d].}", ul_ret);
            return ul_ret;
        }

        /* ??????????bitmap?? */
        oal_bit_clear_bit_one_byte(&pst_board->uc_chip_id_bitmap, uc_chip_idx);
    }

    /*????????????????*/
    mac_board_exit(pst_board);
#ifdef _PRE_WLAN_FEATURE_IP_FILTER
    /* rx ip???????????????????????? */
    dmac_ip_filter_exit();
#endif //_PRE_WLAN_FEATURE_IP_FILTER

    return OAL_SUCC;
}




#ifdef _PRE_DEBUG_MODE

oal_uint32  dmac_device_exception_report_timeout_fn(oal_void *p_arg)
{
#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE))
    oal_uint8                   uc_pci_device_id = 0;
    oal_uint32                  ul_reg_pci_rpt_val  = 0;
    oal_uint32                  ul_pci_warn_clear_cfg_val = 0xFFFFFFFF;             /* ??1?? */
    oal_uint32                  ul_reg_pci_rpt_addr_offset = 0x110;                 /* PCIE 0x110?????? */
    oal_bus_chip_stru           *pst_bus_chip = OAL_PTR_NULL;
    hal_to_dmac_device_stru     *pst_hal_device = OAL_PTR_NULL;
    mac_device_stru             *pst_mac_device = OAL_PTR_NULL;

    pst_hal_device = (hal_to_dmac_device_stru *)p_arg;

    /* ????chip id?? */
    uc_pci_device_id = pst_hal_device->uc_chip_id;

    oal_bus_get_chip_instance(&pst_bus_chip, uc_pci_device_id);

    /* ????????1151???? PCIE */
    ul_reg_pci_rpt_val   = 0;
    oal_pci_read_config_dword(pst_bus_chip->pst_pci_device, ul_reg_pci_rpt_addr_offset, &ul_reg_pci_rpt_val);

    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_device_exception_report_timeout_fn::pst_mac_device[%d] is NULL!}", pst_hal_device->uc_mac_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device->ul_pcie_read_counter++;

    /* Bit[12]: Timer Timeout Status?? ???????????? timeout???? */
    if(0 != (ul_reg_pci_rpt_val & 0x1000))
    {
        pst_mac_device->ul_pcie_reg110_timeout_counter++;

        OAM_WARNING_LOG4(0, OAM_SF_ANY,
         "{dmac_device_exception_report_timeout_fn:: read 1151 pcie reg0x110 timeout, chip id = %d, device id = %d, reg0x110 = [0x%08x]}, timeout counter: %d.",
            pst_hal_device->uc_chip_id, pst_hal_device->uc_mac_device_id, ul_reg_pci_rpt_val, pst_mac_device->ul_pcie_reg110_timeout_counter);

        oal_pci_write_config_dword(pst_bus_chip->pst_pci_device, ul_reg_pci_rpt_addr_offset, ul_pci_warn_clear_cfg_val);
    }
    /* ?????????? timeout???????????????????????????????? 10 * 64?????????? timeout???????? */
    else if(0 == (pst_mac_device->ul_pcie_read_counter & 0x3F))
    {
        OAM_WARNING_LOG3(0, OAM_SF_ANY,
             "{dmac_device_exception_report_timeout_fn:: chip id = %d, device id = %d, reg0x110 read timeout counter: %d.",
                pst_hal_device->uc_chip_id, pst_hal_device->uc_mac_device_id, pst_mac_device->ul_pcie_reg110_timeout_counter);
    }
#endif

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_DFT_REG

OAL_STATIC oal_uint32  dmac_reg_timeout(void *p_arg)
{
    hal_to_dmac_device_stru    *pst_device;

    pst_device = (hal_to_dmac_device_stru *)p_arg;
    if (OAL_PTR_NULL == pst_device)
    {
        MAC_ERR_LOG(0, "ptr is null !");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_reg_timeout::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if(OAL_SUCC != hi1151_debug_refresh_reg(pst_device, OAM_REG_EVT_PRD))
    {
        return OAL_FAIL;
    }
    hi1151_debug_frw_evt(pst_device);

    return OAL_SUCC;
}

#endif



OAL_STATIC oal_uint32 dmac_cfg_vap_init(mac_device_stru *pst_device)
{
    /*VAP????????????HMAC???????? ????VAP*/
    return OAL_SUCC;
}

OAL_STATIC oal_void dmac_alg_stat_init(dmac_device_stru *pst_dmac_device)
{
    dmac_alg_stat_stru *pst_dmac_alg_stat = &pst_dmac_device->st_dmac_alg_stat;
    oal_uint32          aul_compatibility_rate_limit[WLAN_BW_CAP_BUTT][WLAN_PROTOCOL_BUTT] = DMAC_COMPATIBILITY_RATE_LIMIT_TABLE;

    pst_dmac_alg_stat->en_cca_intf_state            = DMAC_ALG_CCA_OPT_NO_INTF;
    pst_dmac_alg_stat->en_co_intf_state             = OAL_FALSE;
    pst_dmac_alg_stat->en_dmac_device_distance_enum = DMAC_ALG_TPC_NORMAL_DISTANCE;

    pst_dmac_device->st_dmac_compatibility_stat.en_compatibility_enable = OAL_FALSE;
    pst_dmac_device->st_dmac_compatibility_stat.en_compatibility_stat   = OAL_FALSE;
    pst_dmac_device->st_dmac_compatibility_stat.ul_rx_rate              = 0;
    pst_dmac_device->st_dmac_compatibility_stat.us_rx_rate_stat_count   = 0;
    oal_memcopy((oal_uint8*)pst_dmac_device->st_dmac_compatibility_stat.aul_compatibility_rate_limit,
                (oal_uint8*)aul_compatibility_rate_limit,
                OAL_SIZEOF(aul_compatibility_rate_limit));

    return;
}


OAL_STATIC oal_uint32  dmac_device_init(oal_uint8 *puc_device_id, oal_uint8 uc_chip_id, oal_uint8 uc_device_id, oal_uint32 ul_chip_ver)
{
    oal_uint32                 ul_ret;
    oal_uint8                  uc_dev_id;
    mac_device_stru           *pst_device;
    mac_data_rate_stru        *pst_data_rate;
    oal_uint32                 ul_rate_num = 0;
    oal_uint32                 ul_idx;
    oal_uint32                 ul_loop = 0;
    dmac_device_stru          *pst_dmac_device;
    hal_cfg_rts_tx_param_stru  st_hal_rts_tx_param;

#ifdef _PRE_WLAN_DFT_STAT
    oam_stats_phy_node_idx_stru st_phy_node_idx = {{OAM_STATS_PHY_NODE_TX_CNT,
                                                    OAM_STATS_PHY_NODE_RX_OK_CNT,
                                                    OAM_STATS_PHY_NODE_11B_HDR_ERR_CNT,
                                                    OAM_STATS_PHY_NODE_OFDM_HDR_ERR_CNT}};
#endif

    /*????????mac device?????????????? ????*/
    ul_ret = mac_res_alloc_dmac_dev(&uc_dev_id);
    if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_device_init::mac_res_alloc_dmac_dev failed[%d].}", ul_ret);

        return OAL_FAIL;
    }

    pst_device = mac_res_get_dev(uc_dev_id);

    if (OAL_PTR_NULL == pst_device)
    {
       OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_device_init::pst_device null.}");

       return OAL_ERR_CODE_PTR_NULL;
    }

#if 0
    pst_device->uc_chip_id   = uc_chip_id;
    pst_device->uc_device_id = uc_dev_id;
#endif

    /* ????dmac device???? */
    if(OAL_UNLIKELY(dmac_res_alloc_mac_dev(uc_dev_id) != OAL_SUCC))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_device_init::dmac_res_alloc_mac_dev failed.}");
        return OAL_FAIL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* ??????device?????????????? */
    ul_ret = mac_device_init(pst_device, ul_chip_ver, uc_chip_id, uc_dev_id);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_device_init::mac_device_init failed[%d], chip_ver[0x%x].}", ul_ret, ul_chip_ver);
        dmac_res_free_mac_dev(uc_dev_id);
        mac_res_free_dev(uc_dev_id);
        return ul_ret;
    }
#endif

    /* ????hmac device???????????????????? */
    pst_dmac_device = dmac_res_get_mac_dev(uc_dev_id);
    if (OAL_PTR_NULL == pst_dmac_device)
    {
       OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_device_init::pst_dmac_device null.}");
       mac_res_free_dev(uc_dev_id);
       return OAL_ERR_CODE_PTR_NULL;
    }

    /* ???????????? */
    OAL_MEMZERO(pst_dmac_device, OAL_SIZEOF(*pst_dmac_device));
    pst_dmac_device->pst_device_base_info = pst_device;

#ifdef _PRE_WLAN_FEATURE_DFR
    pst_dmac_device->en_dfr_hw_reset_enable = OAL_FALSE;
#endif //#ifdef _PRE_WLAN_FEATURE_DFR

#ifdef _PRE_WLAN_SW_CTRL_RSP
    pst_dmac_device->en_usr_bw_mode = WLAN_BAND_ASSEMBLE_20M;
#endif

    /* ??mac????????????????DMAC????????????device??????????????
       ????????????????????????????????device?????? */
    ul_ret = hal_chip_get_device(uc_chip_id, uc_device_id, &pst_device->pst_device_stru);

    pst_device->ul_core_id = pst_device->pst_device_stru->ul_core_id;

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_device_init::hal_chip_get_device failed[%d].}", ul_ret);

        dmac_res_free_mac_dev(uc_dev_id);
        mac_res_free_dev(uc_dev_id);
        return ul_ret;
    }

    /* ????mac????device id */
    pst_device->pst_device_stru->uc_mac_device_id = uc_dev_id;

    if(OAL_SUCC != mac_fcs_init(&pst_device->st_fcs_mgr, pst_device->uc_chip_id, pst_device->uc_device_id))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_device_init::mac_fcs_init failed.}");
        dmac_res_free_mac_dev(uc_dev_id);
        mac_res_free_dev(uc_dev_id);
        return OAL_FAIL;
    }

    /* ?????????????? */
    ul_ret = dmac_alg_init(pst_device);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_device_init::dmac_alg_init failed[%d].}", ul_ret);
        dmac_res_free_mac_dev(uc_dev_id);
        mac_res_free_dev(uc_dev_id);
        return ul_ret;
    }

    /* ?????????????????????????? */
    dmac_alg_stat_init(pst_dmac_device);

    pst_device->us_total_mpdu_num = 0;
    /* ?????????????? */
    OAL_MEMZERO(pst_device->aul_mac_err_cnt, OAL_SIZEOF(pst_device->aul_mac_err_cnt));

    /*??????????????????????????????*/
    pst_device->ul_first_timestamp = 0;

    pst_device->ul_rx_buf_too_small_show_counter = 0;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_device->ul_rx_fsm_st_timeout_show_counter = 0;
    pst_device->ul_tx_fsm_st_timeout_show_counter = 0;
    pst_device->ul_beacon_miss_show_counter = 0;
    pst_device->us_user_nums_max = WLAN_ASSOC_USER_MAX_NUM_SPEC;
    pst_device->ul_pcie_reg110_timeout_counter = 0;
    pst_device->ul_pcie_read_counter = 0;

    pst_device->st_dataflow_brk_bypass.en_brk_limit_aggr_enable = OAL_FALSE;
    pst_device->st_dataflow_brk_bypass.ul_tx_dataflow_brk_cnt = 0;
    pst_device->st_dataflow_brk_bypass.ul_last_tx_complete_isr_cnt = 0;
#endif
    for (ul_loop = 0; ul_loop < WLAN_WME_AC_BUTT; ul_loop++)
    {
        pst_device->aus_ac_mpdu_num[ul_loop] = 0;
    }

    for (ul_loop = 0; ul_loop < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; ul_loop++)
    {
        pst_device->aus_vap_mpdu_num[ul_loop] = 0;
    }

    for (ul_loop = WLAN_WME_AC_BE; ul_loop < WLAN_WME_AC_BUTT; ul_loop++)
    {
        pst_device->aus_ac_mpdu_num[ul_loop] = 0;
    }

#ifdef _PRE_WLAN_DFT_STAT
    /* ?????????????????????????????? */
    OAL_MEMZERO(&(pst_device->st_dbb_env_param_ctx), OAL_SIZEOF(mac_device_dbb_env_param_ctx_stru));
#endif


#ifdef _PRE_WLAN_FEATURE_PM
#if (_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_E5)
    pst_device->en_pm_enable   = OAL_FALSE;
#else
    pst_device->en_pm_enable   = OAL_FALSE;
#endif
    mac_pm_arbiter_init(pst_device);
#endif

    /* ??????TXOP?????????? */
    pst_device->en_txop_enable       = OAL_FALSE;
    pst_device->uc_tx_ba_num = 0;

    /* ??eeprom??flash????MAC???? */
    hal_get_hw_addr(pst_device->pst_device_stru, pst_device->auc_hw_addr);

    /* ??????DEVICE?????????? */
    hal_get_rate_80211g_table(pst_device->pst_device_stru, (oal_void *)&pst_data_rate);
    hal_get_rate_80211g_num(pst_device->pst_device_stru, &ul_rate_num);

    for (ul_idx = 0; ul_idx < ul_rate_num; ul_idx++)
    {
        oal_memcopy(&(pst_device->st_mac_rates_11g[ul_idx]),&pst_data_rate[ul_idx],OAL_SIZEOF(mac_data_rate_stru));
    }

    /* ??????2.4G??5G??RTS????, RTS[0~2]????24Mbps,  RTS[3]??2.4G????1Mbps??5G????24Mbps*/
    st_hal_rts_tx_param.auc_protocol_mode[0]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    st_hal_rts_tx_param.auc_rate[0]             = WLAN_LEGACY_OFDM_24M_BPS;
    st_hal_rts_tx_param.auc_protocol_mode[1]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    st_hal_rts_tx_param.auc_rate[1]             = WLAN_LEGACY_OFDM_24M_BPS;
    st_hal_rts_tx_param.auc_protocol_mode[2]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    st_hal_rts_tx_param.auc_rate[2]             = WLAN_LEGACY_OFDM_24M_BPS;

    st_hal_rts_tx_param.en_band                 = WLAN_BAND_2G;
    st_hal_rts_tx_param.auc_protocol_mode[3]    = WLAN_11B_PHY_PROTOCOL_MODE;
    st_hal_rts_tx_param.auc_rate[3]             = WLAN_LONG_11b_1_M_BPS;
    hal_set_rts_rate_params(pst_device->pst_device_stru, &st_hal_rts_tx_param);

    st_hal_rts_tx_param.en_band                 = WLAN_BAND_5G;
    st_hal_rts_tx_param.auc_protocol_mode[3]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    st_hal_rts_tx_param.auc_rate[3]             = WLAN_LEGACY_OFDM_24M_BPS;
    hal_set_rts_rate_params(pst_device->pst_device_stru, &st_hal_rts_tx_param);

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    /* TBD  */
    /* hal_enable_radar_det(pst_device->pst_device_stru, OAL_TRUE); */
    pst_device->us_dfs_timeout = 0;
#endif

    /* ??????DMAC SCANNER */
    dmac_scan_init(pst_device);

#ifdef _PRE_SUPPORT_ACS
    /* ??????ACS?????? */
    dmac_acs_init(pst_device);
#endif

#ifdef _PRE_WLAN_DFT_REG
    /* ?????????????????????? */
    FRW_TIMER_CREATE_TIMER(&pst_device->st_reg_prd_timer,
                               dmac_reg_timeout,
                               OAM_REGSTER_REFRESH_TIME_MS,
                               pst_device->pst_device_stru,
                               OAL_TRUE,
                               OAM_MODULE_ID_DMAC,
                               pst_device->ul_core_id);
#endif

#ifdef _PRE_WLAN_FEATURE_DFR
    dmac_dfr_init((oal_void *)pst_dmac_device);
#endif
#ifdef _PRE_WLAN_FEATURE_GREEN_AP
    /* Green AP???????????????? */
    dmac_green_ap_init(pst_device);
#endif

    /* ??????????CHIP????????????device id */
    *puc_device_id = uc_dev_id;

#ifdef _PRE_WLAN_FEATURE_AMPDU
#ifdef _PRE_DEBUG_MODE
//#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB != _PRE_CONFIG_TARGET_PRODUCT) )
    //OAL_MEMZERO(g_ast_tx_ba_track[pst_device->uc_device_id], OAL_SIZEOF(dmac_tx_ba_track_stru) * HAL_MAX_AMPDU_LUT_SIZE);
//#endif
#endif
#endif

#ifdef _PRE_DEBUG_MODE
    OAL_MEMZERO(&(pst_device->st_exception_report_timer), OAL_SIZEOF(frw_timeout_stru));

    FRW_TIMER_CREATE_TIMER(&(pst_device->st_exception_report_timer),
                            dmac_device_exception_report_timeout_fn,
                            MAC_EXCEPTION_TIME_OUT,
                            pst_device->pst_device_stru,
                            OAL_TRUE,
                            OAM_MODULE_ID_MAC,
                            pst_device->ul_core_id);

#endif

#ifdef _PRE_WLAN_DFT_STAT
        /* ??????phy???????? */
        dmac_dft_set_phy_stat_node(pst_device, &st_phy_node_idx);
#endif

    ul_ret = dmac_cfg_vap_init(pst_device);
    if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_cfg_vap_init failed[%d].}", ul_ret);
        return OAL_FAIL;
    }

    return OAL_SUCC;
}



OAL_STATIC oal_uint32  dmac_chip_init(mac_chip_stru *pst_chip, oal_uint8 uc_chip_id)
{
    oal_uint8  uc_device;
    oal_uint8  uc_device_max;
    oal_uint32 ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_chip))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_chip_init::pst_chip null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /*??????????????*/
    mac_chip_init(pst_chip, uc_chip_id);

    pst_chip->uc_chip_id = uc_chip_id;

    /*????????id??????hal_to_dmac_chip_stru??????*/
    ul_ret = hal_chip_get_chip(uc_chip_id, &pst_chip->pst_chip_stru);
    if (OAL_SUCC != ul_ret)
    {
     OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_device_init::hal_chip_get_chip failed[%d].}", ul_ret);
     return ul_ret;
    }


    /* CHIP???????? hal_get_chip_version*/
    hal_get_chip_version(pst_chip->pst_chip_stru, &pst_chip->ul_chip_ver);


    /* HAL????????????device???? */
    ul_ret = hal_chip_get_device_num(uc_chip_id, &uc_device_max);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_chip_init::hal_chip_get_device_num failed[%d].}", ul_ret);

        return ul_ret;
    }

    for (uc_device = 0; uc_device < uc_device_max; uc_device++)
    {
        ul_ret = dmac_device_init(&pst_chip->auc_device_id[uc_device], uc_chip_id, uc_device, pst_chip->ul_chip_ver);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_chip_init::dmac_device_init failed[%d].}", ul_ret);

            return ul_ret;
        }
    }

    /* ????device???? */
    pst_chip->uc_device_nums        = uc_device_max;

    /* ??????????????state????TRUE */
    pst_chip->en_chip_state         = OAL_TRUE;

    return OAL_SUCC;
}


oal_uint32  dmac_board_init(mac_board_stru *pst_board)
{
    oal_uint8  uc_chip;
    oal_uint32 ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_board))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_board_init::pst_board null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /*??????????????*/
    mac_board_init(pst_board);

#ifdef _PRE_WLAN_FEATURE_IP_FILTER
    /* rx ip?????????????????????? */
    dmac_ip_filter_init();
#endif //_PRE_WLAN_FEATURE_IP_FILTER

    /* chip??????????????PCIe????????????; */
    for (uc_chip = 0; uc_chip < oal_bus_get_chip_num(); uc_chip++)
    {
        ul_ret = dmac_chip_init(&pst_board->ast_chip[uc_chip], uc_chip);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_board_init::dmac_chip_init failed[%d].}", ul_ret);

            return ul_ret;
        }

        oal_bit_set_bit_one_byte(&pst_board->uc_chip_id_bitmap, uc_chip);
    }

    return OAL_SUCC;
}





oal_uint32  dmac_mac_error_overload(mac_device_stru *pst_mac_device, hal_mac_error_type_enum_uint8 en_error_id)
{
    if (pst_mac_device->aul_mac_err_cnt[en_error_id] > MAX_MAC_ERR_IN_TBTT)
    {
        return 1;
    }
    return 0;
}




oal_void  dmac_mac_error_cnt_clr(mac_device_stru *pst_mac_device)
{
    oal_memset(pst_mac_device->aul_mac_err_cnt, 0, sizeof(pst_mac_device->aul_mac_err_cnt));
}


oal_void  dmac_mac_error_cnt_inc(mac_device_stru *pst_mac_device, oal_uint8 uc_mac_int_bit)
{
    pst_mac_device->aul_mac_err_cnt[uc_mac_int_bit] += 1;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
