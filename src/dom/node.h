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


#ifndef _NODE_H_
#define _NODE_H_

#include <libcss/libcss.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DOM_ELEMENT_NODE        = 1,
    DOM_ATTRIBUTE_NODE      = 2,
    DOM_TEXT_NODE           = 3,
    DOM_CDATA_SECTION_NODE      = 4,
    DOM_ENTITY_REFERENCE_NODE   = 5,
    DOM_ENTITY_NODE         = 6,
    DOM_PROCESSING_INSTRUCTION_NODE = 7,
    DOM_COMMENT_NODE        = 8,
    DOM_DOCUMENT_NODE       = 9,
    DOM_DOCUMENT_TYPE_NODE      = 10,
    DOM_DOCUMENT_FRAGMENT_NODE  = 11,
    DOM_NOTATION_NODE       = 12,

    /* And a count of the number of node types */
    DOM_NODE_TYPE_COUNT
} DomNodeType;

typedef enum {
    LAYOUT_BLOCK,
    LAYOUT_INLINE_CONTAINER,
    LAYOUT_INLINE,
    LAYOUT_TABLE,
    LAYOUT_TABLE_ROW,
    LAYOUT_TABLE_CELL,
    LAYOUT_TABLE_ROW_GROUP,
    LAYOUT_FLOAT_LEFT,
    LAYOUT_FLOAT_RIGHT,
    LAYOUT_INLINE_BLOCK,
    LAYOUT_BR,
    LAYOUT_TEXT,
    LAYOUT_INLINE_END,
    LAYOUT_NONE
} LayoutType;

typedef struct DomNode_ {
    struct DomNode_ *parent;  /**< Parent node */
    struct DomNode_ *firstChild; /**< First child node */
    struct DomNode_ *lastChild;  /**< Last child node */
    struct DomNode_ *previous;    /**< Previous sibling */
    struct DomNode_ *next;        /**< Next sibling */

    void *attach;

    char *name;
    lwc_string *lwcName;

    char *value;
    DomNodeType domType;

    char *id;
    lwc_string *lwcId;

    char **classes;
    lwc_string **lwcClasses;

    int classesCount;

    char *inlineStyle;

    char *runnerType;


    int x;
    int y;
    int width;
    int height;

    int marginLeft;
    int marginTop;
    int marginRight;
    int marginBottom;

    int paddingLeft;
    int paddingTop;
    int paddingRight;
    int paddingBottom;

    int borderLeftWidth;
    int borderTopWidth;
    int borderRightWidth;
    int borderBottomWidth;

    int minWidth;
    int maxWidth;

    LayoutType layoutType;

} DomNode;


DomNode* createDomNode(char* name, char* value, DomNodeType domType, 
        char *id, char **classes, int classesCount, char *inlineStyle, char *runnerType);
int attachDomNode(DomNode *node, DomNode *parent, DomNode *previous, DomNode *next);
int attachDomNodeRange(DomNode *first, DomNode *last, DomNode *parent, DomNode *previous, DomNode *next);
void destroyDomNode(DomNode *node);

#ifdef __cplusplus
}
#endif

#endif // _NODE_H_
