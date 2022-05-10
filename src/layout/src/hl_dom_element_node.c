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
#include "hl_dom_element_node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/ghash.h>

void hl_dom_element_node_set_attach(void *node, void *data,
        cb_free_attach_data cb_free)
{
}

void *hl_dom_element_node_get_attach(void *node, cb_free_attach_data *cb_free)
{
    return NULL;
}

void *hl_dom_element_node_parent(void *node)
{
    return node ? ((HLDomElementNode*)node)->parent : NULL;
}

void hl_dom_element_node_set_parent(void *node, void *parent)
{
    if (node) {
        ((HLDomElementNode*)node)->parent = (HLDomElementNode*)parent;
    }
}

void *hl_dom_element_node_first_child(void *node)
{
    return node ? ((HLDomElementNode*)node)->first_child : NULL;
}

void *hl_dom_element_node_next_child(void *node)
{
    return node ? ((HLDomElementNode*)node)->next : NULL;
}

bool hl_dom_element_node_is_root(void *node)
{
    if (node == NULL) {
        return false;
    }


    HLDomElementNode *parent = ((HLDomElementNode*)node)->parent;
    if (parent != NULL) {
        return false;
    }
    return true;
}


NodeLayout *hl_dom_element_node_layout(void *node)
{
    return &((HLDomElementNode*)node)->layout;
}
