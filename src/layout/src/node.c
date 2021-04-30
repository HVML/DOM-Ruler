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
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/ghash.h>

#define UNKNOWN_WIDTH INT_MAX
#define UNKNOWN_MAX_WIDTH INT_MAX
#define UNKNOWN_MAX_HEIGHT INT_MAX
#define AUTO INT_MIN


lwc_string* _hilayout_lwc_string_dup(const char* str)
{
    if (str == NULL)
    {
        return NULL;
    }

    lwc_string* result = NULL;
    lwc_intern_string(str, strlen(str), &result);
    return result;
}

void _hilayout_lwc_string_destroy(lwc_string* str)
{
    if (str)
        lwc_string_unref(str);
}

HLDomElementNode* hilayout_element_node_create(const char* tag)
{
    if (tag == NULL)
    {
        HL_LOGE("create HLDomElementNode failed. tag=%s\n", tag);
        return NULL;
    }

    HLDomElementNode* node = (HLDomElementNode*)calloc(1, sizeof(HLDomElementNode));
    if (node == NULL)
    {
        HL_LOGE("create HLDomElementNode failed. %d\n", HILAYOUT_NOMEM);
        return NULL;
    }

    node->tag = strdup(tag);
    node->inner_tag = _hilayout_lwc_string_dup(tag);

    node->box_values.w = UNKNOWN_WIDTH;
    node->box_values.display = HL_DISPLAY_BLOCK;
    node->box_values.position = HL_POSITION_RELATIVE;
    node->box_values.visibility = HL_VISIBILITY_VISIBLE;
    node->box_values.opacity = 1.0f;

    node->min_w = 0;
    node->max_w = UNKNOWN_MAX_WIDTH;

    node->min_h = 0;
    node->max_h = UNKNOWN_MAX_HEIGHT;

    return node;
}

const char* hilayout_element_node_get_tag_name(HLDomElementNode* node)
{
    return node ? node->tag : NULL;
}

void _hl_destory_class_list_item (gpointer data)
{
    free(data);
}

static const char _HILAYOUT_WHITESPACE[] = " ";
void _hilayout_fill_inner_classes(HLDomElementNode* node, const char* classes)
{
    if (node == NULL || classes == NULL || strlen(classes) == 0)
    {
        return;
    }

    if (node->inner_classes)
    {
        for (int i = 0; i < node->inner_classes_count; i++)
        {
            _hilayout_lwc_string_destroy(node->inner_classes[i]);
        }
        node->inner_classes_count = 0;
        free(node->inner_classes);
    }

    g_list_free_full(node->class_list, _hl_destory_class_list_item);
    node->class_list = NULL;
    
    char* value = strdup(classes);
    char* c = strtok(value, _HILAYOUT_WHITESPACE);
    while (c != NULL) {
        node->class_list = g_list_append(node->class_list, strdup(c));
        node->inner_classes_count++;
        c = strtok(NULL, _HILAYOUT_WHITESPACE);
    }
    free(value);

    node->inner_classes = (lwc_string**)calloc(node->inner_classes_count, sizeof(lwc_string*));
    int i = 0;
    for (GList* it = node->class_list; it; it = it->next)
    {
        node->inner_classes[i++]= _hilayout_lwc_string_dup((const char*)it->data);
    }
}

void hilayout_element_node_destroy(HLDomElementNode *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->tag)
    {
        free(node->tag);
    }

    if (node->common_attrs)
    {
        g_hash_table_destroy(node->common_attrs);
    }

    if (node->general_attrs)
    {
        g_hash_table_destroy(node->general_attrs);
    }

    if (node->user_data)
    {
        g_hash_table_destroy(node->user_data);
    }

    if (node->inner_attrs)
    {
        g_hash_table_destroy(node->inner_attrs);
    }

    if (node->inner_data)
    {
        g_hash_table_destroy(node->inner_data);
    }

    if (node->attach_data)
    {
        for (int i = 0; i < MAX_ATTACH_DATA_SIZE; i++)
        {
            HLAttachData* attach = node->attach_data + i;
            if (attach->data && attach->callback)
            {
                attach->callback(attach->data);
            }
        }
        free(node->attach_data);
    }

    if (node->class_list)
    {
        g_list_free_full(node->class_list, _hl_destory_class_list_item);
    }

    _hilayout_lwc_string_destroy(node->inner_tag);
    _hilayout_lwc_string_destroy(node->inner_id);

    if (node->inner_classes)
    {
        for (int i = 0; i < node->inner_classes_count; i++)
        {
            _hilayout_lwc_string_destroy(node->inner_classes[i]);
        }
        free(node->inner_classes);
    }

    if (node->text_values.font_family)
    {
        free(node->text_values.font_family);
    }

    if (node->select_styles)
    {
        css_select_results_destroy(node->select_styles);
    }
}

const HLUsedBoxValues* hilayout_element_node_get_used_box_value(HLDomElementNode* node)
{
    return node ? & node->box_values : NULL;
}

const HLUsedBackgroundValues* hilayout_element_node_get_used_background_value(HLDomElementNode* node)
{
    return node ? & node->background_values : NULL;
}

const HLUsedTextValues* hilayout_element_node_get_used_text_value(HLDomElementNode* node)
{
    return node ? & node->text_values : NULL;
}

const HLUsedSvgValues* hilayout_element_node_get_used_svg_value(HLDomElementNode* node)
{
    return NULL;
}

int hilayout_element_node_append_as_last_child(HLDomElementNode* node, HLDomElementNode* parent)
{
    if (node == NULL || parent == NULL)
    {
        HL_LOGE("append as last child|node=%p|parent=%p|param error\n", node, parent);
        return HILAYOUT_BADPARM;
    }


    parent->n_children++;
    node->parent = parent;
    if (parent->first_child == NULL)
    {
        parent->first_child = node;
        parent->last_child = node;
        node->previous = NULL;
        node->next = NULL;
        HL_LOGD("1|curr|tag=%s|id=%s\n", node->tag, node->id);
        HL_LOGD("1|parent->first_child|tag=%s|id=%s|name=%s\n", parent->first_child->tag, node->id, parent->first_child->name);
        HL_LOGD("1|parent->last_child|tag=%s|id=%s|name=%s\n", parent->last_child->tag, node->id, parent->last_child->name);
        return HILAYOUT_OK;
    }

    HLDomElementNode* last = parent->last_child;
    last->next = node;
    parent->last_child = node;

    node->previous = last;
    node->next = NULL;

    HL_LOGD("2|curr|tag=%s|id=%s\n", node->tag, node->id);
    HL_LOGD("2|parent->first_child|tag=%s|id=%s|name=%s\n", parent->first_child->tag, node->id, parent->first_child->name);
    HL_LOGD("2|parent->last_child|tag=%s|id=%s|name=%s\n", parent->last_child->tag, node->id, parent->last_child->name);

    return HILAYOUT_OK;
}

HLDomElementNode* hilayout_element_node_get_parent(HLDomElementNode* node)
{
    return node ? node->parent : NULL;
}

HLDomElementNode* hilayout_element_node_get_first_child(HLDomElementNode* node)
{
    return node ? node->first_child: NULL;
}

HLDomElementNode* hilayout_element_node_get_last_child(HLDomElementNode* node)
{
    return node ? node->last_child : NULL;
}

HLDomElementNode* hilayout_element_node_get_prev(HLDomElementNode* node)
{
    return node ? node->previous : NULL;
}

HLDomElementNode* hilayout_element_node_get_next(HLDomElementNode* node)
{
    return node ? node->next : NULL;
}

uint32_t hilayout_element_node_get_children_count(HLDomElementNode* node)
{
    return node ? node->n_children: 0;
}

void _hl_destory_common_attr_value (gpointer data)
{
    free(data);
}

int _hl_verify_common_attr_id(const HLDomElementNode* node, HLCommonAttribute attr_id)
{
    if (attr_id >= 0 && attr_id < HL_COMMON_ATTR_COUNT)
    {
        return HILAYOUT_OK;
    }
    return HILAYOUT_BADPARM;
}

int hilayout_element_node_set_common_attr(HLDomElementNode* node, HLCommonAttribute attr_id, const char* attr_value)
{
    if (node == NULL || attr_value == NULL)
    {
        return HILAYOUT_OK;
    }

    if (HILAYOUT_OK != _hl_verify_common_attr_id(node, attr_id))
    {
        return HILAYOUT_BADPARM;
    }
    
    if (node->common_attrs == NULL)
    {
        node->common_attrs = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, _hl_destory_common_attr_value);
    }

    switch (attr_id)
    {
        case HL_COMMON_ATTR_ID:
            {
                if (node->inner_id)
                {
                    _hilayout_lwc_string_destroy(node->inner_id);
                }
                node->inner_id = _hilayout_lwc_string_dup(attr_value);
            }
            break;

        case HL_COMMON_ATTR_CLASS_NAME:
            _hilayout_fill_inner_classes(node, attr_value);
            break;
    }

    return g_hash_table_insert(node->common_attrs, (gpointer)attr_id, (gpointer)strdup(attr_value));
}

const char* hilayout_element_node_get_common_attr (const HLDomElementNode* node, HLCommonAttribute attr_id)
{
    if (node == NULL || node->common_attrs == NULL)
    {
        return NULL;
    }

    if (HILAYOUT_OK != _hl_verify_common_attr_id(node, attr_id))
    {
        return NULL;
    }

    return g_hash_table_lookup(node->common_attrs, (gpointer)attr_id);
}


void _hl_destory_general_attr_key (gpointer data)
{
    free(data);
}

void _hl_destory_general_attr_value (gpointer data)
{
    free(data);
}

int hilayout_element_node_set_general_attr(HLDomElementNode* node, const char* attr_name, const char* attr_value)
{
    if (node == NULL || attr_name == NULL || attr_value == NULL)
    {
        return HILAYOUT_OK;
    }

    if (node->general_attrs == NULL)
    {
        node->general_attrs = g_hash_table_new_full(g_str_hash, g_str_equal, _hl_destory_general_attr_key, _hl_destory_general_attr_value);
    }

    return g_hash_table_insert(node->general_attrs, (gpointer)strdup(attr_name), (gpointer)strdup(attr_value));
}

const char* hilayout_element_node_get_general_attr(const HLDomElementNode* node, const char* attr_name)
{
    if (node == NULL || attr_name == NULL || node->general_attrs == NULL)
    {
        return NULL;
    }
    return g_hash_table_lookup(node->general_attrs, (gpointer)attr_name);
}

void _hl_destory_inner_attr_key (gpointer data)
{
    free(data);
}

void _hl_destory_inner_attr_value (gpointer data)
{
    free(data);
}

int _hl_element_node_set_inner_attr(HLDomElementNode* node, const char* attr_name, const char* attr_value)
{
    if (node == NULL || attr_name == NULL || attr_value == NULL)
    {
        return HILAYOUT_OK;
    }

    if (node->inner_attrs == NULL)
    {
        node->inner_attrs = g_hash_table_new_full(g_str_hash, g_str_equal, _hl_destory_inner_attr_key, _hl_destory_inner_attr_value);
    }

    return g_hash_table_insert(node->inner_attrs, (gpointer)strdup(attr_name), (gpointer)strdup(attr_value));
}

const char* _hl_element_node_get_inner_attr(HLDomElementNode* node, const char* attr_name)
{
    if (node == NULL || attr_name == NULL || node->inner_attrs == NULL)
    {
        return NULL;
    }
    return g_hash_table_lookup(node->inner_attrs, (gpointer)attr_name);
}

void _hl_destory_attach_data_key (gpointer data)
{
    free(data);
}

void _hl_destory_attach_data_value (gpointer data)
{
    HLAttachData* attach = (HLAttachData*)data;
    if (attach->callback)
    {
        attach->callback(attach->data);
    }
    free(attach);
}


int hilayout_element_node_set_user_data(HLDomElementNode* node, const char* key, void* data, HlDestroyCallback destroy_callback)
{
    if (node == NULL || key == NULL)
    {
        return HILAYOUT_OK;
    }

    if (node->user_data == NULL)
    {
        node->user_data = g_hash_table_new_full(g_str_hash, g_str_equal, _hl_destory_attach_data_key, _hl_destory_attach_data_value);
    }

    if (data == NULL)
    {
        return g_hash_table_remove(node->user_data, key);
    }

    HLAttachData* attach = (HLAttachData*)calloc(1, sizeof(HLAttachData));
    attach->data = data;
    attach->callback = destroy_callback;
    return g_hash_table_insert(node->user_data, (gpointer)strdup(key), (gpointer)attach);
}

void* hilayout_element_node_get_user_data(const HLDomElementNode* node, const char* key)
{
    if (node == NULL || key == NULL || node->user_data == NULL)
    {
        return NULL;
    }
    HLAttachData* attach = (HLAttachData*) g_hash_table_lookup(node->user_data, (gpointer)key);
    return attach ? attach->data : NULL;
}

int _hl_element_node_set_inner_data(HLDomElementNode* node, const char* key, void* data, HlDestroyCallback destroy_callback)
{
    if (node == NULL || key == NULL)
    {
        return HILAYOUT_OK;
    }

    if (node->inner_data == NULL)
    {
        node->inner_data = g_hash_table_new_full(g_str_hash, g_str_equal, _hl_destory_attach_data_key, _hl_destory_attach_data_value);
    }

    if (data == NULL)
    {
        return g_hash_table_remove(node->inner_data, key);
    }

    HLAttachData* attach = (HLAttachData*)calloc(1, sizeof(HLAttachData));
    attach->data = data;
    attach->callback = destroy_callback;
    return g_hash_table_insert(node->inner_data, (gpointer)strdup(key), (gpointer)attach);
}

void* _hl_element_node_get_inner_data(HLDomElementNode* node, const char* key)
{
    if (node == NULL || key == NULL)
    {
        return NULL;
    }
    HLAttachData* attach = (HLAttachData*) g_hash_table_lookup(node->inner_data, (gpointer)key);
    return attach ? attach->data : NULL;
}

gint _hl_comp_class_name (gconstpointer a, gconstpointer b)
{
    return strcmp((const char*)a, (const char*)b);
}

int hilayout_element_node_has_class (HLDomElementNode* node, const char* class_name)
{
    GList* ret = g_list_find_custom(node->class_list, class_name, _hl_comp_class_name);
    return ret ? 1 : 0;
}

int hilayout_element_node_include_class (HLDomElementNode* node, const char* class_name)
{
    if (node == NULL || class_name == NULL)
    {
        return HILAYOUT_BADPARM;
    }

    if (hilayout_element_node_has_class(node, class_name))
    {
        return 0;
    }

    const char* classes = hilayout_element_node_get_class (node);
    char* buf = (char*) malloc(strlen(classes) + strlen(class_name) + 2);
    strcpy(buf, classes);
    strcat(buf, _HILAYOUT_WHITESPACE);
    strcat(buf, class_name);
    hilayout_element_node_set_class(node, buf);
    free(buf);
    return 0;
}

int hilayout_element_node_exclude_class (HLDomElementNode* node, const char* class_name)
{
    GList* ret = g_list_find_custom(node->class_list, class_name, _hl_comp_class_name);
    if (!ret)
    {
        return 0;
    }

    const char* classes = hilayout_element_node_get_class (node);
    char* buf = (char*) malloc(strlen(classes) + 1);

    GList *it = NULL;
    for (it = node->class_list; it; it = it->next)
    {
        if (it == ret)
        {
            continue;
        }
        strcat(buf, (const char*)it->data);
        strcat(buf, _HILAYOUT_WHITESPACE);
    }
    hilayout_element_node_set_class(node, buf);
    free(buf);
}

bool _hl_node_is_root(HLDomElementNode *n)
{
    if (n == NULL)
    {
        return false;
    }

    HLDomElementNode *parent = n->parent;
    if (parent != NULL) 
    {
        return false;
    }
    return true;
}

void hilayout_element_node_for_each_child(HLDomElementNode* node, NodeCallback callback, void* user_data)
{
    if (node == NULL || callback == NULL)
    {
        return;
    }

    HLDomElementNode* child = node->first_child;
    while(child)
    {
        callback(child, user_data);
        child = child->next;
    }
}

void hilayout_element_node_depth_first_search_tree(HLDomElementNode* node, NodeCallback callback, void* user_data)
{
    if (node == NULL || callback == NULL)
    {
        return;
    }
    callback(node, user_data);

    HLDomElementNode* child = node->first_child;
    while(child)
    {
        hilayout_element_node_depth_first_search_tree(child, callback, user_data);
        child = child->next;
    }
}

const uint32_t MAX_ATTACH_DATA_SIZE = 10;
int hilayout_element_node_set_attach_data(HLDomElementNode* node, uint32_t index, void* data, HlDestroyCallback destroy_callback)
{
    if (node == NULL || index >= MAX_ATTACH_DATA_SIZE)
    {
        return HILAYOUT_BADPARM;
    }

    if (node->attach_data == NULL)
    {
        node->attach_data = (HLAttachData*)calloc(MAX_ATTACH_DATA_SIZE, sizeof(HLAttachData));
    }

    HLAttachData* attach = node->attach_data + index;
    if (attach->data != NULL && attach->callback != NULL)
    {
        attach->callback(attach->data);
    }

    attach->data = data;
    attach->callback = destroy_callback;
    return HILAYOUT_OK;
}

void* hilayout_element_node_get_attach_data(const HLDomElementNode* node, uint32_t index)
{
    if (node == NULL || index >= MAX_ATTACH_DATA_SIZE)
    {
        return NULL;
    }
    HLAttachData* attach = node->attach_data + index;
    return attach->data;
}

