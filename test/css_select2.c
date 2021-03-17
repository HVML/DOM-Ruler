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

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <libcss/libcss.h>
#include "node.h"
#include "select.h"
/*
 
   <div id="root">
        <div id="title">this is title</div>
        <div id="description">this is description</div>
        <div id="page">
            <hijs></hijs>
            <hijs></hijs>
            <hiweb></hiweb>
            <hiweb></hiweb>
        </div>
        <div id="indicator">...</div>
   </div>


 */
 
#define FPCT_OF_INT_TOINT(a, b) (FIXTOINT(FDIV((a * b), F_100)))

int main(int argc, char **argv)
{
	css_error code;
	css_stylesheet *sheet;
	size_t size;
	const char data[] = "h1 { color: red } "
        "#root { display: block; } "
        "#title { position: relative; width: 100%; height: 20%; color: #123; } "
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

    sheet = createStylesheet(data, strlen(data), "UTF-8", "css_select", true, false);


    DomNode* root = createDomNode("div", NULL, DOM_ELEMENT_NODE, "root", NULL, 0, NULL, NULL);
    DomNode* title = createDomNode("div", NULL, DOM_ELEMENT_NODE, "title", NULL, 0, NULL, NULL);
    DomNode* description = createDomNode("div", NULL, DOM_ELEMENT_NODE, "description", NULL, 0, NULL, NULL);
    DomNode* page = createDomNode("div",  NULL, DOM_ELEMENT_NODE, "page", NULL, 0, NULL, NULL);
    DomNode* indicator = createDomNode("div",  NULL, DOM_ELEMENT_NODE, "indicator", NULL, 0, NULL, NULL);

    DomNode* hiweb = createDomNode("hiweb", NULL, DOM_ELEMENT_NODE, NULL, NULL, 0, NULL, NULL);
    DomNode* hijs = createDomNode("hijs", NULL, DOM_ELEMENT_NODE, NULL, NULL, 0, NULL, NULL);

    // node tree
    attachDomNode(title, root, NULL, NULL);
    attachDomNode(description, root, title, NULL);
    attachDomNode(page, root, description, NULL);
    attachDomNode(indicator, root, page, NULL);
    attachDomNode(hiweb, page, NULL, NULL);
    attachDomNode(hijs, page, hiweb, NULL);

    css_select_results *style;
    uint8_t color_type;
    css_color color_shade;
    css_unit unit = CSS_UNIT_PX;
    css_fixed len = 0;
    uint8_t val;

    DomNode* nodeSelect = title;
    style = selectStyle(sheet, nodeSelect, &media, NULL, NULL);
    color_type = css_computed_color( style->styles[CSS_PSEUDO_ELEMENT_NONE], &color_shade);
    fprintf(stderr, "####################\n");
    fprintf(stderr, "name=%s|id=%s|color=%x\n", nodeSelect->name, nodeSelect->id, color_shade);

    int position = css_computed_position(style->styles[CSS_PSEUDO_ELEMENT_NONE]);
    fprintf(stderr, "name=%s|id=%s|position=%d\n", nodeSelect->name, nodeSelect->id, position);

    val = css_computed_width(style->styles[CSS_PSEUDO_ELEMENT_NONE], &len, &unit);
    fprintf(stderr, "name=%s|id=%s|len=%d|unit=%d\n", nodeSelect->name, nodeSelect->id, len, unit);
    switch (val) {
    case CSS_WIDTH_INHERIT:
        fprintf(stderr, "name=%s|id=%s|width=inherit\n", nodeSelect->name, nodeSelect->id);
        break;
    case CSS_WIDTH_AUTO:
        fprintf(stderr, "name=%s|id=%s|width=auto\n", nodeSelect->name, nodeSelect->id);
        break;
    case CSS_WIDTH_SET:
        {
            int width = 0;
            if (unit == CSS_UNIT_PCT)
            {
                width = FPCT_OF_INT_TOINT(len, 1080);
            }
            else
            {
                width = FIXTOINT(css_len2px(len, unit, style->styles[CSS_PSEUDO_ELEMENT_NONE]));
            }

            fprintf(stderr, "name=%s|id=%s|len=%d|width=%d\n", nodeSelect->name, nodeSelect->id, len, width);
        }
        break;
    default:
        break;
    }


    destroySelectResult(style);

    fprintf(stderr, "###################\n");
    nodeSelect = title;
    style = selectStyle(sheet, nodeSelect, &media, NULL, NULL);
    color_type = css_computed_color( style->styles[CSS_PSEUDO_ELEMENT_NONE], &color_shade);
    fprintf(stderr, "name=%s|id=%s|color=%x\n", nodeSelect->name, nodeSelect->id, color_shade);
    destroySelectResult(style);



    destroyStylesheet(sheet);

	return 0;
}

