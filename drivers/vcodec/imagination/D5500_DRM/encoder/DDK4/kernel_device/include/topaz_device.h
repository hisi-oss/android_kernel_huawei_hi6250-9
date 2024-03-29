???/*!
 *****************************************************************************
 *
 * @File       topaz_device.h
 * @Title      Topaz kernel driver data structures
 * @Description    Topaz kernel driver data structures
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#if !defined (__TOPAZ_DEVICE_H__)
#define __TOPAZ_DEVICE_H__

#include <img_defs.h>
#include <sysdev_utils.h>
#include <topazscfwif.h>
#include <MTX_FwIF.h>

#if defined(__cplusplus)
extern "C" {
#endif

struct IMG_COMM_SOCKET_tag;
struct tag_IMG_FW_CONTEXT;

/*!
******************************************************************************
 This structure contains the device context.
******************************************************************************/
typedef struct
{
	IMG_CHAR *				pszDeviceName;			/*!< Device name. */
	SYSDEVU_sInfo *				hSysDevHandle;			/*!< SYSDEVKN device handle */
	IMG_HANDLE				ui32MultiCoreMemSpaceId;
	IMG_UINT32				bInitialised;			/*!< Indicates that the device driver has been initialised */
	IMG_UINT32				usedSockets;
	struct IMG_COMM_SOCKET_tag *deviceSockets[TOPAZHP_MAX_POSSIBLE_STREAMS];

	IMG_HANDLE				hResBHandle; /*!< Resource bucket handle */
	IMG_CODEC				firmwareUploaded;
	IMG_FW_CONTEXT			sFwCtxt;
	IMG_UINT32				psHibernateRegCopy[54];				//!< Copy of HW Register block during hibernate

	IMG_HANDLE				commTxLock;
	IMG_HANDLE				commRxLock;
} TOPAZKM_DevContext;

typedef struct {
	IMG_HANDLE				hResBHandle; /*!< Resource bucket handle */
} TOPAZKM_ConnData;

#define COMM_INCOMING_FIFO_SIZE	(WB_FIFO_SIZE * 2)
typedef struct IMG_COMM_SOCKET_tag
{
	IMG_UINT8	ui8SocketId;
	IMG_UINT32	ui32LowCmdCount;               	//!< count of low-priority commands sent to TOPAZ
	IMG_UINT32	ui32HighCmdCount;              	//!< count of high-priority commands sent to TOPAZ
	IMG_UINT32	ui32LastSync;					//!< Last sync value sent
	IMG_WRITEBACK_MSG	asIncomingFifo[COMM_INCOMING_FIFO_SIZE];
	IMG_UINT32	ui32IncomingFifo_Consumer;
	IMG_UINT32	ui32IncomingFifo_Producer;

	IMG_UINT32	ui32MsgsSent;
	IMG_UINT32	ui32AckReceived;
	IMG_BOOL	bIsSerialized;

	IMG_CODEC	eCodec;

	IMG_HANDLE	hResBHandle;
	IMG_UINT32	ui32ResourceId;
	IMG_HANDLE	isrEvent;

	TOPAZKM_DevContext *devContext;
	TOPAZKM_ConnData *connData;

#if defined(POLL_FOR_INTERRUPT)
	IMG_BOOL	bClientIsWaiting;
#endif
} IMG_COMM_SOCKET;


#if defined(__cplusplus)
}
#endif
 
#endif /* __TOPAZ_DEVICE_H__	*/

