???/*!
 *****************************************************************************
 *
 * @File       report_modules.h
 * @Title      REPORT MODULES
 * @Description    This file contains the header file information for the
 *  REPORT API MODULES
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

#if !defined (__REPORT_MODULES_H__)
#define __REPORT_MODULES_H__

/**
 * @page REPORT MODULES
 *

  Following modules are defined for reporting purposes:

    REPORT_MODULE_ALL        (should not be used for reporting, only for configuration)

    REPORT_MODULE_VDECAPI
    REPORT_MODULE_BSPP
    REPORT_MODULE_BSPPSYNT
    REPORT_MODULE_VDECTEST
    REPORT_MODULE_FWRKTEST
    REPORT_MODULE_MMF
    REPORT_MODULE_READER
    REPORT_MODULE_RENDER
    REPORT_MODULE_VERIF

    REPORT_MODULE_SKIAHW

    REPORT_MODULE_DEVIF

    REPORT_MODULE_FW

    REPORT_MODULE_DEVICEIO
    REPORT_MODULE_IBUF
    REPORT_MODULE_PALLOC
    REPORT_MODULE_VDECCOMP
    REPORT_MODULE_WRAPU
    REPORT_MODULE_XBUF

    REPORT_MODULE_PDP
    REPORT_MODULE_NULLDEV

    REPORT_MODULE_CORE
    REPORT_MODULE_PLANT
    REPORT_MODULE_RESOURCE
    REPORT_MODULE_SCHEDULER
    REPORT_MODULE_DECODER
    REPORT_MODULE_FWBSP_BRIDGE
    REPORT_MODULE_HWCTRL
    REPORT_MODULE_VXDIO
    REPORT_MODULE_MTXIO
    REPORT_MODULE_VDECDD
    REPORT_MODULE_MMU

    REPORT_MODULE_LISTUTILS

    REPORT_MODULE_OMX
    REPORT_MODULE_OMXTEST

    REPORT_MODULE_OSA

    REPORT_MODULE_DBGOPT
    REPORT_MODULE_DMAN
    REPORT_MODULE_IDGEN
    REPORT_MODULE_PERFLOG
    REPORT_MODULE_PMAN
    REPORT_MODULE_POOL
    REPORT_MODULE_REPORT
    REPORT_MODULE_RMAN
    REPORT_MODULE_SYSBRG
    REPORT_MODULE_SYSDEV
    REPORT_MODULE_SYSENV
    REPORT_MODULE_SYSMEM
    REPORT_MODULE_SYSOS
    REPORT_MODULE_UMP

    REPORT_MODULE_RPC
    REPORT_MODULE_TAL

    REPORT_MODULE_SWSR
    REPORT_MODULE_VLC

    REPORT_MODULE_MAX        (should not be used)
 */

#if defined(__cplusplus)
extern "C" {
#endif

#define REPORT_MODULE_TEXT_ALL          "all"

#define REPORT_MODULE_TEXT_VDECAPI      "vdecapi"
#define REPORT_MODULE_TEXT_BSPP         "bspp"
#define REPORT_MODULE_TEXT_BSPPSYNT     "bsppsynt"
#define REPORT_MODULE_TEXT_VDECTEST     "vdectest"
#define REPORT_MODULE_TEXT_FWRKTEST     "fwrktest"
#define REPORT_MODULE_TEXT_MMF          "mmf"
#define REPORT_MODULE_TEXT_READER       "reader"
#define REPORT_MODULE_TEXT_RENDER       "render"
#define REPORT_MODULE_TEXT_VERIF        "verif"

#define REPORT_MODULE_TEXT_SKIAHW       "skiahw"

#define REPORT_MODULE_TEXT_DEVIF        "devif"

#define REPORT_MODULE_TEXT_FW           "firmware"

#define REPORT_MODULE_TEXT_DEVICEIO     "deviceio"
#define REPORT_MODULE_TEXT_IBUF         "ibuf"
#define REPORT_MODULE_TEXT_PALLOC       "palloc"
#define REPORT_MODULE_TEXT_VDECCOMP     "vdeccomp"
#define REPORT_MODULE_TEXT_WRAPU        "wrapu"
#define REPORT_MODULE_TEXT_XBUF         "xbuf"

#define REPORT_MODULE_TEXT_PDP          "pdp"
#define REPORT_MODULE_TEXT_NULLDEV      "nulldev"

#define REPORT_MODULE_TEXT_CORE         "core"
#define REPORT_MODULE_TEXT_PLANT        "plant"
#define REPORT_MODULE_TEXT_RESOURCE     "resource"
#define REPORT_MODULE_TEXT_SCHEDULER    "scheduler"
#define REPORT_MODULE_TEXT_DECODER      "decoder"
#define REPORT_MODULE_TEXT_FWBSP_BRIDGE "fwbsp_bridge"
#define REPORT_MODULE_TEXT_HWCTRL       "hwctrl"
#define REPORT_MODULE_TEXT_VXDIO        "vxdio"
#define REPORT_MODULE_TEXT_MTXIO        "mtxio"
#define REPORT_MODULE_TEXT_VDECDD       "vdecdd"
#define REPORT_MODULE_TEXT_MMU          "mmu"

#define REPORT_MODULE_TEXT_LISTUTILS    "listutils"

#define REPORT_MODULE_TEXT_OMX          "omx"
#define REPORT_MODULE_TEXT_OMXTEST      "omxtest"

#define REPORT_MODULE_TEXT_OSA          "osa"

#define REPORT_MODULE_TEXT_DBGOPT       "dbgopt"
#define REPORT_MODULE_TEXT_DMAN         "dman"
#define REPORT_MODULE_TEXT_IDGEN        "idgen"
#define REPORT_MODULE_TEXT_PERFLOG      "perflog"
#define REPORT_MODULE_TEXT_PMAN         "pman"
#define REPORT_MODULE_TEXT_POOL         "pool"
#define REPORT_MODULE_TEXT_REPORT       "report"
#define REPORT_MODULE_TEXT_RMAN         "rman"
#define REPORT_MODULE_TEXT_SYSBRG       "sysbrg"
#define REPORT_MODULE_TEXT_SYSDEV       "sysdev"
#define REPORT_MODULE_TEXT_SYSENV       "sysenv"
#define REPORT_MODULE_TEXT_SYSMEM       "sysmem"
#define REPORT_MODULE_TEXT_SYSOS        "sysos"
#define REPORT_MODULE_TEXT_UMP          "ump"

#define REPORT_MODULE_TEXT_RPC          "rpc"
#define REPORT_MODULE_TEXT_TAL          "tal"

#define REPORT_MODULE_TEXT_SWSR         "swsr"
#define REPORT_MODULE_TEXT_VLC          "vlc"

#if defined(IMG_KERNEL_MODULE) || defined(ANDROID)

#define REPORT_MODULE_ALL          REPORT_MODULE_TEXT_ALL

#define REPORT_MODULE_VDECAPI      REPORT_MODULE_TEXT_VDECAPI
#define REPORT_MODULE_BSPP         REPORT_MODULE_TEXT_BSPP
#define REPORT_MODULE_BSPPSYNT     REPORT_MODULE_TEXT_BSPPSYNT
#define REPORT_MODULE_VDECTEST     REPORT_MODULE_TEXT_VDECTEST
#define REPORT_MODULE_FWRKTEST     REPORT_MODULE_TEXT_FWRKTEST
#define REPORT_MODULE_MMF          REPORT_MODULE_TEXT_MMF
#define REPORT_MODULE_READER       REPORT_MODULE_TEXT_READER
#define REPORT_MODULE_RENDER       REPORT_MODULE_TEXT_RENDER
#define REPORT_MODULE_VERIF        REPORT_MODULE_TEXT_VERIF

#define REPORT_MODULE_SKIAHW       REPORT_MODULE_TEXT_SKIAHW

#define REPORT_MODULE_DEVIF        REPORT_MODULE_TEXT_DEVIF

#define REPORT_MODULE_FW           REPORT_MODULE_TEXT_FW

#define REPORT_MODULE_DEVICEIO     REPORT_MODULE_TEXT_DEVICEIO
#define REPORT_MODULE_IBUF         REPORT_MODULE_TEXT_IBUF
#define REPORT_MODULE_PALLOC       REPORT_MODULE_TEXT_PALLOC
#define REPORT_MODULE_VDECCOMP     REPORT_MODULE_TEXT_VDECCOMP
#define REPORT_MODULE_WRAPU        REPORT_MODULE_TEXT_WRAPU
#define REPORT_MODULE_XBUF         REPORT_MODULE_TEXT_XBUF

#define REPORT_MODULE_PDP          REPORT_MODULE_TEXT_PDP
#define REPORT_MODULE_NULLDEV      REPORT_MODULE_TEXT_NULLDEV

#define REPORT_MODULE_CORE         REPORT_MODULE_TEXT_CORE
#define REPORT_MODULE_PLANT        REPORT_MODULE_TEXT_PLANT
#define REPORT_MODULE_RESOURCE     REPORT_MODULE_TEXT_RESOURCE
#define REPORT_MODULE_SCHEDULER    REPORT_MODULE_TEXT_SCHEDULER
#define REPORT_MODULE_DECODER      REPORT_MODULE_TEXT_DECODER
#define REPORT_MODULE_FWBSP_BRIDGE REPORT_MODULE_TEXT_FWBSP_BRIDGE
#define REPORT_MODULE_HWCTRL       REPORT_MODULE_TEXT_HWCTRL
#define REPORT_MODULE_VXDIO        REPORT_MODULE_TEXT_VXDIO
#define REPORT_MODULE_MTXIO        REPORT_MODULE_TEXT_MTXIO
#define REPORT_MODULE_VDECDD       REPORT_MODULE_TEXT_VDECDD
#define REPORT_MODULE_MMU          REPORT_MODULE_TEXT_MMU

#define REPORT_MODULE_LISTUTILS    REPORT_MODULE_TEXT_LISTUTILS

#define REPORT_MODULE_OMX          REPORT_MODULE_TEXT_OMX
#define REPORT_MODULE_OMXTEST      REPORT_MODULE_TEXT_OMXTEST

#define REPORT_MODULE_OSA          REPORT_MODULE_TEXT_OSA

#define REPORT_MODULE_DBGOPT       REPORT_MODULE_TEXT_DBGOPT
#define REPORT_MODULE_DMAN         REPORT_MODULE_TEXT_DMAN
#define REPORT_MODULE_IDGEN        REPORT_MODULE_TEXT_IDGEN
#define REPORT_MODULE_PERFLOG      REPORT_MODULE_TEXT_PERFLOG
#define REPORT_MODULE_PMAN         REPORT_MODULE_TEXT_PMAN
#define REPORT_MODULE_POOL         REPORT_MODULE_TEXT_POOL
#define REPORT_MODULE_REPORT       REPORT_MODULE_TEXT_REPORT
#define REPORT_MODULE_RMAN         REPORT_MODULE_TEXT_RMAN
#define REPORT_MODULE_SYSBRG       REPORT_MODULE_TEXT_SYSBRG
#define REPORT_MODULE_SYSDEV       REPORT_MODULE_TEXT_SYSDEV
#define REPORT_MODULE_SYSENV       REPORT_MODULE_TEXT_SYSENV
#define REPORT_MODULE_SYSMEM       REPORT_MODULE_TEXT_SYSMEM
#define REPORT_MODULE_SYSOS        REPORT_MODULE_TEXT_SYSOS
#define REPORT_MODULE_UMP          REPORT_MODULE_TEXT_UMP

#define REPORT_MODULE_RPC          REPORT_MODULE_TEXT_RPC
#define REPORT_MODULE_TAL          REPORT_MODULE_TEXT_TAL

#define REPORT_MODULE_SWSR         REPORT_MODULE_TEXT_SWSR
#define REPORT_MODULE_VLC          REPORT_MODULE_TEXT_VLC

#else /* defined(IMG_KERNEL_MODULE) */


typedef enum
{
    REPORT_MODULE_ALL      = 0,

    REPORT_MODULE_VDECAPI,
    REPORT_MODULE_BSPP,
    REPORT_MODULE_BSPPSYNT,
    REPORT_MODULE_VDECTEST,
    REPORT_MODULE_FWRKTEST,
    REPORT_MODULE_MMF,
    REPORT_MODULE_READER,
    REPORT_MODULE_RENDER,
    REPORT_MODULE_VERIF,

    REPORT_MODULE_SKIAHW,

    REPORT_MODULE_DEVIF,

    REPORT_MODULE_FW,

    REPORT_MODULE_DEVICEIO,
    REPORT_MODULE_IBUF,
    REPORT_MODULE_PALLOC,
    REPORT_MODULE_VDECCOMP,
    REPORT_MODULE_WRAPU,
    REPORT_MODULE_XBUF,

    REPORT_MODULE_PDP,
    REPORT_MODULE_NULLDEV,

    REPORT_MODULE_CORE,
    REPORT_MODULE_PLANT,
    REPORT_MODULE_RESOURCE,
    REPORT_MODULE_SCHEDULER,
    REPORT_MODULE_DECODER,
    REPORT_MODULE_FWBSP_BRIDGE,
    REPORT_MODULE_HWCTRL,
    REPORT_MODULE_VXDIO,
    REPORT_MODULE_MTXIO,
    REPORT_MODULE_VDECDD,
    REPORT_MODULE_MMU,

    REPORT_MODULE_LISTUTILS,

    REPORT_MODULE_OMX,
    REPORT_MODULE_OMXTEST,

    REPORT_MODULE_OSA,

    REPORT_MODULE_DBGOPT,
    REPORT_MODULE_DMAN,
    REPORT_MODULE_IDGEN,
    REPORT_MODULE_PERFLOG,
    REPORT_MODULE_PMAN,
    REPORT_MODULE_POOL,
    REPORT_MODULE_REPORT,
    REPORT_MODULE_RMAN,
    REPORT_MODULE_SYSBRG,
    REPORT_MODULE_SYSDEV,
    REPORT_MODULE_SYSENV,
    REPORT_MODULE_SYSMEM,
    REPORT_MODULE_SYSOS,
    REPORT_MODULE_UMP,

    REPORT_MODULE_RPC,
    REPORT_MODULE_TAL,

    REPORT_MODULE_SWSR,
    REPORT_MODULE_VLC,

    REPORT_MODULE_MAX
} REPORT_eModule;

#endif /* defined(IMG_KERNEL_MODULE) */

#if defined (__cplusplus)
}
#endif

#endif /* __REPORT_MODULES_H__  */

