/////////////////////////////////////////////////////////////////////////////// //
//                          IMPORTANT NOTICE
//
// The following open source license statement does not apply to any
// entity in the Exception List published by FMSoft.
//
// For more information, please visit:
//
// https://www.fmsoft.cn/exception-list
//
//////////////////////////////////////////////////////////////////////////////
/**
 \verbatim

    This file is part of HiDOMLayout. hiDOMLayout is a library to
    maintain a DOM tree, lay out and stylize the DOM nodes by
    using CSS (Cascaded Style Sheets).

    Copyright (C) 2021 Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */


#ifndef _HI_DOMLAYOUT_H_
#define _HI_DOMLAYOUT_H_

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

// log begin
#if defined(_DEBUG)
#   define HL_LOGD(fmt, ...)                                                               \
    do {                                                                                   \
        fprintf (stderr, "D|%s:%d:%s|"fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__);   \
    } while (0)
# else
#   define HL_LOGD(fmt, ...) do { } while (0)
#endif

#define HL_LOGE(fmt, ...)                           \
    do {                                            \
        fprintf (stderr, "E|"fmt, ##__VA_ARGS__);   \
    } while (0)

#define HL_LOGW(fmt, ...)                           \
    do {                                            \
        fprintf (stderr, "W|"fmt, ##__VA_ARGS__);   \
    } while (0)

// log end

// error code begin
#define HILAYOUT_OK                 0
#define HILAYOUT_NOMEM              1
#define HILAYOUT_BADPARM            2
#define HILAYOUT_INVALID            3
#define HILAYOUT_FILENOTFOUND       4
#define HILAYOUT_NEEDDATA           5
#define HILAYOUT_BADCHARSET         6
#define HILAYOUT_EOF                7
#define HILAYOUT_IMPORTS_PENDING    8
#define HILAYOUT_PROPERTY_NOT_SET   9
#define HILAYOUT_NOT_SUPPORT        10
#define HILAYOUT_SELECT_STYLE_ERR   11

// error code end

// common attribute

typedef enum HLCommonAttribute_ {
    HL_COMMON_ATTR_ID           = 0,
    HL_COMMON_ATTR_CLASS_NAME   = 1,
    HL_COMMON_ATTR_STYLE        = 2,
    HL_COMMON_ATTR_NAME         = 3,

    HL_COMMON_ATTR_COUNT
} HLCommonAttribute;

// property

#define  HL_PROP_CATEGORY_BOX                  (1 << 0)
#define  HL_PROP_CATEGORY_BACKGROUND           (1 << 1)
#define  HL_PROP_CATEGORY_TEXT                 (1 << 2)
#define  HL_PROP_CATEGORY_SVG                  (1 << 3)

#define  HL_PROP_CATEGORY_ALL                  (HL_PROP_CATEGORY_BOX | HL_PROP_CATEGORY_BACKGROUND | HL_PROP_CATEGORY_TEXT | HL_PROP_CATEGORY_SVG)

#define HL_MAKE_PROP_ID(gid, i)             (((uint32_t)gid << 16) | (uint32_t)i)

// box group begin
// width
#define HL_PROP_ID_WIDTH                        HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 0)
// height
#define HL_PROP_ID_HEIGHT                       HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 1)
// margin-top
#define HL_PROP_ID_MARGIN_TOP                   HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 2)
// margin-right
#define HL_PROP_ID_MARGIN_RIGHT                 HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 3)
// margin-bottom
#define HL_PROP_ID_MARGIN_BOTTOM                HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 4)
// margin-left
#define HL_PROP_ID_MARGIN_LEFT                  HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 5)
// padding-top
#define HL_PROP_ID_PADDING_TOP                  HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 6)
// padding-right
#define HL_PROP_ID_PADDING_RIGHT                HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 7)
// padding-bottom
#define HL_PROP_ID_PADDING_BOTTOM               HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 8)
// padding-left
#define HL_PROP_ID_PADDING_LEFT                 HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 9)
// border-top-width
#define HL_PROP_ID_BORDER_TOP_WIDTH             HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 10)
// border-right-width
#define HL_PROP_ID_BORDER_RIGHT_WIDTH           HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 11)
// border-bottom-width
#define HL_PROP_ID_BORDER_BOTTOM_WIDTH          HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 12)
// border-left-width
#define HL_PROP_ID_BORDER_LEFT_WIDTH            HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 13)
// border-top-left-radius
#define HL_PROP_ID_BORDER_TOP_LEFT_RADIUS       HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 14)
// border-top-right-radius
#define HL_PROP_ID_BORDER_TOP_RIGHT_RADIUS      HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 15)
// border-bottom-left-radius
#define HL_PROP_ID_BORDER_BOTTOM_LEFT_RADIUS    HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 16)
// border-bottom-right-radius
#define HL_PROP_ID_BORDER_BOTTOM_RIGHT_RADIUS   HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BOX, 17)

// box group end

// background begin
// background-color
#define HL_PROP_ID_BACKGROUND_COLOR             HL_MAKE_PROP_ID(HL_PROP_CATEGORY_BACKGROUND, 0)

// background end

// text begin
// color
#define HL_PROP_ID_COLOR                        HL_MAKE_PROP_ID(HL_PROP_CATEGORY_TEXT, 0)
// font-family
#define HL_PROP_ID_FONT_FAMILY                  HL_MAKE_PROP_ID(HL_PROP_CATEGORY_TEXT, 1)
// font-size
#define HL_PROP_ID_FONT_SIZE                    HL_MAKE_PROP_ID(HL_PROP_CATEGORY_TEXT, 2)
// font-weight
#define HL_PROP_ID_FONT_WEIGHT                  HL_MAKE_PROP_ID(HL_PROP_CATEGORY_TEXT, 3)

// text end

// svg begin
// svg end

typedef enum HLDisplayEnum_ {
    HL_DISPLAY_BLOCK            = 0x02,
    HL_DISPLAY_INLINE_BLOCK     = 0x05,
    HL_DISPLAY_NONE             = 0x10,
    HL_DISPLAY_FLEX             = 0x11,
    HL_DISPLAY_INLINE_FLEX      = 0x12,
    HL_DISPLAY_GRID             = 0x13,
    HL_DISPLAY_INLINE_GRID      = 0x14
} HLDisplayEnum;

typedef enum HLPositionEnum_ {
    HL_POSITION_STATIC          = 0x1,
    HL_POSITION_RELATIVE        = 0x2,
    HL_POSITION_ABSOLUTE        = 0x3,
    HL_POSITION_FIXED           = 0x4
} HLPositionEnum;

typedef enum HLVisibilityEnum_ {
	HL_VISIBILITY_INHERIT			= 0x0,
    HL_VISIBILITY_VISIBLE           = 0x1,
    HL_VISIBILITY_HIDDEN            = 0x2,
	HL_VISIBILITY_COLLAPSE			= 0x3
} HLVisibilityEnum;

typedef struct HLDomElementNode_ HLDomElementNode;
typedef struct HLCSS_ HLCSS;
typedef float hl_real_t;

typedef struct HLUsedBoxValues_ {
    hl_real_t x;
    hl_real_t y;
    hl_real_t w;
    hl_real_t h;

    hl_real_t margin_top;
    hl_real_t margin_right;
    hl_real_t margin_bottom;
    hl_real_t margin_left;

    hl_real_t padding_top;
    hl_real_t padding_right;
    hl_real_t padding_bottom;
    hl_real_t padding_left;

    hl_real_t border_top;
    hl_real_t border_right;
    hl_real_t border_bottom;
    hl_real_t border_left;

    hl_real_t border_top_left_radius;
    hl_real_t border_top_right_radius;
    hl_real_t border_bottom_left_radius;
    hl_real_t border_bottom_right_radius;

    int z_index;

    HLDisplayEnum display;
    HLPositionEnum position;
    HLVisibilityEnum visibility;
    hl_real_t opacity;
} HLUsedBoxValues;

typedef struct HLUsedBackgroundValues_ {
    uint32_t color;
} HLUsedBackgroundValues;

typedef enum {
    HLFONT_WEIGHT_THIN,           // 100
    HLFONT_WEIGHT_EXTRA_LIGHT,    // 200
    HLFONT_WEIGHT_LIGHT,          // 300
    HLFONT_WEIGHT_NORMAL,         // 400
    HLFONT_WEIGHT_MEDIUM,         // 500
    HLFONT_WEIGHT_DEMIBOLD,       // 600
    HLFONT_WEIGHT_BOLD,           // 700
    HLFONT_WEIGHT_EXTRA_BOLD,     // 800
    HLFONT_WEIGHT_BLACK           // 900
} HLFontWeight;

typedef enum {
    HLTEXT_ALIGN_LEFT,
    HLTEXT_ALIGN_RIGHT,
    HLTEXT_ALIGN_CENTER,
    HLTEXT_ALIGN_JUSTIFY
} HLTextAlign;

typedef enum {
    HLTEXT_ALIGN_LAST_AUTO,
    HLTEXT_ALIGN_LAST_LEFT,
    HLTEXT_ALIGN_LAST_RIGHT,
    HLTEXT_ALIGN_LAST_CENTER,
    HLTEXT_ALIGN_LAST_JUSTIFY,
    HLTEXT_ALIGN_LAST_START,
    HLTEXT_ALIGN_LAST_END
} HLTextAlignLast;

typedef enum {
    HLTEXT_JUSTIFY_AUTO,
    HLTEXT_JUSTIFY_NONE,
    HLTEXT_JUSTIFY_INTER_WORD,
    HLTEXT_JUSTIFY_INTER_IDEOGRAPH,
    HLTEXT_JUSTIFY_INTER_CLUSTER,
    HLTEXT_JUSTIFY_DISTRIBUTE,
    HLTEXT_JUSTIFY_KASHIDA
} HLTextJustify;


typedef enum {
    HLTEXT_OVERFLOW_CLIP,
    HLTEXT_OVERFLOW_ELLIPSIS,
    HLTEXT_OVERFLOW_STRING
} HLTextOverflow;

typedef enum {
    HLTEXT_TRANSFORM_NONE,
    HLTEXT_TRANSFORM_CAPITALIZE,
    HLTEXT_TRANSFORM_UPPERCASE,
    HLTEXT_TRANSFORM_LOWERCASE
} HLTextTransform;

typedef enum {
    HLWORD_BREAK_NORMAL,
    HLWORD_BREAK_BREAK_ALL,
    HLWORD_BREAK_KEEP_ALL
} HLWordBreak;

typedef enum {
    HLWORD_WRAP_NORMAL,
    HLWORD_WRAP_BREAK_WORD
} HLWordWrap;

typedef enum {
    HLWORDWRAP_HORIZONTAL_TB,
    HLWORDWRAP_VERTICAL_RL,
    HLWORDWRAP_VERTICAL_LR
} HLWritingMode;

typedef struct HLUsedTextValues_ {
    uint32_t color;

    char* font_family;
    hl_real_t font_size;
    HLFontWeight font_weight;

    HLTextAlign text_align;
    HLTextAlignLast text_align_last;
    hl_real_t text_indent;
    HLTextJustify text_justify;
    HLTextOverflow text_overflow;
    char* text_overflow_string;
    hl_real_t text_shadow_h;
    hl_real_t text_shadow_v;
    hl_real_t text_shadow_blur;
    uint32_t text_shadow_color;
    HLTextTransform text_transform;

    HLWordBreak word_break;
    hl_real_t word_spacing;
    HLWordWrap word_wrap;

    HLWritingMode writing_mode;
} HLUsedTextValues;

typedef enum HLBaseLineShiftEnum_ {
    HL_BASELINE_SHIFT_INHERIT        = 0x0,
    HL_BASELINE_SHIFT_BASELINE       = 0x1,
    HL_BASELINE_SHIFT_SUB            = 0x2,
    HL_BASELINE_SHIFT_SUPER          = 0x3
} HLBaseLineShiftEnum;

typedef enum HLFillEnum_ {
    HL_FILL_INHERIT        = 0x0,
    HL_FILL_NONE           = 0x1,
    HL_FILL_URI            = 0x2,
    HL_FILL_CURRENT_COLOR  = 0x3,
    HL_FILL_SET_COLOR      = 0x4
} HLFillEnum;

typedef enum HLFillRuleEnum_ {
    HL_FILL_RULE_INHERIT     = 0x0,
    HL_FILL_RULE_NONZERO     = 0x1,
    HL_FILL_RULE_EVENODD     = 0x2
} HLFillRuleEnum;

typedef enum HLFillOpacityEnum_ {
	HL_FILL_OPACITY_INHERIT			= 0x0,
	HL_FILL_OPACITY_SET				= 0x1
} HLFillOpacityEnum;

typedef enum HLFloodColorEnum_ {
    HL_FLOOD_COLOR_INHERIT         = 0x0,
    HL_FLOOD_COLOR_COLOR           = 0x1
} HLFloodColorEnum;

typedef enum HLClipRuleEnum_ {
    HL_CLIP_RULE_INHERIT     = 0x0,
    HL_CLIP_RULE_NONZERO     = 0x1,
    HL_CLIP_RULE_EVENODD     = 0x2
} HLClipRuleEnum;

typedef enum HLStrokeEnum_ {
    HL_STROKE_INHERIT        = 0x0,
    HL_STROKE_NONE           = 0x1,
    HL_STROKE_URI            = 0x2,
    HL_STROKE_CURRENT_COLOR  = 0x3,
    HL_STROKE_SET_COLOR      = 0x4
} HLStrokeEnum;

typedef enum HLColorEnum_ {
	HL_COLOR_INHERIT			= 0x0,
	HL_COLOR_COLOR				= 0x1
} HLColorEnum;

typedef enum HLDirectionEnum_ {
    HL_DIRECTION_INHERIT           = 0x0,
    HL_DIRECTION_LTR           = 0x1,
    HL_DIRECTION_RTL           = 0x2
} HLDirectionEnum;

typedef enum HLEnableBackgroundEnum_ {
    HL_ENABLE_BACKGROUND_INHERIT     = 0x0,
    HL_ENABLE_BACKGROUND_ACCUMULATE  = 0x1,
    HL_ENABLE_BACKGROUND_NEW         = 0x2
} HLEnableBackgroundEnum;

typedef enum HLOpacityEnum_ {
	HL_OPACITY_INHERIT			= 0x0,
	HL_OPACITY_SET				= 0x1
} HLOpacityEnum;

typedef enum HLFloodOpacityEnum_ {
	HL_FLOOD_OPACITY_INHERIT			= 0x0,
	HL_FLOOD_OPACITY_SET				= 0x1
} HLFloodOpacityEnum;

typedef enum HLCompOpEnum_ {
    HL_COMP_OP_INHERIT     = 0x0,
    HL_COMP_OP_CLEAR       = 0x1,
    HL_COMP_OP_SRC         = 0x2,
    HL_COMP_OP_DST         = 0x3,
    HL_COMP_OP_SRC_OVER    = 0x4,
    HL_COMP_OP_DST_OVER    = 0x5,
    HL_COMP_OP_SRC_IN      = 0x6,
    HL_COMP_OP_DST_IN      = 0x7,
    HL_COMP_OP_SRC_OUT     = 0x8,
    HL_COMP_OP_DST_OUT     = 0x9,
    HL_COMP_OP_SRC_ATOP    = 0xa,
    HL_COMP_OP_DST_ATOP    = 0xb,
    HL_COMP_OP_XOR         = 0xc,
    HL_COMP_OP_PLUS        = 0xd,
    HL_COMP_OP_MULTIPLY    = 0xe,
    HL_COMP_OP_SCREEN      = 0xf,
    HL_COMP_OP_OVERLAY     = 0x10,
    HL_COMP_OP_DARKEN      = 0x11,
    HL_COMP_OP_LIGHTEN     = 0x12,
    HL_COMP_OP_COLOR_DODGE = 0x13,
    HL_COMP_OP_COLOR_BURN  = 0x14,
    HL_COMP_OP_HARD_LIGHT  = 0x15,
    HL_COMP_OP_SOFT_LIGHT  = 0x16,
    HL_COMP_OP_DIFFERENCE  = 0x17,
    HL_COMP_OP_EXCLUSION   = 0x18
} HLCompOpEnum;

typedef enum HLOverflowEnum_ {
	HL_OVERFLOW_INHERIT			= 0x0,
	HL_OVERFLOW_VISIBLE			= 0x1,
	HL_OVERFLOW_HIDDEN			= 0x2,
	HL_OVERFLOW_SCROLL			= 0x3,
	HL_OVERFLOW_AUTO			= 0x4
} HLOverflowEnum;

typedef enum HLStopColorEnum_ {
    HL_STOP_COLOR_INHERIT         = 0x0,
    HL_STOP_COLOR_COLOR           = 0x1
} HLStopColorEnum;

typedef enum HLStopOpacityEnum_ {
	HL_STOP_OPACITY_INHERIT			= 0x0,
	HL_STOP_OPACITY_SET				= 0x1
} HLStopOpacityEnum;

typedef enum HLUnicodeBidiEnum_ {
	HL_UNICODE_BIDI_INHERIT		= 0x0,
	HL_UNICODE_BIDI_NORMAL			= 0x1,
	HL_UNICODE_BIDI_EMBED			= 0x2,
	HL_UNICODE_BIDI_BIDI_OVERRIDE		= 0x3,
    HL_UNICODE_BIDI_ISOLATE            = 0x4,
    HL_UNICODE_BIDI_ISOLATE_OVERRIDE   = 0x5,
    HL_UNICODE_BIDI_PLAINTEXT          = 0x6
} HLUnicodeBidiEnum;

typedef enum HLWritingModeEnum_ {
	HL_WRITING_MODE_INHERIT		= 0x0,
	HL_WRITING_MODE_HORIZONTAL_TB		= 0x1,
	HL_WRITING_MODE_VERTICAL_RL		= 0x2,
	HL_WRITING_MODE_VERTICAL_LR		= 0x3
} HLWritingModeEnum;

typedef enum HLTextAnchorEnum_ {
    HL_TEXT_ANCHOR_INHERIT     = 0x0,
    HL_TEXT_ANCHOR_START       = 0x1,
    HL_TEXT_ANCHOR_MIDDLE      = 0x2,
    HL_TEXT_ANCHOR_END         = 0x3
} HLTextAnchorEnum;

typedef enum HLTextDecorationEnum_ {
	HL_TEXT_DECORATION_INHERIT		= 0x00,
	HL_TEXT_DECORATION_NONE		= 0x10,
	HL_TEXT_DECORATION_BLINK		= (1<<3),
	HL_TEXT_DECORATION_LINE_THROUGH	= (1<<2),
	HL_TEXT_DECORATION_OVERLINE		= (1<<1),
	HL_TEXT_DECORATION_UNDERLINE		= (1<<0)
} HLTextDecorationEnum;

typedef enum HLShapeRenderingEnum {
    HL_SHAPE_RENDERING_INHERIT            = 0x0,
    HL_SHAPE_RENDERING_AUTO               = 0x1,
    HL_SHAPE_RENDERING_OPTIMIZESPEED      = 0x2,
    HL_SHAPE_RENDERING_CRISPEDGES         = 0x3,
    HL_SHAPE_RENDERING_GEOMETRICPRECISION = 0x4,
    HL_SHAPE_RENDERING_DEFAULT            = 0x5
} HLShapeRenderingEnum;

typedef enum HLTextRenderingEnum_ {
    HL_TEXT_RENDERING_INHERIT              = 0x0,
    HL_TEXT_RENDERING_AUTO                 = 0x1,
    HL_TEXT_RENDERING_OPTIMIZESPEED        = 0x2,
    HL_TEXT_RENDERING_GEOMETRICPRECISION   = 0x3,
    HL_TEXT_RENDERING_OPTIMIZELEGIBILITY   = 0x4,
    HL_TEXT_RENDERING_DEFAULT              = 0x5
} HLTextRenderingEnum;

typedef enum HLStrokeMiterlimitEnum_ {
    HL_STROKE_MITERLIMIT_INHERIT        = 0x0,
    HL_STROKE_MITERLIMIT_SET            = 0X1,
    HL_STROKE_MITERLIMIT_AUTO           = 0x2
} HLStrokeMiterlimitEnum;

typedef enum HLStrokeOpacityEnum_ {
	HL_STROKE_OPACITY_INHERIT			= 0x0,
	HL_STROKE_OPACITY_SET				= 0x1
} HLStrokeOpacityEnum;

typedef enum HLStrokeLinejoinEnum_ {
    HL_STROKE_LINEJOIN_INHERIT    = 0x0,
    HL_STROKE_LINEJOIN_MITER      = 0x1,
    HL_STROKE_LINEJOIN_ROUND      = 0x2,
    HL_STROKE_LINEJOIN_BEVEL      = 0x3
} HLStrokeLinejoinEnum;

typedef enum HLStrokeLinecapEnum_ {
    HL_STROKE_LINECAP_INHERIT     = 0x0,
    HL_STROKE_LINECAP_BUTT        = 0x1,
    HL_STROKE_LINECAP_ROUND       = 0x2,
    HL_STROKE_LINECAP_SQUARE      = 0x3
} HLStrokeLinecapEnum;

typedef enum HLFontStretchEnum_ {
    HL_FONT_STRETCH_INHERIT           = 0x0,
    HL_FONT_STRETCH_NORMAL            = 0x1,
    HL_FONT_STRETCH_WIDER             = 0x2,
    HL_FONT_STRETCH_NARROWER          = 0x3,
    HL_FONT_STRETCH_ULTRA_CONDENSED   = 0x4,
    HL_FONT_STRETCH_EXTRA_CONDENSED   = 0x5,
    HL_FONT_STRETCH_CONDENSED         = 0x6,
    HL_FONT_STRETCH_SEMI_CONDENSED    = 0x7,
    HL_FONT_STRETCH_SEMI_EXPANDED     = 0x8,
    HL_FONT_STRETCH_EXPANDED          = 0x9,
    HL_FONT_STRETCH_EXTRA_EXPANDED    = 0xa,
    HL_FONT_STRETCH_ULTRA_EXPANDED    = 0xb
} HLFontStretchEnum;

typedef enum HLSvgFontWeightEnum_ {
	HL_FONT_WEIGHT_INHERIT			= 0x0,
	HL_FONT_WEIGHT_NORMAL			= 0x1,
	HL_FONT_WEIGHT_BOLD			= 0x2,
	HL_FONT_WEIGHT_BOLDER			= 0x3,
	HL_FONT_WEIGHT_LIGHTER			= 0x4,
	HL_FONT_WEIGHT_100			= 0x5,
	HL_FONT_WEIGHT_200			= 0x6,
	HL_FONT_WEIGHT_300			= 0x7,
	HL_FONT_WEIGHT_400			= 0x8,
	HL_FONT_WEIGHT_500			= 0x9,
	HL_FONT_WEIGHT_600			= 0xa,
	HL_FONT_WEIGHT_700			= 0xb,
	HL_FONT_WEIGHT_800			= 0xc,
	HL_FONT_WEIGHT_900			= 0xd
} HLSvgFontWeightEnum;

typedef struct HLUsedSvgValues_ {
    HLBaseLineShiftEnum baseline_shift;
    char* clip_path;
    HLClipRuleEnum clip_rule;

    HLColorEnum color_type;
    uint32_t color;

    HLDisplayEnum display;
    HLEnableBackgroundEnum enable_background;
    HLCompOpEnum comp_op;

    HLDirectionEnum direction;


    // fill
    HLFillEnum fill_type;
    char* fill_string;
    uint32_t fill_color;

    HLFillOpacityEnum fill_opacity_type;
    hl_real_t fill_opacity;

    HLFillRuleEnum fill_rule;

    char* filter;

    HLFloodColorEnum flood_color_type;
    uint32_t flood_color;

    HLFloodOpacityEnum flood_opacity_type;
    hl_real_t flood_opacity;

    HLFontStretchEnum font_stretch;
    HLSvgFontWeightEnum font_weight;

    char* marker_end;
    char* mask;
    char* marker_mid;
    char* marker_start;

    HLOpacityEnum opacity_type;
    hl_real_t opacity;

    HLOverflowEnum overflow;
    HLShapeRenderingEnum shape_rendering;
    HLTextRenderingEnum text_rendering;
    HLStopColorEnum stop_color_type;
    uint32_t stop_color;

    HLStopOpacityEnum stop_opacity_type;
    hl_real_t stop_opacity;

    // stroke
    HLStrokeEnum stroke_type;
    char* stroke_string;
    uint32_t stroke_color;

    HLStrokeLinecapEnum stroke_linecap;
    HLStrokeLinejoinEnum stroke_linejoin;
    HLStrokeMiterlimitEnum stroke_miterlimit_type;
    hl_real_t stroke_miterlimit;

    HLStrokeOpacityEnum stroke_opacity_type;
    hl_real_t stroke_opacity;


    HLTextAnchorEnum text_anchor;
    HLTextDecorationEnum text_decoration;

    HLUnicodeBidiEnum unicode_bidi;
    HLVisibilityEnum visibility;

    HLWritingModeEnum writing_mode;
} HLUsedSvgValues;

typedef struct HLMedia_ {
    unsigned int width;
    unsigned int height;
    unsigned int dpi;
    unsigned int density;
} HLMedia;

#ifdef __cplusplus
extern "C" {
#endif


HLCSS* hilayout_css_create();
int hilayout_css_append_data(HLCSS* css, const char* data, size_t len);
int hilayout_css_destroy(HLCSS* css);

HLDomElementNode* hilayout_element_node_create(const char* tag_name);
const char* hilayout_element_node_get_tag_name(HLDomElementNode* node);

int hilayout_element_node_set_common_attr (HLDomElementNode* node, HLCommonAttribute attr_id, const char* value);
const char* hilayout_element_node_get_common_attr (const HLDomElementNode* node, HLCommonAttribute attr_id);

static inline int hilayout_element_node_set_id (HLDomElementNode* node, const char* id)
{
    return hilayout_element_node_set_common_attr (node, HL_COMMON_ATTR_ID, id);
}

static inline const char* hilayout_element_node_get_id (const HLDomElementNode* node)
{
    return hilayout_element_node_get_common_attr (node, HL_COMMON_ATTR_ID);
}

static inline int hilayout_element_node_set_class (HLDomElementNode* node, const char* class_name)
{
    return hilayout_element_node_set_common_attr (node, HL_COMMON_ATTR_CLASS_NAME, class_name);
}

static inline const char* hilayout_element_node_get_class (const HLDomElementNode* node)
{
    return hilayout_element_node_get_common_attr (node, HL_COMMON_ATTR_CLASS_NAME);
}

int hilayout_element_node_has_class (HLDomElementNode* node, const char* class_name);
int hilayout_element_node_include_class (HLDomElementNode* node, const char* class_name);
int hilayout_element_node_exclude_class (HLDomElementNode* node, const char* class_name);

static inline int hilayout_element_node_set_style (HLDomElementNode* node, const char* style)
{
    return hilayout_element_node_set_common_attr (node, HL_COMMON_ATTR_STYLE, style);
}

static inline const char* hilayout_element_node_get_style (const HLDomElementNode* node)
{
    return hilayout_element_node_get_common_attr (node, HL_COMMON_ATTR_STYLE);
}

static inline int hilayout_element_node_set_name (HLDomElementNode* node, const char* name)
{
    return hilayout_element_node_set_common_attr (node, HL_COMMON_ATTR_NAME, name);
}

static inline const char* hilayout_element_node_get_name (const HLDomElementNode* node)
{
    return hilayout_element_node_get_common_attr(node, HL_COMMON_ATTR_NAME);
}

int hilayout_element_node_set_general_attr (HLDomElementNode* node, const char* attr_name, const char* attr_value);
const char* hilayout_element_node_get_general_attr (const HLDomElementNode* node, const char* attr_name);

typedef void  (*HlDestroyCallback)(void* data);
int hilayout_element_node_set_user_data(HLDomElementNode* node, const char* key, void* data, HlDestroyCallback destroy_callback);
void* hilayout_element_node_get_user_data(const HLDomElementNode* node, const char* key);

extern const uint32_t MAX_ATTACH_DATA_SIZE;
int hilayout_element_node_set_attach_data(HLDomElementNode* node, uint32_t index, void* data, HlDestroyCallback destroy_callback);
void* hilayout_element_node_get_attach_data(const HLDomElementNode* node, uint32_t index);

void hilayout_element_node_destroy(HLDomElementNode *node);

const HLUsedBoxValues* hilayout_element_node_get_used_box_value(HLDomElementNode* node);
const HLUsedBackgroundValues* hilayout_element_node_get_used_background_value(HLDomElementNode* node);
const HLUsedTextValues* hilayout_element_node_get_used_text_value(HLDomElementNode* node);
HLUsedSvgValues* hilayout_element_node_get_used_svg_value(HLDomElementNode* node);

int hilayout_element_node_append_as_last_child(HLDomElementNode* node, HLDomElementNode* parent);
HLDomElementNode* hilayout_element_node_get_parent(HLDomElementNode* node);
HLDomElementNode* hilayout_element_node_get_first_child(HLDomElementNode* node);
HLDomElementNode* hilayout_element_node_get_last_child(HLDomElementNode* node);
HLDomElementNode* hilayout_element_node_get_prev(HLDomElementNode* node);
HLDomElementNode* hilayout_element_node_get_next(HLDomElementNode* node);
uint32_t hilayout_element_node_get_children_count(HLDomElementNode* node);

int hilayout_do_layout(HLMedia* media, HLCSS* css, HLDomElementNode *root);

typedef void (*NodeCallback)(HLDomElementNode* node, void* user_data);
void hilayout_element_node_for_each_child(HLDomElementNode* node, NodeCallback callback, void* user_data);
void hilayout_element_node_depth_first_search_tree(HLDomElementNode* node, NodeCallback callback, void* user_data);

#ifdef __cplusplus
}
#endif

#endif // _HI_DOMLAYOUT_H_
