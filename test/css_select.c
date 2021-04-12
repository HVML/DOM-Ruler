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

int main(int argc, char **argv)
{
	css_error code;
	size_t size;
	const char data[] = "h1 { color: red } "
		"h4 { color: #321; } "
		"h4, h5 { color: #123456; }";
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

	/* select style for each of h1 to h6 */
	for (hh = 1; hh != 7; hh++) {
		css_select_results *style;
		uint8_t color_type;
		css_color color_shade;


        HLDomElementNode* domNode = hilayout_element_node_create("h1");
        style = _hilayout_css_select_style(css, domNode, &media, NULL, NULL);

		color_type = css_computed_color(
				style->styles[CSS_PSEUDO_ELEMENT_NONE],
				&color_shade);
		if (color_type == CSS_COLOR_INHERIT)
			HL_LOGW("color of h%i is 'inherit'\n", hh);
		else
			HL_LOGW("color of h%i is %x\n", hh, color_shade);

        _hilayout_css_select_result_destroy(style);
        hilayout_element_node_destroy(domNode);
	}


    hilayout_css_destroy(css);

	return 0;
}

