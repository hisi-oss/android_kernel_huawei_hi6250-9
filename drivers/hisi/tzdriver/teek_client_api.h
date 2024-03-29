/**
 * @file tee_client_api.h
 *
 * Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ??????????????????????????\n
 */

/** @defgroup TEEC_API ??????(????????)????
 */
/**@defgroup TEEC_BASIC_FUNC ????????
 *@ingroup TEEC_API
*/

#ifndef _TEEK_CLIENT_API_H_
#define _TEEK_CLIENT_API_H_

#include "teek_client_type.h"

/**
 * @ingroup TEEC_BASIC_FUNC
 * ??????????????????????????????????????????
 */
#define TEEC_PARAM_TYPES(param0Type, param1Type, param2Type, param3Type) \
	((param3Type) << 12 | (param2Type) << 8 | \
	 (param1Type) << 4 | (param0Type))

/**
 * @ingroup TEEC_BASIC_FUNC
 * ????????paramTypes??????index??????
 */
#define TEEC_PARAM_TYPE_GET(paramTypes, index) \
	(((paramTypes) >> (4*(index))) & 0x0F)

/**
 * @ingroup TEEC_BASIC_FUNC
 * ????????????#TEEC_Value????????????????a??b????????????????????????
 * ??????????????????????
 */
#define TEEC_VALUE_UNDEF 0xFFFFFFFF

/*
 * Function:      TEEK_IsAgentAlive
 * Description:   This function check if the special agent is launched.
 *              Used For HDCP key.
 *                e.g. If sfs agent is not alive,
 *                you can not do HDCP key write to SRAM.
 * Parameters:   agent_id.
 * Return:      1:agent is alive
 *              0:agent not exsit.
 */
int TEEK_IsAgentAlive(unsigned int agent_id);
/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ??????TEE????
 *
 * @par ????:
 * ????????????name??TEE??????????name??????????
 * ??????TEE????????????????????????????????
 * ??????????????????????????TEE??????????????
 *
 * @attention ??
 * @param name [IN] TEE????????
 * @param context [IN/OUT] context??????????????????????
 *
 * @retval #TEEC_SUCCESS ??????TEE????????
 * @retval #TEEC_ERROR_BAD_PARAMETERS ????????????name????????context????
 * @retval #TEEC_ERROR_GENERIC ??????????????????????
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see TEEC_FinalizeContext
 * @since V100R002C00B301
 */
TEEC_Result TEEK_InitializeContext(const char *name, TEEC_Context *context);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ????TEE????
 *
 * @par ????:
 * ????context??????TEE??????????????????????TEE??????????
 *
 * @attention ??
 * @param context [IN/OUT] ??????????????????TEE????
 *
 * @retval ??
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see TEEC_InitializeContext
 * @since V100R002C00B301
 */
void TEEK_FinalizeContext(TEEC_Context *context);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ????????
 *
 * @par ????:
 * ????????TEE????context??????????????????UUID
 * ??destination????????????????????????
 * ??????????connectionMethod????????????connectionData,
 * ????????????????opetation????
 * ????????????????????????session??????????????????????
 * ??????????????????????????returnOrigin????????????
 *
 * @attention ??
 * @param context [IN/OUT] ??????????????????TEE????
 * @param session [OUT] ??????????????????????
 * @param destination [IN] ??????????UUID????????????????????????UUID
 * @param connectionMethod [IN] ????????????????????#TEEC_LoginMethod
 * @param connectionData [IN] ????????????????????????????
 * ??????????????#TEEC_LOGIN_PUBLIC, #TEEC_LOGIN_USE,
 * #TEEC_LOGIN_USER_APPLICATION,
 * #TEEC_LOGIN_GROUP_APPLICATION, ??????????????????????
 * ??????????????#TEEC_LOGIN_GROUP??#TEEC_LOGIN_GROUP_APPLICATION??
 * ??????????????????????uint32_t????????????????????????????????????????????
 * @param operation [IN/OUT] ??????????????????????????????
 * @param returnOrigin [IN/OUT] ????????????????????#TEEC_ReturnCodeOrigin
 *
 * @retval #TEEC_SUCCESS ????????????
 * @retval #TEEC_ERROR_BAD_PARAMETERS ????????????????context??????session??????destination????
 * @retval #TEEC_ERROR_ACCESS_DENIED ????????????????????
 * @retval #TEEC_ERROR_OUT_OF_MEMORY ????????????????
 * @retval #TEEC_ERROR_TRUSTED_APP_LOAD_ERROR ????????????????
 * @retval ?????????????? #TEEC_ReturnCode
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see TEEC_CloseSession
 * @since V100R002C00B301
 */
TEEC_Result TEEK_OpenSession(TEEC_Context *context,
			     TEEC_Session *session,
			     const TEEC_UUID *destination,
			     uint32_t connectionMethod,
			     const void *connectionData,
			     TEEC_Operation *operation,
			     uint32_t *returnOrigin);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ????????
 *
 * @par ????:
 * ????session??????????????????????????????????????????
 *
 * @attention ??
 * @param session [IN/OUT] ????????????????????
 *
 * @retval ??
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see TEEC_OpenSession
 * @since V100R002C00B301
 */
void TEEK_CloseSession(TEEC_Session *session);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ????????
 *
 * @par ????:
 * ????????????session??????????????????????????????????commandID??
 * ????????????operation????????????????????????????returnOrigin??????????
 *
 * @attention ??
 * @param session [IN/OUT] ????????????????????
 * @param commandID [IN] ??????????????????ID????????????????
 * @param operation [IN/OUT] ????????????????????????????????????????
 * @param returnOrigin [IN/OUT] ????????????????????#TEEC_ReturnCodeOrigin
 *
 * @retval #TEEC_SUCCESS ????????????
 * @retval #TEEC_ERROR_BAD_PARAMETERS ????????????????session??????????operation??????????
 * @retval #TEEC_ERROR_ACCESS_DENIED ????????????????????
 * @retval #TEEC_ERROR_OUT_OF_MEMORY ????????????????
 * @retval ?????????????? #TEEC_ReturnCode
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see ??
 * @since V100R002C00B301
 */
TEEC_Result TEEK_InvokeCommand(TEEC_Session *session,
			       uint32_t commandID,
			       TEEC_Operation *operation,
			       uint32_t *returnOrigin);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ????????????
 *
 * @par ????:
 * ????????TEE????context??????????????sharedMem??
 * ??????????????????????????????????????????????????????????
 * ??????????????????????????????????
 *
 * @attention ????????sharedMem??size????????0????????????????????????????????
 * ??????????????????????????????
 * @param context [IN/OUT] ??????????????TEE????
 * @param sharedMem [IN/OUT] ????????????????????????????????????????????????????????
 *
 * @retval #TEEC_SUCCESS ????????????
 * @retval #TEEC_ERROR_BAD_PARAMETERS ????????????????context??????sharedMem??????
 * ??????????????????????????
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see TEEC_AllocateSharedMemory
 * @since V100R002C00B301
 */
TEEC_Result TEEK_RegisterSharedMemory(TEEC_Context *context,
				      TEEC_SharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ????????????
 *
 * @par ????:
 * ????????TEE????context??????????????sharedMem??
 * ??????????????????????????????????????????????????????????
 *
 * @attention ????????sharedMem??size????????0????????????????????????????????
 * ??????????????????????????????????????????
 * @param context [IN/OUT] ??????????????TEE????
 * @param sharedMem [IN/OUT] ????????????????????????????????????
 *
 * @retval #TEEC_SUCCESS ????????????
 * @retval #TEEC_ERROR_BAD_PARAMETERS ????????????????context??????sharedMem????
 * @retval #TEEC_ERROR_OUT_OF_MEMORY ??????????????????????????
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see TEEC_RegisterSharedMemory
 * @since V100R002C00B301
 */
TEEC_Result TEEK_AllocateSharedMemory(TEEC_Context *context,
				      TEEC_SharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief ????????????
 *
 * @par ????:
 * ????????????????????????????????????????sharedMem
 *
 * @attention ??????????#TEEC_AllocateSharedMemory????????????????????
 * ????????????????????????????????#TEEC_RegisterSharedMemory????
 * ??????????????????????????????????????????????????????
 * @param sharedMem [IN/OUT] ??????????????????????????????????
 *
 * @retval ??
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see TEEC_RegisterSharedMemory | TEEC_AllocateSharedMemory
 * @since V100R002C00B301
 */
void TEEK_ReleaseSharedMemory(TEEC_SharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief cancel API
 *
 * @par ????:
 * ????????????????????open Session??????????invoke command
 * ????????cancel??signal??????????
 *
 * @attention ????????????????????cancel????????????????cancel????????????TEE ?? TA????
 * @param operation [IN/OUT] ????????????????????????????????????????
 *
 * @retval ??
 *
 * @par ????:
 * @li libteec????????????????????
 * @li tee_client_api.h??????????????????????
 * @see ??
 * @since V100R002C00B309
 */
void TEEK_RequestCancellation(TEEC_Operation *operation);

#endif

