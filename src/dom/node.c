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

#define UNKNOWN_WIDTH INT_MAX
#define UNKNOWN_MAX_WIDTH INT_MAX
#define AUTO INT_MIN


char *HL_ATTR_NAME_ARRAY[HL_ATTR_NAME_COUNT] = {
    "name",
    "value",
    "id",
    "class",
    "style"
};


DomNode* createDomNode(char* name, char* value, DomNodeType domType, 
        char *id, char **classes, int classesCount, char *inlineStyle, char *runnerType)
{
    DomNode* result = (DomNode*)malloc(sizeof(DomNode));
    if (result == NULL)
    {
        return NULL;
    }

    if (name != NULL)
    {
        result->name = strdup(name);
        lwc_intern_string(result->name, strlen(result->name), &result->lwcName);
    }
    else
    {
        result->name = NULL;
        result->lwcName = NULL;
    }

    if (value != NULL)
        result->value = strdup(value);
    else
        result->value = NULL;

    result->domType = domType;

    if (id != NULL)
    {
        result->id = strdup(id);
        lwc_intern_string(result->id, strlen(result->id), &result->lwcId);
    }
    else
    {
        result->id = NULL;
        result->lwcId = NULL;
    }

    if (classesCount > 0 && classes != NULL)
    {
        char** resultClasses = (char**) malloc(sizeof(char*)*classesCount);
        result->lwcClasses = malloc(sizeof(lwc_string *) * classesCount);
        for (int i = 0; i < classesCount; i++)
        {
            resultClasses[i] = strdup(classes[i]);
            lwc_intern_string(resultClasses[i], strlen(resultClasses[i]), &result->lwcClasses[i]);
        }
        result->classes = resultClasses;
        result->classesCount = classesCount;
    }
    else
    {
        result->classes = NULL;
        result->lwcClasses = NULL;
        result->classesCount = 0;
    }

    if (inlineStyle != NULL)
        result->inlineStyle = strdup(inlineStyle);
    else
        result->inlineStyle = NULL;

    if (runnerType != NULL)
        result->runnerType = strdup(runnerType);
    else
        result->runnerType = NULL;

    result->attach = NULL;
    result->parent = NULL;
    result->firstChild = NULL;
    result->lastChild = NULL;
    result->previous = NULL;
    result->next = NULL;

    result->x = 0;
    result->y = 0;
    result->width = UNKNOWN_WIDTH;
    result->height = 0;

    result->marginLeft = 0;
    result->marginTop = 0;
    result->marginRight = 0;
    result->marginBottom = 0;

    result->paddingLeft = 0;
    result->paddingTop = 0;
    result->paddingRight = 0;
    result->paddingBottom = 0;

    result->borderLeftWidth = 0;
    result->borderTopWidth = 0;
    result->borderRightWidth = 0;
    result->borderBottomWidth = 0;

    result->minWidth = 0;
    result->maxWidth = UNKNOWN_MAX_WIDTH;

    result->layoutType = LAYOUT_INLINE;
    return result;
}

int attachDomNode(DomNode *node, DomNode *parent, DomNode *previous, DomNode *next)
{
    return attachDomNodeRange(node, node, parent, previous, next);
}

int attachDomNodeRange(DomNode *first, DomNode *last, DomNode *parent, DomNode *previous, DomNode *next)
{
    DomNode *n;

    first->previous = previous;
    last->next = next;

    if (previous != NULL)
        previous->next = first;
    else
        parent->firstChild = first;

    if (next != NULL)
        next->previous = last;
    else
        parent->lastChild = last;

    return 0;
}


void destroyDomNode(DomNode *node)
{
    if (node == NULL)
        return;

    if (node->name != NULL)
    {
        free(node->name);
        lwc_string_destroy(node->lwcName);
    }

    if (node->value != NULL)
        free(node->value);

    if (node->id != NULL)
    {
        free(node->id);
        lwc_string_destroy(node->lwcId);
    }

    if (node->classesCount > 0 && node->classes)
    {
        for (int i = 0; i < node->classesCount; i++)
        {
            free(node->classes[i]);
            lwc_string_destroy(node->lwcClasses[i]);
        }
        free(node->classes);
        free(node->lwcClasses);
    }

    if (node->inlineStyle != NULL)
        free(node->inlineStyle);

    if (node->runnerType != NULL)
        free(node->runnerType);

    free(node);
}

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
        lwc_string_destroy(str);
}

HLDomElementNode* hilayout_element_node_create(const char* tag)
{
    if (tag == NULL)
    {
        HL_LOGE("create HLDomElementNode failed. tag=%s\n", tag);
        return NULL;
    }

    HLDomElementNode* node = (HLDomElementNode*)malloc(sizeof(HLDomElementNode));
    if (node == NULL)
    {
        HL_LOGE("create HLDomElementNode failed. %d\n", HILAYOUT_NOMEM);
        return NULL;
    }

    memset(node, 0, sizeof(HLDomElementNode));
    node->tag = strdup(tag);
    node->inner_tag = _hilayout_lwc_string_dup(tag);

    return node;
}

const char* hilayout_element_node_get_tag_name(HLDomElementNode* node)
{
    return node ? node->tag : NULL;
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

int hilayout_element_node_set_attr(HLDomElementNode* node, const char* name, const char* value)
{
    if (node == NULL || name == NULL)
    {
        HL_LOGE("set element attr|node=%p|name=%s|value=%s|param error\n", node, name, value);
        return HILAYOUT_BADPARM;
    }

    int index = -1;
    for (int i = 0; i < HL_ATTR_NAME_COUNT; i++) 
    {
        if (strcasecmp(name, HL_ATTR_NAME_ARRAY[i]) == 0)
        {
            index = i;
            break;
        }
    }

    if (index >= 0)
    {
        if (node->attr[index] != NULL)
        {
            free(node->attr[index]);
        }
        if (value)
        {
            node->attr[index] = strdup(value);
            switch (index)
            {
                case HL_ATTR_NAME_ID:
                    node->inner_id = _hilayout_lwc_string_dup(value);
                    break;

                case HL_ATTR_NAME_CLASSES:
                    _hilayout_fill_inner_classes(node, value);
                    break;
            }
        }
        else
        {
            node->attr[index] = NULL;
        }
        return HILAYOUT_OK;
    }
    HL_LOGE("set element attr|node=%p|name=%s|value=%s|not support\n", node, name, value);
    return HILAYOUT_NOT_SUPPORT;
}

const char* hilayout_element_node_get_attr(HLDomElementNode* node, const char* name)
{
    if (node == NULL || name == NULL)
    {
        HL_LOGE("get element attr|node=%p|name=%s|param error\n", node, name);
        return NULL;
    }

    int index = -1;
    for (int i = 0; i < HL_ATTR_NAME_COUNT; i++) 
    {
        if (strcasecmp(name, HL_ATTR_NAME_ARRAY[i]) == 0)
        {
            index = i;
            break;
        }
    }

    return index >= 0 ? node->attr[index] : NULL;
}

int hilayout_element_node_set_private_data(HLDomElementNode* node, void* data)
{
    if (node)
        node->private_data = data;
}

void* hilayout_element_node_get_private_data(HLDomElementNode* node)
{
    return node ? node->private_data : NULL;
}

int hilayout_element_node_set_content(HLDomElementNode* node, const char* content)
{
    if (node == NULL)
    {
        HL_LOGE("set content|node=%p|content=%s|param error\n", node, content);
        return HILAYOUT_BADPARM;
    }

    if (node->content)
    {
        free(node->content);
    }
    node->content = strdup(content);
    return HILAYOUT_OK;
}

const char* hilayout_element_node_get_content(HLDomElementNode* node)
{
    return node ? node->content : NULL;
}

void hilayout_element_node_destroy(HLDomElementNode *node, HILAYOUT_ELEMENT_NODE_DESTROY_CALLBACK callback)
{
    if (node == NULL)
        return;

    if (node->tag)
    {
        free(node->tag);
    }

    for (int i = 0; i < HL_ATTR_NAME_COUNT; i++)
    {
        if (node->attr[i])
            free(node->attr[i]);
    }

    if (node->content)
    {
        free(node->content);
    }

    if (node->private_data && callback)
    {
        callback(node->private_data);
    }

    _hilayout_lwc_string_destroy(node->inner_tag);
    _hilayout_lwc_string_destroy(node->inner_id);

    for (int i = 0; i < node->inner_classes_count; i++)
    {
        _hilayout_lwc_string_destroy(node->inner_classes[i]);
    }

    if (node->textValues.family)
    {
        free(node->textValues.family);
    }
}

const HLUsedBoxValues* hilayout_element_node_get_used_box_value(HLDomElementNode* node)
{
    return node ? & node->boxValues : NULL;
}

const HLUsedBackgroundValues* hilayout_element_node_get_used_background_value(HLDomElementNode* node)
{
    return node ? & node->backgroundValues : NULL;
}

const HLUsedTextValues* hilayout_element_node_get_used_font_value(HLDomElementNode* node)
{
    return node ? & node->textValues : NULL;
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
        HL_LOGD("curr|tag=%s|name=%s\n", node->tag, node->attr[HL_ATTR_NAME_NAME]);
        HL_LOGD("parent->first_child|tag=%s|name=%s\n", parent->first_child->tag, parent->first_child->attr[HL_ATTR_NAME_NAME]);
        HL_LOGD("parent->last_child|tag=%s|name=%s\n", parent->last_child->tag, parent->last_child->attr[HL_ATTR_NAME_NAME]);
        return HILAYOUT_OK;
    }

    HLDomElementNode* last = parent->last_child;
    last->next = node;
    parent->last_child = node;

    node->previous = last;
    node->next = NULL;

    HL_LOGD("curr|tag=%s|name=%s\n", node->tag, node->attr[HL_ATTR_NAME_NAME]);
    HL_LOGD("parent->first_child|tag=%s|name=%s\n", parent->first_child->tag, parent->first_child->attr[HL_ATTR_NAME_NAME]);
    HL_LOGD("parent->last_child|tag=%s|name=%s\n", parent->last_child->tag, parent->last_child->attr[HL_ATTR_NAME_NAME]);

    return HILAYOUT_OK;
}
