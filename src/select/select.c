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

#define DEFAULT_CHARSET "UTF-8"
#define DEFAULT_URL "hilayout_css_select"

#define UNUSED(x) ((x) = (x))

/******************************************************************************
 * Style selection callbacks                                                  *
 ******************************************************************************/

/**
 * Callback to retrieve a node's name.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Pointer to location to receive node name
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 */
css_error node_name(void *pw, void *node, css_qname *qname)
{
    DomNode *n = node;

    if (n->name == NULL)
    {
        qname->name = NULL;
        return CSS_NOMEM;
    }

    qname->name = lwc_string_ref(n->lwcName);
    return CSS_OK;
}

/**
 * Callback to retrieve a node's classes.
 *
 * \param pw         HTML document
 * \param node       DOM node
 * \param classes    Pointer to location to receive class name array
 * \param n_classes  Pointer to location to receive length of class name array
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \note The returned array will be destroyed by libcss. Therefore, it must
 *       be allocated using the same allocator as used by libcss during style
 *       selection.
 */
css_error node_classes(void *pw, void *node, lwc_string ***classes, uint32_t *n_classes)
{
    DomNode *n = node;

    if (n->classesCount > 0)
    {
        uint32_t classnr;

        *classes = n->lwcClasses;
        *n_classes = n->classesCount;

        for (classnr = 0; classnr < n->classesCount; classnr++)
            (void) lwc_string_ref((*classes)[classnr]);

    } else {
        *n_classes = 0;
        *classes = NULL;
    }
    return CSS_OK;
}

/**
 * Callback to retrieve a node's ID.
 *
 * \param pw    HTML document
 * \param node  DOM node
 * \param id    Pointer to location to receive id value
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 */
css_error node_id(void *pw, void *node, lwc_string **id)
{
    DomNode *n = node;

    if (n->id == NULL)
    {
        *id = NULL;
        return CSS_OK;
    }

    *id = lwc_string_ref(n->lwcId);

    return CSS_OK;
}

/**
 * Callback to find a named parent node
 *
 * \param pw      HTML document
 * \param node    DOM node
 * \param qname   Node name to search for
 * \param parent  Pointer to location to receive parent
 * \return CSS_OK.
 *
 * \post \a parent will contain the result, or NULL if there is no match
 */
css_error named_parent_node(void *pw, void *n, const css_qname *qname, void **parent)
{
    DomNode* node = n;

    *parent = NULL;

    for (node = node->parent; node != NULL; node = node->parent) {
        if (node->domType != DOM_ELEMENT_NODE)
            continue;

        assert(node->name != NULL);

        bool match = false;
        if (lwc_string_caseless_isequal(node->lwcName, qname->name,
                    &match) == lwc_error_ok && match)
        {
            *parent = (DomNode *)node;
        }
        break;
    }

    return CSS_OK;
}

int dom_node_get_previous_sibling(DomNode *node,
        DomNode **result)
{
    /* Attr nodes have no previous siblings */
    if (node->domType == DOM_ATTRIBUTE_NODE) {
        *result = NULL;
        return CSS_OK;
    }

    *result = node->previous;
    return CSS_OK;
}

/**
 * Callback to find a named sibling node.
 *
 * \param pw       HTML document
 * \param node     DOM node
 * \param qname    Node name to search for
 * \param sibling  Pointer to location to receive sibling
 * \return CSS_OK.
 *
 * \post \a sibling will contain the result, or NULL if there is no match
 */
css_error named_sibling_node(void *pw, void *node, const css_qname *qname, void **sibling)
{
	DomNode *n = node;
	DomNode *prev;
	int err;

	*sibling = NULL;

	/* Find sibling element */
	dom_node_get_previous_sibling(n, &n);

	while (n != NULL) {
        DomNodeType type = n->domType;

		if (type == DOM_ELEMENT_NODE)
			break;

		dom_node_get_previous_sibling(n, &prev);
		n = prev;
	}

	if (n != NULL) {
        bool match = false;
        if (lwc_string_caseless_isequal(n->lwcName, qname->name,
                    &match) == lwc_error_ok && match)
        {
			*sibling = n;
        }
	}

	return CSS_OK;
}

/**
 * Callback to find a named generic sibling node.
 *
 * \param pw       HTML document
 * \param node     DOM node
 * \param qname    Node name to search for
 * \param sibling  Pointer to location to receive ancestor
 * \return CSS_OK.
 *
 * \post \a sibling will contain the result, or NULL if there is no match
 */
css_error named_generic_sibling_node(void *pw, void *node, const css_qname *qname, void **sibling)
{
	DomNode *n = node;
	DomNode *prev;
	int err;

	*sibling = NULL;

	dom_node_get_previous_sibling(n, &n);

	while (n != NULL) {
		DomNodeType type = n->domType;
		lwc_string *name;

		if (type == DOM_ELEMENT_NODE) {
            bool match = false;
            if (lwc_string_caseless_isequal(n->lwcName, qname->name,
                        &match) == lwc_error_ok && match)
            {
                *sibling = n;
                break;
            }
		}

		dom_node_get_previous_sibling(n, &prev);
		n = prev;
	}

	return CSS_OK;
}

/**
 * Callback to retrieve the parent of a node.
 *
 * \param pw      HTML document
 * \param node    DOM node
 * \param parent  Pointer to location to receive parent
 * \return CSS_OK.
 *
 * \post \a parent will contain the result, or NULL if there is no match
 */
css_error parent_node(void *pw, void *node, void **parent)
{
    DomNode *n = node;
    *parent = NULL;
    for (n = n->parent; n != NULL; n = n->parent) {
        if (n->domType != DOM_ELEMENT_NODE)
            continue;

        *parent = n;
        break;
    }
    return CSS_OK;
}

/**
 * Callback to retrieve the preceding sibling of a node.
 *
 * \param pw       HTML document
 * \param node     DOM node
 * \param sibling  Pointer to location to receive sibling
 * \return CSS_OK.
 *
 * \post \a sibling will contain the result, or NULL if there is no match
 */
css_error sibling_node(void *pw, void *node, void **sibling)
{
	DomNode *n = node;
	DomNode *prev;
	int err;

	*sibling = NULL;

	/* Find sibling element */
	dom_node_get_previous_sibling(n, &n);

	while (n != NULL) {
		DomNodeType type = n->domType;
		if (type == DOM_ELEMENT_NODE)
			break;

		dom_node_get_previous_sibling(n, &prev);
		n = prev;
	}

	if (n != NULL) {
		*sibling = n;
	}

	return CSS_OK;
}

/**
 * Callback to determine if a node has the given name.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Name to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_name(void *pw, void *node, const css_qname *qname, bool *match)
{
	DomNode *n = node;
    lwc_string_caseless_isequal(n->lwcName, qname->name, match);
	return CSS_OK;
}

/**
 * Callback to determine if a node has the given class.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param name   Name to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_class(void *pw, void *node, lwc_string *name, bool *match)
{
	unsigned int class;
    DomNode *n = node;
	
	/* Short-circuit case where we have no classes */
	if (n->classesCount == 0) {
		*match = false;
        return CSS_OK;
	}

    /* Standards mode: case sensitively match */
    for (class = 0; class < n->classesCount; class++) {
        if (lwc_error_ok == lwc_string_caseless_isequal(name,
                    n->lwcClasses[class], match) &&
                *match == true)
            return CSS_OK;
    }

    return CSS_OK;
}

/**
 * Callback to determine if a node has the given id.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param name   Name to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_id(void *pw, void *node, lwc_string *name, bool *match)
{
	DomNode *n = node;
    lwc_string_caseless_isequal(n->lwcId, name, match);
    return CSS_OK;
}

/**
 * Callback to determine if a node has an attribute with the given name.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Name to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_attribute(void *pw, void *node, const css_qname *qname, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node has an attribute with given name and value.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Name to match
 * \param value  Value to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_attribute_equal(void *pw, void *node,
        const css_qname *qname, lwc_string *value,
        bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node has an attribute with the given name whose
 * value dashmatches that given.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Name to match
 * \param value  Value to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_attribute_dashmatch(void *pw, void *node,
        const css_qname *qname, lwc_string *value,
        bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node has an attribute with the given name whose
 * value includes that given.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Name to match
 * \param value  Value to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_attribute_includes(void *pw, void *node,
        const css_qname *qname, lwc_string *value,
        bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node has an attribute with the given name whose
 * value has the prefix given.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Name to match
 * \param value  Value to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_attribute_prefix(void *pw, void *node,
        const css_qname *qname, lwc_string *value,
        bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node has an attribute with the given name whose
 * value has the suffix given.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Name to match
 * \param value  Value to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_attribute_suffix(void *pw, void *node,
        const css_qname *qname, lwc_string *value,
        bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node has an attribute with the given name whose
 * value contains the substring given.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param qname  Name to match
 * \param value  Value to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_has_attribute_substring(void *pw, void *node,
        const css_qname *qname, lwc_string *value,
        bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node is the root node of the document.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_is_root(void *pw, void *node, bool *match)
{
    DomNode *n = node;
    if (n->parent == NULL)
        *match = true;
    else
        *match = false;
    return CSS_OK;
}

int dom_node_get_next_sibling(DomNode *node,
        DomNode **result)
{
    /* Attr nodes have no next siblings */
    if (node->domType == DOM_ATTRIBUTE_NODE) {
        *result = NULL;
        return CSS_OK;
    }

    *result = node->next;
    return CSS_OK;
}

static int
node_count_siblings_check(DomNode *node,
			  bool check_name,
			  lwc_string *name)
{
	DomNodeType type;
	int ret = 0;
	int exc;

	if (node == NULL)
		return 0;

	type = node->domType;
	if (type != DOM_ELEMENT_NODE) {
		return 0;
	}

	if (check_name) {
		lwc_string *node_name = node->lwcName;

		if (node_name != NULL) {

            bool match = false;
            if (lwc_string_caseless_isequal(node_name, name,
                    &match) == lwc_error_ok && match) {
				ret = 1;
			}
		}
	} else {
		ret = 1;
	}
	return ret;
}

/**
 * Callback to count a node's siblings.
 *
 * \param pw         HTML document
 * \param n          DOM node
 * \param same_name  Only count siblings with the same name, or all
 * \param after      Count anteceding instead of preceding siblings
 * \param count      Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a count will contain the number of siblings
 */
css_error node_count_siblings(void *pw, void *n,
        bool same_name, bool after, int32_t *count)
{
	int32_t cnt = 0;
	int exc;
	lwc_string *node_name = NULL;

	if (same_name) {
		DomNode *node = n;
        node_name = node->lwcName;
		if (node_name == NULL) {
			return CSS_NOMEM;
		}
	}

	if (after) {
		DomNode *node = n;
		DomNode *next;

		do {
			dom_node_get_next_sibling(node, &next);
			node = next;
			cnt += node_count_siblings_check(node, same_name, node_name);
		} while (node != NULL);
	} else {
		DomNode *node = n;
		DomNode *next;

		do {
			dom_node_get_previous_sibling(node, &next);
			node = next;
			cnt += node_count_siblings_check(node, same_name, node_name);
		} while (node != NULL);
	}

	*count = cnt;
	return CSS_OK;
}

/**
 * Callback to determine if a node is empty.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node is empty and false otherwise.
 */
css_error node_is_empty(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node is a linking element.
 *
 * \param pw     HTML document
 * \param n      DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_is_link(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node is currently being hovered over.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_is_hover(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node is currently activated.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_is_active(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node has the input focus.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_is_focus(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node is enabled.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match with contain true if the node is enabled and false otherwise.
 */
css_error node_is_enabled(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node is disabled.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match with contain true if the node is disabled and false otherwise.
 */
css_error node_is_disabled(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node is checked.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match with contain true if the node is checked and false otherwise.
 */
css_error node_is_checked(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node is the target of the document URL.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match with contain true if the node matches and false otherwise.
 */
css_error node_is_target(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to determine if a node has the given language
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param lang   Language specifier to match
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_is_lang(void *pw, void *node,
        lwc_string *lang, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to retrieve the User-Agent defaults for a CSS property.
 *
 * \param pw        HTML document
 * \param property  Property to retrieve defaults for
 * \param hint      Pointer to hint object to populate
 * \return CSS_OK       on success,
 *         CSS_INVALID  if the property should not have a user-agent default.
 */
css_error ua_default_for_property(void *pw, uint32_t property,
        css_hint *hint)
{

    if (property == CSS_PROP_COLOR) {
        hint->data.color = 0x00000000;
        hint->status = CSS_COLOR_COLOR;
    } else if (property == CSS_PROP_FONT_FAMILY) {
        hint->data.strings = NULL;
        hint->status = CSS_FONT_FAMILY_SANS_SERIF;
    } else if (property == CSS_PROP_QUOTES) {
        /* Not exactly useful :) */
        hint->data.strings = NULL;
        hint->status = CSS_QUOTES_NONE;
    } else if (property == CSS_PROP_VOICE_FAMILY) {
        /** \todo Fix this when we have voice-family done */
        hint->data.strings = NULL;
        hint->status = 0;
    } else {
        return CSS_INVALID;
    }

	return CSS_OK;
}

css_error set_libcss_node_data(void *pw, void *node,
        void *libcss_node_data)
{
    DomNode *n = node;
    n->attach = libcss_node_data;
    return CSS_OK;
}

css_error get_libcss_node_data(void *pw, void *node,
        void **libcss_node_data)
{
    DomNode* n = node;
    *libcss_node_data = n->attach;
    return CSS_OK;
}


css_error compute_font_size(void *pw, const css_hint *parent,
        css_hint *size)
{
	static css_hint_length sizes[] = {
		{ FLTTOFIX(6.75), CSS_UNIT_PT },
		{ FLTTOFIX(7.50), CSS_UNIT_PT },
		{ FLTTOFIX(9.75), CSS_UNIT_PT },
		{ FLTTOFIX(12.0), CSS_UNIT_PT },
		{ FLTTOFIX(13.5), CSS_UNIT_PT },
		{ FLTTOFIX(18.0), CSS_UNIT_PT },
		{ FLTTOFIX(24.0), CSS_UNIT_PT }
	};
	const css_hint_length *parent_size;

	UNUSED(pw);

	/* Grab parent size, defaulting to medium if none */
	if (parent == NULL) {
		parent_size = &sizes[CSS_FONT_SIZE_MEDIUM - 1];
	} else {
		assert(parent->status == CSS_FONT_SIZE_DIMENSION);
		assert(parent->data.length.unit != CSS_UNIT_EM);
		assert(parent->data.length.unit != CSS_UNIT_EX);
		parent_size = &parent->data.length;
	}

	assert(size->status != CSS_FONT_SIZE_INHERIT);

	if (size->status < CSS_FONT_SIZE_LARGER) {
		/* Keyword -- simple */
		size->data.length = sizes[size->status - 1];
	} else if (size->status == CSS_FONT_SIZE_LARGER) {
		/** \todo Step within table, if appropriate */
		size->data.length.value =
				FMUL(parent_size->value, FLTTOFIX(1.2));
		size->data.length.unit = parent_size->unit;
	} else if (size->status == CSS_FONT_SIZE_SMALLER) {
		/** \todo Step within table, if appropriate */
		size->data.length.value =
				FMUL(parent_size->value, FLTTOFIX(1.2));
		size->data.length.unit = parent_size->unit;
	} else if (size->data.length.unit == CSS_UNIT_EM ||
			size->data.length.unit == CSS_UNIT_EX) {
		size->data.length.value =
			FMUL(size->data.length.value, parent_size->value);

		if (size->data.length.unit == CSS_UNIT_EX) {
			size->data.length.value = FMUL(size->data.length.value,
					FLTTOFIX(0.6));
		}

		size->data.length.unit = parent_size->unit;
	} else if (size->data.length.unit == CSS_UNIT_PCT) {
		size->data.length.value = FDIV(FMUL(size->data.length.value,
				parent_size->value), FLTTOFIX(100));
		size->data.length.unit = parent_size->unit;
	}

	size->status = CSS_FONT_SIZE_DIMENSION;

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

/**
 * Callback to find a named ancestor node.
 *
 * \param pw        HTML document
 * \param node      DOM node
 * \param qname     Node name to search for
 * \param ancestor  Pointer to location to receive ancestor
 * \return CSS_OK.
 *
 * \post \a ancestor will contain the result, or NULL if there is no match
 */
css_error named_ancestor_node(void *pw, void *n,
        const css_qname *qname, void **ancestor)
{
	DomNode *node = n;

	*ancestor = NULL;

	for (node = node->parent; node != NULL; node = node->parent) {
		if (node->domType != DOM_ELEMENT_NODE)
			continue;

		assert(node->name != NULL);

        bool match = false;
        if (lwc_string_caseless_isequal(node->lwcName, qname->name,
                    &match) == lwc_error_ok && match)
        {
			*ancestor = node;
			break;
		}
	}

    return CSS_OK;
}

/**
 * Callback to determine if a node is a linking element whose target has been
 * visited.
 *
 * \param pw     HTML document
 * \param node   DOM node
 * \param match  Pointer to location to receive result
 * \return CSS_OK.
 *
 * \post \a match will contain true if the node matches and false otherwise.
 */
css_error node_is_visited(void *pw, void *node, bool *match)
{
    *match = false;
    return CSS_OK;
}

/**
 * Callback to retrieve presentational hints for a node
 *
 * \param[in] pw HTML document
 * \param[in] node DOM node
 * \param[out] nhints number of hints retrieved
 * \param[out] hints retrieved hints
 * \return CSS_OK               on success,
 *         CSS_PROPERTY_NOT_SET if there is no hint for the requested property,
 *         CSS_NOMEM            on memory exhaustion.
 */
css_error node_presentational_hint( void *pw, void *node, uint32_t *nhints, css_hint **hints)
{
    *nhints = 0;
    *hints = NULL;
    return CSS_OK;
}

css_select_handler selection_handler = {
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
    compute_font_size,
    set_libcss_node_data,
    get_libcss_node_data
};

css_stylesheet* _hilayout_css_stylesheet_create(const char *charset, const char *url, bool allow_quirks, bool inline_style)
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
        HL_LOGE("Failed create sheet: %d\n", error);
        return NULL;
    }

    return sheet;
}

int _hilayout_css_stylesheet_append_data(css_stylesheet* sheet, const uint8_t *data, size_t len)
{
    if (sheet == NULL || data == NULL || len <= 0)
        return HILAYOUT_BADPARM;

    css_error error = css_stylesheet_append_data(sheet, data, len);
    if (error != CSS_OK && error != CSS_NEEDDATA) {
        HL_LOGE("append css data failed|code=%d\n", error);
        return error;
    }
    return HILAYOUT_OK;
}

int _hilayout_css_stylesheet_data_done(css_stylesheet* sheet)
{
    if (sheet)
        return css_stylesheet_data_done(sheet);
    return HILAYOUT_OK;
}

int _hilayout_css_stylesheet_destroy(css_stylesheet* sheet)
{
    if (sheet)
        return css_stylesheet_destroy(sheet);
    return HILAYOUT_OK;
}

css_stylesheet* _hilayout_css_stylesheet_inline_style_create(const uint8_t *data, size_t len)
{
    css_stylesheet *sheet = _hilayout_css_stylesheet_create(DEFAULT_CHARSET, DEFAULT_URL, true, false);
    if (sheet == NULL)
    {
        return NULL;
    }

    css_error error = css_stylesheet_data_done(sheet);
    if (error != CSS_OK) {
        fprintf(stderr, "failed completing parse: %d\n", error);
        css_stylesheet_destroy(sheet);
        return NULL;
    }

    size_t size = 0;
    error = css_stylesheet_size(sheet, &size);
    if (error != CSS_OK)
        fprintf(stderr, "css_stylesheet_size %d\n", error);

    fprintf(stderr, "appended data, size now %zu\n", size);

    return sheet;
}


HLCSS* hilayout_css_create(void)
{
    char url[] = "hilayout_css_select";
    css_stylesheet *sheet = _hilayout_css_stylesheet_create(DEFAULT_CHARSET, DEFAULT_URL, true, false);
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
    if (css)
        return _hilayout_css_stylesheet_append_data(css->sheet, data, len);
    return HILAYOUT_BADPARM;
}

int hilayout_css_destroy(HLCSS* css)
{
    if (css == NULL)
        return HILAYOUT_OK;

    _hilayout_css_stylesheet_destroy(css->sheet);
    free(css);
}

css_select_results *_hilayout_css_select_style(const HLCSS* css, void *n,
        const css_media *media, const css_stylesheet *inlineStyleSheet, css_select_handler *handler)
{
    css_computed_style *composed;
    css_select_results *styles;
    int pseudo_element;
    css_error error;
    css_error code;
    css_select_ctx *select_ctx;
    uint32_t count;

    if (css == NULL || css->sheet == NULL)
    {
        HL_LOGW("css select style param error.\n");
        return NULL;
    }

    if (css->done != 1)
    {
        _hilayout_css_stylesheet_data_done(css->sheet);
    }

    css_stylesheet* styleSheet = css->sheet;

    code = css_select_ctx_create(&select_ctx);
    if (code != CSS_OK)
    {
        fprintf(stderr, "css_select_ctx_create failed! code=%d\n", code);
        return NULL;
    }

    code = css_select_ctx_append_sheet(select_ctx, styleSheet, CSS_ORIGIN_AUTHOR, NULL);
    if (code != CSS_OK)
    {
        fprintf(stderr, "css_select_ctx_append_sheet failed! code=%d\n", code);
        return NULL;
    }

    code = css_select_ctx_count_sheets(select_ctx, &count);
    if (code != CSS_OK)
    {
        fprintf(stderr, "css_select_ctx_count_sheets failed! code=%d\n", code);
        return NULL;
    }

    fprintf(stderr, "created selection context with %i sheets\n", count);

    /* Select style for node */
    error = css_select_style(select_ctx, n, media, inlineStyleSheet,
            handler ? handler : &selection_handler, NULL, &styles);

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
                compute_font_size, NULL,
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

int _hilayout_css_select_result_destroy(css_select_results *result)
{
    if (result)
        return css_select_results_destroy(result);
}

css_fixed css_screen_dpi = F_90;
css_fixed css_baseline_pixel_density = F_96;
static inline css_fixed css_pixels_css_to_physical(
        css_fixed css_pixels)
{
    return FDIV(FMUL(css_pixels, css_screen_dpi),
            css_baseline_pixel_density);
}


css_fixed css_len2px(
		css_fixed length,
		css_unit unit,
		const css_computed_style *style)
{
	/* We assume the screen and any other output has the same dpi */
	css_fixed px_per_unit;

//	unit = css_utils__fudge_viewport_units(ctx, unit);

	switch (unit) {
	case CSS_UNIT_PX:
		px_per_unit = F_1;
		break;
	default:
		px_per_unit = 0;
		break;
	}

	px_per_unit = css_pixels_css_to_physical(px_per_unit);

	/* Ensure we round px_per_unit to the nearest whole number of pixels:
	 * the use of FIXTOINT() below will truncate. */
	px_per_unit += F_0_5;

	/* Calculate total number of pixels */
	return FMUL(length, TRUNCATEFIX(px_per_unit));
}
