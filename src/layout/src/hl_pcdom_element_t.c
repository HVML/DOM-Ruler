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

#include "node.h"
#include "utils.h"
#include "hl_pcdom_element_t.h"
#include "libcss/libcss.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/ghash.h>


void hl_pcdom_element_set_attach(void *n, void *data,
        cb_free_attach_data cb_free)
{
}

void *hl_pcdom_element_get_attach(void *n, cb_free_attach_data *cb_free)
{
    return NULL;
}

HLNodeType hl_pcdom_element_get_type(void *node)
{
    return 0;
}

const char *hl_pcdom_element_get_name(void *node)
{
    return NULL;
}

const char *hl_pcdom_element_get_id(void *node)
{
    return NULL;
}

int hl_pcdom_element_get_classes(void *n, char ***classes)
{
    return 0;
}

const char *hl_pcdom_element_get_attr(void *n, const char *name)
{
    return NULL;
}

void hl_pcdom_element_set_parent(void *node, void *parent)
{
}

void *hl_pcdom_element_get_parent(void *node)
{
    return NULL;
}

void *hl_pcdom_element_first_child(void *node)
{
    return NULL;
}

void *hl_pcdom_element_next(void *node)
{
    return NULL;
}

void *hl_pcdom_element_previous(void *node)
{
    return NULL;
}

bool hl_pcdom_element_is_root(void *node)
{
    return false;
}

hidomlayout_node_op hl_pcdom_element_op = {
    .set_attach = hl_pcdom_element_set_attach,
    .get_attach = hl_pcdom_element_get_attach,
    .get_type = hl_pcdom_element_get_type,
    .get_name = hl_pcdom_element_get_name,
    .get_id = hl_pcdom_element_get_id,
    .get_classes = hl_pcdom_element_get_classes,
    .get_attr = hl_pcdom_element_get_attr,
    .set_parent = hl_pcdom_element_set_parent,
    .get_parent = hl_pcdom_element_get_parent,
    .first_child = hl_pcdom_element_first_child,
    .next = hl_pcdom_element_next,
    .previous = hl_pcdom_element_previous,
    .is_root = hl_pcdom_element_is_root
};

hidomlayout_node_op *hl_pcdom_element_get_op()
{
    return &hl_pcdom_element_op;
}


