

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "frw_main.h"
#include "frw_event_deploy.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_DEPLOY_C

/*****************************************************************************
  2 ????????????
*****************************************************************************/
/* ipc??????????:??????????,AMP???????????????????????? */
OAL_STATIC frw_ipc_node_stru         g_st_ipc_node[FRW_IPC_CORE_TYPE_BUTT];

/* ???????????????????????? */
OAL_STATIC frw_ipc_msg_queue_stru    g_st_queue_master_to_slave;

/* ???????????????????????? */
OAL_STATIC frw_ipc_msg_queue_stru    g_st_queue_slave_to_master;

/*****************************************************************************
  3 ????????
*****************************************************************************/
/* IPC???? */
OAL_STATIC oal_uint32  frw_ipc_init(oal_void);
OAL_STATIC oal_uint32  frw_ipc_init_master(frw_ipc_node_stru *pst_ipc_node);
OAL_STATIC oal_uint32  frw_ipc_init_slave(frw_ipc_node_stru *pst_ipc_node);
OAL_STATIC oal_uint32  frw_ipc_exit(oal_void);
OAL_STATIC oal_void  frw_ipc_recv(frw_ipc_msg_mem_stru *pst_ipc_mem_msg);
OAL_STATIC oal_uint32  frw_ipc_send(frw_ipc_msg_mem_stru *pst_ipc_mem_msg);
OAL_STATIC oal_uint32  frw_ipc_send_connect_request(oal_void);
OAL_STATIC oal_uint32  frw_ipc_send_connect_response(oal_void);
OAL_STATIC oal_uint32  frw_ipc_send_inter_msg(oal_uint8 uc_msg_type, oal_uint8 *puc_data, oal_uint8 us_len);
OAL_STATIC oal_void  frw_ipc_tx_complete(frw_ipc_msg_mem_stru *pst_msg);
OAL_STATIC oal_uint32  frw_ipc_event_queue_full(oal_void);
OAL_STATIC oal_uint32  frw_ipc_event_queue_empty(oal_void);

/* ???????????? */
OAL_STATIC oal_uint32  frw_event_deploy_pipeline(oal_mem_stru *pst_mem_event, frw_event_deploy_enum_uint8 *en_deploy_result);


OAL_STATIC oal_void  frw_ipc_recv(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    frw_ipc_msg_header_stru     *pst_header;    /* ?????????????? */
    frw_ipc_core_type_enum_uint8 en_type;       /* CPU????: ?????????? */

    /* ???????? */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_recv::OAL_PTR_NULL == pst_ipc_mem_msg}\r\n");
        return;
    }

    /* ????????????, ??IPC??????????????puc_data??????????????????????IPC?? */
    pst_header = (frw_ipc_msg_header_stru *)(pst_ipc_mem_msg->puc_data);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_header
        || pst_header->uc_target_cpuid > FRW_IPC_CORE_NUM_BUTT
        || pst_header->uc_msg_type > FRW_IPC_MSG_TYPE_BUTT))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{pst_header is incorrect.}");
        return;
    }

    /* ???????????????? */
    en_type = frw_ipc_get_core_type();

    /* ????seq number???????? */
    if (OAL_LIKELY(g_st_ipc_node[en_type].us_seq_num_rx_expect == pst_header->us_seq_number))
    {
        g_st_ipc_node[en_type].us_seq_num_rx_expect++;  /* ???????????????????? */
    }
    else if(g_st_ipc_node[en_type].us_seq_num_rx_expect < pst_header->us_seq_number)
    {
        /* ???????????????????? */
        g_st_ipc_node[en_type].us_seq_num_rx_expect = pst_header->us_seq_number + 1;

    #ifdef _PRE_DEBUG_MODE
        /* ?????????? */
        frw_ipc_log_recv_alarm_etc(&g_st_ipc_node[en_type].st_log,
                               (pst_header->us_seq_number - g_st_ipc_node[en_type].us_seq_num_rx_expect));
    #endif
    }
    else
    {
        /* ???????????????? */
        /* ???????????????????? */
        g_st_ipc_node[en_type].us_seq_num_rx_expect = pst_header->us_seq_number + 1;
    #ifdef _PRE_DEBUG_MODE
        /* ????????????????????????: ??????????+????????????-????????????+1 */
        frw_ipc_log_recv_alarm_etc(&g_st_ipc_node[en_type].st_log,
                               (pst_header->us_seq_number + FRW_IPC_MAX_SEQ_NUMBER - g_st_ipc_node[en_type].us_seq_num_rx_expect + 1));
    #endif
    }

#ifdef _PRE_DEBUG_MODE
    /* ???????? */
    frw_ipc_log_recv_etc(&g_st_ipc_node[en_type].st_log,
                     pst_header->us_seq_number,
                     pst_header->uc_target_cpuid,
                     pst_header->uc_msg_type);
#endif

    switch (pst_header->uc_msg_type)
    {
        case FRW_IPC_MSG_TYPE_EVENT:

            /* ??IPC??????????????IPC???????????????????????????????????????????? */
            pst_ipc_mem_msg->puc_data += FRW_IPC_MSG_HEADER_LENGTH;

            /* ???????????????? */
            frw_event_post_event_etc(pst_ipc_mem_msg,OAL_GET_CORE_ID());

            break;

        case FRW_IPC_MSG_TYPE_TX_INT_ENABLE:
            /* ?????????????????????????????? */
            g_st_ipc_node[en_type].en_tx_int_ctl = FRW_IPC_TX_CTRL_ENABLED;

            break;

        case FRW_IPC_MSG_TYPE_TX_INT_DISENABLE:
            /* ?????????????????????????????? */
            g_st_ipc_node[en_type].en_tx_int_ctl = FRW_IPC_TX_CTRL_DISABLED;

            break;

        case FRW_IPC_MSG_TYPE_CONNECT_REQUEST:
            /* ???????????? */
            frw_ipc_send_connect_response();

            break;

        case FRW_IPC_MSG_TYPE_CONNECT_RESPONSE:
            /* ?????????????????? */
            g_st_ipc_node[en_type].en_states = FRW_IPC_CORE_STATE_CONNECTED;

            break;

        case FRW_IPC_MSG_TYPE_CONFIG_REQUEST:
        case FRW_IPC_MSG_TYPE_CONFIG_RESPONSE:
        case FRW_IPC_MSG_TYPE_ERROR_NOTICE:
        case FRW_IPC_MSG_TYPE_RESET_REQUEST:
        case FRW_IPC_MSG_TYPE_RESET_RESPONSE:
        case FRW_IPC_MSG_TYPE_OPEN_OAM:
        case FRW_IPC_MSG_TYPE_CLOSE_OAM:
        case FRW_IPC_MSG_TYPE_EXIT_REQUEST:
        case FRW_IPC_MSG_TYPE_EXIT_RESPONSE:
        default:

            break;
    }

    /* ???????? */
    FRW_EVENT_FREE(pst_ipc_mem_msg);
}


OAL_STATIC oal_uint32  frw_ipc_send(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    oal_uint32                   ul_ret;
    frw_ipc_msg_header_stru     *pst_header;        /* ?????????????? */
    frw_ipc_msg_queue_stru      *pst_msg_queue;     /* ???????? */
    frw_ipc_core_type_enum_uint8 en_type;           /* CPU????: ?????????? */



    /* ???????????????? */
    en_type = frw_ipc_get_core_type();
    FRW_IPC_GET_MSG_QUEUE(pst_msg_queue, en_type);

    /* ????????IPC????????*/
    if (FRW_IPC_CORE_STATE_CONNECTED != g_st_ipc_node[en_type].en_states)
    {
        OAM_WARNING_LOG2(0, OAM_SF_FRW, "{frw_ipc_send::FRW_IPC_CORE_STATE_CONNECTED != g_st_ipc_node[en_type].en_states. en_type:%d, en_states:%d}\r\n", en_type, g_st_ipc_node[en_type].en_states);
        return OAL_FAIL;
    }

    /* ????IPC???? */
    pst_header = (frw_ipc_msg_header_stru *)frw_ipc_get_header(pst_ipc_mem_msg);

    /* ???????????????? */
    pst_header->us_seq_number   = g_st_ipc_node[en_type].us_seq_num_tx_expect;
    pst_header->uc_target_cpuid = g_st_ipc_node[en_type].en_target_cpuid;
    pst_header->uc_msg_type     = FRW_IPC_MSG_TYPE_EVENT;

    /* ???????????? */
    ul_ret = frw_ipc_msg_queue_send_etc(pst_msg_queue,
                                    pst_ipc_mem_msg,
                                    g_st_ipc_node[en_type].en_tx_int_ctl,
                                    g_st_ipc_node[en_type].en_target_cpuid);

    if (OAL_UNLIKELY(OAL_ERR_CODE_IPC_QUEUE_FULL == ul_ret))
    {
    #ifdef _PRE_DEBUG_MODE
        frw_ipc_log_send_alarm_etc(&g_st_ipc_node[en_type].st_log);
    #endif
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send::frw_ipc_msg_queue_send_etc return err code: %d}", OAL_ERR_CODE_IPC_QUEUE_FULL);
        return ul_ret;
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send::frw_ipc_msg_queue_send_etc return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* ?????????? */
    g_st_ipc_node[en_type].us_seq_num_tx_expect++;

    /* ?????????????????????? */
    pst_ipc_mem_msg->uc_user_cnt++;

#ifdef _PRE_DEBUG_MODE
    /* ???????? */
    frw_ipc_log_send_etc(&g_st_ipc_node[en_type].st_log,
                     pst_header->us_seq_number,
                     pst_header->uc_target_cpuid,
                     pst_header->uc_msg_type);
#endif

    return OAL_SUCC;
}


OAL_STATIC oal_void  frw_ipc_tx_complete(frw_ipc_msg_mem_stru *pst_msg)
{
    /* TBD */
}


OAL_STATIC oal_uint32  frw_ipc_init(oal_void)
{
    oal_uint32   ul_ret;

    if(FRW_IPC_CORE_TYPE_MASTER == frw_ipc_get_core_type())
    {
        ul_ret = frw_ipc_init_master(&g_st_ipc_node[FRW_IPC_CORE_TYPE_MASTER]);
    }
    else
    {
        ul_ret = frw_ipc_init_slave(&g_st_ipc_node[FRW_IPC_CORE_TYPE_SLAVE]);
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw ipc init fail.}");
        return ul_ret;
    }

    /* ???????? */
    ul_ret = frw_ipc_send_connect_request();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw ipc connect fail.}");
        return ul_ret;
    }

    /* ?????????????????????????????? */
    frw_event_ipc_event_queue_full_register_etc(frw_ipc_event_queue_full);
    frw_event_ipc_event_queue_empty_register_etc(frw_ipc_event_queue_empty);

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  frw_ipc_init_master(frw_ipc_node_stru *pst_ipc_node)
{
    oal_uint32 ul_ret;

    /* ???????????????? */
    pst_ipc_node->en_cpuid             = FRW_IPC_CORE_ID_MASTER;
    pst_ipc_node->en_target_cpuid      = FRW_IPC_CORE_ID_SLAVE;
    pst_ipc_node->en_cpu_type          = FRW_IPC_CORE_TYPE_MASTER;
    pst_ipc_node->us_seq_num_rx_expect = 0;
    pst_ipc_node->us_seq_num_tx_expect = 0;
    pst_ipc_node->en_states            = FRW_IPC_CORE_STATE_INIT;
    pst_ipc_node->en_tx_int_ctl        = FRW_IPC_TX_CTRL_ENABLED;

    /* ?????????????????????? */
    /* ?????????????? */
    ul_ret = frw_ipc_msg_queue_init_etc(&g_st_queue_master_to_slave,
                                    FRW_IPC_MASTER_TO_SLAVE_QUEUE_MAX_NUM);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_msg_queue_init_etc g_st_queue_master_to_slave return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* ?????????????? */
    ul_ret = frw_ipc_msg_queue_init_etc(&g_st_queue_slave_to_master,
                                    FRW_IPC_SLAVE_TO_MASTER_QUEUE_MAX_NUM);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW,  "{frw_ipc_init_master:: frw_ipc_msg_queue_init_etc g_st_queue_slave_to_master return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* ???????? */
    pst_ipc_node->st_irq_dev.p_irq_intr_func    = frw_ipc_msg_queue_recv_etc;
    pst_ipc_node->st_irq_dev.ul_irq             = OAL_IRQ_NUM;
    pst_ipc_node->st_irq_dev.l_irq_type         = OAL_SA_SHIRQ;
    pst_ipc_node->st_irq_dev.pc_name            = "ipc";
    pst_ipc_node->st_irq_dev.p_drv_arg          = (void *)&g_st_queue_slave_to_master;

    if (OAL_UNLIKELY(0 != oal_irq_setup(&pst_ipc_node->st_irq_dev)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_setup_irq:: oal_irq_setup fail!}");
        return OAL_FAIL;
    }

    /* ???????????? */
    pst_ipc_node->st_ipc_msg_callback.p_rx_complete_func = frw_ipc_recv;
    pst_ipc_node->st_ipc_msg_callback.p_tx_complete_func = frw_ipc_tx_complete;
    ul_ret = frw_ipc_msg_queue_register_callback_etc(&pst_ipc_node->st_ipc_msg_callback);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_msg_queue_register_callback_etc return err code:%d}", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* ?????????? */
    ul_ret = frw_ipc_log_init_etc(&pst_ipc_node->st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_log_init_etc return err code:%d}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;

}



OAL_STATIC oal_uint32  frw_ipc_init_slave(frw_ipc_node_stru *pst_ipc_node)
{
    oal_uint32 ul_ret;

    /* ???????????????? */
    pst_ipc_node->en_cpuid             = (oal_uint8)OAL_GET_CORE_ID();
    pst_ipc_node->en_target_cpuid      = FRW_IPC_CORE_ID_MASTER;
    pst_ipc_node->en_cpu_type          = FRW_IPC_CORE_TYPE_SLAVE;
    pst_ipc_node->us_seq_num_rx_expect = 0;
    pst_ipc_node->us_seq_num_tx_expect = 0;
    pst_ipc_node->en_states            = FRW_IPC_CORE_STATE_INIT;
    pst_ipc_node->en_tx_int_ctl        = FRW_IPC_TX_CTRL_ENABLED;

    /* ???????? */
    pst_ipc_node->st_irq_dev.p_irq_intr_func    = frw_ipc_msg_queue_recv_etc;
    pst_ipc_node->st_irq_dev.ul_irq             = OAL_IRQ_NUM;
    pst_ipc_node->st_irq_dev.l_irq_type         = OAL_SA_SHIRQ;
    pst_ipc_node->st_irq_dev.pc_name            = "ipc";
    pst_ipc_node->st_irq_dev.p_drv_arg          = (void *)&g_st_queue_master_to_slave;

    if (OAL_UNLIKELY(0 != oal_irq_setup(&pst_ipc_node->st_irq_dev)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_setup_irq: oal_irq_setup fail!}");
        return OAL_FAIL;
    }

    /* ???????????? */
    pst_ipc_node->st_ipc_msg_callback.p_rx_complete_func = frw_ipc_recv;
    pst_ipc_node->st_ipc_msg_callback.p_tx_complete_func = frw_ipc_tx_complete;
    ul_ret = frw_ipc_msg_queue_register_callback_etc(&pst_ipc_node->st_ipc_msg_callback);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_slave:: frw_ipc_msg_queue_register_callback_etc return err code:%d}", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* ?????????? */
    ul_ret = frw_ipc_log_init_etc(&pst_ipc_node->st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_slave: frw_ipc_log_init_etc return err code:%d}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;

}


OAL_STATIC oal_uint32  frw_ipc_exit(oal_void)
{
    oal_uint32 ul_ret;
    frw_ipc_core_type_enum_uint8  en_type;       /* CPU????: ?????????? */

    /* ???????????????? */
    en_type = frw_ipc_get_core_type();

    /* ????IPC???????? */
    g_st_ipc_node[en_type].en_states = FRW_IPC_CORE_STATE_EXIT;

    /* ???????????? */
    oal_irq_free(&g_st_ipc_node[en_type].st_irq_dev);

    /* ???????????? */
    if (FRW_IPC_CORE_ID_MASTER == en_type) /* ???? */
    {
        /* ???????????? */
        ul_ret = frw_ipc_msg_queue_destroy_etc(&g_st_queue_master_to_slave);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_exit: frw_ipc_msg_queue_destroy_etc g_st_queue_master_to_slave return err code:%d}", ul_ret);
            return ul_ret;
        }

        /* ???????????? */
        ul_ret = frw_ipc_msg_queue_destroy_etc(&g_st_queue_slave_to_master);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_FRW, "frw_ipc_exit:: frw_ipc_msg_queue_destroy_etc g_st_queue_slave_to_master return err code:%d", ul_ret);
            return ul_ret;
        }
    }

#ifdef _PRE_DEBUG_MODE
    /* ???????????? */
    frw_ipc_log_tx_print_etc(&g_st_ipc_node[en_type].st_log);
    frw_ipc_log_rx_print_etc(&g_st_ipc_node[en_type].st_log);

    /* ???????????? */
    ul_ret = frw_ipc_log_exit_etc(&g_st_ipc_node[en_type].st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        return ul_ret;
    }
#endif

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  frw_ipc_send_connect_request(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_CONNECT_REQUEST,
                                    OAL_PTR_NULL,
                                    0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send_connect_request: frw_ipc_send_inter_msg return %d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  frw_ipc_send_connect_response(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_CONNECT_RESPONSE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send_connect_response: frw_ipc_send_inter_msg return %d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  frw_ipc_send_inter_msg(oal_uint8  uc_msg_type,
                                                       oal_uint8 *puc_data,
                                                       oal_uint8  us_len)
{
    oal_uint32                   ul_ret;
    frw_ipc_msg_mem_stru        *pst_msg_mem_stru;  /* ?????????? */
    frw_ipc_inter_msg_stru      *pst_ipc_msg;       /* ?????????? */
    frw_ipc_msg_queue_stru      *pst_msg_queue;     /* ???????? */
    frw_ipc_core_type_enum_uint8 en_type;           /* CPU????: ?????????? */
    oal_uint8                    ul_length;

    /* ???????????????? */
    en_type = frw_ipc_get_core_type();
    FRW_IPC_GET_MSG_QUEUE(pst_msg_queue, en_type);

    /* ???????????????????? */
    ul_length = OAL_SIZEOF(frw_ipc_inter_msg_stru) - 4 + us_len;
    pst_msg_mem_stru = FRW_EVENT_ALLOC(ul_length);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_mem_stru))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_send_inter_msg: FRW_EVENT_ALLOC fail!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ???????????? */
    pst_ipc_msg = (frw_ipc_inter_msg_stru *)frw_ipc_get_header(pst_msg_mem_stru);

    /* ?????????? */
    pst_ipc_msg->st_ipc_hdr.us_seq_number   = g_st_ipc_node[en_type].us_seq_num_tx_expect;
    pst_ipc_msg->st_ipc_hdr.uc_target_cpuid = g_st_ipc_node[en_type].en_target_cpuid;
    pst_ipc_msg->st_ipc_hdr.uc_msg_type     = uc_msg_type;
    pst_ipc_msg->ul_length                  = us_len;

    /* ???????? */
    if (us_len > 0)
    {
        oal_memcopy((oal_void *)pst_ipc_msg->auc_data, (oal_void *)puc_data, us_len);
    }

    /* ???????????? */
    ul_ret = frw_ipc_msg_queue_send_etc(pst_msg_queue,
                                    pst_msg_mem_stru,
                                    g_st_ipc_node[en_type].en_tx_int_ctl,
                                    g_st_ipc_node[en_type].en_target_cpuid);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{send inter msg fail.}");
        FRW_EVENT_FREE(pst_msg_mem_stru);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* ???????? */
    frw_ipc_log_send_etc(&g_st_ipc_node[en_type].st_log,
                      g_st_ipc_node[en_type].us_seq_num_tx_expect,
                      g_st_ipc_node[en_type].en_target_cpuid,
                      uc_msg_type);
#endif

    /* ?????????? */
    g_st_ipc_node[en_type].us_seq_num_tx_expect++;

    return OAL_SUCC;
}


oal_uint32  frw_ipc_reset_etc(oal_void)
{
    /* TBD */
    return OAL_SUCC;
}


oal_uint32  frw_ipc_smp_dispatch_etc(oal_void *buf)
{
    /* TBD */

    return OAL_SUCC;
}


oal_uint32  frw_ipc_smp_ordering_etc(oal_void *buf)
{
    /* TBD */

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  frw_ipc_event_queue_full(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_TX_INT_DISENABLE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_event_queue_full: frw_ipc_send_inter_msg return err code:%d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  frw_ipc_event_queue_empty(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_TX_INT_ENABLE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_event_queue_empty: frw_ipc_send_inter_msg return err code:%d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


oal_uint32  frw_event_deploy_init_etc(oal_void)
{
    oal_uint32 ul_ret;

    ul_ret = frw_ipc_init();
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw event deploy init fail.}");
        return ul_ret;
    }

    /* TBD */

    /* ?????????????????????????? */

    /* ???????????????????????????????????????????? */

    /* ??????, ??????HMAC DMAC PIPELINE????????????frw_event_deploy_pipeline */

    /* ??????, ??????????CHIP,DEVICE,VAP????????????frw_event_deploy_owner */

    frw_event_deploy_register_etc(frw_event_deploy_pipeline);

    return OAL_SUCC;
}



oal_uint32  frw_event_deploy_exit_etc(oal_void)
{
    oal_uint32 ul_ret;

    ul_ret = frw_ipc_exit();
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw event deploy exit fail.}");
        return ul_ret;
    }

    /* TBD */

    /* ???????????????????????? */

    /* ?????????????????????????????????????????? */

    return OAL_SUCC;
}



OAL_STATIC oal_uint32  frw_event_deploy_pipeline(frw_ipc_msg_mem_stru *pst_ipc_mem_msg,
                                              frw_event_deploy_enum_uint8 *en_deploy_result)
{
    frw_event_hdr_stru *pst_event_hdr;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg) || (OAL_PTR_NULL == en_deploy_result))
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_deploy_pipeline: pst_ipc_mem_msg/en_deploy_result null ptr err:%d, %d}", pst_ipc_mem_msg, en_deploy_result);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_hdr = (frw_event_hdr_stru *)pst_ipc_mem_msg->puc_data;

    if (FRW_EVENT_PIPELINE_STAGE_0 == pst_event_hdr->en_pipeline)
    {
        (*en_deploy_result) = FRW_EVENT_DEPLOY_NON_IPC;
    }
    else
    {
        (*en_deploy_result) = FRW_EVENT_DEPLOY_IPC;

        frw_ipc_send(pst_ipc_mem_msg);
    }

    return OAL_SUCC;
}

#if 0

oal_uint32  frw_event_deploy_owner(frw_ipc_msg_mem_stru *pst_ipc_mem_msg,
                                            frw_event_deploy_enum_uint8 *en_deploy_result)
{
    if ((OAL_PTR_NULL == pst_ipc_mem_msg) || (OAL_PTR_NULL == en_deploy_result))
    {
        FRW_ERR_LOG2(0, "frw_event_deploy_owner: pst_ipc_mem_msg/en_deploy_result null ptr err:", pst_ipc_mem_msg, en_deploy_result);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD */

    /* 1. ????????payload????chip id, device id??vap id */

    /* 2. ????????VAP?????????????????????????????????? */

    /* 3. ????????????????CHIP, DEVICE, VAP???????????? */

    (*en_deploy_result) = FRW_EVENT_DEPLOY_IPC;

    return OAL_SUCC;
}


oal_uint32  frw_event_deploy_set_affinity_device(oal_uint8 uc_device_id,
                                                            oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. ??????????device??????????????????????chip??????????????????: */
    /* ????chip??????????????????????????,??????2??; */
    /* ????chip??coremask????device??????coremask??????????,??????2??; ?????????????????? */

    /* 2. ??????????device??????????????????????vap??????????????????:*/
    /* ????????vap??????????????????????????,??????3??; */
    /* ????device??????coremask????????????????vap??coremask??????????????????;????????????3??; */

    /* 3. ?????????????????????????????????? */
    /* ??????device????????????????????VAP????????????device?????????????????????? */

    return OAL_SUCC;
}


oal_uint32  frw_event_deploy_set_affinity_vap(oal_uint8 uc_vap_id,
                                                        oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. ??????????vap??????????????????????device??????????????????: */
    /* ????device??????????????????????????????????2??; */
    /* ????device??coremask????vap??????coremask??????????????????3??; ?????????????????? */

    /* 2. ??????????vap??????????????????????chip??????????????????: */
    /* ????chip??????????????????????????????????3??; */
    /* ????chip??coremask????vap??????coremask??????????????????3??; ?????????????????? */

    /* 3. ?????????????????????????????????? */

    return OAL_SUCC;
}


oal_uint32  frw_event_deploy_set_affinity_chip(oal_uint8 uc_chip_id,
                                                         oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. ??????????chip??????????????????????device??????????????????:*/
    /* ????????device??????????????????????????????????2??; */
    /* ????chip??????coremask????????????????device??coremask??????????????????; ????????????3?? */

    /* 2. ??????????chip??????????????????????vap??????????????????:*/
    /* ????????vap??????????????????????????????????3??; */
    /* ????chip??????coremask????????????????vap??coremask????????????????????????????????3?? */

    /* 3. ??????????????????????????????????: */
    /* ??????CHIP????????????????????DEVICE??VAP????????????CHIP?????????????????????? */

    return OAL_SUCC;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

