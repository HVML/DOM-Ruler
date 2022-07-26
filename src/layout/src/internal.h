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

    This file is part of DOM Ruler. DOM Ruler is a library to
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

#ifndef _HL_INTERNAL_H
#define _HL_INTERNAL_H

#include "domruler.h"
#include <libcss/libcss.h>

#include <glib.h>
#include <glib/ghash.h>

struct HiLayoutNode;

struct DOMRulerCtxt {
    // media
    uint32_t width;
    uint32_t height;
    uint32_t dpi;
    uint32_t density;

    // css
    HLCSS *css;
    css_fixed hl_css_media_dpi;
    css_fixed hl_css_baseline_pixel_density;

    int vw;
    int vh;
    const css_computed_style *root_style;

    struct HiLayoutNode *root;

    // Origin Root Node
    void *origin_root;
    DOMRulerNodeOp *origin_op;

    GHashTable *node_map; // key(origin node pointer) -> value(HiLayoutNode *)
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif // _HL_INTERNAL_H

