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

#define HL_INNER_CSS_SELECT_ATTACH "hl_inner_css_select_attach"
#define HL_INNER_LAYOUT_ATTACH "hl_inner_layout_attach"

typedef struct HiLayoutNode HiLayoutNode;

typedef struct HLDomElementNode_ {
    struct HLDomElementNode_* parent;  /**< Parent node */
    struct HLDomElementNode_* first_child; /**< First child node */
    struct HLDomElementNode_* last_child;  /**< Last child node */
    struct HLDomElementNode_* previous;    /**< Previous sibling */
    struct HLDomElementNode_* next;        /**< Next sibling */
    uint32_t n_children;        // child count;

    char* tag;

    GHashTable* common_attrs;  // common attrs key(uint64_t) -> value(string)

    GHashTable* general_attrs;     // user attrs key(string) -> value(string)
    GHashTable* user_data;     // user data key(string) -> value(HLAttachData)

    GHashTable* inner_attrs;    // inner attrs key(string) -> value(string)
    GHashTable* inner_data;     // inner data key(string) -> value(HLAttachData)

    HLAttachData* attach_data; // attach data


    // class name
    GList* class_list;

    // begin for hicss inner
    lwc_string* inner_tag;
    lwc_string* inner_id;
    lwc_string** inner_classes;
    int inner_classes_count;

    HLNodeType inner_dom_type;
    // end for hicss inner

    double min_w;
    double max_w;

    double min_h;
    double max_h;

    // begin layout attach
    HiLayoutNode *layout;
    cb_free_attach_data layout_free_cb;
    // end layout attch

} HLDomElementNode;

#ifdef __cplusplus
extern "C" {
#endif

bool hl_node_is_root(HLDomElementNode *n);
int hl_element_node_set_inner_attr(HLDomElementNode* node, const char* attr_name, const char* attr_value);
const char* hl_element_node_get_inner_attr(HLDomElementNode* node, const char* attr_name);
int hl_element_node_set_inner_data(HLDomElementNode* node, const char* key, void* data, HlDestroyCallback destroy_callback);
void* hl_element_node_get_inner_data(HLDomElementNode* node, const char* key);

// HLDomElelementNode op
void hl_dom_element_node_set_attach(void *node, void *data,
        cb_free_attach_data cb_free);
void *hl_dom_element_node_get_attach(void *node, cb_free_attach_data *cb_free);
HLNodeType hl_dom_element_node_get_type(void *node);
const char *hl_dom_element_node_get_name(void *node);
const char *hl_dom_element_node_get_id(void *node);
int hl_dom_element_node_get_classes(void *node, char ***classes);
const char *hl_dom_element_node_get_attr(void *node, const char *attr);
void hl_dom_element_node_set_parent(void *node, void *parent);
void *hl_dom_element_node_get_parent(void *node);
void *hl_dom_element_node_first_child(void *node);
void *hl_dom_element_node_next(void *node);
void *hl_dom_element_node_previous(void *node);
bool hl_dom_element_node_is_root(void *node);
// End HLDomElelementNode op

#ifdef __cplusplus
}
#endif

#endif // _HL_DOM_ELEMENT_NODE_H
