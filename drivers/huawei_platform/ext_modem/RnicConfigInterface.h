

#ifndef __RNICCONFIGINTERFACE_H__
#define __RNICCONFIGINTERFACE_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define RNIC_MODEM_TYPE_IS_VALID(enModemType)\
    (((enModemType) == RNIC_MODEM_TYPE_INSIDE)\
  || ((enModemType) == RNIC_MODEM_TYPE_OUTSIDE))

#define RNIC_RMNET_STATUS_IS_VALID(enRmnetStatus)\
    (((enRmnetStatus) == RNIC_RMNET_STATUS_UP) \
  || ((enRmnetStatus) == RNIC_RMNET_STATUS_DOWN) \
  || ((enRmnetStatus) == RNIC_RMNET_STATUS_SWITCH))

#define RNIC_IP_TYPE_IS_VALID(enIpType)\
    (((enIpType) == RNIC_IP_TYPE_IPV4) \
  || ((enIpType) == RNIC_IP_TYPE_IPV6) \
  || ((enIpType) == RNIC_IP_TYPE_IPV4V6))

/*****************************************************************************
   3 ????????
*****************************************************************************/

	enum RNIC_MODEM_TYPE_ENUM {
		RNIC_MODEM_TYPE_INSIDE,	/* ????modem */
		RNIC_MODEM_TYPE_OUTSIDE,	/* ????modem */

		RNIC_MODEM_TYPE_BUTT
	};

	typedef unsigned char RNIC_MODEM_TYPE_ENUM_UINT8;


	enum RNIC_RMNET_STATUS_ENUM {
		RNIC_RMNET_STATUS_UP,	/* PDP??????????????up???? */
		RNIC_RMNET_STATUS_DOWN,	/* PDP????????????????down???? */
		RNIC_RMNET_STATUS_SWITCH,	/* ????modem PDP??????????????????switch???? */

		RNIC_RMNET_STATUS_BUTT
	};

	typedef unsigned char RNIC_RMNET_STATUS_ENUM_UINT8;


	enum RNIC_IP_TYPE_ENUM {
		RNIC_IP_TYPE_IPV4 = 0x01,
		RNIC_IP_TYPE_IPV6 = 0x02,
		RNIC_IP_TYPE_IPV4V6 = 0x03,

		RNIC_IP_TYPE_BUTT = 0xFF
	};

	typedef unsigned char RNIC_IP_TYPE_ENUM_UINT8;


	typedef struct {
		RNIC_MODEM_TYPE_ENUM_UINT8 enModemType;
		unsigned char ucRmNetId;
		unsigned short usModemId;
		unsigned char ucPdnId;
		unsigned char ucRabId;
		RNIC_RMNET_STATUS_ENUM_UINT8 enRmnetStatus;
		RNIC_IP_TYPE_ENUM_UINT8 enIpType;
	} RNIC_RMNET_CONFIG_STRU;

/*****************************************************************************
   10 ????????
*****************************************************************************/

/* RNIC???????????????????????????????? */
	unsigned long RNIC_ConfigRmnetStatus(RNIC_RMNET_CONFIG_STRU *
					     pstConfigInfo);

/*****************************************************************************
 ?? ?? ??  : RNIC_StartFlowCtrl
 ????????  : ????????????
 ????????  : ucRmNetId : ????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK     - ????????????
			VOS_ERR    - ????????????
 ????????  :
 ????????  :
*****************************************************************************/
	unsigned int RNIC_StartFlowCtrl(unsigned char ucRmNetId);

/*****************************************************************************
 ?? ?? ??  : RNIC_StopFlowCtrl
 ????????  : ????????????
 ????????  : ucRmNetId : ????ID
 ????????  : ??
 ?? ?? ??  : VOS_OK     - ????????????
			VOS_ERR    - ????????????
 ????????  :
 ????????  :
*****************************************************************************/
	unsigned int RNIC_StopFlowCtrl(unsigned char ucRmNetId);

#pragma pack(0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif				/* end of RnicConfigInterface.h */
