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
#include "select.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t (*css_len_func)(const css_computed_style *style, css_fixed *length, css_unit *unit);
typedef uint8_t (*css_border_style_func)(const css_computed_style *style);
typedef uint8_t (*css_border_color_func)(const css_computed_style *style, css_color *color);

/** Array of per-side access functions for computed style margins. */
static const css_len_func margin_funcs[4] = {
	css_computed_margin_top,
	css_computed_margin_right,
	css_computed_margin_bottom,
	css_computed_margin_left,
};

/** Array of per-side access functions for computed style paddings. */
static const css_len_func padding_funcs[4] = {
	css_computed_padding_top,
	css_computed_padding_right,
	css_computed_padding_bottom,
	css_computed_padding_left,
};

/** Array of per-side access functions for computed style border_widths. */
static const css_len_func border_width_funcs[4] = {
	css_computed_border_top_width,
	css_computed_border_right_width,
	css_computed_border_bottom_width,
	css_computed_border_left_width,
};

/** Array of per-side access functions for computed style border styles. */
static const css_border_style_func border_style_funcs[4] = {
	css_computed_border_top_style,
	css_computed_border_right_style,
	css_computed_border_bottom_style,
	css_computed_border_left_style,
};

/** Array of per-side access functions for computed style border colors. */
static const css_border_color_func border_color_funcs[4] = {
	css_computed_border_top_color,
	css_computed_border_right_color,
	css_computed_border_bottom_color,
	css_computed_border_left_color,
};


int _hilayout_select_child_style(const css_media* media, css_select_ctx* select_ctx, HLDomElementNode* node)
{
    int ret = _hilayout_select_node_style(media, select_ctx, node);
    if (ret != HILAYOUT_OK)
    {
        return ret;
    }
    HLDomElementNode* child = node->first_child;
    while(child)
    {
        ret = _hilayout_select_child_style(media, select_ctx, child);
        if (ret != HILAYOUT_OK)
        {
            return ret;
        }
        child = child->next;
    }
    return HILAYOUT_OK;
}


void _hl_calculate_mbp_width(const HLContext *len_ctx,
		    const css_computed_style *style,
		    unsigned int side,
		    bool margin,
		    bool border,
		    bool padding,
		    int *fixed,
		    float *frac
            )
{
    *fixed += 0;
    *frac += 0;
}

void _layout_handle_box_sizing(
		const HLContext *len_ctx,
		HLDomElementNode *node,
		int available_width,
		bool setwidth,
		int *dimension)
{
	enum css_box_sizing_e bs;

	assert(node && node->computed_style);

	bs = css_computed_box_sizing(node->computed_style);

	if (bs == CSS_BOX_SIZING_BORDER_BOX) {
		int orig = *dimension;
		int fixed = 0;
		float frac = 0;

		_hl_calculate_mbp_width(len_ctx, node->computed_style,
				setwidth ? HL_LEFT : HL_TOP,
				false, true, true, &fixed, &frac);
		_hl_calculate_mbp_width(len_ctx, node->computed_style,
				setwidth ? HL_RIGHT : HL_BOTTOM,
				false, true, true, &fixed, &frac);
		orig -= frac * available_width + fixed;
		*dimension = orig > 0 ? orig : 0;
	}
}

int _hilayout_calc_z_index(HLDomElementNode *node)
{
    int32_t index = 0;
    int8_t val = css_computed_z_index(node->computed_style, &index);
    switch (val) {
    case CSS_Z_INDEX_INHERIT:
        HL_LOGW("calc z index|tag=%s|id=%s|name=%s|z-index=inherit|index=%d\n", node->tag, node->attr[HL_ATTR_NAME_ID], node->attr[HL_ATTR_NAME_NAME], index);
        index = node->parent ? node->parent->box_values.z_index : 0;
        break;

    case CSS_Z_INDEX_AUTO:
        HL_LOGW("calc z index||tag=%s|id=%s|name=%s|z-index=auto|index=%d\n", node->tag, node->attr[HL_ATTR_NAME_ID], node->attr[HL_ATTR_NAME_NAME], index);
        break;

    case CSS_Z_INDEX_SET:
        HL_LOGW("calc z index|tag=%s|id=%s|name=%s|z-index=%d|index=%d\n", node->tag, node->attr[HL_ATTR_NAME_ID], node->attr[HL_ATTR_NAME_NAME], index, index);
        break;

    default:
        HL_LOGW("calc z index|tag=%s|id=%s|name=%s|z-index=default|index=%d\n", node->tag, node->attr[HL_ATTR_NAME_ID], node->attr[HL_ATTR_NAME_NAME], index);
        break;
    }
    node->box_values.z_index = index;
    return index;
}

int _hilayout_layout_node(HLDomElementNode *node, int x, int y, int container_width, int container_height, int level)
{
    if (node == NULL)
    {
        HL_LOGW("layout node|level=%d|node=%p\n", level, node);
        return HILAYOUT_OK;
    }

    HL_LOGW("layout node|level=%d|tag=%s|id=%s|name=%s|parent=%p\n", level, node->tag, node->attr[HL_ATTR_NAME_ID], node->attr[HL_ATTR_NAME_NAME], node->parent);
    node->box_values.x = x;
    node->box_values.y = y;

    if (node->parent == NULL)
    {
        node->box_values.w = container_width;
        node->box_values.h = container_height;
        _hilayout_calc_z_index(node);
    }

    int cx = x;
    int cy = y;
    int cw = container_width;
    int ch = container_height;
    int cl = level + 1;
    int node_height = 0;
    int node_width = 0;
    HLDomElementNode* child = node->first_child;
    while(child)
    {
        switch (child->layout_type)
        {
            case LAYOUT_BLOCK:
                cy = cy + node_height;
                _hilayout_layout_node(child, cx, cy, cw, ch, cl);
                node_width = node_width + child->box_values.w;
                node_height = node_height + child->box_values.h;
                break;

            case LAYOUT_INLINE_BLOCK:
                cx = cx + node_width;
                _hilayout_layout_node(child, cx, cy, cw, ch, cl);
                node_width = node_width + child->box_values.w;
                node_height = node_height + child->box_values.h;
                break;

            default:
                cy = cy + node_height;
                _hilayout_layout_node(child, cx, cy, cw, ch, cl);
                node_width = node_width + child->box_values.w;
                node_height = node_height + child->box_values.h;
                break;
        }
        child = child->next;
    }

    node->box_values.w = node_width + 10;
    node->box_values.h = node_height + 10;
    HL_LOGW("layout node|level=%d|tag=%s|id=%s|name=%s|parent=%p|w=%f|h=%f\n", level, node->tag, node->attr[HL_ATTR_NAME_ID], node->attr[HL_ATTR_NAME_NAME], node->parent, node->box_values.w, node->box_values.h);
    return HILAYOUT_OK;
}

int hilayout_do_layout(HLMedia* media, HLCSS* css, HLDomElementNode *root)
{
    if (media == NULL || root == NULL || css == NULL || css->sheet == NULL)
    {
        HL_LOGW("%s|media=%p|root=%p|css=%p|style_sheet=%p|param error\n", __func__, media, root, css, css->sheet);
        return HILAYOUT_NOMEM;
    }

	HLContext context = {
		.media = media,
		.css = css,
	};
    _hl_set_media_dpi(&context, media->dpi);
    _hl_set_baseline_pixel_density(&context, media->density);

	css_media m;
	m.type = CSS_MEDIA_SCREEN;
    m.width  = _hl_css_pixels_physical_to_css(&context, INTTOFIX(media->width));
    m.height = _hl_css_pixels_physical_to_css(&context, INTTOFIX(media->height));
    context.vw = m.width;
    context.vh = m.height;

    HL_LOGD("media|param dpi=%d|density=%d|after calc inner|dpi=0x%x|density=0x%x\n",
            media->dpi, media->density, ctx->hl_css_media_dpi, ctx->hl_css_baseline_pixel_density);
    HL_LOGD("media|param w=%d|h=%d|after calc inner|w=%d|h=%d|to physical|w=%d|h=%d\n",
            media->width, media->height, m.width, m.height, 
            FIXTOINT(_hl_css_pixels_css_to_physical(ctx, m.width)), 
            FIXTOINT(_hl_css_pixels_css_to_physical(ctx, m.height)));

    // create css select context
    css_select_ctx* select_ctx = _hilayout_css_select_ctx_create(css);

    int ret = _hilayout_select_child_style(&m, select_ctx, root);
    if (ret != HILAYOUT_OK)
    {
        HL_LOGW("%s|select child style failed.|code=%d\n", __func__, ret);
        _hilayout_css_select_ctx_destroy(select_ctx);
        return ret;
    }
    context.root_style = root->computed_style;

    _hilayout_layout_node(root, 0, 0, media->width, media->height, 0);
    _hilayout_css_select_ctx_destroy(select_ctx);
    return ret;
}

