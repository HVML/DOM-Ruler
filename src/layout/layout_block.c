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

int layout_block_child_node(DomNode *node, int y, int *cy, int level)
{
    if (node == NULL)
        return 0;

    level++;
    fprintf(stderr, "layout_block_node|    %d     |name=%s|id=%s\n", level, node->name, node->id);
    int height = 0;
    DomNode* child = node->firstChild;
    if (child)
    {
        while(child)
        {
            int ch = layout_block_child_node(child, 0, cy, level);
            height += ch;
            child = child->next;
        }
        node->height = height;
    }
    else
    {
        height = 10;
        node->height = height;
    }
    fprintf(stderr, "layout_block_node|    %d     |name=%s|id=%s|height=%d\n", level, node->name, node->id, height);
    return height;
}

bool layout_block(DomNode *node, int w, int h)
{
    if (node == NULL)
        return true;

    int level = 0;
    int cy = 0;
    int height = layout_block_child_node(node, 0, &cy, level);
    return false;
}

int layout_child_node_block(DomNode *node, int x, int y, int widthLimit, int heightLimit, int *width, int *height, int level)
{
    level++;
  //  fprintf(stderr, "............................%s...............begin|name=%s|id=%s\n", __func__, node->name, node->id);
    if (node == NULL || node->firstChild == NULL)
    {
 //       fprintf(stderr, "............................%s...............end|name=%s|id=%s\n", __func__, node->name, node->id);
        return 0;
    }

    int cx = x;
    int cy = y;
    int tw = 0;
    int th = 0;

    DomNode* child = node->firstChild;
    while(child)
    {
        layout_node(child, cx, cy, widthLimit, heightLimit, &tw, &th, level);
        cy = cy + th;
        *width = *width > tw ? *width : tw;
        *height += th;

        child = child->next;
    }

//    fprintf(stderr, "............................%s...............end|name=%s|id=%s|retW=%d|retH=%d\n", __func__, node->name, node->id, *width, *height);
    return 0;
}

