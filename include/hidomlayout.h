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

    This file is part of HybridOS, a developing operating system based on
    MiniGUI. HybridOs will support embedded systems and smart IoT devices.

    Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.

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

#define HILAYOUT_MAX_CLASS_COUNT   1024

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


typedef struct HLUsedTextValues_ {
    char* family;
    int size;
    uint32_t color;
    HLFontWeight weight;
} HLUsedTextValues;

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

int hilayout_element_node_set_common_attr(HLDomElementNode* node, HLCommonAttribute attr_id, const char* value);
const char* hilayout_element_node_get_common_attr (HLDomElementNode* node, HLCommonAttribute attr_id);

static inline void hilayout_element_node_set_id(HLDomElementNode* node, const char* id)
{
    hilayout_element_node_set_common_attr(node, HL_COMMON_ATTR_ID, id);
}

static inline const char* hilayout_element_node_get_id(HLDomElementNode* node)
{
    return hilayout_element_node_get_common_attr(node, HL_COMMON_ATTR_ID);
}

static inline void hilayout_element_node_set_class_name(HLDomElementNode* node, const char* class_name)
{
    hilayout_element_node_set_common_attr(node, HL_COMMON_ATTR_CLASS_NAME, class_name);
}

static inline const char* hilayout_element_node_get_class_name(HLDomElementNode* node)
{
    return hilayout_element_node_get_common_attr(node, HL_COMMON_ATTR_CLASS_NAME);
}

static inline void hilayout_element_node_set_style(HLDomElementNode* node, const char* style)
{
    hilayout_element_node_set_common_attr(node, HL_COMMON_ATTR_STYLE, style);
}

static inline const char* hilayout_element_node_get_style(HLDomElementNode* node)
{
    return hilayout_element_node_get_common_attr(node, HL_COMMON_ATTR_STYLE);
}

static inline void hilayout_element_node_set_name(HLDomElementNode* node, const char* name)
{
    hilayout_element_node_set_common_attr(node, HL_COMMON_ATTR_NAME, name);
}

static inline const char* hilayout_element_node_get_name(HLDomElementNode* node)
{
    return hilayout_element_node_get_common_attr(node, HL_COMMON_ATTR_NAME);
}

int hilayout_element_node_set_general_attr(HLDomElementNode* node, const char* attr_name, const char* attr_value);
const char* hilayout_element_node_get_general_attr(HLDomElementNode* node, const char* attr_name);

typedef void  (*HlDestroyCallback)(void* data);
int hilayout_element_node_set_user_data(HLDomElementNode* node, const char* key, void* data, HlDestroyCallback destroy_callback);
void* hilayout_element_node_get_user_data(HLDomElementNode* node, const char* key);

void hilayout_element_node_destroy(HLDomElementNode *node);

const HLUsedBoxValues* hilayout_element_node_get_used_box_value(HLDomElementNode* node);
const HLUsedBackgroundValues* hilayout_element_node_get_used_background_value(HLDomElementNode* node);
const HLUsedTextValues* hilayout_element_node_get_used_text_value(HLDomElementNode* node);

int hilayout_element_node_append_as_last_child(HLDomElementNode* node, HLDomElementNode* parent);

int hilayout_do_layout(HLMedia* media, HLCSS* css, HLDomElementNode *root);

#ifdef __cplusplus
}
#endif

#endif // _HI_DOMLAYOUT_H_
