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


#include <hilayout.h>

#include <libcss/libcss.h>

typedef struct HLCSS_ {
    css_stylesheet* sheet;
    int done;
} HLCSS;

css_error resolve_url(void *pw, const char *base, lwc_string *rel, lwc_string **abs);

css_stylesheet *create_css_stylesheet(const char *charset, const char *url, bool allow_quirks, bool inline_style)
{
    css_stylesheet_params params;
    css_stylesheet *sheet;
    css_error error;

    params.params_version = CSS_STYLESHEET_PARAMS_VERSION_1;
    params.level = CSS_LEVEL_DEFAULT;
    params.charset = charset;
    params.url = url;
    params.title = NULL;
    params.allow_quirks = allow_quirks;
    params.inline_style = inline_style;
    params.resolve = resolve_url;
    params.resolve_pw = NULL;
    params.import = NULL;
    params.import_pw = NULL;
    params.color = NULL;
    params.color_pw = NULL;
    params.font = NULL;
    params.font_pw = NULL;

    error = css_stylesheet_create(&params, &sheet);
    if (error != CSS_OK) {
        fprintf(stderr, "Failed creating sheet: %d\n", error);
        return NULL;
    }

    return sheet;
}

HLCSS* hilayout_css_create(void)
{
    char url[] = "hilayout_css_select";
    char charset[] = "UTF-8";

    css_stylesheet *sheet = create_css_stylesheet(charset, url, true, false);
    if (sheet == NULL)
    {
        return NULL;
    }

    HLCSS* css = (HLCSS*)malloc(sizeof(HLCSS));
    css->sheet = sheet;
    css->done = 0;
    return css;
}

int hilayout_css_append_data(HLCSS* css, const char* data, size_t len)
{
    if (css == NULL || data == NULL || len <= 0)
    {
        return HILAYOUT_BADPARM;
    }

    css_error error = css_stylesheet_append_data(css->sheet, data, len);
    if (error != CSS_OK && error != CSS_NEEDDATA) {
        fprintf(stderr, "failed appending data: %d\n", error);
        return error;
    }

    return HILAYOUT_OK;
}

int hilayout_css_destroy(HLCSS* css)
{
    if (css == NULL)
        return HILAYOUT_OK;

    if (css->sheet)
        css_stylesheet_destroy(css->sheet);

    free(css);
}
