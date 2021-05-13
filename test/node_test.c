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

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "hidomlayout.h"

int main(int argc, char **argv)
{

    HLDomElementNode* root = hilayout_element_node_create("div");

    // test get tag name
    const char* tag_name = hilayout_element_node_get_tag_name(root);
    HL_LOGW("test|get tag name|tag=%s\n", tag_name);

    // test set attribute
    hilayout_element_node_set_id(root, "idAttribute");
    hilayout_element_node_set_class(root, "classA classB classC");
    hilayout_element_node_set_style(root, "color=#33333; width=10px;");


    // test get attribute
    const char* value = hilayout_element_node_get_id(root);
    HL_LOGW("test|get attribute|attr=id|value=%s\n", value);

    value = hilayout_element_node_get_class(root);
    HL_LOGW("test|get attribute|attr=class|value=%s\n", value);

    value = hilayout_element_node_get_style(root);
    HL_LOGW("test|get attribute|attr=style|value=%s\n", value);

    // output test
    const HLUsedBoxValues* box = hilayout_element_node_get_used_box_value(root);
    HL_LOGW("test|get box value|ret=%p\n", box);

    const HLUsedBackgroundValues* bg = hilayout_element_node_get_used_background_value(root);
    HL_LOGW("test|get bg value|ret=%p\n", bg);

    const HLUsedTextValues* text = hilayout_element_node_get_used_text_value(root);
    HL_LOGW("test|get text value|ret=%p\n", text);

    // test append as last child
    char name[20];
    int index = 0;
    for (index = 0; index < 10; index++)
    {
        HL_LOGW("\n");
        HL_LOGW("test|add node|index=%d\n", index);
        HLDomElementNode* div = hilayout_element_node_create("div");
        hilayout_element_node_append_as_last_child(div, root);
    }


    hilayout_element_node_destroy(root);
	return 0;
}

