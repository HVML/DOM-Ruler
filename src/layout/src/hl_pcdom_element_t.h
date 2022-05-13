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


#ifndef _HL_DOM_ELEMENT_NODE_H
#define _HL_DOM_ELEMENT_NODE_H

#include "hidomlayout.h"
#include "node.h"
#include "libcss/libcss.h"

#include <glib.h>
#include <glib/ghash.h>

void hl_pcdom_element_set_attach(void *node, void *data,
        cb_free_attach_data cb_free);
void *hl_pcdom_element_get_attach(void *node, cb_free_attach_data *cb_free);
HLNodeType hl_pcdom_element_get_type(void *node);
const char *hl_pcdom_element_get_name(void *node);
const char *hl_pcdom_element_get_id(void *node);
int hl_pcdom_element_get_classes(void *node, char ***classes);
const char *hl_pcdom_element_get_attr(void *node, const char *attr);
void hl_pcdom_element_set_parent(void *node, void *parent);
void *hl_pcdom_element_get_parent(void *node);
void *hl_pcdom_element_first_child(void *node);
void *hl_pcdom_element_next(void *node);
void *hl_pcdom_element_previous(void *node);
bool hl_pcdom_element_is_root(void *node);

hidomlayout_node_op *hl_pcdom_element_get_op();

#ifdef __cplusplus
}
#endif

#endif // _HL_DOM_ELEMENT_NODE_H
