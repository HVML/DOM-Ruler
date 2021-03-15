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

#include <stdlib.h>
#include <string.h>


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
