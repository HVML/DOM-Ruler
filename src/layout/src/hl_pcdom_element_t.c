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


void hl_pcdom_element_t_set_attach(void *n, void *data,
        cb_free_attach_data cb_free)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    if (node->attach && node->attach != data && node->attach_destroy_f) {
        node->attach_destroy_f(node->attach);
    }
    node->attach = data;
    node->attach_destroy_f = cb_free;
}

void *hl_pcdom_element_t_get_attach(void *n, cb_free_attach_data *cb_free)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    if (cb_free) {
        *cb_free = node->attach_destroy_f;
    }
    return node->attach;
}

HLNodeType hl_pcdom_element_t_get_type(void *n)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    switch (node->type) {
    case PCDOM_NODE_TYPE_UNDEF:
        return DOM_UNDEF;
    case PCDOM_NODE_TYPE_ELEMENT:
        return DOM_ELEMENT_NODE;
    case PCDOM_NODE_TYPE_ATTRIBUTE:
        return DOM_ATTRIBUTE_NODE;
    case PCDOM_NODE_TYPE_TEXT:
        return DOM_TEXT_NODE;
    case PCDOM_NODE_TYPE_CDATA_SECTION:
        return DOM_CDATA_SECTION_NODE;
    case PCDOM_NODE_TYPE_ENTITY_REFERENCE:
        return DOM_ENTITY_REFERENCE_NODE;
    case PCDOM_NODE_TYPE_ENTITY:
        return DOM_ENTITY_NODE;
    case PCDOM_NODE_TYPE_PROCESSING_INSTRUCTION:
        return DOM_PROCESSING_INSTRUCTION_NODE;
    case PCDOM_NODE_TYPE_COMMENT:
        return DOM_COMMENT_NODE;
    case PCDOM_NODE_TYPE_DOCUMENT:
        return DOM_DOCUMENT_NODE;
    case PCDOM_NODE_TYPE_DOCUMENT_TYPE:
        return DOM_DOCUMENT_TYPE_NODE;
    case PCDOM_NODE_TYPE_DOCUMENT_FRAGMENT:
        return DOM_DOCUMENT_FRAGMENT_NODE;
    case PCDOM_NODE_TYPE_NOTATION:
        return DOM_NOTATION_NODE;
    }
    return DOM_UNDEF;
}

const char *hl_pcdom_element_t_get_name(void *n)
{
    pcdom_element_t *elem = (pcdom_element_t *)n;
    const char *name = NULL;
    if (elem->node.type == PCDOM_NODE_TYPE_TEXT) {
        name = "TEXT";
    }
    else {
        name = pcdom_element_tag_name(elem, NULL);
    }
    return name;
}

const char *hl_pcdom_element_t_get_id(void *n)
{
    pcdom_element_t *elem = (pcdom_element_t *)n;
    const char *id = pcdom_element_get_attribute(elem, ATTR_ID, strlen(ATTR_ID), NULL);
    return id;
}

#define WHITESPACE      " "
int hl_pcdom_element_t_get_classes(void *n, char ***classes)
{
    pcdom_element_t *elem = (pcdom_element_t *)n;
    *classes = NULL;
    const char *cls =  pcdom_element_get_attribute(elem, ATTR_CLASS,
            strlen(ATTR_CLASS), NULL);
    if (cls == NULL) {
        return 0;
    }
    int nr_classes = 0;
    char *value = strdup(cls);
    char *c = strtok(value, WHITESPACE);
    while (c != NULL) {
        nr_classes++;
        char **space = (char **)realloc(*classes, sizeof(char *) * nr_classes);
        if (space == NULL) {
            return nr_classes - 1;
        }
        *classes = space;
        (*classes)[nr_classes - 1] = strdup(c);
        c = strtok(NULL, WHITESPACE);
    }
    free(value);
    return nr_classes;
}

const char *hl_pcdom_element_t_get_attr(void *n, const char *name)
{
    pcdom_element_t *elem = (pcdom_element_t *)n;
    return pcdom_element_get_attribute(elem, name, strlen(name), NULL);
}

void hl_pcdom_element_t_set_parent(void *n, void *parent)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    node->parent = (pcdom_node_t *)parent;
}

void *hl_pcdom_element_t_get_parent(void *n)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    pcdom_node_t *parent = node->parent;
    if (parent && parent->type == PCDOM_NODE_TYPE_DOCUMENT) {
        return NULL;
    }
    return parent;
}

void *hl_pcdom_element_t_first_child(void *n)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    return node->first_child;
}

void *hl_pcdom_element_t_next(void *n)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    pcdom_node_t *next = pcdom_node_next(node);
    if (next && next->type == PCDOM_NODE_TYPE_UNDEF) {
        return NULL;
    }
    return next;
}

void *hl_pcdom_element_t_previous(void *n)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    return node->prev;
}

bool hl_pcdom_element_t_is_root(void *n)
{
    pcdom_node_t *node = (pcdom_node_t *)n;
    if (node->parent == NULL || node->parent->type == PCDOM_NODE_TYPE_DOCUMENT) {
        return true;
    }
    return false;
}

hidomlayout_node_op hl_pcdom_element_t_op = {
    .set_attach = hl_pcdom_element_t_set_attach,
    .get_attach = hl_pcdom_element_t_get_attach,
    .get_type = hl_pcdom_element_t_get_type,
    .get_name = hl_pcdom_element_t_get_name,
    .get_id = hl_pcdom_element_t_get_id,
    .get_classes = hl_pcdom_element_t_get_classes,
    .get_attr = hl_pcdom_element_t_get_attr,
    .set_parent = hl_pcdom_element_t_set_parent,
    .get_parent = hl_pcdom_element_t_get_parent,
    .first_child = hl_pcdom_element_t_first_child,
    .next = hl_pcdom_element_t_next,
    .previous = hl_pcdom_element_t_previous,
    .is_root = hl_pcdom_element_t_is_root
};

hidomlayout_node_op *hl_pcdom_element_t_get_op()
{
    return &hl_pcdom_element_t_op;
}


