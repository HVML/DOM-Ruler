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

    Copyright (C) 2021~2022 Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General License for more details.

    You should have received a copy of the GNU Lesser General License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU Lesser General License version 3 (LGPLv3). If you cannot accept
    LGPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */


#ifndef _HL_NODE_H
#define _HL_NODE_H

#include "hidomlayout.h"
#include "utils.h"

#include <libcss/libcss.h>
#include <glib.h>

#define HL_INNER_CSS_SELECT_ATTACH  "hl_inner_css_select_attach"
#define HL_INNER_LAYOUT_ATTACH      "hl_inner_layout_attach"

#define ATTR_NAME_STYLE             "style"

typedef struct HLAttachData_ {
    void* data;
    HlDestroyCallback callback;
} HLAttachData;

typedef enum HLGridItemRowColumnE_ {
    HL_GRID_ITEM_RC_NONE            = 0x00,
    HL_GRID_ITEM_RC_FULL            = 0x0F,
    HL_GRID_ITEM_RC_ROW_START       = (1<<3),
    HL_GRID_ITEM_RC_ROW_END         = (1<<2),
    HL_GRID_ITEM_RC_COLUMN_START    = (1<<1),
    HL_GRID_ITEM_RC_COLUMN_END      = (1<<0),
} HLGridItemRowColumnE;

typedef struct HLGridItem_ {
    HLGridItemRowColumnE rc_set;
    int row_start;
    int row_end;

    int column_start;
    int column_end;
    uint8_t layout_done;
} HLGridItem;

typedef struct HLGridTemplate_ {
    int x;
    int y;
    int w;
    int h;
    int32_t *rows;
    int32_t *columns;

    int n_row;
    int n_column;

    uint8_t **mask;
} HLGridTemplate;

typedef struct HiLayoutNode {
    //inner layout
    LayoutType layout_type;

    // begin for layout output
    HLUsedBoxValues box_values;
    HLUsedBackgroundValues background_values;
    HLUsedTextValues text_values;
    HLUsedSvgValues *svg_values;

    // top, right, bottom, left
    double margin[4];
    double padding[4];
    double border[4];
    int borderType[4];
    // end for layout output

    // for css select result
    css_select_results *select_styles;
    css_computed_style *computed_style;

    // inner data
    GHashTable *inner_data;   // inner data key(string) -> value(HLAttachData)
    HLAttachData *attach_data; // attach data

    // begin for hicss inner
    lwc_string *inner_tag;
    lwc_string *inner_id;
    lwc_string **inner_classes;
    int nr_inner_classes;
    // end for hicss inner

    // Origin Node
    void *origin;
    hidomlayout_node_op *origin_op;
} HiLayoutNode;

#ifdef __cplusplus
extern "C" {
#endif

int hi_layout_node_set_attach_data(HiLayoutNode *node,
        uint32_t index, void *data, HlDestroyCallback destroy_callback);
void *hi_layout_node_get_attach_data(const HiLayoutNode *node,
        uint32_t index);
int hi_layout_node_set_inner_data(HiLayoutNode *node, const char *key,
        void *data, HlDestroyCallback destroy_callback);
void *hi_layout_node_get_inner_data(HiLayoutNode *node, const char *key);

int hl_find_background(HiLayoutNode *node);
int hl_find_font(HLContext *ctx, HiLayoutNode *node);

HLGridItem *hl_grid_item_create(HiLayoutNode *node);
void hl_grid_item_destroy(HLGridItem*);

HLGridTemplate *hl_grid_template_create(const HLContext *ctx,
        HiLayoutNode *node);
void hl_grid_template_destroy(HLGridTemplate*);

typedef void (*each_child_callback)(HLContext *ctx, HiLayoutNode *node,
        void *user_data);

void hl_for_each_child(HLContext *ctx, HiLayoutNode *node,
        each_child_callback callback, void *user_data);


// BEGIN: HiLayoutNode  < ----- > Origin Node
HiLayoutNode *hi_layout_node_from_origin_node(void *node,
        hidomlayout_node_op *op);
void *hi_layout_node_to_origin_node(HiLayoutNode *layout,
        hidomlayout_node_op **op);

HLNodeType hi_layout_node_get_type(HiLayoutNode *node);
const char *hi_layout_node_get_name(HiLayoutNode *node);
const char *hi_layout_node_get_id(HiLayoutNode *node);
const char **hi_layout_node_get_classes(HiLayoutNode *node, int *nr_classes);
const char *hi_layout_node_get_attr(HiLayoutNode *node, const char *attr);
HiLayoutNode *hi_layout_node_get_parent(HiLayoutNode *node);
void hi_layout_node_set_parent(HiLayoutNode *node, HiLayoutNode *parent);
HiLayoutNode *hi_layout_node_first_child(HiLayoutNode *node);
HiLayoutNode *hi_layout_node_next(HiLayoutNode *node);
HiLayoutNode *hi_layout_node_previous(HiLayoutNode *node);
bool hi_layout_node_is_root(HiLayoutNode *node);
// END: HiLayoutNode  < ----- > Origin Node


#ifdef __cplusplus
}
#endif

#endif // _HL_NODE_H
