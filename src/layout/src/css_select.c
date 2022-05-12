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

#include "select.h"
#include "utils.h"
#include "node.h"
#include <stdio.h>
#include <string.h>


#define UNUSED(x) ((x) = (x))

/******************************************************************************
 * Style selection callbacks                                                  *
 ******************************************************************************/

lwc_string *to_lwc_string(const char* str)
{
    if (str == NULL) {
        return NULL;
    }

    lwc_string *result = NULL;
    lwc_intern_string(str, strlen(str), &result);
    return result;
}

/**
 * Callback to retrieve a node's name.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Pointer to location to receive node name
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 */
static
css_error node_name(void *pw, void *node, css_qname *qname)
{
    HiLayoutNode *n = node;

    const char *name = hi_layout_node_get_name(n);
    if (name == NULL) {
        qname->name = NULL;
        return CSS_NOMEM;
    }

    if (!n->inner_tag) {
        n->inner_tag = to_lwc_string(name);
    }
    qname->name = lwc_string_ref(n->inner_tag);
    return CSS_OK;
}

