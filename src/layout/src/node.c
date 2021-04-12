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

    This file is part of HybridOS, a developing operating system based on
    MiniGUI. HybridOs will support embedded systems and smart IoT devices.

    Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.

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

void hilayout_element_node_set_id(HLDomElementNode* node, const char* value)
{
    if (node == NULL)
    {
        return;
    }

    if (node->id)
    {
        free(node->id);
        _hilayout_lwc_string_destroy(node->inner_id);
    }
    node->id = strdup(value);
    node->inner_id = _hilayout_lwc_string_dup(value);
}

const char* hilayout_element_node_get_id(HLDomElementNode* node)
{
    return node ? node->id : NULL;
}

static const char _HILAYOUT_WHITESPACE[] = " ";
void _hilayout_fill_inner_classes(HLDomElementNode* node, const char* classes)
{
    if (node == NULL || classes == NULL || strlen(classes) == 0)
    {
        node->inner_classes_count = 0;
        return;
    }
    char* value = strdup(classes);
    char* c = strtok(value, _HILAYOUT_WHITESPACE);
    while (c != NULL) {
        node->inner_classes[node->inner_classes_count]= _hilayout_lwc_string_dup(c);
        node->inner_classes_count++;
        c = strtok(NULL, _HILAYOUT_WHITESPACE);
    }
    free(value);
}


void hilayout_element_node_set_class_name(HLDomElementNode* node, const char* value)
{
    if (node == NULL)
    {
        return;
    }

    if (node->class_name)
    {
        free(node->class_name);
        for (int i = 0; i < node->inner_classes_count; i++)
        {
            _hilayout_lwc_string_destroy(node->inner_classes[i]);
        }
    }
    node->class_name = strdup(value);
    _hilayout_fill_inner_classes(node, value);
}

const char* hilayout_element_node_get_class_name(HLDomElementNode* node)
{
    return node ? node->class_name : NULL;
}

void hilayout_element_node_set_style(HLDomElementNode* node, const char* value)
{
    if (node == NULL)
    {
        return;
    }

    if (node->style)
    {
        free(node->style);
    }
    node->style = strdup(value);
}

const char* hilayout_element_node_get_style(HLDomElementNode* node)
{
    return node ? node->style : NULL;
}

void hilayout_element_node_destroy(HLDomElementNode *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->node_name)
    {
        free(node->node_name);
    }

    if (node->node_value)
    {
        free(node->node_value);
    }

    if (node->tag)
    {
        free(node->tag);
    }

    if (node->id)
    {
        free(node->id);
    }

    if (node->class_name)
    {
        free(node->class_name);
    }

    if (node->style)
    {
        free(node->style);
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

    _hilayout_lwc_string_destroy(node->inner_tag);
    _hilayout_lwc_string_destroy(node->inner_id);

    for (int i = 0; i < node->inner_classes_count; i++)
    {
        _hilayout_lwc_string_destroy(node->inner_classes[i]);
    }

    if (node->text_values.family)
    {
        free(node->text_values.family);
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


int hilayout_element_node_append_as_last_child(HLDomElementNode* node, HLDomElementNode* parent)
{
    if (node == NULL || parent == NULL)
    {
        HL_LOGE("append as last child|node=%p|parent=%p|param error\n", node, parent);
        return HILAYOUT_BADPARM;
    }


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

void _hl_destory_common_attr_value (gpointer data)
{
    free(data);
}

int _hl_verify_common_attr_id(HLDomElementNode* node, HLCommonAttribute attr_id)
{
    return HILAYOUT_OK;
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

    return g_hash_table_insert(node->common_attrs, (gpointer)attr_id, (gpointer)strdup(attr_value));
}

const char* hilayout_element_node_get_common_attr (HLDomElementNode* node, HLCommonAttribute attr_id)
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

const char* hilayout_element_node_get_general_attr(HLDomElementNode* node, const char* attr_name)
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

void* hilayout_element_node_get_user_data(HLDomElementNode* node, const char* key)
{
    if (node == NULL || key == NULL)
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

