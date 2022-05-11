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

#include "node.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/ghash.h>

HiLayoutNode *hl_layout(void *node, hidomlayout_node_op *op)
{
    return (HiLayoutNode*) op->get_attach(node, NULL);
}

HiLayoutNode *hi_layout_node_create(void)
{
    return (HiLayoutNode*) calloc(1, sizeof(HiLayoutNode));
}

void hi_layout_node_destroy(HiLayoutNode *node)
{
    if (!node) {
        return;
    }

    hl_destroy_svg_values(node->svg_values);

    if (node->text_values.font_family) {
        free(node->text_values.font_family);
    }

    if (node->select_styles) {
        css_select_results_destroy(node->select_styles);
    }
    free(node);
}

void cb_hi_layout_node_destroy(void *n)
{
    hi_layout_node_destroy((HiLayoutNode *)n);
}

HiLayoutNode *hi_layout_node_from_origin_node(void *origin,
        hidomlayout_node_op *op)
{
    if (!origin) {
        return NULL;
    }

    HiLayoutNode *layout =  op->get_attach(origin, NULL);
    if (layout) {
        return layout;
    }
    layout = hi_layout_node_create();
    if (!layout) {
        return NULL;
    }
    layout->origin = origin;
    layout->origin_op = op;
    op->set_attach(origin, layout, cb_hi_layout_node_destroy);
    return layout;
}

void *hi_layout_node_to_origin_node(HiLayoutNode *layout,
        hidomlayout_node_op **op)
{
    if (!layout->origin) {
        return NULL;
    }
    if (op) {
        *op = layout->origin_op;
    }
    return layout->origin;
}

HiLayoutNode *hi_layout_node_get_parent(HiLayoutNode *node)
{
    void *origin = node->origin_op->get_parent(node->origin);
    return hi_layout_node_from_origin_node(origin, NULL);
}

void hi_layout_node_set_parent(HiLayoutNode *node, HiLayoutNode *parent)
{
    node->origin_op->set_parent(node->origin, parent->origin);
}

HiLayoutNode *hi_layout_node_first_child(HiLayoutNode *node)
{
    void *origin = node->origin_op->first_child(node->origin);
    return hi_layout_node_from_origin_node(origin, NULL);
}

HiLayoutNode *hi_layout_node_next(HiLayoutNode *node)
{
    void *origin = node->origin_op->next(node->origin);
    return hi_layout_node_from_origin_node(origin, NULL);
}

bool hi_layout_node_is_root(HiLayoutNode *node)
{
    return node->origin_op->is_root(node->origin);
}

int hl_find_background(HiLayoutNode *node)
{
    css_color color;
    css_computed_background_color(node->computed_style, &color);
    node->background_values.color = color;
    return HILAYOUT_OK;
}

int hl_find_font(HLContext *ctx, HiLayoutNode *node)
{
    lwc_string **families;
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;

    HiLayoutNode* parent = hi_layout_node_get_parent(node);

    uint8_t val = css_computed_font_family(node->computed_style, &families);
    if (val == CSS_FONT_FAMILY_INHERIT) {
        HL_LOGD("node node|tag=%s|id=%s|font inherit\n", node->tag, node->id);
        if (parent && parent->text_values.font_family) {
            free (node->text_values.font_family);
            node->text_values.font_family =
                strdup(parent->text_values.font_family);
        }
    }
    else {
        char* buf[1024] = {0};
        int index = 0;
        int len = 0;
        if (families != NULL) {
            while (*families != NULL) {
                buf[index] = strdup(lwc_string_data(*families));
                len += strlen(buf[index]) + 1;
                index++;
                families++;
            }
        }

        switch (val) {
            case CSS_FONT_FAMILY_SERIF:
                buf[index] = strdup("serif");
                len += strlen(buf[index]) + 1;
                index++;
                break;
            case CSS_FONT_FAMILY_SANS_SERIF:
                buf[index] = strdup("sans-serif");
                len += strlen(buf[index]) + 1;
                index++;
                break;
            case CSS_FONT_FAMILY_CURSIVE:
                buf[index] = strdup("cursive");
                len += strlen(buf[index]) + 1;
                index++;
                break;
            case CSS_FONT_FAMILY_FANTASY:
                buf[index] = strdup("fantasy");
                len += strlen(buf[index]) + 1;
                index++;
                break;
            case CSS_FONT_FAMILY_MONOSPACE:
                buf[index] = strdup("monospace");
                len += strlen(buf[index]) + 1;
                index++;
                break;
        }

        char* result = (char*)calloc(len + 1, 1);
        for (int i=0; i<index; i++) {
            strcat(result, buf[i]);
            strcat(result, ",");
            free(buf[i]);
        }
        result[strlen(result) - 1 ] = 0;
        free (node->text_values.font_family);
        node->text_values.font_family = result;
    }

    css_computed_font_size(node->computed_style, &length, &unit);
    int text_height = hl_css_len2px(ctx, length, unit, node->computed_style);
    node->text_values.font_size = FIXTOINT(text_height * 3 / 4);

    css_color color;
    val = css_computed_color(node->computed_style, &color);
    if (val == CSS_COLOR_INHERIT) {
        if (parent) {
            node->text_values.color = parent->text_values.color;
        }
    } else if (val == CSS_COLOR_COLOR) {
        node->text_values.color = color;
    }

    val = css_computed_font_weight(node->computed_style);
    switch (val) {
    case CSS_FONT_WEIGHT_100:
        node->text_values.font_weight = HLFONT_WEIGHT_THIN;
        break;
    case CSS_FONT_WEIGHT_200:
        node->text_values.font_weight = HLFONT_WEIGHT_EXTRA_LIGHT;
        break;
    case CSS_FONT_WEIGHT_300:
        node->text_values.font_weight = HLFONT_WEIGHT_LIGHT;
        break;
    case CSS_FONT_WEIGHT_400:
    case CSS_FONT_WEIGHT_NORMAL:
    default:
        node->text_values.font_weight = HLFONT_WEIGHT_NORMAL;
        break;
    case CSS_FONT_WEIGHT_500:
        node->text_values.font_weight = HLFONT_WEIGHT_MEDIUM;
        break;
    case CSS_FONT_WEIGHT_600:
        node->text_values.font_weight = HLFONT_WEIGHT_DEMIBOLD;
        break;
    case CSS_FONT_WEIGHT_700:
    case CSS_FONT_WEIGHT_BOLD:
        node->text_values.font_weight = HLFONT_WEIGHT_BOLD;
        break;
    case CSS_FONT_WEIGHT_800:
        node->text_values.font_weight = HLFONT_WEIGHT_EXTRA_BOLD;
        break;
    case CSS_FONT_WEIGHT_900:
        node->text_values.font_weight = HLFONT_WEIGHT_BLACK;
        break;
    }
}

