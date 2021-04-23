/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 The NetSurf Project
 */


#define ALIGN_CONTENT_INDEX 11
#define ALIGN_CONTENT_SHIFT 3
#define ALIGN_CONTENT_MASK 0x38
static inline uint8_t get_align_content(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[ALIGN_CONTENT_INDEX];
	bits &= ALIGN_CONTENT_MASK;
	bits >>= ALIGN_CONTENT_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef ALIGN_CONTENT_INDEX
#undef ALIGN_CONTENT_SHIFT
#undef ALIGN_CONTENT_MASK

#define ALIGN_ITEMS_INDEX 11
#define ALIGN_ITEMS_SHIFT 15
#define ALIGN_ITEMS_MASK 0x38000
static inline uint8_t get_align_items(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[ALIGN_ITEMS_INDEX];
	bits &= ALIGN_ITEMS_MASK;
	bits >>= ALIGN_ITEMS_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef ALIGN_ITEMS_INDEX
#undef ALIGN_ITEMS_SHIFT
#undef ALIGN_ITEMS_MASK

#define ALIGN_SELF_INDEX 17
#define ALIGN_SELF_SHIFT 20
#define ALIGN_SELF_MASK 0x700000
static inline uint8_t get_align_self(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[ALIGN_SELF_INDEX];
	bits &= ALIGN_SELF_MASK;
	bits >>= ALIGN_SELF_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef ALIGN_SELF_INDEX
#undef ALIGN_SELF_SHIFT
#undef ALIGN_SELF_MASK

#define BACKGROUND_ATTACHMENT_INDEX 18
#define BACKGROUND_ATTACHMENT_SHIFT 16
#define BACKGROUND_ATTACHMENT_MASK 0x30000
static inline uint8_t get_background_attachment(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BACKGROUND_ATTACHMENT_INDEX];
	bits &= BACKGROUND_ATTACHMENT_MASK;
	bits >>= BACKGROUND_ATTACHMENT_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef BACKGROUND_ATTACHMENT_INDEX
#undef BACKGROUND_ATTACHMENT_SHIFT
#undef BACKGROUND_ATTACHMENT_MASK

#define BACKGROUND_COLOR_INDEX 14
#define BACKGROUND_COLOR_SHIFT 24
#define BACKGROUND_COLOR_MASK 0x3000000
static inline uint8_t get_background_color(const css_computed_style *style,
		css_color *color)
{
	uint32_t bits = style->i.bits[BACKGROUND_COLOR_INDEX];
	bits &= BACKGROUND_COLOR_MASK;
	bits >>= BACKGROUND_COLOR_SHIFT;
	
	/* 2bits: tt : type */
	*color = style->i.background_color;
	
	return (bits & 0x3);
}
#undef BACKGROUND_COLOR_INDEX
#undef BACKGROUND_COLOR_SHIFT
#undef BACKGROUND_COLOR_MASK

#define BACKGROUND_IMAGE_INDEX 15
#define BACKGROUND_IMAGE_SHIFT 0
#define BACKGROUND_IMAGE_MASK 0x1
static inline uint8_t get_background_image(const css_computed_style *style,
		lwc_string **string)
{
	uint32_t bits = style->i.bits[BACKGROUND_IMAGE_INDEX];
	bits &= BACKGROUND_IMAGE_MASK;
	bits >>= BACKGROUND_IMAGE_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.background_image;
	
	return (bits & 0x1);
}
#undef BACKGROUND_IMAGE_INDEX
#undef BACKGROUND_IMAGE_SHIFT
#undef BACKGROUND_IMAGE_MASK

#define BACKGROUND_POSITION_INDEX 15
#define BACKGROUND_POSITION_SHIFT 10
#define BACKGROUND_POSITION_MASK 0x1ffc00
static inline uint8_t get_background_position(const css_computed_style *style,
		css_fixed *length_a, css_unit *unit_a, css_fixed *length_b,
		css_unit *unit_b)
{
	uint32_t bits = style->i.bits[BACKGROUND_POSITION_INDEX];
	bits &= BACKGROUND_POSITION_MASK;
	bits >>= BACKGROUND_POSITION_SHIFT;
	
	/* 11bits: aaaaabbbbbt : unit_a | unit_b | type */
	if ((bits & 0x1) == CSS_BACKGROUND_POSITION_SET) {
		*length_a = style->i.background_position_a;
		*length_b = style->i.background_position_b;
		*unit_a = bits >> 6;
		*unit_b = (bits & 0x3e) >> 1;
	}
	
	return (bits & 0x1);
}
#undef BACKGROUND_POSITION_INDEX
#undef BACKGROUND_POSITION_SHIFT
#undef BACKGROUND_POSITION_MASK

#define BACKGROUND_REPEAT_INDEX 17
#define BACKGROUND_REPEAT_SHIFT 29
#define BACKGROUND_REPEAT_MASK 0xe0000000
static inline uint8_t get_background_repeat(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BACKGROUND_REPEAT_INDEX];
	bits &= BACKGROUND_REPEAT_MASK;
	bits >>= BACKGROUND_REPEAT_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef BACKGROUND_REPEAT_INDEX
#undef BACKGROUND_REPEAT_SHIFT
#undef BACKGROUND_REPEAT_MASK

#define BASELINE_SHIFT_INDEX 3
#define BASELINE_SHIFT_SHIFT 0
#define BASELINE_SHIFT_MASK 0xf
static inline uint8_t get_baseline_shift(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BASELINE_SHIFT_INDEX];
	bits &= BASELINE_SHIFT_MASK;
	bits >>= BASELINE_SHIFT_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef BASELINE_SHIFT_INDEX
#undef BASELINE_SHIFT_SHIFT
#undef BASELINE_SHIFT_MASK

#define BORDER_BOTTOM_COLOR_INDEX 14
#define BORDER_BOTTOM_COLOR_SHIFT 2
#define BORDER_BOTTOM_COLOR_MASK 0xc
static inline uint8_t get_border_bottom_color(const css_computed_style *style,
		css_color *color)
{
	uint32_t bits = style->i.bits[BORDER_BOTTOM_COLOR_INDEX];
	bits &= BORDER_BOTTOM_COLOR_MASK;
	bits >>= BORDER_BOTTOM_COLOR_SHIFT;
	
	/* 2bits: tt : type */
	*color = style->i.border_bottom_color;
	
	return (bits & 0x3);
}
#undef BORDER_BOTTOM_COLOR_INDEX
#undef BORDER_BOTTOM_COLOR_SHIFT
#undef BORDER_BOTTOM_COLOR_MASK

#define BORDER_BOTTOM_LEFT_RADIUS_INDEX 5
#define BORDER_BOTTOM_LEFT_RADIUS_SHIFT 18
#define BORDER_BOTTOM_LEFT_RADIUS_MASK 0x1fc0000
static inline uint8_t get_border_bottom_left_radius(const css_computed_style
		*style, css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BORDER_BOTTOM_LEFT_RADIUS_INDEX];
	bits &= BORDER_BOTTOM_LEFT_RADIUS_MASK;
	bits >>= BORDER_BOTTOM_LEFT_RADIUS_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_BORDER_BOTTOM_LEFT_RADIUS_SET) {
		*length = style->i.border_bottom_left_radius;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef BORDER_BOTTOM_LEFT_RADIUS_INDEX
#undef BORDER_BOTTOM_LEFT_RADIUS_SHIFT
#undef BORDER_BOTTOM_LEFT_RADIUS_MASK

#define BORDER_BOTTOM_RIGHT_RADIUS_INDEX 6
#define BORDER_BOTTOM_RIGHT_RADIUS_SHIFT 11
#define BORDER_BOTTOM_RIGHT_RADIUS_MASK 0x3f800
static inline uint8_t get_border_bottom_right_radius(const css_computed_style
		*style, css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BORDER_BOTTOM_RIGHT_RADIUS_INDEX];
	bits &= BORDER_BOTTOM_RIGHT_RADIUS_MASK;
	bits >>= BORDER_BOTTOM_RIGHT_RADIUS_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_BORDER_BOTTOM_RIGHT_RADIUS_SET) {
		*length = style->i.border_bottom_right_radius;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef BORDER_BOTTOM_RIGHT_RADIUS_INDEX
#undef BORDER_BOTTOM_RIGHT_RADIUS_SHIFT
#undef BORDER_BOTTOM_RIGHT_RADIUS_MASK

#define BORDER_BOTTOM_STYLE_INDEX 5
#define BORDER_BOTTOM_STYLE_SHIFT 0
#define BORDER_BOTTOM_STYLE_MASK 0xf
static inline uint8_t get_border_bottom_style(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BORDER_BOTTOM_STYLE_INDEX];
	bits &= BORDER_BOTTOM_STYLE_MASK;
	bits >>= BORDER_BOTTOM_STYLE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef BORDER_BOTTOM_STYLE_INDEX
#undef BORDER_BOTTOM_STYLE_SHIFT
#undef BORDER_BOTTOM_STYLE_MASK

#define BORDER_BOTTOM_WIDTH_INDEX 0
#define BORDER_BOTTOM_WIDTH_SHIFT 0
#define BORDER_BOTTOM_WIDTH_MASK 0xff
static inline uint8_t get_border_bottom_width(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BORDER_BOTTOM_WIDTH_INDEX];
	bits &= BORDER_BOTTOM_WIDTH_MASK;
	bits >>= BORDER_BOTTOM_WIDTH_SHIFT;
	
	/* 8bits: uuuuuttt : unit | type */
	if ((bits & 0x7) == CSS_BORDER_WIDTH_WIDTH) {
		*length = style->i.border_bottom_width;
		*unit = bits >> 3;
	}
	
	return (bits & 0x7);
}
#undef BORDER_BOTTOM_WIDTH_INDEX
#undef BORDER_BOTTOM_WIDTH_SHIFT
#undef BORDER_BOTTOM_WIDTH_MASK

#define BORDER_COLLAPSE_INDEX 14
#define BORDER_COLLAPSE_SHIFT 16
#define BORDER_COLLAPSE_MASK 0x30000
static inline uint8_t get_border_collapse(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BORDER_COLLAPSE_INDEX];
	bits &= BORDER_COLLAPSE_MASK;
	bits >>= BORDER_COLLAPSE_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef BORDER_COLLAPSE_INDEX
#undef BORDER_COLLAPSE_SHIFT
#undef BORDER_COLLAPSE_MASK

#define BORDER_LEFT_COLOR_INDEX 12
#define BORDER_LEFT_COLOR_SHIFT 0
#define BORDER_LEFT_COLOR_MASK 0x3
static inline uint8_t get_border_left_color(const css_computed_style *style,
		css_color *color)
{
	uint32_t bits = style->i.bits[BORDER_LEFT_COLOR_INDEX];
	bits &= BORDER_LEFT_COLOR_MASK;
	bits >>= BORDER_LEFT_COLOR_SHIFT;
	
	/* 2bits: tt : type */
	*color = style->i.border_left_color;
	
	return (bits & 0x3);
}
#undef BORDER_LEFT_COLOR_INDEX
#undef BORDER_LEFT_COLOR_SHIFT
#undef BORDER_LEFT_COLOR_MASK

#define BORDER_LEFT_STYLE_INDEX 10
#define BORDER_LEFT_STYLE_SHIFT 16
#define BORDER_LEFT_STYLE_MASK 0xf0000
static inline uint8_t get_border_left_style(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BORDER_LEFT_STYLE_INDEX];
	bits &= BORDER_LEFT_STYLE_MASK;
	bits >>= BORDER_LEFT_STYLE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef BORDER_LEFT_STYLE_INDEX
#undef BORDER_LEFT_STYLE_SHIFT
#undef BORDER_LEFT_STYLE_MASK

#define BORDER_LEFT_WIDTH_INDEX 0
#define BORDER_LEFT_WIDTH_SHIFT 24
#define BORDER_LEFT_WIDTH_MASK 0xff000000
static inline uint8_t get_border_left_width(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BORDER_LEFT_WIDTH_INDEX];
	bits &= BORDER_LEFT_WIDTH_MASK;
	bits >>= BORDER_LEFT_WIDTH_SHIFT;
	
	/* 8bits: uuuuuttt : unit | type */
	if ((bits & 0x7) == CSS_BORDER_WIDTH_WIDTH) {
		*length = style->i.border_left_width;
		*unit = bits >> 3;
	}
	
	return (bits & 0x7);
}
#undef BORDER_LEFT_WIDTH_INDEX
#undef BORDER_LEFT_WIDTH_SHIFT
#undef BORDER_LEFT_WIDTH_MASK

#define BORDER_RIGHT_COLOR_INDEX 14
#define BORDER_RIGHT_COLOR_SHIFT 26
#define BORDER_RIGHT_COLOR_MASK 0xc000000
static inline uint8_t get_border_right_color(const css_computed_style *style,
		css_color *color)
{
	uint32_t bits = style->i.bits[BORDER_RIGHT_COLOR_INDEX];
	bits &= BORDER_RIGHT_COLOR_MASK;
	bits >>= BORDER_RIGHT_COLOR_SHIFT;
	
	/* 2bits: tt : type */
	*color = style->i.border_right_color;
	
	return (bits & 0x3);
}
#undef BORDER_RIGHT_COLOR_INDEX
#undef BORDER_RIGHT_COLOR_SHIFT
#undef BORDER_RIGHT_COLOR_MASK

#define BORDER_RIGHT_STYLE_INDEX 9
#define BORDER_RIGHT_STYLE_SHIFT 0
#define BORDER_RIGHT_STYLE_MASK 0xf
static inline uint8_t get_border_right_style(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BORDER_RIGHT_STYLE_INDEX];
	bits &= BORDER_RIGHT_STYLE_MASK;
	bits >>= BORDER_RIGHT_STYLE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef BORDER_RIGHT_STYLE_INDEX
#undef BORDER_RIGHT_STYLE_SHIFT
#undef BORDER_RIGHT_STYLE_MASK

#define BORDER_RIGHT_WIDTH_INDEX 0
#define BORDER_RIGHT_WIDTH_SHIFT 8
#define BORDER_RIGHT_WIDTH_MASK 0xff00
static inline uint8_t get_border_right_width(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BORDER_RIGHT_WIDTH_INDEX];
	bits &= BORDER_RIGHT_WIDTH_MASK;
	bits >>= BORDER_RIGHT_WIDTH_SHIFT;
	
	/* 8bits: uuuuuttt : unit | type */
	if ((bits & 0x7) == CSS_BORDER_WIDTH_WIDTH) {
		*length = style->i.border_right_width;
		*unit = bits >> 3;
	}
	
	return (bits & 0x7);
}
#undef BORDER_RIGHT_WIDTH_INDEX
#undef BORDER_RIGHT_WIDTH_SHIFT
#undef BORDER_RIGHT_WIDTH_MASK

#define BORDER_SPACING_INDEX 15
#define BORDER_SPACING_SHIFT 21
#define BORDER_SPACING_MASK 0xffe00000
static inline uint8_t get_border_spacing(const css_computed_style *style,
		css_fixed *length_a, css_unit *unit_a, css_fixed *length_b,
		css_unit *unit_b)
{
	uint32_t bits = style->i.bits[BORDER_SPACING_INDEX];
	bits &= BORDER_SPACING_MASK;
	bits >>= BORDER_SPACING_SHIFT;
	
	/* 11bits: aaaaabbbbbt : unit_a | unit_b | type */
	if ((bits & 0x1) == CSS_BORDER_SPACING_SET) {
		*length_a = style->i.border_spacing_a;
		*length_b = style->i.border_spacing_b;
		*unit_a = bits >> 6;
		*unit_b = (bits & 0x3e) >> 1;
	}
	
	return (bits & 0x1);
}
#undef BORDER_SPACING_INDEX
#undef BORDER_SPACING_SHIFT
#undef BORDER_SPACING_MASK

#define BORDER_TOP_COLOR_INDEX 18
#define BORDER_TOP_COLOR_SHIFT 28
#define BORDER_TOP_COLOR_MASK 0x30000000
static inline uint8_t get_border_top_color(const css_computed_style *style,
		css_color *color)
{
	uint32_t bits = style->i.bits[BORDER_TOP_COLOR_INDEX];
	bits &= BORDER_TOP_COLOR_MASK;
	bits >>= BORDER_TOP_COLOR_SHIFT;
	
	/* 2bits: tt : type */
	*color = style->i.border_top_color;
	
	return (bits & 0x3);
}
#undef BORDER_TOP_COLOR_INDEX
#undef BORDER_TOP_COLOR_SHIFT
#undef BORDER_TOP_COLOR_MASK

#define BORDER_TOP_LEFT_RADIUS_INDEX 6
#define BORDER_TOP_LEFT_RADIUS_SHIFT 18
#define BORDER_TOP_LEFT_RADIUS_MASK 0x1fc0000
static inline uint8_t get_border_top_left_radius(const css_computed_style
		*style, css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BORDER_TOP_LEFT_RADIUS_INDEX];
	bits &= BORDER_TOP_LEFT_RADIUS_MASK;
	bits >>= BORDER_TOP_LEFT_RADIUS_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_BORDER_TOP_LEFT_RADIUS_SET) {
		*length = style->i.border_top_left_radius;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef BORDER_TOP_LEFT_RADIUS_INDEX
#undef BORDER_TOP_LEFT_RADIUS_SHIFT
#undef BORDER_TOP_LEFT_RADIUS_MASK

#define BORDER_TOP_RIGHT_RADIUS_INDEX 8
#define BORDER_TOP_RIGHT_RADIUS_SHIFT 25
#define BORDER_TOP_RIGHT_RADIUS_MASK 0xfe000000
static inline uint8_t get_border_top_right_radius(const css_computed_style
		*style, css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BORDER_TOP_RIGHT_RADIUS_INDEX];
	bits &= BORDER_TOP_RIGHT_RADIUS_MASK;
	bits >>= BORDER_TOP_RIGHT_RADIUS_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_BORDER_TOP_RIGHT_RADIUS_SET) {
		*length = style->i.border_top_right_radius;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef BORDER_TOP_RIGHT_RADIUS_INDEX
#undef BORDER_TOP_RIGHT_RADIUS_SHIFT
#undef BORDER_TOP_RIGHT_RADIUS_MASK

#define BORDER_TOP_STYLE_INDEX 11
#define BORDER_TOP_STYLE_SHIFT 24
#define BORDER_TOP_STYLE_MASK 0xf000000
static inline uint8_t get_border_top_style(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BORDER_TOP_STYLE_INDEX];
	bits &= BORDER_TOP_STYLE_MASK;
	bits >>= BORDER_TOP_STYLE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef BORDER_TOP_STYLE_INDEX
#undef BORDER_TOP_STYLE_SHIFT
#undef BORDER_TOP_STYLE_MASK

#define BORDER_TOP_WIDTH_INDEX 1
#define BORDER_TOP_WIDTH_SHIFT 15
#define BORDER_TOP_WIDTH_MASK 0x7f8000
static inline uint8_t get_border_top_width(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BORDER_TOP_WIDTH_INDEX];
	bits &= BORDER_TOP_WIDTH_MASK;
	bits >>= BORDER_TOP_WIDTH_SHIFT;
	
	/* 8bits: uuuuuttt : unit | type */
	if ((bits & 0x7) == CSS_BORDER_WIDTH_WIDTH) {
		*length = style->i.border_top_width;
		*unit = bits >> 3;
	}
	
	return (bits & 0x7);
}
#undef BORDER_TOP_WIDTH_INDEX
#undef BORDER_TOP_WIDTH_SHIFT
#undef BORDER_TOP_WIDTH_MASK

#define BOTTOM_INDEX 9
#define BOTTOM_SHIFT 4
#define BOTTOM_MASK 0x7f0
static inline uint8_t get_bottom(
		const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[BOTTOM_INDEX];
	bits &= BOTTOM_MASK;
	bits >>= BOTTOM_SHIFT;

	/* 7bits: uuuuutt : units | type */
	if ((bits & 0x3) == CSS_BOTTOM_SET) {
		*length = style->i.bottom;
		*unit = bits >> 2;
	}

	return (bits & 0x3);
}
static inline uint8_t get_bottom_bits(
		const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BOTTOM_INDEX];
	bits &= BOTTOM_MASK;
	bits >>= BOTTOM_SHIFT;

	/* 7bits: uuuuutt : units | type */
	return bits;
}
#undef BOTTOM_INDEX
#undef BOTTOM_SHIFT
#undef BOTTOM_MASK

#define BOX_SIZING_INDEX 18
#define BOX_SIZING_SHIFT 26
#define BOX_SIZING_MASK 0xc000000
static inline uint8_t get_box_sizing(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BOX_SIZING_INDEX];
	bits &= BOX_SIZING_MASK;
	bits >>= BOX_SIZING_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef BOX_SIZING_INDEX
#undef BOX_SIZING_SHIFT
#undef BOX_SIZING_MASK

#define BREAK_AFTER_INDEX 4
#define BREAK_AFTER_SHIFT 0
#define BREAK_AFTER_MASK 0xf
static inline uint8_t get_break_after(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BREAK_AFTER_INDEX];
	bits &= BREAK_AFTER_MASK;
	bits >>= BREAK_AFTER_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef BREAK_AFTER_INDEX
#undef BREAK_AFTER_SHIFT
#undef BREAK_AFTER_MASK

#define BREAK_BEFORE_INDEX 6
#define BREAK_BEFORE_SHIFT 0
#define BREAK_BEFORE_MASK 0xf
static inline uint8_t get_break_before(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BREAK_BEFORE_INDEX];
	bits &= BREAK_BEFORE_MASK;
	bits >>= BREAK_BEFORE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef BREAK_BEFORE_INDEX
#undef BREAK_BEFORE_SHIFT
#undef BREAK_BEFORE_MASK

#define BREAK_INSIDE_INDEX 10
#define BREAK_INSIDE_SHIFT 24
#define BREAK_INSIDE_MASK 0xf000000
static inline uint8_t get_break_inside(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[BREAK_INSIDE_INDEX];
	bits &= BREAK_INSIDE_MASK;
	bits >>= BREAK_INSIDE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef BREAK_INSIDE_INDEX
#undef BREAK_INSIDE_SHIFT
#undef BREAK_INSIDE_MASK

#define CAPTION_SIDE_INDEX 18
#define CAPTION_SIDE_SHIFT 20
#define CAPTION_SIDE_MASK 0x300000
static inline uint8_t get_caption_side(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[CAPTION_SIDE_INDEX];
	bits &= CAPTION_SIDE_MASK;
	bits >>= CAPTION_SIDE_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef CAPTION_SIDE_INDEX
#undef CAPTION_SIDE_SHIFT
#undef CAPTION_SIDE_MASK

#define CLEAR_INDEX 17
#define CLEAR_SHIFT 17
#define CLEAR_MASK 0xe0000
static inline uint8_t get_clear(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[CLEAR_INDEX];
	bits &= CLEAR_MASK;
	bits >>= CLEAR_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef CLEAR_INDEX
#undef CLEAR_SHIFT
#undef CLEAR_MASK

#define CLIP_INDEX 2
#define CLIP_SHIFT 6
#define CLIP_MASK 0xffffffc0
static inline uint8_t get_clip(
		const css_computed_style *style,
		css_computed_clip_rect *rect)
{
	uint32_t bits = style->i.bits[CLIP_INDEX];
	bits &= CLIP_MASK;
	bits >>= CLIP_SHIFT;

	/*
	26bits: tt tttr rrrr bbbb blll llTR BLyy:
	units: top | right | bottom | left
	opcodes: top | right | bottom | left | type
	*/

	if ((bits & 0x3) == CSS_CLIP_RECT) {
		rect->left_auto = (bits & 0x4);
		rect->bottom_auto = (bits & 0x8);
		rect->right_auto = (bits & 0x10);
		rect->top_auto = (bits & 0x20);

		rect->top = style->i.clip_a;
		rect->tunit = bits & 0x3e00000 >> 21;

		rect->right = style->i.clip_b;
		rect->runit = bits & 0x1f0000 >> 16;

		rect->bottom = style->i.clip_c;
		rect->bunit = (bits & 0xf800) >> 11;

		rect->left = style->i.clip_d;
		rect->lunit = (bits & 0x7c0) >> 6;
	}

	return (bits & 0x3);
}
#undef CLIP_INDEX
#undef CLIP_SHIFT
#undef CLIP_MASK

#define CLIP_PATH_INDEX 19
#define CLIP_PATH_SHIFT 23
#define CLIP_PATH_MASK 0x800000
static inline uint8_t get_clip_path(const css_computed_style *style, lwc_string
		**string)
{
	uint32_t bits = style->i.bits[CLIP_PATH_INDEX];
	bits &= CLIP_PATH_MASK;
	bits >>= CLIP_PATH_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.clip_path;
	
	return (bits & 0x1);
}
#undef CLIP_PATH_INDEX
#undef CLIP_PATH_SHIFT
#undef CLIP_PATH_MASK

#define CLIP_RULE_INDEX 13
#define CLIP_RULE_SHIFT 18
#define CLIP_RULE_MASK 0x3c0000
static inline uint8_t get_clip_rule(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[CLIP_RULE_INDEX];
	bits &= CLIP_RULE_MASK;
	bits >>= CLIP_RULE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef CLIP_RULE_INDEX
#undef CLIP_RULE_SHIFT
#undef CLIP_RULE_MASK

#define COLOR_INDEX 19
#define COLOR_SHIFT 31
#define COLOR_MASK 0x80000000
static inline uint8_t get_color(const css_computed_style *style, css_color
		*color)
{
	uint32_t bits = style->i.bits[COLOR_INDEX];
	bits &= COLOR_MASK;
	bits >>= COLOR_SHIFT;
	
	/* 1bit: t : type */
	*color = style->i.color;
	
	return (bits & 0x1);
}
#undef COLOR_INDEX
#undef COLOR_SHIFT
#undef COLOR_MASK

#define COLUMN_COUNT_INDEX 14
#define COLUMN_COUNT_SHIFT 10
#define COLUMN_COUNT_MASK 0xc00
static inline uint8_t get_column_count(const css_computed_style *style, int32_t
		*integer)
{
	uint32_t bits = style->i.bits[COLUMN_COUNT_INDEX];
	bits &= COLUMN_COUNT_MASK;
	bits >>= COLUMN_COUNT_SHIFT;
	
	/* 2bits: tt : type */
	*integer = style->i.column_count;
	
	return (bits & 0x3);
}
#undef COLUMN_COUNT_INDEX
#undef COLUMN_COUNT_SHIFT
#undef COLUMN_COUNT_MASK

#define COLUMN_FILL_INDEX 18
#define COLUMN_FILL_SHIFT 22
#define COLUMN_FILL_MASK 0xc00000
static inline uint8_t get_column_fill(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[COLUMN_FILL_INDEX];
	bits &= COLUMN_FILL_MASK;
	bits >>= COLUMN_FILL_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef COLUMN_FILL_INDEX
#undef COLUMN_FILL_SHIFT
#undef COLUMN_FILL_MASK

#define COLUMN_GAP_INDEX 7
#define COLUMN_GAP_SHIFT 25
#define COLUMN_GAP_MASK 0xfe000000
static inline uint8_t get_column_gap(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[COLUMN_GAP_INDEX];
	bits &= COLUMN_GAP_MASK;
	bits >>= COLUMN_GAP_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_COLUMN_GAP_SET) {
		*length = style->i.column_gap;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef COLUMN_GAP_INDEX
#undef COLUMN_GAP_SHIFT
#undef COLUMN_GAP_MASK

#define COLUMN_RULE_COLOR_INDEX 14
#define COLUMN_RULE_COLOR_SHIFT 12
#define COLUMN_RULE_COLOR_MASK 0x3000
static inline uint8_t get_column_rule_color(const css_computed_style *style,
		css_color *color)
{
	uint32_t bits = style->i.bits[COLUMN_RULE_COLOR_INDEX];
	bits &= COLUMN_RULE_COLOR_MASK;
	bits >>= COLUMN_RULE_COLOR_SHIFT;
	
	/* 2bits: tt : type */
	*color = style->i.column_rule_color;
	
	return (bits & 0x3);
}
#undef COLUMN_RULE_COLOR_INDEX
#undef COLUMN_RULE_COLOR_SHIFT
#undef COLUMN_RULE_COLOR_MASK

#define COLUMN_RULE_STYLE_INDEX 7
#define COLUMN_RULE_STYLE_SHIFT 0
#define COLUMN_RULE_STYLE_MASK 0xf
static inline uint8_t get_column_rule_style(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[COLUMN_RULE_STYLE_INDEX];
	bits &= COLUMN_RULE_STYLE_MASK;
	bits >>= COLUMN_RULE_STYLE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef COLUMN_RULE_STYLE_INDEX
#undef COLUMN_RULE_STYLE_SHIFT
#undef COLUMN_RULE_STYLE_MASK

#define COLUMN_RULE_WIDTH_INDEX 0
#define COLUMN_RULE_WIDTH_SHIFT 16
#define COLUMN_RULE_WIDTH_MASK 0xff0000
static inline uint8_t get_column_rule_width(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[COLUMN_RULE_WIDTH_INDEX];
	bits &= COLUMN_RULE_WIDTH_MASK;
	bits >>= COLUMN_RULE_WIDTH_SHIFT;
	
	/* 8bits: uuuuuttt : unit | type */
	if ((bits & 0x7) == CSS_COLUMN_RULE_WIDTH_WIDTH) {
		*length = style->i.column_rule_width;
		*unit = bits >> 3;
	}
	
	return (bits & 0x7);
}
#undef COLUMN_RULE_WIDTH_INDEX
#undef COLUMN_RULE_WIDTH_SHIFT
#undef COLUMN_RULE_WIDTH_MASK

#define COLUMN_SPAN_INDEX 14
#define COLUMN_SPAN_SHIFT 20
#define COLUMN_SPAN_MASK 0x300000
static inline uint8_t get_column_span(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[COLUMN_SPAN_INDEX];
	bits &= COLUMN_SPAN_MASK;
	bits >>= COLUMN_SPAN_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef COLUMN_SPAN_INDEX
#undef COLUMN_SPAN_SHIFT
#undef COLUMN_SPAN_MASK

#define COLUMN_WIDTH_INDEX 3
#define COLUMN_WIDTH_SHIFT 4
#define COLUMN_WIDTH_MASK 0x7f0
static inline uint8_t get_column_width(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[COLUMN_WIDTH_INDEX];
	bits &= COLUMN_WIDTH_MASK;
	bits >>= COLUMN_WIDTH_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_COLUMN_WIDTH_SET) {
		*length = style->i.column_width;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef COLUMN_WIDTH_INDEX
#undef COLUMN_WIDTH_SHIFT
#undef COLUMN_WIDTH_MASK

#define COMP_OP_INDEX 12
#define COMP_OP_SHIFT 7
#define COMP_OP_MASK 0xf80
static inline uint8_t get_comp_op(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[COMP_OP_INDEX];
	bits &= COMP_OP_MASK;
	bits >>= COMP_OP_SHIFT;
	
	/* 5bits: ttttt : type */
	
	return (bits & 0x1f);
}
#undef COMP_OP_INDEX
#undef COMP_OP_SHIFT
#undef COMP_OP_MASK

#define CONTENT_INDEX 14
#define CONTENT_SHIFT 30
#define CONTENT_MASK 0xc0000000
static inline uint8_t get_content(const css_computed_style *style, const
		css_computed_content_item **content_item)
{
	uint32_t bits = style->i.bits[CONTENT_INDEX];
	bits &= CONTENT_MASK;
	bits >>= CONTENT_SHIFT;
	
	/* 2bits: tt : type */
	if ((bits & 0x3) == CSS_CONTENT_SET) {
		*content_item = style->content;
	}
	
	return (bits & 0x3);
}
#undef CONTENT_INDEX
#undef CONTENT_SHIFT
#undef CONTENT_MASK

#define COUNTER_INCREMENT_INDEX 18
#define COUNTER_INCREMENT_SHIFT 7
#define COUNTER_INCREMENT_MASK 0x80
static inline uint8_t get_counter_increment(const css_computed_style *style,
		const css_computed_counter **counter_arr)
{
	uint32_t bits = style->i.bits[COUNTER_INCREMENT_INDEX];
	bits &= COUNTER_INCREMENT_MASK;
	bits >>= COUNTER_INCREMENT_SHIFT;
	
	/* 1bit: t : type */
	*counter_arr = style->counter_increment;
	
	return (bits & 0x1);
}
#undef COUNTER_INCREMENT_INDEX
#undef COUNTER_INCREMENT_SHIFT
#undef COUNTER_INCREMENT_MASK

#define COUNTER_RESET_INDEX 16
#define COUNTER_RESET_SHIFT 0
#define COUNTER_RESET_MASK 0x1
static inline uint8_t get_counter_reset(const css_computed_style *style, const
		css_computed_counter **counter_arr)
{
	uint32_t bits = style->i.bits[COUNTER_RESET_INDEX];
	bits &= COUNTER_RESET_MASK;
	bits >>= COUNTER_RESET_SHIFT;
	
	/* 1bit: t : type */
	*counter_arr = style->counter_reset;
	
	return (bits & 0x1);
}
#undef COUNTER_RESET_INDEX
#undef COUNTER_RESET_SHIFT
#undef COUNTER_RESET_MASK

#define CURSOR_INDEX 13
#define CURSOR_SHIFT 27
#define CURSOR_MASK 0xf8000000
static inline uint8_t get_cursor(const css_computed_style *style, lwc_string
		***string_arr)
{
	uint32_t bits = style->i.bits[CURSOR_INDEX];
	bits &= CURSOR_MASK;
	bits >>= CURSOR_SHIFT;
	
	/* 5bits: ttttt : type */
	*string_arr = style->cursor;
	
	return (bits & 0x1f);
}
#undef CURSOR_INDEX
#undef CURSOR_SHIFT
#undef CURSOR_MASK

#define DIRECTION_INDEX 14
#define DIRECTION_SHIFT 8
#define DIRECTION_MASK 0x300
static inline uint8_t get_direction(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[DIRECTION_INDEX];
	bits &= DIRECTION_MASK;
	bits >>= DIRECTION_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef DIRECTION_INDEX
#undef DIRECTION_SHIFT
#undef DIRECTION_MASK

#define DISPLAY_INDEX 12
#define DISPLAY_SHIFT 12
#define DISPLAY_MASK 0x1f000
static inline uint8_t get_display(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[DISPLAY_INDEX];
	bits &= DISPLAY_MASK;
	bits >>= DISPLAY_SHIFT;
	
	/* 5bits: ttttt : type */
	
	return (bits & 0x1f);
}
#undef DISPLAY_INDEX
#undef DISPLAY_SHIFT
#undef DISPLAY_MASK

#define EMPTY_CELLS_INDEX 17
#define EMPTY_CELLS_SHIFT 3
#define EMPTY_CELLS_MASK 0x18
static inline uint8_t get_empty_cells(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[EMPTY_CELLS_INDEX];
	bits &= EMPTY_CELLS_MASK;
	bits >>= EMPTY_CELLS_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef EMPTY_CELLS_INDEX
#undef EMPTY_CELLS_SHIFT
#undef EMPTY_CELLS_MASK

#define ENABLE_BACKGROUND_INDEX 12
#define ENABLE_BACKGROUND_SHIFT 2
#define ENABLE_BACKGROUND_MASK 0x7c
static inline uint8_t get_enable_background(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[ENABLE_BACKGROUND_INDEX];
	bits &= ENABLE_BACKGROUND_MASK;
	bits >>= ENABLE_BACKGROUND_SHIFT;
	
	/* 5bits: ttttt : type */
	
	return (bits & 0x1f);
}
#undef ENABLE_BACKGROUND_INDEX
#undef ENABLE_BACKGROUND_SHIFT
#undef ENABLE_BACKGROUND_MASK

#define FILL_INDEX 18
#define FILL_SHIFT 13
#define FILL_MASK 0x2000
static inline uint8_t get_fill(const css_computed_style *style, lwc_string
		**string)
{
	uint32_t bits = style->i.bits[FILL_INDEX];
	bits &= FILL_MASK;
	bits >>= FILL_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.fill;
	
	return (bits & 0x1);
}
#undef FILL_INDEX
#undef FILL_SHIFT
#undef FILL_MASK

#define FILL_OPACITY_INDEX 18
#define FILL_OPACITY_SHIFT 2
#define FILL_OPACITY_MASK 0x4
static inline uint8_t get_fill_opacity(const css_computed_style *style,
		css_fixed *fixed)
{
	uint32_t bits = style->i.bits[FILL_OPACITY_INDEX];
	bits &= FILL_OPACITY_MASK;
	bits >>= FILL_OPACITY_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_FILL_OPACITY_SET) {
		*fixed = style->i.fill_opacity;
	}
	
	return (bits & 0x1);
}
#undef FILL_OPACITY_INDEX
#undef FILL_OPACITY_SHIFT
#undef FILL_OPACITY_MASK

#define FILTER_INDEX 18
#define FILTER_SHIFT 1
#define FILTER_MASK 0x2
static inline uint8_t get_filter(const css_computed_style *style, lwc_string
		**string)
{
	uint32_t bits = style->i.bits[FILTER_INDEX];
	bits &= FILTER_MASK;
	bits >>= FILTER_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.filter;
	
	return (bits & 0x1);
}
#undef FILTER_INDEX
#undef FILTER_SHIFT
#undef FILTER_MASK

#define FLEX_BASIS_INDEX 4
#define FLEX_BASIS_SHIFT 11
#define FLEX_BASIS_MASK 0x3f800
static inline uint8_t get_flex_basis(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[FLEX_BASIS_INDEX];
	bits &= FLEX_BASIS_MASK;
	bits >>= FLEX_BASIS_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_FLEX_BASIS_SET) {
		*length = style->i.flex_basis;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef FLEX_BASIS_INDEX
#undef FLEX_BASIS_SHIFT
#undef FLEX_BASIS_MASK

#define FLEX_DIRECTION_INDEX 11
#define FLEX_DIRECTION_SHIFT 12
#define FLEX_DIRECTION_MASK 0x7000
static inline uint8_t get_flex_direction(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[FLEX_DIRECTION_INDEX];
	bits &= FLEX_DIRECTION_MASK;
	bits >>= FLEX_DIRECTION_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef FLEX_DIRECTION_INDEX
#undef FLEX_DIRECTION_SHIFT
#undef FLEX_DIRECTION_MASK

#define FLEX_GROW_INDEX 18
#define FLEX_GROW_SHIFT 12
#define FLEX_GROW_MASK 0x1000
static inline uint8_t get_flex_grow(const css_computed_style *style, css_fixed
		*fixed)
{
	uint32_t bits = style->i.bits[FLEX_GROW_INDEX];
	bits &= FLEX_GROW_MASK;
	bits >>= FLEX_GROW_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_FLEX_GROW_SET) {
		*fixed = style->i.flex_grow;
	}
	
	return (bits & 0x1);
}
#undef FLEX_GROW_INDEX
#undef FLEX_GROW_SHIFT
#undef FLEX_GROW_MASK

#define FLEX_SHRINK_INDEX 19
#define FLEX_SHRINK_SHIFT 28
#define FLEX_SHRINK_MASK 0x10000000
static inline uint8_t get_flex_shrink(const css_computed_style *style,
		css_fixed *fixed)
{
	uint32_t bits = style->i.bits[FLEX_SHRINK_INDEX];
	bits &= FLEX_SHRINK_MASK;
	bits >>= FLEX_SHRINK_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_FLEX_SHRINK_SET) {
		*fixed = style->i.flex_shrink;
	}
	
	return (bits & 0x1);
}
#undef FLEX_SHRINK_INDEX
#undef FLEX_SHRINK_SHIFT
#undef FLEX_SHRINK_MASK

#define FLEX_WRAP_INDEX 18
#define FLEX_WRAP_SHIFT 18
#define FLEX_WRAP_MASK 0xc0000
static inline uint8_t get_flex_wrap(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[FLEX_WRAP_INDEX];
	bits &= FLEX_WRAP_MASK;
	bits >>= FLEX_WRAP_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef FLEX_WRAP_INDEX
#undef FLEX_WRAP_SHIFT
#undef FLEX_WRAP_MASK

#define FLOAT_INDEX 18
#define FLOAT_SHIFT 24
#define FLOAT_MASK 0x3000000
static inline uint8_t get_float(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[FLOAT_INDEX];
	bits &= FLOAT_MASK;
	bits >>= FLOAT_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef FLOAT_INDEX
#undef FLOAT_SHIFT
#undef FLOAT_MASK

#define FLOOD_COLOR_INDEX 19
#define FLOOD_COLOR_SHIFT 27
#define FLOOD_COLOR_MASK 0x8000000
static inline uint8_t get_flood_color(const css_computed_style *style,
		css_color *color)
{
	uint32_t bits = style->i.bits[FLOOD_COLOR_INDEX];
	bits &= FLOOD_COLOR_MASK;
	bits >>= FLOOD_COLOR_SHIFT;
	
	/* 1bit: t : type */
	*color = style->i.flood_color;
	
	return (bits & 0x1);
}
#undef FLOOD_COLOR_INDEX
#undef FLOOD_COLOR_SHIFT
#undef FLOOD_COLOR_MASK

#define FLOOD_OPACITY_INDEX 18
#define FLOOD_OPACITY_SHIFT 8
#define FLOOD_OPACITY_MASK 0x100
static inline uint8_t get_flood_opacity(const css_computed_style *style,
		css_fixed *fixed)
{
	uint32_t bits = style->i.bits[FLOOD_OPACITY_INDEX];
	bits &= FLOOD_OPACITY_MASK;
	bits >>= FLOOD_OPACITY_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_FLOOD_OPACITY_SET) {
		*fixed = style->i.flood_opacity;
	}
	
	return (bits & 0x1);
}
#undef FLOOD_OPACITY_INDEX
#undef FLOOD_OPACITY_SHIFT
#undef FLOOD_OPACITY_MASK

#define FONT_FAMILY_INDEX 11
#define FONT_FAMILY_SHIFT 9
#define FONT_FAMILY_MASK 0xe00
static inline uint8_t get_font_family(const css_computed_style *style,
		lwc_string ***string_arr)
{
	uint32_t bits = style->i.bits[FONT_FAMILY_INDEX];
	bits &= FONT_FAMILY_MASK;
	bits >>= FONT_FAMILY_SHIFT;
	
	/* 3bits: ttt : type */
	*string_arr = style->font_family;
	
	return (bits & 0x7);
}
#undef FONT_FAMILY_INDEX
#undef FONT_FAMILY_SHIFT
#undef FONT_FAMILY_MASK

#define FONT_SIZE_INDEX 1
#define FONT_SIZE_SHIFT 23
#define FONT_SIZE_MASK 0xff800000
static inline uint8_t get_font_size(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[FONT_SIZE_INDEX];
	bits &= FONT_SIZE_MASK;
	bits >>= FONT_SIZE_SHIFT;
	
	/* 9bits: uuuuutttt : unit | type */
	if ((bits & 0xf) == CSS_FONT_SIZE_DIMENSION) {
		*length = style->i.font_size;
		*unit = bits >> 4;
	}
	
	return (bits & 0xf);
}
#undef FONT_SIZE_INDEX
#undef FONT_SIZE_SHIFT
#undef FONT_SIZE_MASK

#define FONT_STRETCH_INDEX 12
#define FONT_STRETCH_SHIFT 27
#define FONT_STRETCH_MASK 0xf8000000
static inline uint8_t get_font_stretch(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[FONT_STRETCH_INDEX];
	bits &= FONT_STRETCH_MASK;
	bits >>= FONT_STRETCH_SHIFT;
	
	/* 5bits: ttttt : type */
	
	return (bits & 0x1f);
}
#undef FONT_STRETCH_INDEX
#undef FONT_STRETCH_SHIFT
#undef FONT_STRETCH_MASK

#define FONT_STYLE_INDEX 18
#define FONT_STYLE_SHIFT 14
#define FONT_STYLE_MASK 0xc000
static inline uint8_t get_font_style(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[FONT_STYLE_INDEX];
	bits &= FONT_STYLE_MASK;
	bits >>= FONT_STYLE_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef FONT_STYLE_INDEX
#undef FONT_STYLE_SHIFT
#undef FONT_STYLE_MASK

#define FONT_VARIANT_INDEX 14
#define FONT_VARIANT_SHIFT 14
#define FONT_VARIANT_MASK 0xc000
static inline uint8_t get_font_variant(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[FONT_VARIANT_INDEX];
	bits &= FONT_VARIANT_MASK;
	bits >>= FONT_VARIANT_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef FONT_VARIANT_INDEX
#undef FONT_VARIANT_SHIFT
#undef FONT_VARIANT_MASK

#define FONT_WEIGHT_INDEX 10
#define FONT_WEIGHT_SHIFT 0
#define FONT_WEIGHT_MASK 0xf
static inline uint8_t get_font_weight(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[FONT_WEIGHT_INDEX];
	bits &= FONT_WEIGHT_MASK;
	bits >>= FONT_WEIGHT_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef FONT_WEIGHT_INDEX
#undef FONT_WEIGHT_SHIFT
#undef FONT_WEIGHT_MASK

#define GRID_COLUMN_END_INDEX 16
#define GRID_COLUMN_END_SHIFT 25
#define GRID_COLUMN_END_MASK 0xfe000000
static inline uint8_t get_grid_column_end(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[GRID_COLUMN_END_INDEX];
	bits &= GRID_COLUMN_END_MASK;
	bits >>= GRID_COLUMN_END_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_GRID_COLUMN_END_SET) {
		*length = style->i.grid_column_end;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef GRID_COLUMN_END_INDEX
#undef GRID_COLUMN_END_SHIFT
#undef GRID_COLUMN_END_MASK

#define GRID_COLUMN_START_INDEX 4
#define GRID_COLUMN_START_SHIFT 25
#define GRID_COLUMN_START_MASK 0xfe000000
static inline uint8_t get_grid_column_start(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[GRID_COLUMN_START_INDEX];
	bits &= GRID_COLUMN_START_MASK;
	bits >>= GRID_COLUMN_START_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_GRID_COLUMN_START_SET) {
		*length = style->i.grid_column_start;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef GRID_COLUMN_START_INDEX
#undef GRID_COLUMN_START_SHIFT
#undef GRID_COLUMN_START_MASK

#define GRID_ROW_END_INDEX 3
#define GRID_ROW_END_SHIFT 25
#define GRID_ROW_END_MASK 0xfe000000
static inline uint8_t get_grid_row_end(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[GRID_ROW_END_INDEX];
	bits &= GRID_ROW_END_MASK;
	bits >>= GRID_ROW_END_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_GRID_ROW_END_SET) {
		*length = style->i.grid_row_end;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef GRID_ROW_END_INDEX
#undef GRID_ROW_END_SHIFT
#undef GRID_ROW_END_MASK

#define GRID_ROW_START_INDEX 6
#define GRID_ROW_START_SHIFT 25
#define GRID_ROW_START_MASK 0xfe000000
static inline uint8_t get_grid_row_start(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[GRID_ROW_START_INDEX];
	bits &= GRID_ROW_START_MASK;
	bits >>= GRID_ROW_START_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_GRID_ROW_START_SET) {
		*length = style->i.grid_row_start;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef GRID_ROW_START_INDEX
#undef GRID_ROW_START_SHIFT
#undef GRID_ROW_START_MASK

#define GRID_TEMPLATE_COLUMNS_INDEX 17
#define GRID_TEMPLATE_COLUMNS_SHIFT 9
#define GRID_TEMPLATE_COLUMNS_MASK 0x600
static inline uint8_t get_grid_template_columns(const css_computed_style *style, int32_t *size,
    css_fixed **values, css_unit **units)
{
    *size = style->i.grid_template_columns_size;
    if (*size > 0)
    {
        css_fixed* v = (css_fixed*) malloc(*size * sizeof(css_fixed));
        css_unit* u = (css_unit*) malloc(*size * sizeof(css_unit));
        for (int i = 0; i < *size; i++)
        {
            v[i] = style->i.grid_template_columns[i];
            u[i] = style->i.grid_template_columns_unit[i];
        }
        *values = v;
        *units = u;
    }
	return style->i.grid_template_columns_type;
}
#undef GRID_TEMPLATE_COLUMNS_INDEX
#undef GRID_TEMPLATE_COLUMNS_SHIFT
#undef GRID_TEMPLATE_COLUMNS_MASK

#define GRID_TEMPLATE_ROWS_INDEX 14
#define GRID_TEMPLATE_ROWS_SHIFT 28
#define GRID_TEMPLATE_ROWS_MASK 0x30000000
static inline uint8_t get_grid_template_rows(const css_computed_style *style, int32_t *size,
    css_fixed **values, css_unit **units)
{
    *size = style->i.grid_template_rows_size;
    if (*size > 0)
    {
        css_fixed* v = (css_fixed*) malloc(*size * sizeof(css_fixed));
        css_unit* u = (css_unit*) malloc(*size * sizeof(css_unit));
        for (int i = 0; i < *size; i++)
        {
            v[i] = style->i.grid_template_rows[i];
            u[i] = style->i.grid_template_rows_unit[i];
        }
        *values = v;
        *units = u;
    }
	return style->i.grid_template_rows_type;
}
#undef GRID_TEMPLATE_ROWS_INDEX
#undef GRID_TEMPLATE_ROWS_SHIFT
#undef GRID_TEMPLATE_ROWS_MASK

#define HEIGHT_INDEX 3
#define HEIGHT_SHIFT 18
#define HEIGHT_MASK 0x1fc0000
static inline uint8_t get_height(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[HEIGHT_INDEX];
	bits &= HEIGHT_MASK;
	bits >>= HEIGHT_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_HEIGHT_SET) {
		*length = style->i.height;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef HEIGHT_INDEX
#undef HEIGHT_SHIFT
#undef HEIGHT_MASK

#define JUSTIFY_CONTENT_INDEX 17
#define JUSTIFY_CONTENT_SHIFT 14
#define JUSTIFY_CONTENT_MASK 0x1c000
static inline uint8_t get_justify_content(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[JUSTIFY_CONTENT_INDEX];
	bits &= JUSTIFY_CONTENT_MASK;
	bits >>= JUSTIFY_CONTENT_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef JUSTIFY_CONTENT_INDEX
#undef JUSTIFY_CONTENT_SHIFT
#undef JUSTIFY_CONTENT_MASK

#define LEFT_INDEX 8
#define LEFT_SHIFT 18
#define LEFT_MASK 0x1fc0000
static inline uint8_t get_left(
		const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[LEFT_INDEX];
	bits &= LEFT_MASK;
	bits >>= LEFT_SHIFT;

	/* 7bits: uuuuutt : units | type */
	if ((bits & 0x3) == CSS_LEFT_SET) {
		*length = style->i.left;
		*unit = bits >> 2;
	}

	return (bits & 0x3);
}
static inline uint8_t get_left_bits(
		const css_computed_style *style)
{
	uint32_t bits = style->i.bits[LEFT_INDEX];
	bits &= LEFT_MASK;
	bits >>= LEFT_SHIFT;

	/* 7bits: uuuuutt : units | type */
	return bits;
}
#undef LEFT_INDEX
#undef LEFT_SHIFT
#undef LEFT_MASK

#define LETTER_SPACING_INDEX 5
#define LETTER_SPACING_SHIFT 25
#define LETTER_SPACING_MASK 0xfe000000
static inline uint8_t get_letter_spacing(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[LETTER_SPACING_INDEX];
	bits &= LETTER_SPACING_MASK;
	bits >>= LETTER_SPACING_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_LETTER_SPACING_SET) {
		*length = style->i.letter_spacing;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef LETTER_SPACING_INDEX
#undef LETTER_SPACING_SHIFT
#undef LETTER_SPACING_MASK

#define LINE_HEIGHT_INDEX 7
#define LINE_HEIGHT_SHIFT 11
#define LINE_HEIGHT_MASK 0x3f800
static inline uint8_t get_line_height(
		const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[LINE_HEIGHT_INDEX];
	bits &= LINE_HEIGHT_MASK;
	bits >>= LINE_HEIGHT_SHIFT;

	/* 7bits: uuuuutt : units | type */
	if ((bits & 0x3) == CSS_LINE_HEIGHT_NUMBER ||
			(bits & 0x3) == CSS_LINE_HEIGHT_DIMENSION) {
		*length = style->i.line_height;
	}

	if ((bits & 0x3) == CSS_LINE_HEIGHT_DIMENSION) {
		*unit = bits >> 2;
	}

	return (bits & 0x3);
}
#undef LINE_HEIGHT_INDEX
#undef LINE_HEIGHT_SHIFT
#undef LINE_HEIGHT_MASK

#define LIST_STYLE_IMAGE_INDEX 18
#define LIST_STYLE_IMAGE_SHIFT 11
#define LIST_STYLE_IMAGE_MASK 0x800
static inline uint8_t get_list_style_image(const css_computed_style *style,
		lwc_string **string)
{
	uint32_t bits = style->i.bits[LIST_STYLE_IMAGE_INDEX];
	bits &= LIST_STYLE_IMAGE_MASK;
	bits >>= LIST_STYLE_IMAGE_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.list_style_image;
	
	return (bits & 0x1);
}
#undef LIST_STYLE_IMAGE_INDEX
#undef LIST_STYLE_IMAGE_SHIFT
#undef LIST_STYLE_IMAGE_MASK

#define LIST_STYLE_POSITION_INDEX 14
#define LIST_STYLE_POSITION_SHIFT 18
#define LIST_STYLE_POSITION_MASK 0xc0000
static inline uint8_t get_list_style_position(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[LIST_STYLE_POSITION_INDEX];
	bits &= LIST_STYLE_POSITION_MASK;
	bits >>= LIST_STYLE_POSITION_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef LIST_STYLE_POSITION_INDEX
#undef LIST_STYLE_POSITION_SHIFT
#undef LIST_STYLE_POSITION_MASK

#define LIST_STYLE_TYPE_INDEX 11
#define LIST_STYLE_TYPE_SHIFT 28
#define LIST_STYLE_TYPE_MASK 0xf0000000
static inline uint8_t get_list_style_type(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[LIST_STYLE_TYPE_INDEX];
	bits &= LIST_STYLE_TYPE_MASK;
	bits >>= LIST_STYLE_TYPE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef LIST_STYLE_TYPE_INDEX
#undef LIST_STYLE_TYPE_SHIFT
#undef LIST_STYLE_TYPE_MASK

#define MARGIN_BOTTOM_INDEX 4
#define MARGIN_BOTTOM_SHIFT 4
#define MARGIN_BOTTOM_MASK 0x7f0
static inline uint8_t get_margin_bottom(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[MARGIN_BOTTOM_INDEX];
	bits &= MARGIN_BOTTOM_MASK;
	bits >>= MARGIN_BOTTOM_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_MARGIN_SET) {
		*length = style->i.margin_bottom;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef MARGIN_BOTTOM_INDEX
#undef MARGIN_BOTTOM_SHIFT
#undef MARGIN_BOTTOM_MASK

#define MARGIN_LEFT_INDEX 7
#define MARGIN_LEFT_SHIFT 18
#define MARGIN_LEFT_MASK 0x1fc0000
static inline uint8_t get_margin_left(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[MARGIN_LEFT_INDEX];
	bits &= MARGIN_LEFT_MASK;
	bits >>= MARGIN_LEFT_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_MARGIN_SET) {
		*length = style->i.margin_left;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef MARGIN_LEFT_INDEX
#undef MARGIN_LEFT_SHIFT
#undef MARGIN_LEFT_MASK

#define MARGIN_RIGHT_INDEX 9
#define MARGIN_RIGHT_SHIFT 25
#define MARGIN_RIGHT_MASK 0xfe000000
static inline uint8_t get_margin_right(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[MARGIN_RIGHT_INDEX];
	bits &= MARGIN_RIGHT_MASK;
	bits >>= MARGIN_RIGHT_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_MARGIN_SET) {
		*length = style->i.margin_right;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef MARGIN_RIGHT_INDEX
#undef MARGIN_RIGHT_SHIFT
#undef MARGIN_RIGHT_MASK

#define MARGIN_TOP_INDEX 5
#define MARGIN_TOP_SHIFT 4
#define MARGIN_TOP_MASK 0x7f0
static inline uint8_t get_margin_top(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[MARGIN_TOP_INDEX];
	bits &= MARGIN_TOP_MASK;
	bits >>= MARGIN_TOP_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_MARGIN_SET) {
		*length = style->i.margin_top;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef MARGIN_TOP_INDEX
#undef MARGIN_TOP_SHIFT
#undef MARGIN_TOP_MASK

#define MARKER_END_INDEX 18
#define MARKER_END_SHIFT 10
#define MARKER_END_MASK 0x400
static inline uint8_t get_marker_end(const css_computed_style *style,
		lwc_string **string)
{
	uint32_t bits = style->i.bits[MARKER_END_INDEX];
	bits &= MARKER_END_MASK;
	bits >>= MARKER_END_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.marker_end;
	
	return (bits & 0x1);
}
#undef MARKER_END_INDEX
#undef MARKER_END_SHIFT
#undef MARKER_END_MASK

#define MARKER_MID_INDEX 18
#define MARKER_MID_SHIFT 0
#define MARKER_MID_MASK 0x1
static inline uint8_t get_marker_mid(const css_computed_style *style,
		lwc_string **string)
{
	uint32_t bits = style->i.bits[MARKER_MID_INDEX];
	bits &= MARKER_MID_MASK;
	bits >>= MARKER_MID_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.marker_mid;
	
	return (bits & 0x1);
}
#undef MARKER_MID_INDEX
#undef MARKER_MID_SHIFT
#undef MARKER_MID_MASK

#define MARKER_START_INDEX 19
#define MARKER_START_SHIFT 25
#define MARKER_START_MASK 0x2000000
static inline uint8_t get_marker_start(const css_computed_style *style,
		lwc_string **string)
{
	uint32_t bits = style->i.bits[MARKER_START_INDEX];
	bits &= MARKER_START_MASK;
	bits >>= MARKER_START_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.marker_start;
	
	return (bits & 0x1);
}
#undef MARKER_START_INDEX
#undef MARKER_START_SHIFT
#undef MARKER_START_MASK

#define MASK_INDEX 19
#define MASK_SHIFT 30
#define MASK_MASK 0x40000000
static inline uint8_t get_mask(const css_computed_style *style, lwc_string
		**string)
{
	uint32_t bits = style->i.bits[MASK_INDEX];
	bits &= MASK_MASK;
	bits >>= MASK_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.mask;
	
	return (bits & 0x1);
}
#undef MASK_INDEX
#undef MASK_SHIFT
#undef MASK_MASK

#define MAX_HEIGHT_INDEX 9
#define MAX_HEIGHT_SHIFT 11
#define MAX_HEIGHT_MASK 0x3f800
static inline uint8_t get_max_height(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[MAX_HEIGHT_INDEX];
	bits &= MAX_HEIGHT_MASK;
	bits >>= MAX_HEIGHT_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_MAX_HEIGHT_SET) {
		*length = style->i.max_height;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef MAX_HEIGHT_INDEX
#undef MAX_HEIGHT_SHIFT
#undef MAX_HEIGHT_MASK

#define MAX_WIDTH_INDEX 6
#define MAX_WIDTH_SHIFT 4
#define MAX_WIDTH_MASK 0x7f0
static inline uint8_t get_max_width(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[MAX_WIDTH_INDEX];
	bits &= MAX_WIDTH_MASK;
	bits >>= MAX_WIDTH_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_MAX_WIDTH_SET) {
		*length = style->i.max_width;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef MAX_WIDTH_INDEX
#undef MAX_WIDTH_SHIFT
#undef MAX_WIDTH_MASK

#define MIN_HEIGHT_INDEX 7
#define MIN_HEIGHT_SHIFT 4
#define MIN_HEIGHT_MASK 0x7f0
static inline uint8_t get_min_height(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[MIN_HEIGHT_INDEX];
	bits &= MIN_HEIGHT_MASK;
	bits >>= MIN_HEIGHT_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_MIN_HEIGHT_SET) {
		*length = style->i.min_height;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef MIN_HEIGHT_INDEX
#undef MIN_HEIGHT_SHIFT
#undef MIN_HEIGHT_MASK

#define MIN_WIDTH_INDEX 8
#define MIN_WIDTH_SHIFT 4
#define MIN_WIDTH_MASK 0x7f0
static inline uint8_t get_min_width(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[MIN_WIDTH_INDEX];
	bits &= MIN_WIDTH_MASK;
	bits >>= MIN_WIDTH_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_MIN_WIDTH_SET) {
		*length = style->i.min_width;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef MIN_WIDTH_INDEX
#undef MIN_WIDTH_SHIFT
#undef MIN_WIDTH_MASK

#define OPACITY_INDEX 18
#define OPACITY_SHIFT 3
#define OPACITY_MASK 0x8
static inline uint8_t get_opacity(const css_computed_style *style, css_fixed
		*fixed)
{
	uint32_t bits = style->i.bits[OPACITY_INDEX];
	bits &= OPACITY_MASK;
	bits >>= OPACITY_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_OPACITY_SET) {
		*fixed = style->i.opacity;
	}
	
	return (bits & 0x1);
}
#undef OPACITY_INDEX
#undef OPACITY_SHIFT
#undef OPACITY_MASK

#define ORDER_INDEX 19
#define ORDER_SHIFT 22
#define ORDER_MASK 0x400000
static inline uint8_t get_order(const css_computed_style *style, int32_t
		*integer)
{
	uint32_t bits = style->i.bits[ORDER_INDEX];
	bits &= ORDER_MASK;
	bits >>= ORDER_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_ORDER_SET) {
		*integer = style->i.order;
	}
	
	return (bits & 0x1);
}
#undef ORDER_INDEX
#undef ORDER_SHIFT
#undef ORDER_MASK

#define ORPHANS_INDEX 18
#define ORPHANS_SHIFT 6
#define ORPHANS_MASK 0x40
static inline uint8_t get_orphans(const css_computed_style *style, int32_t
		*integer)
{
	uint32_t bits = style->i.bits[ORPHANS_INDEX];
	bits &= ORPHANS_MASK;
	bits >>= ORPHANS_SHIFT;
	
	/* 1bit: t : type */
	*integer = style->i.orphans;
	
	return (bits & 0x1);
}
#undef ORPHANS_INDEX
#undef ORPHANS_SHIFT
#undef ORPHANS_MASK

#define OUTLINE_COLOR_INDEX 17
#define OUTLINE_COLOR_SHIFT 7
#define OUTLINE_COLOR_MASK 0x180
static inline uint8_t get_outline_color(const css_computed_style *style,
		css_color *color)
{
	uint32_t bits = style->i.bits[OUTLINE_COLOR_INDEX];
	bits &= OUTLINE_COLOR_MASK;
	bits >>= OUTLINE_COLOR_SHIFT;
	
	/* 2bits: tt : type */
	if ((bits & 0x3) == CSS_OUTLINE_COLOR_COLOR) {
		*color = style->i.outline_color;
	}
	
	return (bits & 0x3);
}
#undef OUTLINE_COLOR_INDEX
#undef OUTLINE_COLOR_SHIFT
#undef OUTLINE_COLOR_MASK

#define OUTLINE_STYLE_INDEX 13
#define OUTLINE_STYLE_SHIFT 10
#define OUTLINE_STYLE_MASK 0x3c00
static inline uint8_t get_outline_style(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[OUTLINE_STYLE_INDEX];
	bits &= OUTLINE_STYLE_MASK;
	bits >>= OUTLINE_STYLE_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef OUTLINE_STYLE_INDEX
#undef OUTLINE_STYLE_SHIFT
#undef OUTLINE_STYLE_MASK

#define OUTLINE_WIDTH_INDEX 1
#define OUTLINE_WIDTH_SHIFT 7
#define OUTLINE_WIDTH_MASK 0x7f80
static inline uint8_t get_outline_width(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[OUTLINE_WIDTH_INDEX];
	bits &= OUTLINE_WIDTH_MASK;
	bits >>= OUTLINE_WIDTH_SHIFT;
	
	/* 8bits: uuuuuttt : unit | type */
	if ((bits & 0x7) == CSS_OUTLINE_WIDTH_WIDTH) {
		*length = style->i.outline_width;
		*unit = bits >> 3;
	}
	
	return (bits & 0x7);
}
#undef OUTLINE_WIDTH_INDEX
#undef OUTLINE_WIDTH_SHIFT
#undef OUTLINE_WIDTH_MASK

#define OVERFLOW_X_INDEX 11
#define OVERFLOW_X_SHIFT 6
#define OVERFLOW_X_MASK 0x1c0
static inline uint8_t get_overflow_x(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[OVERFLOW_X_INDEX];
	bits &= OVERFLOW_X_MASK;
	bits >>= OVERFLOW_X_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef OVERFLOW_X_INDEX
#undef OVERFLOW_X_SHIFT
#undef OVERFLOW_X_MASK

#define OVERFLOW_Y_INDEX 17
#define OVERFLOW_Y_SHIFT 26
#define OVERFLOW_Y_MASK 0x1c000000
static inline uint8_t get_overflow_y(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[OVERFLOW_Y_INDEX];
	bits &= OVERFLOW_Y_MASK;
	bits >>= OVERFLOW_Y_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef OVERFLOW_Y_INDEX
#undef OVERFLOW_Y_SHIFT
#undef OVERFLOW_Y_MASK

#define PADDING_BOTTOM_INDEX 16
#define PADDING_BOTTOM_SHIFT 1
#define PADDING_BOTTOM_MASK 0x7e
static inline uint8_t get_padding_bottom(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[PADDING_BOTTOM_INDEX];
	bits &= PADDING_BOTTOM_MASK;
	bits >>= PADDING_BOTTOM_SHIFT;
	
	/* 6bits: uuuuut : unit | type */
	if ((bits & 0x1) == CSS_PADDING_SET) {
		*length = style->i.padding_bottom;
		*unit = bits >> 1;
	}
	
	return (bits & 0x1);
}
#undef PADDING_BOTTOM_INDEX
#undef PADDING_BOTTOM_SHIFT
#undef PADDING_BOTTOM_MASK

#define PADDING_LEFT_INDEX 16
#define PADDING_LEFT_SHIFT 13
#define PADDING_LEFT_MASK 0x7e000
static inline uint8_t get_padding_left(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[PADDING_LEFT_INDEX];
	bits &= PADDING_LEFT_MASK;
	bits >>= PADDING_LEFT_SHIFT;
	
	/* 6bits: uuuuut : unit | type */
	if ((bits & 0x1) == CSS_PADDING_SET) {
		*length = style->i.padding_left;
		*unit = bits >> 1;
	}
	
	return (bits & 0x1);
}
#undef PADDING_LEFT_INDEX
#undef PADDING_LEFT_SHIFT
#undef PADDING_LEFT_MASK

#define PADDING_RIGHT_INDEX 2
#define PADDING_RIGHT_SHIFT 0
#define PADDING_RIGHT_MASK 0x3f
static inline uint8_t get_padding_right(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[PADDING_RIGHT_INDEX];
	bits &= PADDING_RIGHT_MASK;
	bits >>= PADDING_RIGHT_SHIFT;
	
	/* 6bits: uuuuut : unit | type */
	if ((bits & 0x1) == CSS_PADDING_SET) {
		*length = style->i.padding_right;
		*unit = bits >> 1;
	}
	
	return (bits & 0x1);
}
#undef PADDING_RIGHT_INDEX
#undef PADDING_RIGHT_SHIFT
#undef PADDING_RIGHT_MASK

#define PADDING_TOP_INDEX 16
#define PADDING_TOP_SHIFT 7
#define PADDING_TOP_MASK 0x1f80
static inline uint8_t get_padding_top(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[PADDING_TOP_INDEX];
	bits &= PADDING_TOP_MASK;
	bits >>= PADDING_TOP_SHIFT;
	
	/* 6bits: uuuuut : unit | type */
	if ((bits & 0x1) == CSS_PADDING_SET) {
		*length = style->i.padding_top;
		*unit = bits >> 1;
	}
	
	return (bits & 0x1);
}
#undef PADDING_TOP_INDEX
#undef PADDING_TOP_SHIFT
#undef PADDING_TOP_MASK

#define PAGE_BREAK_AFTER_INDEX 11
#define PAGE_BREAK_AFTER_SHIFT 18
#define PAGE_BREAK_AFTER_MASK 0x1c0000
static inline uint8_t get_page_break_after(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[PAGE_BREAK_AFTER_INDEX];
	bits &= PAGE_BREAK_AFTER_MASK;
	bits >>= PAGE_BREAK_AFTER_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef PAGE_BREAK_AFTER_INDEX
#undef PAGE_BREAK_AFTER_SHIFT
#undef PAGE_BREAK_AFTER_MASK

#define PAGE_BREAK_BEFORE_INDEX 11
#define PAGE_BREAK_BEFORE_SHIFT 0
#define PAGE_BREAK_BEFORE_MASK 0x7
static inline uint8_t get_page_break_before(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[PAGE_BREAK_BEFORE_INDEX];
	bits &= PAGE_BREAK_BEFORE_MASK;
	bits >>= PAGE_BREAK_BEFORE_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef PAGE_BREAK_BEFORE_INDEX
#undef PAGE_BREAK_BEFORE_SHIFT
#undef PAGE_BREAK_BEFORE_MASK

#define PAGE_BREAK_INSIDE_INDEX 17
#define PAGE_BREAK_INSIDE_SHIFT 1
#define PAGE_BREAK_INSIDE_MASK 0x6
static inline uint8_t get_page_break_inside(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[PAGE_BREAK_INSIDE_INDEX];
	bits &= PAGE_BREAK_INSIDE_MASK;
	bits >>= PAGE_BREAK_INSIDE_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef PAGE_BREAK_INSIDE_INDEX
#undef PAGE_BREAK_INSIDE_SHIFT
#undef PAGE_BREAK_INSIDE_MASK

#define POSITION_INDEX 17
#define POSITION_SHIFT 11
#define POSITION_MASK 0x3800
static inline uint8_t get_position(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[POSITION_INDEX];
	bits &= POSITION_MASK;
	bits >>= POSITION_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef POSITION_INDEX
#undef POSITION_SHIFT
#undef POSITION_MASK

#define QUOTES_INDEX 18
#define QUOTES_SHIFT 4
#define QUOTES_MASK 0x10
static inline uint8_t get_quotes(const css_computed_style *style, lwc_string
		***string_arr)
{
	uint32_t bits = style->i.bits[QUOTES_INDEX];
	bits &= QUOTES_MASK;
	bits >>= QUOTES_SHIFT;
	
	/* 1bit: t : type */
	*string_arr = style->quotes;
	
	return (bits & 0x1);
}
#undef QUOTES_INDEX
#undef QUOTES_SHIFT
#undef QUOTES_MASK

#define RIGHT_INDEX 3
#define RIGHT_SHIFT 11
#define RIGHT_MASK 0x3f800
static inline uint8_t get_right(
		const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[RIGHT_INDEX];
	bits &= RIGHT_MASK;
	bits >>= RIGHT_SHIFT;

	/* 7bits: uuuuutt : units | type */
	if ((bits & 0x3) == CSS_RIGHT_SET) {
		*length = style->i.right;
		*unit = bits >> 2;
	}

	return (bits & 0x3);
}
static inline uint8_t get_right_bits(
		const css_computed_style *style)
{
	uint32_t bits = style->i.bits[RIGHT_INDEX];
	bits &= RIGHT_MASK;
	bits >>= RIGHT_SHIFT;

	/* 7bits: uuuuutt : units | type */
	return bits;
}
#undef RIGHT_INDEX
#undef RIGHT_SHIFT
#undef RIGHT_MASK

#define SHAPE_RENDERING_INDEX 13
#define SHAPE_RENDERING_SHIFT 22
#define SHAPE_RENDERING_MASK 0x7c00000
static inline uint8_t get_shape_rendering(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[SHAPE_RENDERING_INDEX];
	bits &= SHAPE_RENDERING_MASK;
	bits >>= SHAPE_RENDERING_SHIFT;
	
	/* 5bits: ttttt : type */
	
	return (bits & 0x1f);
}
#undef SHAPE_RENDERING_INDEX
#undef SHAPE_RENDERING_SHIFT
#undef SHAPE_RENDERING_MASK

#define STOP_COLOR_INDEX 19
#define STOP_COLOR_SHIFT 24
#define STOP_COLOR_MASK 0x1000000
static inline uint8_t get_stop_color(const css_computed_style *style, css_color
		*color)
{
	uint32_t bits = style->i.bits[STOP_COLOR_INDEX];
	bits &= STOP_COLOR_MASK;
	bits >>= STOP_COLOR_SHIFT;
	
	/* 1bit: t : type */
	*color = style->i.stop_color;
	
	return (bits & 0x1);
}
#undef STOP_COLOR_INDEX
#undef STOP_COLOR_SHIFT
#undef STOP_COLOR_MASK

#define STOP_OPACITY_INDEX 18
#define STOP_OPACITY_SHIFT 9
#define STOP_OPACITY_MASK 0x200
static inline uint8_t get_stop_opacity(const css_computed_style *style,
		css_fixed *fixed)
{
	uint32_t bits = style->i.bits[STOP_OPACITY_INDEX];
	bits &= STOP_OPACITY_MASK;
	bits >>= STOP_OPACITY_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_FLOOD_OPACITY_SET) {
		*fixed = style->i.stop_opacity;
	}
	
	return (bits & 0x1);
}
#undef STOP_OPACITY_INDEX
#undef STOP_OPACITY_SHIFT
#undef STOP_OPACITY_MASK

#define STROKE_INDEX 19
#define STROKE_SHIFT 29
#define STROKE_MASK 0x20000000
static inline uint8_t get_stroke(const css_computed_style *style, lwc_string
		**string)
{
	uint32_t bits = style->i.bits[STROKE_INDEX];
	bits &= STROKE_MASK;
	bits >>= STROKE_SHIFT;
	
	/* 1bit: t : type */
	*string = style->i.stroke;
	
	return (bits & 0x1);
}
#undef STROKE_INDEX
#undef STROKE_SHIFT
#undef STROKE_MASK

#define STROKE_DASHARRAY_INDEX 14
#define STROKE_DASHARRAY_SHIFT 4
#define STROKE_DASHARRAY_MASK 0x30
static inline uint8_t get_stroke_dasharray(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[STROKE_DASHARRAY_INDEX];
	bits &= STROKE_DASHARRAY_MASK;
	bits >>= STROKE_DASHARRAY_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef STROKE_DASHARRAY_INDEX
#undef STROKE_DASHARRAY_SHIFT
#undef STROKE_DASHARRAY_MASK

#define STROKE_DASHOFFSET_INDEX 4
#define STROKE_DASHOFFSET_SHIFT 18
#define STROKE_DASHOFFSET_MASK 0x1fc0000
static inline uint8_t get_stroke_dashoffset(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[STROKE_DASHOFFSET_INDEX];
	bits &= STROKE_DASHOFFSET_MASK;
	bits >>= STROKE_DASHOFFSET_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_STROKE_DASHOFFSET_SET) {
		*length = style->i.stroke_dashoffset;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef STROKE_DASHOFFSET_INDEX
#undef STROKE_DASHOFFSET_SHIFT
#undef STROKE_DASHOFFSET_MASK

#define STROKE_LINECAP_INDEX 10
#define STROKE_LINECAP_SHIFT 28
#define STROKE_LINECAP_MASK 0xf0000000
static inline uint8_t get_stroke_linecap(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[STROKE_LINECAP_INDEX];
	bits &= STROKE_LINECAP_MASK;
	bits >>= STROKE_LINECAP_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef STROKE_LINECAP_INDEX
#undef STROKE_LINECAP_SHIFT
#undef STROKE_LINECAP_MASK

#define STROKE_LINEJOIN_INDEX 10
#define STROKE_LINEJOIN_SHIFT 20
#define STROKE_LINEJOIN_MASK 0xf00000
static inline uint8_t get_stroke_linejoin(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[STROKE_LINEJOIN_INDEX];
	bits &= STROKE_LINEJOIN_MASK;
	bits >>= STROKE_LINEJOIN_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef STROKE_LINEJOIN_INDEX
#undef STROKE_LINEJOIN_SHIFT
#undef STROKE_LINEJOIN_MASK

#define STROKE_MITERLIMIT_INDEX 19
#define STROKE_MITERLIMIT_SHIFT 26
#define STROKE_MITERLIMIT_MASK 0x4000000
static inline uint8_t get_stroke_miterlimit(const css_computed_style *style,
		css_fixed *fixed)
{
	uint32_t bits = style->i.bits[STROKE_MITERLIMIT_INDEX];
	bits &= STROKE_MITERLIMIT_MASK;
	bits >>= STROKE_MITERLIMIT_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_STROKE_MITERLIMIT_SET) {
		*fixed = style->i.stroke_miterlimit;
	}
	
	return (bits & 0x1);
}
#undef STROKE_MITERLIMIT_INDEX
#undef STROKE_MITERLIMIT_SHIFT
#undef STROKE_MITERLIMIT_MASK

#define STROKE_OPACITY_INDEX 18
#define STROKE_OPACITY_SHIFT 5
#define STROKE_OPACITY_MASK 0x20
static inline uint8_t get_stroke_opacity(const css_computed_style *style,
		css_fixed *fixed)
{
	uint32_t bits = style->i.bits[STROKE_OPACITY_INDEX];
	bits &= STROKE_OPACITY_MASK;
	bits >>= STROKE_OPACITY_SHIFT;
	
	/* 1bit: t : type */
	if ((bits & 0x1) == CSS_STROKE_OPACITY_SET) {
		*fixed = style->i.stroke_opacity;
	}
	
	return (bits & 0x1);
}
#undef STROKE_OPACITY_INDEX
#undef STROKE_OPACITY_SHIFT
#undef STROKE_OPACITY_MASK

#define STROKE_WIDTH_INDEX 9
#define STROKE_WIDTH_SHIFT 18
#define STROKE_WIDTH_MASK 0x1fc0000
static inline uint8_t get_stroke_width(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[STROKE_WIDTH_INDEX];
	bits &= STROKE_WIDTH_MASK;
	bits >>= STROKE_WIDTH_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_STROKE_WIDTH_SET) {
		*length = style->i.stroke_width;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef STROKE_WIDTH_INDEX
#undef STROKE_WIDTH_SHIFT
#undef STROKE_WIDTH_MASK

#define TABLE_LAYOUT_INDEX 13
#define TABLE_LAYOUT_SHIFT 0
#define TABLE_LAYOUT_MASK 0x3
static inline uint8_t get_table_layout(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TABLE_LAYOUT_INDEX];
	bits &= TABLE_LAYOUT_MASK;
	bits >>= TABLE_LAYOUT_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef TABLE_LAYOUT_INDEX
#undef TABLE_LAYOUT_SHIFT
#undef TABLE_LAYOUT_MASK

#define TEXT_ALIGN_INDEX 13
#define TEXT_ALIGN_SHIFT 14
#define TEXT_ALIGN_MASK 0x3c000
static inline uint8_t get_text_align(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TEXT_ALIGN_INDEX];
	bits &= TEXT_ALIGN_MASK;
	bits >>= TEXT_ALIGN_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef TEXT_ALIGN_INDEX
#undef TEXT_ALIGN_SHIFT
#undef TEXT_ALIGN_MASK

#define TEXT_ALIGN_LAST_INDEX 10
#define TEXT_ALIGN_LAST_SHIFT 8
#define TEXT_ALIGN_LAST_MASK 0xf00
static inline uint8_t get_text_align_last(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TEXT_ALIGN_LAST_INDEX];
	bits &= TEXT_ALIGN_LAST_MASK;
	bits >>= TEXT_ALIGN_LAST_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef TEXT_ALIGN_LAST_INDEX
#undef TEXT_ALIGN_LAST_SHIFT
#undef TEXT_ALIGN_LAST_MASK

#define TEXT_ANCHOR_INDEX 13
#define TEXT_ANCHOR_SHIFT 2
#define TEXT_ANCHOR_MASK 0x3c
static inline uint8_t get_text_anchor(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TEXT_ANCHOR_INDEX];
	bits &= TEXT_ANCHOR_MASK;
	bits >>= TEXT_ANCHOR_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef TEXT_ANCHOR_INDEX
#undef TEXT_ANCHOR_SHIFT
#undef TEXT_ANCHOR_MASK

#define TEXT_DECORATION_INDEX 12
#define TEXT_DECORATION_SHIFT 22
#define TEXT_DECORATION_MASK 0x7c00000
static inline uint8_t get_text_decoration(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TEXT_DECORATION_INDEX];
	bits &= TEXT_DECORATION_MASK;
	bits >>= TEXT_DECORATION_SHIFT;
	
	/* 5bits: ttttt : type */
	
	return (bits & 0x1f);
}
#undef TEXT_DECORATION_INDEX
#undef TEXT_DECORATION_SHIFT
#undef TEXT_DECORATION_MASK

#define TEXT_INDENT_INDEX 16
#define TEXT_INDENT_SHIFT 19
#define TEXT_INDENT_MASK 0x1f80000
static inline uint8_t get_text_indent(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[TEXT_INDENT_INDEX];
	bits &= TEXT_INDENT_MASK;
	bits >>= TEXT_INDENT_SHIFT;
	
	/* 6bits: uuuuut : unit | type */
	if ((bits & 0x1) == CSS_TEXT_INDENT_SET) {
		*length = style->i.text_indent;
		*unit = bits >> 1;
	}
	
	return (bits & 0x1);
}
#undef TEXT_INDENT_INDEX
#undef TEXT_INDENT_SHIFT
#undef TEXT_INDENT_MASK

#define TEXT_JUSTIFY_INDEX 10
#define TEXT_JUSTIFY_SHIFT 12
#define TEXT_JUSTIFY_MASK 0xf000
static inline uint8_t get_text_justify(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TEXT_JUSTIFY_INDEX];
	bits &= TEXT_JUSTIFY_MASK;
	bits >>= TEXT_JUSTIFY_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef TEXT_JUSTIFY_INDEX
#undef TEXT_JUSTIFY_SHIFT
#undef TEXT_JUSTIFY_MASK

#define TEXT_OVERFLOW_INDEX 14
#define TEXT_OVERFLOW_SHIFT 6
#define TEXT_OVERFLOW_MASK 0xc0
static inline uint8_t get_text_overflow(const css_computed_style *style,
		lwc_string **string)
{
	uint32_t bits = style->i.bits[TEXT_OVERFLOW_INDEX];
	bits &= TEXT_OVERFLOW_MASK;
	bits >>= TEXT_OVERFLOW_SHIFT;
	
	/* 2bits: tt : type */
	*string = style->i.text_overflow;
	
	return (bits & 0x3);
}
#undef TEXT_OVERFLOW_INDEX
#undef TEXT_OVERFLOW_SHIFT
#undef TEXT_OVERFLOW_MASK

#define TEXT_RENDERING_INDEX 10
#define TEXT_RENDERING_SHIFT 4
#define TEXT_RENDERING_MASK 0xf0
static inline uint8_t get_text_rendering(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TEXT_RENDERING_INDEX];
	bits &= TEXT_RENDERING_MASK;
	bits >>= TEXT_RENDERING_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef TEXT_RENDERING_INDEX
#undef TEXT_RENDERING_SHIFT
#undef TEXT_RENDERING_MASK

#define TEXT_SHADOW_INDEX 14
#define TEXT_SHADOW_SHIFT 22
#define TEXT_SHADOW_MASK 0xc00000
static inline uint8_t get_text_shadow(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TEXT_SHADOW_INDEX];
	bits &= TEXT_SHADOW_MASK;
	bits >>= TEXT_SHADOW_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef TEXT_SHADOW_INDEX
#undef TEXT_SHADOW_SHIFT
#undef TEXT_SHADOW_MASK

#define TEXT_TRANSFORM_INDEX 11
#define TEXT_TRANSFORM_SHIFT 21
#define TEXT_TRANSFORM_MASK 0xe00000
static inline uint8_t get_text_transform(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TEXT_TRANSFORM_INDEX];
	bits &= TEXT_TRANSFORM_MASK;
	bits >>= TEXT_TRANSFORM_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef TEXT_TRANSFORM_INDEX
#undef TEXT_TRANSFORM_SHIFT
#undef TEXT_TRANSFORM_MASK

#define TOP_INDEX 5
#define TOP_SHIFT 11
#define TOP_MASK 0x3f800
static inline uint8_t get_top(
		const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[TOP_INDEX];
	bits &= TOP_MASK;
	bits >>= TOP_SHIFT;

	/* 7bits: uuuuutt : units | type */
	if ((bits & 0x3) == CSS_TOP_SET) {
		*length = style->i.top;
		*unit = bits >> 2;
	}

	return (bits & 0x3);
}
static inline uint8_t get_top_bits(
		const css_computed_style *style)
{
	uint32_t bits = style->i.bits[TOP_INDEX];
	bits &= TOP_MASK;
	bits >>= TOP_SHIFT;

	/* 7bits: uuuuutt : units | type */
	return bits;
}
#undef TOP_INDEX
#undef TOP_SHIFT
#undef TOP_MASK

#define UNICODE_BIDI_INDEX 12
#define UNICODE_BIDI_SHIFT 17
#define UNICODE_BIDI_MASK 0x3e0000
static inline uint8_t get_unicode_bidi(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[UNICODE_BIDI_INDEX];
	bits &= UNICODE_BIDI_MASK;
	bits >>= UNICODE_BIDI_SHIFT;
	
	/* 5bits: ttttt : type */
	
	return (bits & 0x1f);
}
#undef UNICODE_BIDI_INDEX
#undef UNICODE_BIDI_SHIFT
#undef UNICODE_BIDI_MASK

#define VERTICAL_ALIGN_INDEX 15
#define VERTICAL_ALIGN_SHIFT 1
#define VERTICAL_ALIGN_MASK 0x3fe
static inline uint8_t get_vertical_align(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[VERTICAL_ALIGN_INDEX];
	bits &= VERTICAL_ALIGN_MASK;
	bits >>= VERTICAL_ALIGN_SHIFT;
	
	/* 9bits: uuuuutttt : unit | type */
	if ((bits & 0xf) == CSS_VERTICAL_ALIGN_SET) {
		*length = style->i.vertical_align;
		*unit = bits >> 4;
	}
	
	return (bits & 0xf);
}
#undef VERTICAL_ALIGN_INDEX
#undef VERTICAL_ALIGN_SHIFT
#undef VERTICAL_ALIGN_MASK

#define VISIBILITY_INDEX 18
#define VISIBILITY_SHIFT 30
#define VISIBILITY_MASK 0xc0000000
static inline uint8_t get_visibility(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[VISIBILITY_INDEX];
	bits &= VISIBILITY_MASK;
	bits >>= VISIBILITY_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef VISIBILITY_INDEX
#undef VISIBILITY_SHIFT
#undef VISIBILITY_MASK

#define WHITE_SPACE_INDEX 17
#define WHITE_SPACE_SHIFT 23
#define WHITE_SPACE_MASK 0x3800000
static inline uint8_t get_white_space(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[WHITE_SPACE_INDEX];
	bits &= WHITE_SPACE_MASK;
	bits >>= WHITE_SPACE_SHIFT;
	
	/* 3bits: ttt : type */
	
	return (bits & 0x7);
}
#undef WHITE_SPACE_INDEX
#undef WHITE_SPACE_SHIFT
#undef WHITE_SPACE_MASK

#define WIDOWS_INDEX 17
#define WIDOWS_SHIFT 0
#define WIDOWS_MASK 0x1
static inline uint8_t get_widows(const css_computed_style *style, int32_t
		*integer)
{
	uint32_t bits = style->i.bits[WIDOWS_INDEX];
	bits &= WIDOWS_MASK;
	bits >>= WIDOWS_SHIFT;
	
	/* 1bit: t : type */
	*integer = style->i.widows;
	
	return (bits & 0x1);
}
#undef WIDOWS_INDEX
#undef WIDOWS_SHIFT
#undef WIDOWS_MASK

#define WIDTH_INDEX 1
#define WIDTH_SHIFT 0
#define WIDTH_MASK 0x7f
static inline uint8_t get_width(const css_computed_style *style, css_fixed
		*length, css_unit *unit)
{
	uint32_t bits = style->i.bits[WIDTH_INDEX];
	bits &= WIDTH_MASK;
	bits >>= WIDTH_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_WIDTH_SET) {
		*length = style->i.width;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef WIDTH_INDEX
#undef WIDTH_SHIFT
#undef WIDTH_MASK

#define WORD_BREAK_INDEX 13
#define WORD_BREAK_SHIFT 6
#define WORD_BREAK_MASK 0x3c0
static inline uint8_t get_word_break(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[WORD_BREAK_INDEX];
	bits &= WORD_BREAK_MASK;
	bits >>= WORD_BREAK_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef WORD_BREAK_INDEX
#undef WORD_BREAK_SHIFT
#undef WORD_BREAK_MASK

#define WORD_SPACING_INDEX 8
#define WORD_SPACING_SHIFT 11
#define WORD_SPACING_MASK 0x3f800
static inline uint8_t get_word_spacing(const css_computed_style *style,
		css_fixed *length, css_unit *unit)
{
	uint32_t bits = style->i.bits[WORD_SPACING_INDEX];
	bits &= WORD_SPACING_MASK;
	bits >>= WORD_SPACING_SHIFT;
	
	/* 7bits: uuuuutt : unit | type */
	if ((bits & 0x3) == CSS_WORD_SPACING_SET) {
		*length = style->i.word_spacing;
		*unit = bits >> 2;
	}
	
	return (bits & 0x3);
}
#undef WORD_SPACING_INDEX
#undef WORD_SPACING_SHIFT
#undef WORD_SPACING_MASK

#define WORD_WRAP_INDEX 8
#define WORD_WRAP_SHIFT 0
#define WORD_WRAP_MASK 0xf
static inline uint8_t get_word_wrap(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[WORD_WRAP_INDEX];
	bits &= WORD_WRAP_MASK;
	bits >>= WORD_WRAP_SHIFT;
	
	/* 4bits: tttt : type */
	
	return (bits & 0xf);
}
#undef WORD_WRAP_INDEX
#undef WORD_WRAP_SHIFT
#undef WORD_WRAP_MASK

#define WRITING_MODE_INDEX 17
#define WRITING_MODE_SHIFT 5
#define WRITING_MODE_MASK 0x60
static inline uint8_t get_writing_mode(const css_computed_style *style)
{
	uint32_t bits = style->i.bits[WRITING_MODE_INDEX];
	bits &= WRITING_MODE_MASK;
	bits >>= WRITING_MODE_SHIFT;
	
	/* 2bits: tt : type */
	
	return (bits & 0x3);
}
#undef WRITING_MODE_INDEX
#undef WRITING_MODE_SHIFT
#undef WRITING_MODE_MASK

#define Z_INDEX_INDEX 14
#define Z_INDEX_SHIFT 0
#define Z_INDEX_MASK 0x3
static inline uint8_t get_z_index(const css_computed_style *style, int32_t
		*integer)
{
	uint32_t bits = style->i.bits[Z_INDEX_INDEX];
	bits &= Z_INDEX_MASK;
	bits >>= Z_INDEX_SHIFT;
	
	/* 2bits: tt : type */
	*integer = style->i.z_index;
	
	return (bits & 0x3);
}
#undef Z_INDEX_INDEX
#undef Z_INDEX_SHIFT
#undef Z_INDEX_MASK
