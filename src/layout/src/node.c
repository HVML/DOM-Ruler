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

HiLayoutNode *hl_layout(void *node, hidomlayout_layout_handler *handler)
{
    return (HiLayoutNode*) handler->get_attach(node, NULL);
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
        hidomlayout_layout_handler *op)
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
        hidomlayout_layout_handler **op)
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

