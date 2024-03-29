???/*!
 *****************************************************************************
 *
 * @File       h264fw_data.h
 * @Title      Public data structures for the h264 parser firmware module
 * @Description    Public data structures for the h264 parser firmware module
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

#ifdef USE_SHARING
#include "h264fw_data_shared.h" /* Include shared header version here to replace the standard version. */
#endif

#ifndef _H264FW_DATA_H_
#define _H264FW_DATA_H_

#include "img_types.h"
#include "vdecfw.h"

#define H264_MAX_SPS_COUNT         32
#define H264_MAX_PPS_COUNT         256

#define H264_SCALING_LISTS_NUM_CHROMA_IDC_NON_3 (8)
#define H264_SCALING_LISTS_NUM_CHROMA_IDC_3 (12)
#define MAX_PIC_SCALING_LIST (12)

#define H264_MAXIMUMVALUEOFCPB_CNT  32                       //!< Maximum number of alternative CPB specifications in the stream


/*!
 *  The maximum DPB size is related to the number of MVC views supported
 *  The size is defined in H.10.2 for the H.264 spec.
 *  If the number of views needs to be changed the DPB size should be too
 *  The limits are as follows:
 *  NumViews:        1,  2,  4,  8, 16
 *  MaxDpbFrames:   16, 16, 32, 48, 64
 */

#ifdef H264_ENABLE_MVC
#define H264FW_MAX_NUM_VIEWS       4
#define H264FW_MAX_DPB_SIZE        32
#define H264FW_MAX_NUM_MVC_REFS    16
#else
#define H264FW_MAX_NUM_VIEWS       1
#define H264FW_MAX_DPB_SIZE        16
#define H264FW_MAX_NUM_MVC_REFS    1
#endif
/*! Number of H264 VLC table configuration registers */
#define H264FW_NUM_VLC_REG    22

/*! Maximum value for num_ref_frames_in_pic_order_cnt_cycle */
#define H264FW_MAX_CYCLE_REF_FRAMES   256

/*! 4x4 scaling list size */
#define H264FW_4X4_SIZE         16
/*! 8x8 scaling list size */
#define H264FW_8X8_SIZE         64
/*! Number of 4x4 scaling lists */
#define H264FW_NUM_4X4_LISTS    6
/*! Number of 8x8 scaling lists */
#define H264FW_NUM_8X8_LISTS    6

/*! Number of reference picture lists */
#define H264FW_MAX_REFPIC_LISTS 2

/*! The maximum number of slice groups
 * remove if slice group map is prepared on the host */
#define H264FW_MAX_SLICE_GROUPS   8

/*! The maximum number of planes for 4:4:4 separate colour plane streams */
#define H264FW_MAX_PLANES       3


#define H264_MAX_SGM_SIZE 8196

#define IS_H264_HIGH_PROFILE(profile_idc)           \
(                                                   \
    (profile_idc == H264_PROFILE_HIGH)      ||      \
    (profile_idc == H264_PROFILE_HIGH10)    ||      \
    (profile_idc == H264_PROFILE_HIGH422)   ||      \
    (profile_idc == H264_PROFILE_HIGH444)   ||      \
    (profile_idc == H264_PROFILE_CAVLC444)  ||      \
    (profile_idc == H264_PROFILE_MVC_HIGH)  ||      \
    (profile_idc == H264_PROFILE_MVC_STEREO)        \
)

/* Definitions of errors detected by parser in FWBSP mode follows */
#ifdef VDEC_USE_PVDEC_SEC

/*! Error codes returned by H264_parseSPS() */
#define H264_ERR_SPS_INV_PROFILE_IDC (20)
#define H264_ERR_SPS_INV_SPS_ID (21)
#define H264_ERR_SPS_INV_FORMAT_IDC (22)
#define H264_ERR_SPS_INV_BIT_DEPTH_LUMA_MIN8 (23)
#define H264_ERR_SPS_INV_BIT_DEPTH_CHROMA_MIN8 (24)
#define H264_ERR_SPS_INV_SCAL_LIST (25)
#define H264_ERR_SPS_INV_LOG2_MAX_FRAME_NUM (26)
#define H264_ERR_SPS_INV_PIC_ORD_CNT (27)
#define H264_ERR_SPS_INV_MAX_PIC_ORD_CNT (28)
#define H264_ERR_SPS_INV_NUM_REF_FRM_IN_PIC (29)
#define H264_ERR_SPS_INV_NUM_REF_FRM (30)
#define H264_ERR_SPS_INV_PIC_WIDTH (31)
#define H264_ERR_SPS_INV_PIC_HEIGHT (32)

/*! Error codes returned by H264_parseVUI() */
#define H264_ERR_VUI_INV_ASPECT_RATIO (40)
#define H264_ERR_VUI_INV_TIMING (41)
#define H264_ERR_VUI_INV_NUM_REORDERED_FRAMES (42)
#define H264_ERR_VUI_INV_CPB_CNT (43)

/*! Error codes returned by H264_parsePPS() */
#define H264_ERR_PPS_SLICE_GROUPS_NOT_SUP ((50) | VDECFW_UNSUPPORTED_CODE_BASE)
#define H264_ERR_PPS_PPS_INV_ID (51)
#define H264_ERR_PPS_SPS_INV_ID (52)
#define H264_ERR_PPS_SPS_MISSING (53)
#define H264_ERR_PPS_INV_NUM_SLICE_GROUPS (54)
#define H264_ERR_PPS_INV_SIZE_IN_MAP (55)
#define H264_ERR_PPS_INV_NUM_REF_LX (56)
#define H264_ERR_PPS_INV_SCAL_LIST_NUM (57)
#define H264_ERR_PPS_INV_SCAL_LIST (58)

/* SEI error codes */
#define H264_ERR_SEI_DATA_OVERFLOW   (70)
#define H264_ERR_SEI_DATA_UNDERFLOW  (71)

/* Other error codes */
#define H264_ERR_FAILED_TO_STORE_SPS (100)
#define H264_ERR_FAILED_TO_STORE_PPS (101)

#define H264_ERR_FAILED_TO_FETCH_SPS (102)
#define H264_ERR_FAILED_TO_FETCH_PPS (103)

#define H264_ERR_FIELD_NOT_SUP ((104) | VDECFW_UNSUPPORTED_CODE_BASE)
#define H264_ERR_ASO_NOT_SUP   ((105) | VDECFW_UNSUPPORTED_CODE_BASE)

#define H264_IS_UNSUPPORTED_CODE(code) ((code) & VDECFW_UNSUPPORTED_CODE_BASE)

/*!
******************************************************************************

 SEI Definitions

******************************************************************************/
#define H264_BYTES_IN_128_BITS           16
#define H264_MAX_UNREGISTERED_BYTES      128

/*!
******************************************************************************

 SEI Types

******************************************************************************/
typedef enum {
    H264_SEI_BUFFERING_PERIOD                        =   0,
    H264_SEI_PIC_TIMING                              =   1,
    H264_SEI_PAN_SCAN_RECT                           =   2,
    H264_SEI_FILLER_PAYLOAD                          =   3,
    H264_SEI_USER_DATA_REGISTERED_ITU_T_T35          =   4,
    H264_SEI_USER_DATA_UNREGISTERED                  =   5,
    H264_SEI_RECOVERY_POINT                          =   6,
    H264_SEI_DEC_REF_PIC_MARKING_REPETITION          =   7,
    H264_SEI_SPARE_PIC                               =   8,
    H264_SEI_SCENE_INFO                              =   9,
    H264_SEI_SUB_SEQ_INFO                            =   10,
    H264_SEI_SUB_SEQ_LAYER_CHARACTERISTICS           =   11,
    H264_SEI_SUB_SEQ_CHARACTERISTICS                 =   12,
    H264_SEI_FULL_FRAME_FREEZE                       =   13,
    H264_SEI_FULL_FRAME_FREEZE_RELEASE               =   14,
    H264_SEI_FULL_FRAME_SNAPSHOT                     =   15,
    H264_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START    =   16,
    H264_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END      =   17,
    H264_SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET      =   18,
    H264_SEI_FILM_GRAIN_CHARACTERISTICS              =   19,
    H264_SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE    =   20,
    H264_SEI_STEREO_VIDEO_INFO                       =   21,
    H264_SEI_POST_FILTER_HINT                        =   22,
    H264_SEI_TONE_MAPPING_INFO                       =   23,
    H264_SEI_MAX_ELEMENTS  //!< number of maximum syntax elements
} H264_eSEIType;

#endif /* VDEC_USE_PVDEC_SEC  */

/*
******************************************************************************

 This type describes the H.264 NAL unit types

******************************************************************************/
typedef enum
{
    H264FW_NALTYPE_SLICE = 1,
    H264FW_NALTYPE_IDRSLICE = 5,
    H264FW_NALTYPE_SEI = 6,
    H264FW_NALTYPE_SPS = 7,
    H264FW_NALTYPE_PPS = 8,
    H264FW_NALTYPE_AUD = 9,
    H264FW_NALTYPE_EOSEQ = 10,
    H264FW_NALTYPE_EOSTR = 11,
    H264FW_NALTYPE_PREFIX = 14,
    H264FW_NALTYPE_SUBSET_SPS = 15,
    H264FW_NALTYPE_AUXILIARY_SLICE = 19,
    H264FW_NALTYPE_EXTSLICE = 20,
    H264FW_NALTYPE_EXTSLICE_DEPTH_VIEW = 21,

} H264_eNalType;


/*!
******************************************************************************

                AVC Profile IDC definitions

******************************************************************************/
typedef enum
{
    H264_PROFILE_CAVLC444                               =   44,     //!< YUV 4:4:4/14 "CAVLC 4:4:4"
    H264_PROFILE_BASELINE                               =   66,     //!< YUV 4:2:0/8  "Baseline"
    H264_PROFILE_MAIN                                   =   77,     //!< YUV 4:2:0/8  "Main"
    H264_PROFILE_SCALABLE                               =   83,     //!< YUV 4:2:0/8  "Scalable"
    H264_PROFILE_EXTENDED                               =   88,     //!< YUV 4:2:0/8  "Extended"
    H264_PROFILE_HIGH                                   =   100,    //!< YUV 4:2:0/8  "High"
    H264_PROFILE_HIGH10                                 =   110,    //!< YUV 4:2:0/10 "High 10"
    H264_PROFILE_MVC_HIGH                               =   118,    //!< YUV 4:2:0/8  "Multiview High"
    H264_PROFILE_HIGH422                                =   122,    //!< YUV 4:2:2/10 "High 4:2:2"
    H264_PROFILE_MVC_STEREO                             =   128,    //!< YUV 4:2:0/8  "Stereo High"
    H264_PROFILE_HIGH444                                =   244,    //!< YUV 4:4:4/14 "High 4:4:4"

}   H264_eProfileIdc;


/*!
******************************************************************************

 This type defines the constraint set flags

******************************************************************************/
typedef enum
{
    H264FW_CONSTRAINT_BASELINE_SHIFT    = 7,   //!< Compatible with Baseline profile
    H264FW_CONSTRAINT_MAIN_SHIFT        = 6,   //!< Compatible with Main profile
    H264FW_CONSTRAINT_EXTENDED_SHIFT    = 5,   //!< Compatible with Extended profile
    H264FW_CONSTRAINT_INTRA_SHIFT       = 4,   //!< Compatible with Intra profiles
    H264FW_CONSTRAINT_MULTIHIGH_SHIFT   = 3,   //!< Compatible with Multiview High profile
    H264FW_CONSTRAINT_STEREOHIGH_SHIFT  = 2,   //!< Compatible with Stereo High profile
    H264FW_CONSTRAINT_RESERVED6_SHIFT   = 1,   //!< Reserved flag
    H264FW_CONSTRAINT_RESERVED7_SHIFT   = 0,   //!< Reserved flag

} h264fw_eConstraintFlag;


/*!
******************************************************************************
 This enum describes the reference status of an H.264 picture.

 Unpaired fields should have all eRefStatusX set to the same value

 For Frame, Mbaff, and Pair types individual fields and frame ref status
 should be set accordingly.

 eRefStatusFrame    eRefStatusTop   eRefStatusBottom
 UNUSED             UNUSED          UNUSED
 SHORTTERM          SHORTTERM       SHORTTERM
 LONGTERM           LONGTERM        LONGTERM

 UNUSED             SHORT/LONGTERM  UNUSED
 UNUSED             UNUSED          SHORT/LONGTERM

 SHORTTERM          LONGTERM        SHORTTERM
 SHORTTERM          SHORTTERM       LONGTERM
 - NB: It is not clear from the spec if the Frame should be marked as short
        or long term in this case
******************************************************************************/
typedef enum
{
    H264FW_REF_UNUSED = 0,          //!< Picture is unused for reference
    H264FW_REF_SHORTTERM,           //!< used for short term reference
    H264FW_REF_LONGTERM,            //!< used for Long Term reference

} H264FW_eReference;


/*!
******************************************************************************
 This type defines the picture structure.
******************************************************************************/
typedef enum
{
    H264FW_TYPE_NONE = 0,   //!< No valid picture
    H264FW_TYPE_TOP,        //!< Picture contains the top (even) lines of the frame
    H264FW_TYPE_BOTTOM,     //!< Picture contains the bottom (odd) lines of the frame
    H264FW_TYPE_FRAME,      //!< Picture contains the entire frame
    H264FW_TYPE_MBAFF,      //!< Picture contains an MBAFF frame
    H264FW_TYPE_PAIR,       //!< Picture contains top and bottom lines of the frame

} H264FW_ePictureType;


/*!
******************************************************************************

 This describes the SPS header data required by the H264 firmware that should
 be supplied by the Host.

******************************************************************************/
typedef struct
{
    /* syntax elements from SPS */
    IMG_UINT8   profile_idc;                                //!< syntax element from bitstream - 8 bit

    IMG_UINT8   chroma_format_idc;                          //!< syntax element from bitstream - 2 bit
    IMG_UINT8   separate_colour_plane_flag;                 //!< syntax element from bitstream - 1 bit
    IMG_UINT8   bit_depth_luma_minus8;                      //!< syntax element from bitstream - 3 bit
    IMG_UINT8   bit_depth_chroma_minus8;                    //!< syntax element from bitstream - 3 bit
    IMG_UINT8   delta_pic_order_always_zero_flag;           //!< syntax element from bitstream - 1 bit
    IMG_UINT8   log2_max_pic_order_cnt_lsb;                 //!< syntax element from bitstream - 4+ bit

    IMG_UINT8   max_num_ref_frames;                         //!< syntax element from bitstream - 5 bit
    IMG_UINT8   log2_max_frame_num;                         //!< syntax element from bitstream - 4+ bit
    IMG_UINT8   pic_order_cnt_type;                         //!< syntax element from bitstream - 2 bit
    IMG_UINT8   frame_mbs_only_flag;                        //!< syntax element from bitstream - 1 bit
    IMG_UINT8   gaps_in_frame_num_value_allowed_flag;       //!< syntax element from bitstream - 1 bit

    IMG_UINT8   constraint_set_flags;                       //!< set0--7 flags as they occur in the bitstream (including reserved values)
    IMG_UINT8   level_idc;                                  //!< syntax element from bitstream - 8 bit
    IMG_UINT8   num_ref_frames_in_pic_order_cnt_cycle;      //!< syntax element from bitstream - 8 bit

    IMG_UINT8   mb_adaptive_frame_field_flag;               //!< syntax element from bitstream - 1 bit
    IMG_INT32   offset_for_non_ref_pic;                     //!< syntax element from bitstream - 32 bit
    IMG_INT32   offset_for_top_to_bottom_field;             //!< syntax element from bitstream - 32 bit

    IMG_UINT32  pic_width_in_mbs_minus1;                    //!< syntax element from bitstream
    IMG_UINT32  pic_height_in_map_units_minus1;             //!< syntax element from bitstream
    IMG_BOOL8   direct_8x8_inference_flag;                  //!< syntax element from bitstream - 1 bit
    IMG_UINT8   qpprime_y_zero_transform_bypass_flag;       //!< syntax element from bitstream

    IMG_INT32   offset_for_ref_frame[H264FW_MAX_CYCLE_REF_FRAMES];//!< syntax element from bitstream - 32 bit each

    /* From VUI information */
    IMG_UINT8   num_reorder_frames;                         //!< From VUI information
    IMG_UINT8   max_dec_frame_buffering;                    //!< From VUI/MVC SEI, 0 indicates not set, any actual 0 value will be inferred by the firmware

    /* From SPS MVC Extention - for the current view_id */
    IMG_UINT8   ui8NumViews;                          //!< Number of views in this stream
    IMG_UINT16  aui16ViewIds[H264FW_MAX_NUM_VIEWS];   //!< a Map in order of VOIdx of view_id's

    IMG_BOOL8   bDisableVDMCFilt;                       //!< Disable VDMC horizontal/vertical filtering
    IMG_BOOL8   b4x4TransformMBNotAvailable;            //!< Disable CABAC 4:4:4 4x4 transform as not available

    IMG_UINT16  aui16AnchorInterViewReferenceIDLX[2][H264FW_MAX_NUM_VIEWS][H264FW_MAX_NUM_MVC_REFS];     //!< anchor reference list
    IMG_UINT16  aui16NonAnchorInterViewReferenceIDLX[2][H264FW_MAX_NUM_VIEWS][H264FW_MAX_NUM_MVC_REFS];  //!< nonanchor reference list
    IMG_UINT16  aui16NumAnchorRefsX[2][H264FW_MAX_NUM_VIEWS];                      //!< number of elements in aui16AnchorInterViewReferenceIndiciesLX[]
    IMG_UINT16  aui16NumNonAnchorRefsX[2][H264FW_MAX_NUM_VIEWS];                   //!< number of elements in aui16NonAnchorInterViewReferenceIndiciesLX[]

#ifdef VDEC_USE_PVDEC_SEC
    IMG_UINT8   seq_parameter_set_id;                                                   //!< syntax element from bitstream
    IMG_BOOL8   seq_scaling_matrix_present_flag;                                        //!< syntax element from bitstream
    IMG_UINT8   aui8ScalingList4x4[H264FW_NUM_4X4_LISTS][H264FW_4X4_SIZE];              //!< syntax element from bitstream
    IMG_UINT8   aui8ScalingList8x8[H264FW_NUM_8X8_LISTS][H264FW_8X8_SIZE];              //!< syntax element from bitstream
    IMG_UINT8   seq_scaling_list_present_flag[H264_SCALING_LISTS_NUM_CHROMA_IDC_3];     //!< syntax element from bitstream
    IMG_BOOL8   vui_parameters_present_flag;                                            //!< syntax element from bitstream, subject of optimization, not used by HW
    IMG_UINT8   frame_cropping_flag;                                                    //!< syntax element from bitstream
    IMG_UINT16  frame_crop_left_offset;                                                 //!< syntax element from bitstream
    IMG_UINT16  frame_crop_right_offset;                                                //!< syntax element from bitstream
    IMG_UINT16  frame_crop_top_offset;                                                  //!< syntax element from bitstream
    IMG_UINT16  frame_crop_bottom_offset;                                               //!< syntax element from bitstream

    IMG_UINT8   aui8UseDefScalingMatrixFlag[H264_SCALING_LISTS_NUM_CHROMA_IDC_3];       //!< Indicates whether default scaling list should be picked

#endif /* VDEC_USE_PVDEC_SEC */

} H264FW_sSequencePS;


/*!
******************************************************************************
This structure represents HRD parameters.

******************************************************************************/
typedef struct{
    IMG_UINT8      ui32CPBCntMinus1;                                           /*!< cpb_cnt_minus1;                                 */
    IMG_UINT8      ui32BitRateScale;                                           /*!< bit_rate_scale;                                 */
    IMG_UINT8      ui32CPBSizeScale;                                           /*!< cpb_size_scale;                                 */
    IMG_UINT32     aui32BitRateValueMinus1[H264_MAXIMUMVALUEOFCPB_CNT];        /*!< bit_rate_value_minus1                           */
    IMG_UINT32     aui32CPBSizeValueMinus1[H264_MAXIMUMVALUEOFCPB_CNT];        /*!< cpb_size_value_minus1                           */
    IMG_UINT8      aui8CBRFlag[H264_MAXIMUMVALUEOFCPB_CNT];                    /*!< cbr_flag                                        */
    IMG_UINT8      ui32InitialCPBRemovalDelayLengthMinus1;                     /*!< initial_cpb_removal_delay_length_minus1;        */
    IMG_UINT8      ui32CPBRemovalDelayLenghtMinus1;                            /*!< cpb_removal_delay_length_minus1;                */
    IMG_UINT8      ui32DPBOutputDelayLengthMinus1;                             /*!< dpb_output_delay_length_minus1;                 */
    IMG_UINT8      ui32TimeOffsetLength;                                       /*!< time_offset_length;                             */
} H264FW_HRD;


/*!
******************************************************************************

 This structure represents the VUI parameters data.

******************************************************************************/
typedef struct
{
    IMG_BOOL                aspect_ratio_info_present_flag;
    IMG_UINT8               aspect_ratio_idc;
    IMG_UINT16              sar_width;
    IMG_UINT16              sar_height;
    IMG_BOOL                overscan_info_present_flag;
    IMG_BOOL                overscan_appropriate_flag;
    IMG_BOOL                video_signal_type_present_flag;
    IMG_UINT8               video_format;
    IMG_BOOL                video_full_range_flag;
    IMG_BOOL                colour_description_present_flag;
    IMG_UINT8               colour_primaries;
    IMG_UINT8               transfer_characteristics;
    IMG_UINT8               matrix_coefficients;
    IMG_BOOL                chroma_location_info_present_flag;
    IMG_UINT32              chroma_sample_loc_type_top_field;
    IMG_UINT32              chroma_sample_loc_type_bottom_field;
    IMG_BOOL                timing_info_present_flag;
    IMG_UINT32              num_units_in_tick;
    IMG_UINT32              time_scale;
    IMG_BOOL                fixed_frame_rate_flag;
    IMG_BOOL                nal_hrd_parameters_present_flag;
    H264FW_HRD              sNALHRDParams;
    IMG_BOOL                vcl_hrd_parameters_present_flag;
    H264FW_HRD              sVCLHRDParams;
    IMG_BOOL                low_delay_hrd_flag;
    IMG_BOOL                pic_struct_present_flag;
    IMG_BOOL                bitstream_restriction_flag;
    IMG_BOOL                motion_vectors_over_pic_boundaries_flag;
    IMG_UINT32              max_bytes_per_pic_denom;
    IMG_UINT32              max_bits_per_mb_denom;
    IMG_UINT32              log2_max_mv_length_vertical;
    IMG_UINT32              log2_max_mv_length_horizontal;
    IMG_UINT32              num_reorder_frames;
    IMG_UINT32              max_dec_frame_buffering;

} H264FW_sVUI;


/*!
******************************************************************************

 This describes the HW specific SPS header data required by the H264
 firmware that should be supplied by the Host.

******************************************************************************/
typedef struct
{
    /* pre-packed registers derived from SPS */
    IMG_UINT32  ui32RegEntdecControl;                       //!< Value for CR_VEC_ENTDEC_FE_CONTROL

    // NB: This register should contain the 4-bit SGM flag
    IMG_UINT32  ui32RegSps0;                                //!< Value for CR_VEC_H264_FE_SPS0 & CR_VEC_H264_BE_SPS0 combined
    IMG_UINT32  ui32RegBEINTRA8x8;                          //!< Value of CR_VEC_H264_BE_INTRA_8x8
    IMG_UINT32  ui32RegFECABAC444;                          //!< Value of CR_VEC_H264_FE_CABAC444

    IMG_BOOL8   b4x4TransformMBNotAvailable;                //!< Treat CABAC 4:4:4 4x4 transform as not available
    IMG_BOOL8   bDisableVDMCFilt;                           //!< Disable VDMC horizontal/vertical filtering

} H264FW_sDdSequencePS;


/*!
******************************************************************************

 This describes the PPS header data required by the H264 firmware that should
 be supplied by the Host.

******************************************************************************/
typedef struct
{
    /* syntax elements from the PPS */
    IMG_BOOL8   deblocking_filter_control_present_flag;                 //!< syntax element from bitstream - 1 bit
    IMG_BOOL8   transform_8x8_mode_flag;                                //!< syntax element from bitstream - 1 bit
    IMG_BOOL8   entropy_coding_mode_flag;                               //!< syntax element from bitstream - 1 bit
    IMG_BOOL8   redundant_pic_cnt_present_flag;                         //!< syntax element from bitstream - 1 bit

    IMG_UINT8   weighted_bipred_idc;                                    //!< syntax element from bitstream - 2 bit
    IMG_BOOL8   weighted_pred_flag;                                     //!< syntax element from bitstream - 1 bit
    IMG_BOOL8   pic_order_present_flag;                                 //!< syntax element from bitstream - 1 bit

    IMG_INT8    pic_init_qp;                                            //!< 26 + syntax element from bitstream - 7 bit
    IMG_BOOL8   constrained_intra_pred_flag;                            //!< syntax element from bitstream - 1 bit
    IMG_UINT8   num_ref_lX_active_minus1[H264FW_MAX_REFPIC_LISTS];      //!< syntax element from bitstream - 5 bit each

    IMG_UINT8   slice_group_map_type;                                   //!< syntax element from bitstream - 3 bit
    IMG_UINT8   num_slice_groups_minus1;                                //!< syntax element from bitstream - 3 bit
    IMG_UINT16  slice_group_change_rate_minus1;                         //!< syntax element from bitstream - 13 bit

    IMG_INT32   chroma_qp_index_offset;                                 //!< syntax element from bitstream
    IMG_INT32   second_chroma_qp_index_offset;                          //!< syntax element from bitstream

    /* scaling lists are derived from both SPS and PPS information */
    /* but will change whenever the PPS changes */
    /* The derived set of tables are associated here with the PPS */
    /* NB: These are in H.264 order */
    IMG_UINT8   ScalingList4x4[H264FW_NUM_4X4_LISTS][H264FW_4X4_SIZE];  //!< derived from SPS and PPS - 8 bit each
    IMG_UINT8   ScalingList8x8[H264FW_NUM_8X8_LISTS][H264FW_8X8_SIZE];  //!< derived from SPS and PPS - 8 bit each

#ifdef VDEC_USE_PVDEC_SEC
    IMG_UINT8   seq_parameter_set_id;                                   //!< syntax element from bitstream
    IMG_UINT32  pic_parameter_set_id;                                   //!< syntax element from bitstream
#ifdef H264_ENABLE_FMO_ASO
    IMG_UINT16  run_length_minus1[8];                                   //!< syntax element from bitstream
    IMG_UINT16  top_left[8];                                            //!< syntax element from bitstream
    IMG_UINT16  bottom_right[8];                                        //!< syntax element from bitstream
    IMG_BOOL    slice_group_change_direction_flag;                      //!< syntax element from bitstream
    IMG_UINT16  pic_size_in_map_unit;                                   //!< syntax element from bitstream
    IMG_UINT8   aui_slice_group_id[H264_MAX_SGM_SIZE];                  //!< syntax element from bitstream
#endif /* H264_ENABLE_FMO_ASO */

    IMG_UINT8   pic_scaling_matrix_present_flag;                        //!< syntax element from bitstream
    IMG_UINT8   pic_scaling_list_present_flag[MAX_PIC_SCALING_LIST];    //!< syntax element from bitstream
    IMG_UINT8   UseDefScalingMatrixFlag[MAX_PIC_SCALING_LIST];          //!< Indicates whether default scaling list should be picked for PPS

#endif /* VDEC_USE_PVDEC_SEC */

} H264FW_sPicturePS;


/*!
******************************************************************************

 This describes the HW specific PPS header data required by the H264
 firmware that should be supplied by the Host.

******************************************************************************/
typedef struct
{
    /* values derived from the PPS */
    IMG_UINT8   ui8VdmcModeConfig;                          //!< Value for MSVDX_CMDS_SLICE_PARAMS_MODE_CONFIG

    /* pre-packed registers derived from the PPS */
    IMG_UINT32  ui32RegPps0;                                //!< Value for CR_VEC_H264_FE_PPS0 & CR_VEC_H264_BE_PPS0 combined

    /* scaling lists are derived from both SPS and PPS information */
    /* but will change whenever the PPS changes */
    /* The derived set of tables are associated here with the PPS */
    /* But this will become invalid if the SPS changes and will have to be recalculated */
    /* These tables MUST be aligned on a 32-bit boundary */
    /* NB: These are in MSVDX order */
    IMG_UINT8   ScalingList4x4[H264FW_NUM_4X4_LISTS][H264FW_4X4_SIZE];  //!< derived from SPS and PPS - 8 bit each
    IMG_UINT8   ScalingList8x8[H264FW_NUM_8X8_LISTS][H264FW_8X8_SIZE];  //!< derived from SPS and PPS - 8 bit each

} H264FW_sDdPicturePS;


/*!
******************************************************************************

 This describes the H.264 parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the H264 firmware
 and should be supplied by the Host.

******************************************************************************/
typedef struct
{
    /* Decode buffers and output control for the current picture */
    VDECFW_sImageBuffer     sPrimary;     //!< Primary decode buffer base addresses
    VDECFW_sImageBuffer     sAlternate;  //!< buffer base addresses for alternate output
    IMG_UINT32              aui32PictCmds[VDECFW_CMD_MAX];        //!< Output control: rotation, scaling, oold, etc.

    IMG_UINT32              ui32MbParamsBaseAddress;//!< Macroblock parameters base address for the picture
#ifdef ENABLE_SEPARATE_COLOUR_PLANES
    IMG_UINT32              ui32MbParamsSizePerPlane;
#endif

    IMG_UINT32              aui32PreloadBufferBaseAddress[H264FW_MAX_PLANES];    //!< Buffers for context preload for colour plane switching (6.x.x)


    /* H.264 BE Commands */
    //IMG_UINT32  gui32CmdCacheConfig;            //!< MC_CACHE_CONFIGURATION
    //IMG_UINT32  ui32CmdIntraBufferBaseAddress;  //!< INTRA_BUFFER_BASE_ADDRESS
    //IMG_UINT32  gui32IntraBuff;                 //!< Intra Buffer base address

    /* H.264 BE Commands - 6.x.x listed as H.264 only */
    //IMG_UINT32  ui32CmdExtendedOperatingMode;   //!< EXT_OP_MODE
    //IMG_UINT32  ui32CmdChromaRowStride;         //!< CHROMA_ROW_STRIDE
    //IMG_UINT32  ui32CmdScaleHorizontalChroma;   //!< SCALE_HORIZONTAL_CHROMA
    //IMG_UINT32  ui32CmdScaleVerticalChroma;     //!< SCALE_VERTICAL_CHROMA

    /* Parser configuration parameters */
    //IMG_UINT32  ui32VlcBaseAddress;             //!< base address to DMA VLC tables from
    //IMG_UINT32  ui32VlcSize;                    //!< size of VLC table DMA

    /* slice group map should be calculated on Host */
    /* (using some slice params) and base address provided here */
    IMG_UINT32  ui32SliceGroupMapBaseAddress;   //!< Base address of active slice group map



    /* H264 specific control */
    // IMG_BOOL8   bOutputAllPics;                 //!< H.264 spec says that under certain circumstances pictures should be flushed with no output, this ensures they are output

    IMG_BOOL8   bDoOold;                        //!< do second pass Intra Deblock on frame
    IMG_BOOL8   bTwoPassFlag;                   //!< set to IMG_FALSE to disable second-pass deblock
    IMG_BOOL8   bDisableMvc;                    //!< set to IMG_TRUE to disable MVC
    IMG_BOOL8   bSecondPPS;                     //!< Do we have second PPS in uipSecondPPSInfoSource provided for the second field.

} H264FW_sHeaderData;


/*!
******************************************************************************

 This describes an H.264 picture. It is part of the Context data

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer sPrimary;               //!< Primary (reconstructed) picture buffers
    VDECFW_sImageBuffer sAlternate;             //!< Secondary (alternative) picture buffers
    IMG_UINT32          ui32MbParamsBaseAddress;//!< Macroblock parameters base address for the picture

    IMG_UINT32          ui32TransactionId;      //!< Unique ID for this picture
    H264FW_ePictureType ePictureType;           //!< Picture type

    H264FW_eReference   eRefStatusBottom;             //!< Reference status of the picture
    H264FW_eReference   eRefStatusTop;             //!< Reference status of the picture
    H264FW_eReference   eRefStatusFrame;             //!< Reference status of the picture

    IMG_UINT32          ui32FrameNum;           //!< Frame Number
    IMG_INT32           i32FrameNumWrap;        //!< Short term reference info
    IMG_UINT32          ui32LongTermFrameIdx;   //!< long term reference number - should be 8-bit

    IMG_INT32           i32TopFieldOrderCount;  //!< Top field order count for this picture
    IMG_INT32           i32BottomFieldOrderCount;//!< Bottom field order count for this picture

    IMG_UINT16          ui16ViewId;             //!< MVC view_id

    IMG_UINT8           ui8ViewDpbOffset;       /*!< When picture is in the DPB Offset to use into
                                                        the MSVDX DPB reg table when the current
                                                        picture is the same view as this. */
    IMG_UINT8           ui8DisplayFlags;        //!< Flags for this picture for the display process

    // is this required as is represented in ePictureType
    //IMG_BOOL8           bMbaffFrameFlag;        //!< IMG_TRUE if frame is MBAFF
    IMG_BOOL8           bNeededForOutput;       //!< IMG_FALSE if sent to display, or otherwise not needed for display

} H264FW_sPicture;


/*
******************************************************************************

 This structure describes frame data for POC calculation

******************************************************************************/
typedef struct
{
    /* type 0,1,2 */
    IMG_BOOL8   bMmco5Flag;

    /* type 0 */
    IMG_BOOL8   bottom_field_flag;
    IMG_UINT16  pic_order_cnt_lsb;
    IMG_INT32   TopFieldOrderCount;
    IMG_INT32   PicOrderCntMsb;

    /* type 1,2 */
    IMG_INT16   frame_num;
    IMG_INT32   FrameNumOffset;

    /* output */
    IMG_INT32   BottomFieldOrderCount;

} H264FW_sPocPictureData;


/*
******************************************************************************

 This structure describes picture data for determining Complementary Field Pairs

******************************************************************************/
typedef struct
{
    IMG_UINT32          ui32TransactionId;      //!< Unique ID for this picture
    H264FW_ePictureType ePictureType;           //!< Picture type
    H264FW_eReference   eRefStatusFrame;        //!< Reference status of the picture
    IMG_UINT32          ui32FrameNum;           //!< Frame Number

    IMG_UINT32          ui32LumaRecon;
    IMG_UINT32          ui32ChromaRecon;
    IMG_UINT32          ui32Chroma2Recon;
    IMG_UINT32          ui32LumaAlter;
    IMG_UINT32          ui32ChromaAlter;
    IMG_UINT32          ui32Chroma2Alter;
    VDECFW_sImageBuffer sPrimary;
    VDECFW_sImageBuffer sAlternative;
    IMG_UINT32          ui32MbParamsBaseAddress;

} H264FW_sLastPicData;


#ifdef VDEC_USE_PVDEC_SEC
typedef struct
{
    IMG_UINT8  aValid[H264_SEI_MAX_ELEMENTS/8];    //!< Indicates which type of SEI message was present

    /* Picture timing related output */
    IMG_BOOL   bRepeatFirstField;
    IMG_UINT8  ui8MaxFrmRepeat;                    //!< possible values 2,1,0

    /* Data unregistered related output */
    IMG_BOOL   bDisableVDMCFilt;
    IMG_BOOL   b4x4TransformMBNotAvailable;

} H264FW_sSEIInfo;
#endif /* VDEC_USE_PVDEC_SEC */

/*!
******************************************************************************

 This describes the H.264 parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.

******************************************************************************/
typedef struct
{
    H264FW_sPicture asDpb[H264FW_MAX_DPB_SIZE];     //!< Decoded Picture Buffer

    H264FW_sPicture asInterViewPredictionReference[H264FW_MAX_NUM_VIEWS];    //!< Inter-view reference components - also used as detail of the previous picture for any particular view, can be used to determine complemetary field pairs

    H264FW_sPocPictureData  asPreviousPocPicData[H264FW_MAX_NUM_VIEWS]; //!< previous ref pic for type0, previous pic for type1&2
    H264FW_sLastPicData     asLastPicData[H264FW_MAX_NUM_VIEWS];        //!< previous picture information to detect complementary field pairs
    H264FW_sLastPicData     asLastDisplayedPicData[H264FW_MAX_NUM_VIEWS];

    IMG_UINT16      aPrevRefFrameNum[H264FW_MAX_NUM_VIEWS]; //! previous reference frame number for each view
    IMG_UINT16      aui16DpbBitmap[H264FW_MAX_NUM_VIEWS];   //! Bitmap of used slots in each view DPB

    IMG_UINT32      ui32DpbSize;                    //!< DPB size
    IMG_UINT32      ui32DpbFullness;                //!< Number of pictures in DPB

    IMG_UINT8   ui8PrevDisplayFlags;
    IMG_BOOL    bPrevDisplay;
    IMG_BOOL    bPrevRelease;
    /* Active parameter sets */
    H264FW_sSequencePS              sSPS;               //!< Sequence Parameter Set data
    H264FW_sPicturePS               sPPS;               //!< Picture Parameter Set data
    H264FW_sPicturePS               sSecondPPS;         //!< Picture Parameter Set data for second field when in the same buffer

    IMG_BOOL                        bMVC;               //!< Set if stream is MVC
    IMG_INT32       ai32MaxLongTermFrameIdx[H264FW_MAX_NUM_VIEWS]; //!< DPB long term reference information
#ifdef VDEC_USE_PVDEC_SEC
    IMG_UINT8       aSPSValid[H264_MAX_SPS_COUNT/8];
    IMG_UINT8       aPPSValid[H264_MAX_PPS_COUNT/8];
    H264FW_sVUI     sVUI;
    H264FW_sSEIInfo sSEI;
    IMG_UINT32      ui32ActiveSps4SEI;
#endif /* VDEC_USE_PVDEC_SEC */
} H264FW_sContextData;


#endif /* _H264FW_DATA_H_ */
