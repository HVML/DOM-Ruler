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

    Copyright (C) 2022 Beijing FMSoft Technologies Co., Ltd.

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


#include "hidomlayout.h"
#include "internal.h"
#include "layout.h"

#include "utils.h"
#include "select.h"

#include "hl_dom_element_node.h"
#include "hl_pcdom_element_t.h"

#include <stdio.h>
#include <stdlib.h>

static inline
bool hl_verify_handler(HiDOMLayoutNodeOp *op)
{
    if (!op || !op->set_attach || !op->get_attach
            || !op->get_type || !op->get_name
            || !op->get_id || !op->get_classes
            || !op->get_attr
            || !op->set_parent || !op->get_parent
            || !op->first_child || !op->next
            || !op->previous
            || !op->is_root) {
        return false;
    }
    return true;
}

struct HiDOMLayoutCtxt *hidomlayout_create(uint32_t width, uint32_t height,
        uint32_t dpi, uint32_t density)
{
    struct HiDOMLayoutCtxt *ctxt = (struct HiDOMLayoutCtxt *)calloc(1,
            sizeof(struct HiDOMLayoutCtxt));
    if (ctxt == NULL) {
        return NULL;
    }
    ctxt->width = width;
    ctxt->height = height;
    ctxt->dpi = dpi;
    ctxt->density = density;

    ctxt->node_map = g_hash_table_new_full(g_direct_hash,
            g_direct_equal, NULL, cb_hi_layout_node_destroy);
    if (ctxt->node_map == NULL) {
        hidomlayout_destroy(ctxt);
        return NULL;
    }
    return ctxt;
}

int hidomlayout_append_css(struct HiDOMLayoutCtxt *ctxt, const char *css,
        size_t nr_css)
{
    return 0;
}

int hidomlayout_layout(struct HiDOMLayoutCtxt *ctxt, void *root_node,
        HiDOMLayoutNodeOp *op)
{
    return 0;
}

const HLBox *hidomlayout_get_node_box(struct HiDOMLayoutCtxt *ctxt,
        void *node)
{
    return 0;
}

void hidomlayout_destroy(struct HiDOMLayoutCtxt *ctxt)
{
    if (ctxt->css) {
        hilayout_css_destroy(ctxt->css);
    }

    if (ctxt->node_map) {
        g_hash_table_destroy(ctxt->node_map);
    }
    free(ctxt);
}

int hidomlayout_layout_ex(HLMedia *media, HLCSS *css, void *root,
        HiDOMLayoutNodeOp *op)
{
    if (!media || !css || !root || !hl_verify_handler(op)) {
        HL_LOGE("%s|media=%p|root=%p|css=%p|style_sheet=%p|param error\n",
                __func__, media, root, css, css->sheet);
        return HILAYOUT_BADPARM;
    }

    HiLayoutNode *node = hi_layout_node_from_origin_node(root, op);
    return hi_layout_do_layout(media, css, node);
}

int hilayout_do_layout(HLMedia* media, HLCSS* css, HLDomElementNode *root)
{
    return hidomlayout_layout_ex(media, css, root, hl_dom_element_node_get_op());
}

int hilayout_do_pcdom_layout(HLMedia* media, HLCSS* css, pcdom_element_t *root)
{
    return hidomlayout_layout_ex(media, css, root, hl_pcdom_element_t_get_op());
}

const HLBox* hidomlayout_get_layout_box(void *node,
        HiDOMLayoutNodeOp *handler)
{
    if (!node) {
        return NULL;
    }

    HiLayoutNode *layout = hi_layout_node_from_origin_node(node, handler);
    return layout ? &layout->box_values : NULL;
}

const HLBox *hilayout_get_pcdom_layout_box(pcdom_element_t *node)
{
    return hidomlayout_get_layout_box(node, hl_pcdom_element_t_get_op());
}

