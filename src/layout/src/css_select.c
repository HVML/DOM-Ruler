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
static css_error
node_name(void *pw, void *node, css_qname *qname)
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

/**
 * Callback to retrieve a node's classes.
 *
 * \param pw         HTML document
 * \param node       DOM node
 * \param classes    Pointer to location to receive class name array
 * \param n_classes  Pointer to location to receive length of class name array
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \note The returned array will be destroyed by libcss. Therefore, it must
 *       be allocated using the same allocator as used by libcss during style
 *       selection.
 */
static css_error
node_classes(void *pw, void *node, lwc_string ***classes, uint32_t *n_classes)
{
    HiLayoutNode *n = node;

    if (n->nr_inner_classes == 0) {
        int nr_clses = 0;
        const char **clses = hi_layout_node_get_classes(n, &nr_clses);
        n->inner_classes = (lwc_string**)calloc(nr_clses, sizeof(lwc_string*));
        for (int i = 0; i < nr_clses; i++) {
            n->inner_classes[i]= to_lwc_string(clses[i]);
        }
        n->nr_inner_classes = nr_clses;
    }

    if (n->nr_inner_classes > 0) {
        *classes = n->inner_classes;
        *n_classes = n->nr_inner_classes;

        for (int i = 0; i < n->nr_inner_classes; i++) {
            (void) lwc_string_ref((*classes)[i]);
        }
    } else {
        *n_classes = 0;
        *classes = NULL;
    }
    return CSS_OK;
}

/**
 * Callback to retrieve a node's ID.
 *
 * \param pw    HTML document
 * \param node  DOM node
 * \param id    Pointer to location to receive id value
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 */
static css_error
node_id(void *pw, void *node, lwc_string **id)
{
    HiLayoutNode *n = node;

    const char *nid = hi_layout_node_get_id(n);
    if (nid == NULL) {
        *id = NULL;
        return CSS_OK;
    }

    if (n->inner_id == NULL) {
        n->inner_id = to_lwc_string(nid);
    }

    *id = lwc_string_ref(n->inner_id);
    return CSS_OK;
}

/**
 * Callback to find a named parent node
 *
 * \param pw      HTML document
 * \param node    DOM node
 * \param qname   Node name to search for
 * \param parent  Pointer to location to receive parent
 * \return CSS_OK.
 *
 * \post \a parent will contain the result, or NULL if there is no match
 */
static css_error
named_parent_node(void *pw, void *n, const css_qname *qname, void **parent)
{
    HiLayoutNode *node = n;

    *parent = NULL;

    for (node = hi_layout_node_get_parent(node); node != NULL;
            node = hi_layout_node_get_parent(node)) {

#if 0 // TODO
        if (node->inner_dom_type != DOM_ELEMENT_NODE) {
            continue;
        }
#endif

        const char *name = hi_layout_node_get_name(node);
        assert(name != NULL);
        if (!node->inner_tag) {
            node->inner_tag = to_lwc_string(name);
        }

        bool match = false;
        if (lwc_string_caseless_isequal(node->inner_tag, qname->name,
                    &match) == lwc_error_ok && match)
        {
            *parent = node;
        }
        break;
    }

    return CSS_OK;
}
