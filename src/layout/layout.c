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


bool layout_page(DomNode *page, int width, int height)
{
    if (page == NULL)
    {
        return false;
    }
    switch (page->layoutType)
    {
        case LAYOUT_BLOCK:
            return layout_block(page, width, height);

        case LAYOUT_INLINE_BLOCK:
            return layout_inline_block(page, width, height);
    }
    return layout_block(page, width, height);
}

int calcNodeWidthHeight(DomNode *node, int containerWidth, int containerHeight, int childWidth, int childHeight)
{
    node->width = 10 + childWidth;
    node->height = 10 + childHeight;
    return 0;
}

int layout_node(DomNode *node, int x, int y, int widthLimit, int heightLimit, int *width, int *height)
{
    if (node == NULL)
    {
        return 0;
    }

    node->x = x;
    node->y = y;

    int childWidth = 0;
    int childHeight = 0;
    if (node->firstChild)
    {
        switch (node->layoutType)
        {
            case LAYOUT_BLOCK:
                layout_child_node_block(node, x, y, widthLimit, heightLimit, &childWidth, &childHeight);
                break;

            case LAYOUT_INLINE_BLOCK:
                layout_child_node_inline_block(node, x, y, widthLimit, heightLimit, &childWidth, &childHeight);
                break;

            default:
                layout_child_node_block(node, x, y, widthLimit, heightLimit, &childWidth, &childHeight);
                break;
        }
    }

    calcNodeWidthHeight(node, widthLimit, heightLimit, childWidth, childHeight);
    *width = node->width;
    *height = node->height;
    fprintf(stderr, "............................%s...............node|name=%s|id=%s|(%d, %d, %d, %d)\n", __func__, node->name, node->id, node->x, node->y, node->width, node->height);
    return 0;
}
