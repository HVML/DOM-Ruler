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


#include "hidomlayout.h"
#include "layout.h"

#include "utils.h"
#include "select.h"

#include "hl_dom_element_node.h"

#include <stdio.h>
#include <stdlib.h>


static inline
bool hl_verify_handler(hidomlayout_node_op *op)
{
    if (!op || !op->set_attach || !op->get_attach
            || !op->set_parent || !op->get_parent
            || !op->first_child || !op->next
            || !op->is_root) {
        return false;
    }
    return true;
}

int hidomlayout_layout(HLMedia *media, HLCSS *css, void *root,
        hidomlayout_node_op *op)
{
    if (!media || !css || !root || !hl_verify_handler(op)) {
        HL_LOGE("%s|media=%p|root=%p|css=%p|style_sheet=%p|param error\n",
                __func__, media, root, css, css->sheet);
        return HILAYOUT_BADPARM;
    }

    int ret = HILAYOUT_OK;
    HLContext context = {
        .media = media,
        .css = css,
        .root = root,
    };
    hl_set_media_dpi(&context, media->dpi);
    hl_set_baseline_pixel_density(&context, media->density);

    css_media m;
    m.type = CSS_MEDIA_SCREEN;
    m.width  = hl_css_pixels_physical_to_css(&context, INTTOFIX(media->width));
    m.height = hl_css_pixels_physical_to_css(&context, INTTOFIX(media->height));
    context.vw = m.width;
    context.vh = m.height;

    // create css select context
    css_select_ctx* select_ctx = hl_css_select_ctx_create(css);

#if 0
    ret = hl_select_child_style(&m, select_ctx, root, op);
    if (ret != HILAYOUT_OK) {
        HL_LOGD("%s|select child style failed.|code=%d\n", __func__, ret);
        hl_css_select_ctx_destroy(select_ctx);
        return ret;
    }

    HiLayoutNode* layout = hl_layout(root, op);
    context.root_style = layout->computed_style;
    hl_layout_node(&context, root, 0, 0, media->width, media->height, 0,
            op);
#endif
    hl_css_select_ctx_destroy(select_ctx);

    return ret;
}
