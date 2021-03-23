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


#include "layout.h"
#include <stdio.h>


int calcNodeWidthHeight(HLDomElementNode *node, int containerWidth, int containerHeight, int childWidth, int childHeight)
{
    node->boxValues.w = 10 + childWidth;
    node->boxValues.h = 10 + childHeight;
    return 0;
}

int layout_node(HLDomElementNode *node, int x, int y, int widthLimit, int heightLimit, int *width, int *height, int level)
{
    for (int i = 0; i < level; i++)
    {
        fprintf(stderr, "    ");
    }

    fprintf(stderr, "node|tag=%s|id=%s\n", node->tag, node->attr[HL_ATTR_NAME_ID]);
    if (node == NULL)
    {
        return 0;
    }

    node->boxValues.x = x;
    node->boxValues.y = y;

    int childWidth = 0;
    int childHeight = 0;
    if (node->first_child)
    {
        switch (node->layout_type)
        {
            case LAYOUT_BLOCK:
                layout_child_node_block(node, x, y, widthLimit, heightLimit, &childWidth, &childHeight, level);
                break;

            case LAYOUT_INLINE_BLOCK:
                layout_child_node_inline_block(node, x, y, widthLimit, heightLimit, &childWidth, &childHeight, level);
                break;

            default:
                layout_child_node_block(node, x, y, widthLimit, heightLimit, &childWidth, &childHeight, level);
                break;
        }
    }

    calcNodeWidthHeight(node, widthLimit, heightLimit, childWidth, childHeight);
    *width = node->boxValues.w;
    *height = node->boxValues.h;
    for (int i = 0; i < level; i++)
    {
        fprintf(stderr, "    ");
    }
    fprintf(stderr, "node|tag=%s|id=%s|(%f, %f, %f, %f)\n", node->tag, node->attr[HL_ATTR_NAME_ID], node->boxValues.x, node->boxValues.y, node->boxValues.w, node->boxValues.h);
    return 0;
}
