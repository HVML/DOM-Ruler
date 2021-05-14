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
    GNU Lesser General License version 3 (LLGPLv3). If you cannot accept
    LLGPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <libcss/libcss.h>
#include "node.h"
#include "select.h"
#include "layout.h"
#include "hidomlayout.h"
/*
 
   <div id="root">
        <div id="title">this is title</div>
        <div id="description">this is description</div>
        <div id="page">
            <hiweb></hiweb>
            <hijs></hijs>
        </div>
        <div id="indicator">...</div>
   </div>


 */
 
#define FPCT_OF_INT_TOINT(a, b) (FIXTOINT(FDIV((a * b), F_100)))

int main(int argc, char **argv)
{
	css_error code;
	size_t size;
	const char data[] = "h1 { color: red } "
        "#root { display: block; } "
        "#title { position: relative; left:20%; width: 100%; height: 20%; color: #123; } "
        "#description { position: relative; width: 100%; height: 10%; color: #124; } "
        "#page { position: relative; width: 100%; height: 60%; color: #125; } "
        "#indicator { position: relative; width: 100%; height: 10%; color: #126; } "
        "hiweb { position: relative; width: 100%; height: 25%; color: #127; } "
        "hijs { position: relative; width: 100%; height: 50%; color: #128; }";
	css_select_ctx *select_ctx;
	uint32_t count;
	unsigned int hh;
	css_stylesheet_params params;
	css_media media = {
		.type = CSS_MEDIA_SCREEN,
	};

    HLCSS* css = hilayout_css_create();
    if (css == NULL)
    {
        HL_LOGE("create HLCSS failed.\n");
        return HILAYOUT_INVALID;
    }

    hilayout_css_append_data(css, data, strlen(data));


    HLDomElementNode* root = hilayout_element_node_create("div");
    hilayout_element_node_set_id(root,  "root");

    HLDomElementNode* title = hilayout_element_node_create("div");
    hilayout_element_node_set_id(title, "title");

    HLDomElementNode* description = hilayout_element_node_create("div");
    hilayout_element_node_set_id(description, "description");

    HLDomElementNode* page = hilayout_element_node_create("div");
    hilayout_element_node_set_id(page, "page");

    HLDomElementNode* indicator = hilayout_element_node_create("div");
    hilayout_element_node_set_id(indicator, "indicator");


    HLDomElementNode* hiweb = hilayout_element_node_create("hiweb");
    hilayout_element_node_set_id(hiweb, "hiweb");

    HLDomElementNode* hijs = hilayout_element_node_create("hijs");
    hilayout_element_node_set_id(hijs, "hijs");

    hilayout_element_node_append_as_last_child(title, root);
    hilayout_element_node_append_as_last_child(description, root);
    hilayout_element_node_append_as_last_child(page, root);
    hilayout_element_node_append_as_last_child(indicator, root);

    hilayout_element_node_append_as_last_child(hiweb, page);
    hilayout_element_node_append_as_last_child(hijs, page);

#if 1
    css_select_results *style;
    uint8_t color_type;
    css_color color_shade;
    css_unit unit = CSS_UNIT_PX;
    css_fixed len = 0;
    uint8_t val;

    HLDomElementNode* node_select = title;
    style = _hilayout_css_select_style(css, node_select, &media, NULL, NULL);
    color_type = css_computed_color( style->styles[CSS_PSEUDO_ELEMENT_NONE], &color_shade);
    HL_LOGD("################################\n");
    HL_LOGW("tag=%s|id=%s|color=%x\n", hilayout_element_node_get_tag_name(node_select), hilayout_element_node_get_id(node_select), color_shade);

    int position = css_computed_position(style->styles[CSS_PSEUDO_ELEMENT_NONE]);
    HL_LOGW("tag=%s|id=%s|position=%d\n", hilayout_element_node_get_tag_name(node_select), hilayout_element_node_get_id(node_select ), position);

    val = css_computed_width(style->styles[CSS_PSEUDO_ELEMENT_NONE], &len, &unit);
    HL_LOGW("tag=%s|id=%s|len=%d|unit=%d\n", hilayout_element_node_get_tag_name(node_select), hilayout_element_node_get_id(node_select), len, unit);

    _hilayout_css_select_result_destroy(style);

    HL_LOGD("###################\n");
    node_select = title;
    style = _hilayout_css_select_style(css, node_select, &media, NULL, NULL);
    color_type = css_computed_color( style->styles[CSS_PSEUDO_ELEMENT_NONE], &color_shade);
    HL_LOGW("tag=%s|id=%s|color=%x\n", hilayout_element_node_get_tag_name(node_select), hilayout_element_node_get_id(node_select), color_shade);
    _hilayout_css_select_result_destroy(style);

    HLMedia hl_media = {
        .width = 1080,
        .height = 720,
        .dpi = 72,
        .density = 72
    };

    HL_LOGD("############################\n");
    hilayout_do_layout(&hl_media, css, root);

    hilayout_css_destroy(css);
#endif

	return 0;
}

