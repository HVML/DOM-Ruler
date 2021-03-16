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
 
   <root>
        <title>this is title</title>
        <description>this is description</description>
        <page>
            <hijs></hijs>
            <hijs></hijs>
            <hiweb></hiweb>
            <hiweb></hiweb>
        </page>
        <indicator>...</indicator>
   </root>


 */
 
int main(int argc, char **argv)
{
	css_error code;
	css_stylesheet *sheet;
	size_t size;
	const char data[] = "h1 { color: red } "
		"hiweb { color: #321; } "
		"hijs { color: #123456; }";
	css_select_ctx *select_ctx;
	uint32_t count;
	unsigned int hh;
	css_stylesheet_params params;
	css_media media = {
		.type = CSS_MEDIA_SCREEN,
	};

    sheet = createStylesheet(data, strlen(data), "UTF-8", "css_select", true, false);


    DomNode* root = createDomNode("root", NULL, DOM_ELEMENT_NODE, NULL, NULL, 0, NULL, NULL);
    DomNode* title = createDomNode("title", NULL, DOM_ELEMENT_NODE, NULL, NULL, 0, NULL, NULL);
    DomNode* description = createDomNode("description", NULL, DOM_ELEMENT_NODE, NULL, NULL, 0, NULL, NULL);
    DomNode* page = createDomNode("page", NULL, DOM_ELEMENT_NODE, NULL, NULL, 0, NULL, NULL);
    DomNode* indicator = createDomNode("indicator", NULL, DOM_ELEMENT_NODE, NULL, NULL, 0, NULL, NULL);

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

    style = selectStyle(sheet, hiweb, &media, NULL, NULL);
    color_type = css_computed_color( style->styles[CSS_PSEUDO_ELEMENT_NONE], &color_shade);
    printf("color of %s is %x\n", hiweb->name, color_shade);
    destroySelectResult(style);

    style = selectStyle(sheet, hijs, &media, NULL, NULL);
    color_type = css_computed_color( style->styles[CSS_PSEUDO_ELEMENT_NONE], &color_shade);
    printf("color of %s is %x\n", hijs->name, color_shade);
    destroySelectResult(style);


    destroyStylesheet(sheet);

	return 0;
}

