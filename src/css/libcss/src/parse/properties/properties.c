/*
 * This file is part of LibCSS.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2008 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "parse/properties/properties.h"

/**
 * Dispatch table of property handlers, indexed by property enum
 */
const css_prop_handler property_handlers[LAST_PROP + 1 - FIRST_PROP] =
{
	css__parse_align_content,
	css__parse_align_items,
	css__parse_align_self,
	css__parse_azimuth,
	css__parse_background,
	css__parse_background_attachment,
	css__parse_background_color,
	css__parse_background_image,
	css__parse_background_position,
	css__parse_background_repeat,
	css__parse_border,
	css__parse_border_bottom,
	css__parse_border_bottom_color,
	css__parse_border_bottom_style,
	css__parse_border_bottom_width,
	css__parse_border_collapse,
	css__parse_border_color,
	css__parse_border_left,
	css__parse_border_left_color,
	css__parse_border_left_style,
	css__parse_border_left_width,
	css__parse_border_right,
	css__parse_border_right_color,
	css__parse_border_right_style,
	css__parse_border_right_width,
	css__parse_border_spacing,
	css__parse_border_style,
	css__parse_border_top,
	css__parse_border_top_color,
	css__parse_border_top_style,
	css__parse_border_top_width,
	css__parse_border_width,
	css__parse_bottom,
	css__parse_box_sizing,
	css__parse_break_after,
	css__parse_break_before,
	css__parse_break_inside,
	css__parse_caption_side,
	css__parse_clear,
	css__parse_clip,
	css__parse_color,
	css__parse_columns,
	css__parse_column_count,
	css__parse_column_fill,
	css__parse_column_gap,
	css__parse_column_rule,
	css__parse_column_rule_color,
	css__parse_column_rule_style,
	css__parse_column_rule_width,
	css__parse_column_span,
	css__parse_column_width,
	css__parse_content,
	css__parse_counter_increment,
	css__parse_counter_reset,
	css__parse_cue,
	css__parse_cue_after,
	css__parse_cue_before,
	css__parse_cursor,
	css__parse_direction,
	css__parse_display,
	css__parse_elevation,
	css__parse_empty_cells,
	css__parse_flex,
	css__parse_flex_basis,
	css__parse_flex_direction,
	css__parse_flex_flow,
	css__parse_flex_grow,
	css__parse_flex_shrink,
	css__parse_flex_wrap,
	css__parse_float,
	css__parse_font,
	css__parse_font_family,
	css__parse_font_size,
	css__parse_font_style,
	css__parse_font_variant,
	css__parse_font_weight,
	css__parse_height,
	css__parse_justify_content,
	css__parse_left,
	css__parse_letter_spacing,
	css__parse_line_height,
	css__parse_list_style,
	css__parse_list_style_image,
	css__parse_list_style_position,
	css__parse_list_style_type,
	css__parse_margin,
	css__parse_margin_bottom,
	css__parse_margin_left,
	css__parse_margin_right,
	css__parse_margin_top,
	css__parse_max_height,
	css__parse_max_width,
	css__parse_min_height,
	css__parse_min_width,
	css__parse_opacity,
	css__parse_order,
	css__parse_orphans,
	css__parse_outline,
	css__parse_outline_color,
	css__parse_outline_style,
	css__parse_outline_width,
	css__parse_overflow,
	css__parse_overflow_x,
	css__parse_overflow_y,
	css__parse_padding,
	css__parse_padding_bottom,
	css__parse_padding_left,
	css__parse_padding_right,
	css__parse_padding_top,
	css__parse_page_break_after,
	css__parse_page_break_before,
	css__parse_page_break_inside,
	css__parse_pause,
	css__parse_pause_after,
	css__parse_pause_before,
	css__parse_pitch_range,
	css__parse_pitch,
	css__parse_play_during,
	css__parse_position,
	css__parse_quotes,
	css__parse_richness,
	css__parse_right,
	css__parse_speak_header,
	css__parse_speak_numeral,
	css__parse_speak_punctuation,
	css__parse_speak,
	css__parse_speech_rate,
	css__parse_stress,
	css__parse_table_layout,
	css__parse_text_align,
	css__parse_text_decoration,
	css__parse_text_indent,
	css__parse_text_transform,
	css__parse_top,
	css__parse_unicode_bidi,
	css__parse_vertical_align,
	css__parse_visibility,
	css__parse_voice_family,
	css__parse_volume,
	css__parse_white_space,
	css__parse_widows,
	css__parse_width,
	css__parse_word_spacing,
	css__parse_writing_mode,
	css__parse_z_index,
	css__parse_grid_template_columns,
	css__parse_grid_template_rows,
	css__parse_grid_column_start,
	css__parse_grid_column_end,
	css__parse_grid_row_start,
	css__parse_grid_row_end,
    css__parse_border_top_left_radius,
    css__parse_border_top_right_radius,
    css__parse_border_bottom_left_radius,
    css__parse_border_bottom_right_radius,
    css__parse_text_align_last,
    css__parse_text_justify,
    css__parse_text_overflow,
    css__parse_word_break,
    css__parse_word_wrap,
    css__parse_baseline_shift,
    css__parse_clip_path,
    css__parse_clip_rule,
    css__parse_comp_op,
    css__parse_enable_background,
    css__parse_fill,
    css__parse_fill_opacity,
    css__parse_fill_rule,
    css__parse_filter,
    css__parse_flood_color,
    css__parse_flood_opacity,
    css__parse_font_stretch,
    css__parse_marker_start,
    css__parse_marker_mid,
    css__parse_marker_end,
    css__parse_mask,
    css__parse_shape_rendering,
    css__parse_stop_color,
    css__parse_stop_opacity,
    css__parse_stroke,
    css__parse_stroke_width,
    css__parse_stroke_opacity,
    css__parse_stroke_dasharray,
    css__parse_stroke_dashoffset,
    css__parse_stroke_linecap,
    css__parse_stroke_linejoin,
    css__parse_stroke_miterlimit,
    css__parse_text_anchor,
    css__parse_text_rendering
};
