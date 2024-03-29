???/*!
 *****************************************************************************
 *
 * @File       devaio.h
 * @Title      Low-level MTX interface with DEVA PVDEC firmware
 * @Description    This file contains functions to communicate with MTX DEVA PVDEC firmware.
 *  This includes sending and receiving messages and state indicators.
 *  It is a subcomponent of the Decoder block and operates on the Decoder
 *  block state.
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

#if !defined (__DEVAIO_H__)
#define __DEVAIO_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_types.h"
#include "lst.h"

#include "system.h"
#include "vdecfw.h"
#include "vxd_ext.h"

/* Included from PVDEC firmware. */
#include "source/core/vdec_fw_interface.h"

#define DEVAIO_MAX_DBG_TASK_NAME_SIZE     (10)
#define DEVAIO_DEBUG_TEXT_SIZE            (2048)
#define DEVAIO_DEBUG_MAX_PARAMS           (10)

/*!
******************************************************************************
 This structure is used to keep comms buffers details
******************************************************************************/
typedef struct
{
    IMG_UINT32 ui32Offset;
    IMG_UINT32 ui32Size;

} DEVAIO_sBufConfig;


#if (defined(IMG_DEBUG_FLAG) || defined(FW_PERFORMANCE_LOGGING))

/*!
******************************************************************************
 Description of firmware task debug context
******************************************************************************/
typedef struct
{
    LST_LINK;

    IMG_UINT32 ui32TaskSp;                                //!< Stack pointer of this task, used for identification
    IMG_INT32  i32Indent;                                 //!< Logs indent
    IMG_CHAR   acTaskName[DEVAIO_MAX_DBG_TASK_NAME_SIZE]; //!< Name of task, used for logging

} DEVAIO_sDbgTaskDesc;

/*!
******************************************************************************
 Debug fifo context
******************************************************************************/
typedef struct
{
    IMG_BOOL             bReady;          //!< Whether debug fifo context was initialised.
    IMG_HANDLE           hFile;           //!< File used to save debug logs.
#if defined(SYSBRG_BRIDGING)
    IMG_HANDLE           hTimer;          //!< Debug FIFO timer handle.
#endif

    IMG_UINT32           ui32Collecting;  //!< Current state of routine receiving logs from debug fifo

    IMG_UINT32           ui32ParamsCount; //!< Number of parameters in upcoming chunk of debug data
    IMG_UINT32           ui32DataIndex;   //!< Write offset in aui32DebugData
    IMG_UINT32           aui32DebugData[DEVAIO_DEBUG_MAX_PARAMS];
                                          //!< Buffer used to collect data from debug fifo

    IMG_CHAR             acText[DEVAIO_DEBUG_TEXT_SIZE];
                                          //!< Decoded log message

    LST_T                asDbgTasks;      //!< List of tasks debug context sDEVAIO_sDbgTaskDesc

    IMG_UINT32           ui32FifoSize;
#ifdef VDEC_USE_PVDEC_SEC
    IMG_BOOL             bSecureFwLogs;
#endif

} DEVAIO_DebugFifo;
#endif /* (defined(IMG_DEBUG_FLAG) || defined(FW_PERFORMANCE_LOGGING)) */

/*!
******************************************************************************
 This structure is used to retain DEVA IO specific data for a particular core
******************************************************************************/
typedef struct
{
    IMG_HANDLE       *  hPvdecIoCtx;

    /* Queue of headers for messages read from MTX */
    LST_T               sFreeMsgList;                       //!< List of free messages
    LST_T               sActiveMsgList;                     //!< List of active messages

    DEVAIO_sBufConfig   sToMtxBuf;                          //!< Config of buffer for communication host -> MTX
    DEVAIO_sBufConfig   sToHostBuf;                         //!< Config of buffer for communication MTX -> host

    IMG_BOOL            bReady;                             //!< Whether communication areas were already intialized.

#if defined(IMG_DEBUG_FLAG) || defined(FW_PERFORMANCE_LOGGING)
    DEVAIO_DebugFifo    sDebugFifo;
#endif

} DEVAIO_sContext;

/*!
******************************************************************************

 @Function              DEVAIO_InitMTXComms

 @Description

 This function should be called before sending any messages to FW

 It sets up DEVAIO context required for MTX communication.

 @Input     hPvdecIoCtx    : Handle to PVDECIO context.

 @Input     psContext      : A pointer to DEVAIO context.

 @Input     bSecureFw      : Whether secure firmware (FWBSP flow) is used.

 @Return    IMG_RESULT     : This function returns either IMG_SUCCESS or an
                             error code.

******************************************************************************/
extern IMG_RESULT
DEVAIO_InitMTXComms(
    IMG_HANDLE       * hPvdecIoCtx,
    DEVAIO_sContext  * psContext,
    IMG_BOOL           bSecureFw
);

/*
******************************************************************************

 @Function              DEVAIO_SendMTXMsg

 @Description

 This function sends message to firmware

 @Input     psContext      : A pointer to DEVAIO context.

 @Input     psMsgHdr       : A pointer to buffer with message in DEVA format.

 @Input     hPvdecIoCtx    : A handle to PVDECIO context.

 @Return    IMG_RESULT     : This function returns either IMG_SUCCESS or an
                             error code.

******************************************************************************/
extern IMG_RESULT
DEVAIO_SendMTXMsg(
    DEVAIO_sContext    * psContext,
    const IMG_VOID     * psMsgHdr,
    const IMG_HANDLE     hPvdecIoCtx
);


/*
******************************************************************************

 @Function              DEVAIO_ProcessMTXMsgs

 @Description

 This function is called to process messages from MTX to the host.  This would
 usually be done in an interrupt service routine.


 @Input     psContext       : Pointer to the DEVAIO context.

 @Output    psMsgQStatus    : Pointer to message queue resources.

 @Return    IMG_RESULT      : This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
extern IMG_RESULT
DEVAIO_ProcessMTXMsgs(
    DEVAIO_sContext   * psContext,
    VXD_sMsgQueue     * psMsgQStatus
);

/*
******************************************************************************

 @Function              DEVAIO_ProcessMTXMsgs

 @Description

 This function is called to obtain MMU report.  This would
 usually be done in an interrupt service routine.


 @Input     psContext       : Pointer to the DEVAIO context.

 @Output    pui32Status0    : Pointer to status0.

 @Output    pui32Status1    : Pointer to status1.

 @Return    IMG_RESULT      : This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
IMG_RESULT DEVAIO_ProcessMMUReport(
    DEVAIO_sContext  * psContext,
    IMG_UINT32       * pui32Status0,
    IMG_UINT32       * pui32Status1
);

#if (defined(IMG_DEBUG_FLAG) || defined(FW_PERFORMANCE_LOGGING))
/*!
******************************************************************************

 @Function              DEVAIO_HandleDebugFifo

 @Description

 This function processes PVDEC debug FIFO which contains firmware logs.

 @Input     psContext       : Pointer to the DEVAIO context.

 @Return    none.

******************************************************************************/
extern IMG_VOID
DEVAIO_HandleDebugFifo(
    DEVAIO_sContext   * psContext
);

/*!
******************************************************************************

 @Function              DEVAIO_CloseDebugFifo

 @Description

 This function deinitialises debug fifo context.

 @Input     psContext       : Pointer to the DEVAIO context.

 @Return    IMG_RESULT      : This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
extern IMG_RESULT
DEVAIO_CloseDebugFifo(
    DEVAIO_sContext    * psContext
);

#ifdef VDEC_USE_PVDEC_SEC
/*!
******************************************************************************

 @Function              DEVAIO_SelectSecureFwLogs

 @Description

 This function selects secure firmware logs database.

 @Input     psContext       : Pointer to the DEVAIO context.

 @Return    IMG_VOID        :

******************************************************************************/
extern IMG_VOID DEVAIO_SelectSecureFwLogs(
    DEVAIO_sContext * psContext
);
#endif

/*!
******************************************************************************

 @Function              DEVAIO_EnableDebugFifo

 @Description

 This function enables debug fifo.

 @Input     psContext       : Pointer to the DEVAIO context.

 @Return    IMG_VOID        :

******************************************************************************/
extern IMG_VOID
DEVAIO_EnableDebugFifo(
    DEVAIO_sContext    * psContext
);

/*!
******************************************************************************

 @Function              DEVAIO_DisableDebugFifo

 @Description

 This function disables debug fifo.

 @Input     psContext       : Pointer to the DEVAIO context.

 @Return    IMG_VOID        :

******************************************************************************/
extern IMG_VOID
DEVAIO_DisableDebugFifo(
    DEVAIO_sContext    * psContext
);

/*!
******************************************************************************

 @Function              DEVAIO_GetDebugFifoSize

 @Description

 This function returns debug fifo size..

 @Input     psContext       : Pointer to the DEVAIO context.

 @Return    IMG_RESULT      : Debug fifo size.

******************************************************************************/
extern IMG_UINT32
DEVAIO_GetDebugFifoSize(
    DEVAIO_sContext    * psContext
);

#endif /* (defined(IMG_DEBUG_FLAG) || defined(FW_PERFORMANCE_LOGGING))*/

#if defined(__cplusplus)
}
#endif

#endif /* __DEVAIO_H__ */



