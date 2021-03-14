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

#include "select.h"
#include <stdio.h>

#define UNUSED(x) ((x) = (x))
static css_error node_name(void *pw, void *node, css_qname *qname);
static css_error node_classes(void *pw, void *node,
		lwc_string ***classes, uint32_t *n_classes);
static css_error node_id(void *pw, void *node, lwc_string **id);
static css_error named_parent_node(void *pw, void *node,
		const css_qname *qname, void **parent);
static css_error named_sibling_node(void *pw, void *node,
		const css_qname *qname, void **sibling);
static css_error named_generic_sibling_node(void *pw, void *node,
		const css_qname *qname, void **sibling);
static css_error parent_node(void *pw, void *node, void **parent);
static css_error sibling_node(void *pw, void *node, void **sibling);
static css_error node_has_name(void *pw, void *node,
		const css_qname *qname, bool *match);
static css_error node_has_class(void *pw, void *node,
		lwc_string *name, bool *match);
static css_error node_has_id(void *pw, void *node,
		lwc_string *name, bool *match);
static css_error node_has_attribute(void *pw, void *node,
		const css_qname *qname, bool *match);
static css_error node_has_attribute_equal(void *pw, void *node,
		const css_qname *qname, lwc_string *value,
		bool *match);
static css_error node_has_attribute_dashmatch(void *pw, void *node,
		const css_qname *qname, lwc_string *value,
		bool *match);
static css_error node_has_attribute_includes(void *pw, void *node,
		const css_qname *qname, lwc_string *value,
		bool *match);
static css_error node_has_attribute_prefix(void *pw, void *node,
		const css_qname *qname, lwc_string *value,
		bool *match);
static css_error node_has_attribute_suffix(void *pw, void *node,
		const css_qname *qname, lwc_string *value,
		bool *match);
static css_error node_has_attribute_substring(void *pw, void *node,
		const css_qname *qname, lwc_string *value,
		bool *match);
static css_error node_is_root(void *pw, void *node, bool *match);
static css_error node_count_siblings(void *pw, void *node,
		bool same_name, bool after, int32_t *count);
static css_error node_is_empty(void *pw, void *node, bool *match);
static css_error node_is_link(void *pw, void *node, bool *match);
static css_error node_is_hover(void *pw, void *node, bool *match);
static css_error node_is_active(void *pw, void *node, bool *match);
static css_error node_is_focus(void *pw, void *node, bool *match);
static css_error node_is_enabled(void *pw, void *node, bool *match);
static css_error node_is_disabled(void *pw, void *node, bool *match);
static css_error node_is_checked(void *pw, void *node, bool *match);
static css_error node_is_target(void *pw, void *node, bool *match);
static css_error node_is_lang(void *pw, void *node,
		lwc_string *lang, bool *match);
static css_error ua_default_for_property(void *pw, uint32_t property,
		css_hint *hint);
static css_error set_libcss_node_data(void *pw, void *node,
		void *libcss_node_data);
static css_error get_libcss_node_data(void *pw, void *node,
		void **libcss_node_data);

css_error nscss_compute_font_size(void *pw, const css_hint *parent,
		css_hint *size)
{
    return CSS_OK;
}

css_error resolve_url(void *pw,
        const char *base, lwc_string *rel, lwc_string **abs)
{
    UNUSED(pw);
    UNUSED(base);

    /* About as useless as possible */
    *abs = lwc_string_ref(rel);

    return CSS_OK;
}

css_error named_ancestor_node(void *pw, void *node,
		const css_qname *qname, void **ancestor)
{
	return CSS_OK;
}

css_error node_is_visited(void *pw, void *node, bool *match)
{
	return CSS_OK;
}

css_error node_presentational_hint( void *pw, void *node, uint32_t *nhints, css_hint **hints)
{
	return CSS_OK;
}

static css_select_handler selection_handler = {
	CSS_SELECT_HANDLER_VERSION_1,

	node_name,
	node_classes,
	node_id,
	named_ancestor_node,
	named_parent_node,
	named_sibling_node,
	named_generic_sibling_node,
	parent_node,
	sibling_node,
	node_has_name,
	node_has_class,
	node_has_id,
	node_has_attribute,
	node_has_attribute_equal,
	node_has_attribute_dashmatch,
	node_has_attribute_includes,
	node_has_attribute_prefix,
	node_has_attribute_suffix,
	node_has_attribute_substring,
	node_is_root,
	node_count_siblings,
	node_is_empty,
	node_is_link,
	node_is_visited,
	node_is_hover,
	node_is_active,
	node_is_focus,
	node_is_enabled,
	node_is_disabled,
	node_is_checked,
	node_is_target,
	node_is_lang,
	node_presentational_hint,
	ua_default_for_property,
	nscss_compute_font_size,
	set_libcss_node_data,
	get_libcss_node_data
};

css_stylesheet *createStylesheet(const uint8_t *data, size_t len,
		const char *charset, const char *url, bool allow_quirks)
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
	params.inline_style = true;
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
		fprintf(stderr, "Failed creating sheet: %d", error);
		return NULL;
	}

	error = css_stylesheet_append_data(sheet, data, len);
	if (error != CSS_OK && error != CSS_NEEDDATA) {
		fprintf(stderr, "failed appending data: %d", error);
		css_stylesheet_destroy(sheet);
		return NULL;
	}

	error = css_stylesheet_data_done(sheet);
	if (error != CSS_OK) {
		fprintf(stderr, "failed completing parse: %d", error);
		css_stylesheet_destroy(sheet);
		return NULL;
	}

	return sheet;
}


int destroyStylesheet(css_stylesheet *style)
{
    return css_stylesheet_destroy(style);
}

css_select_results *selectStyle(const css_stylesheet *styleSheet, DomNode *n,
		const css_media *media, const css_stylesheet *inlineStyleSheet)
{
	css_computed_style *composed;
	css_select_results *styles;
	int pseudo_element;
	css_error error;
    css_error code;
    css_select_ctx *select_ctx;
    uint32_t count;

    code = css_select_ctx_create(&select_ctx);
    if (code != CSS_OK)
        fprintf(stderr, "css_select_ctx_create failed! code=%d", code);

    code = css_select_ctx_append_sheet(select_ctx, styleSheet, CSS_ORIGIN_AUTHOR, NULL);
    if (code != CSS_OK)
        fprintf(stderr, "css_select_ctx_append_sheet failed! code=%d", code);

    code = css_select_ctx_count_sheets(select_ctx, &count);
    if (code != CSS_OK)
        fprintf(stderr, "css_select_ctx_count_sheets failed! code=%d", code);

    printf("created selection context with %i sheets\n", count);

	/* Select style for node */
	error = css_select_style(select_ctx, n, media, inlineStyleSheet,
			&selection_handler, NULL, &styles);

	if (error != CSS_OK || styles == NULL) {
		/* Failed selecting partial style -- bail out */
		return NULL;
	}

	for (pseudo_element = CSS_PSEUDO_ELEMENT_NONE + 1;
			pseudo_element < CSS_PSEUDO_ELEMENT_COUNT;
			pseudo_element++) {

		if (pseudo_element == CSS_PSEUDO_ELEMENT_FIRST_LETTER ||
				pseudo_element == CSS_PSEUDO_ELEMENT_FIRST_LINE)
			/* TODO: Handle first-line and first-letter pseudo
			 *       element computed style completion */
			continue;

		if (styles->styles[pseudo_element] == NULL)
			/* There were no rules concerning this pseudo element */
			continue;

		/* Complete the pseudo element's computed style, by composing
		 * with the base element's style */
		error = css_computed_style_compose(
				styles->styles[CSS_PSEUDO_ELEMENT_NONE],
				styles->styles[pseudo_element],
				nscss_compute_font_size, NULL,
				&composed);
		if (error != CSS_OK) {
			/* TODO: perhaps this shouldn't be quite so
			 * catastrophic? */
			css_select_results_destroy(styles);
			return NULL;
		}

		/* Replace select_results style with composed style */
		css_computed_style_destroy(styles->styles[pseudo_element]);
		styles->styles[pseudo_element] = composed;
	}

	return styles;
}

