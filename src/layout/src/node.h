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


#ifndef _HL_NODE_H
#define _HL_NODE_H

#include "hidomlayout.h"

#include <libcss/libcss.h>
#include <glib.h>

#define LAYOUT(node)            (hl_layout(node, handler))

typedef struct NodeLayout {
    //inner layout
    LayoutType layout_type;

    // begin for layout output
    HLUsedBoxValues box_values;
    HLUsedBackgroundValues background_values;
    HLUsedTextValues text_values;
    HLUsedSvgValues* svg_values;

    // top, right, bottom, left
    double margin[4];
    double padding[4];
    double border[4];
    int borderType[4];
    // end for layout output

    // for css select result
    css_select_results* select_styles;
    css_computed_style* computed_style;

} NodeLayout;

#ifdef __cplusplus
extern "C" {
#endif

NodeLayout *hl_layout(void *node, hidomlayout_layout_handler *handler);

#ifdef __cplusplus
}
#endif

#endif // _HL_NODE_H
