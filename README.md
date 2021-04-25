# hiLayout

- [Introduction](#introduction)
- [Dependencies](#dependencies)
- [Building hiDOMLayout](#building-hidomlayout)
- [Usage](#usage)
- [CSS property support](#css-property-support)
- [Copying](#copying)

## Introduction

hiDOMLayout is a library to maintain a DOM tree, lay out and stylize the DOM nodes by using CSS (Cascaded Style Sheets).

## Dependencies

hiDOMLayout depends on the following libraries:

- [GLib](https://developer.gnome.org/glib/stable/)

## Building hiDOMLayout

We recommend that you use a latest Linux distribution with long term support,
for example, Ubuntu Linux LTS 18.04 or 20.04.

On Ubuntu Linux LTS 18.04 or 20.04, you should run `apt install <package_name>`
to install the following packages:

 * Building tools:
    * cmake
 * Dependent libraries (all are optional):
    * libglib2.0-dev

hiDOMLayout uses cmake to configure and build the project.

```
$ cmake .
$ make
$ make install
```

## Usage

* create HLDomElementNode and set attribute

```
HLDomElementNode* hilayout_element_node_create(const char* tag_name);

// set common attribute
int hilayout_element_node_set_id (HLDomElementNode* node, const char* id);
int hilayout_element_node_set_class (HLDomElementNode* node, const char* class_name);
int hilayout_element_node_set_style (HLDomElementNode* node, const char* style);
int hilayout_element_node_set_name (HLDomElementNode* node, const char* name);
int hilayout_element_node_set_common_attr (HLDomElementNode* node, HLCommonAttribute attr_id, const char* value);
```

* build tree

```
int hilayout_element_node_append_as_last_child(HLDomElementNode* node, HLDomElementNode* parent);
```

* create HLCSS and append css data

```
HLCSS* hilayout_css_create();
int hilayout_css_append_data(HLCSS* css, const char* data, size_t len);
```

* layout

```
int hilayout_do_layout(HLMedia* media, HLCSS* css, HLDomElementNode *root);
```

* free memory 

```
void hilayout_element_node_destroy(HLDomElementNode *node);
int hilayout_css_destroy(HLCSS* css);
```

## CSS property support

* align_content
* align_items
* align_self
* background_attachment
* background_color
* background_image
* background_repeat
* border_bottom
* border_bottom_color
* border_bottom_style
* border_bottom_width
* border_collapse
* border_left
* border_left_color
* border_left_style
* border_left_width
* border_right
* border_right_color
* border_right_style
* border_right_width
* border_side_color
* border_side_style
* border_side_width
* border_top
* border_top_color
* border_top_style
* border_top_width
* bottom
* box_sizing
* break_after
* break_before
* break_inside
* caption_side
* clear
* color
* column_count
* column_fill
* column_gap
* column_rule_color
* column_rule_style
* column_rule_width
* column_span
* column_width
* counter_increment
* counter_reset
* cue_after
* cue_before
* direction
* display
* empty_cells
* flex_basis
* flex_direction
* flex_grow
* flex_shrink
* flex_wrap
* float
* font_size
* font_style
* font_variant
* height
* justify_content
* left
* letter_spacing
* line_height
* list_style_image
* list_style_position
* margin_bottom
* margin_left
* margin_right
* margin_side
* margin_top
* max_height
* max_width
* min_height
* min_width
* order
* orphans
* outline_color
* outline_style
* outline_width
* overflow_x
* overflow_y
* padding_bottom
* padding_left
* padding_right
* padding_side
* padding_top
* page_break_after
* page_break_before
* page_break_inside
* pause_after
* pause_before
* pitch
* pitch_range
* position
* richness
* right
* side
* speak
* speak_header
* speak_numeral
* speak_punctuation
* speech_rate
* stress
* table_layout
* text_align
* text_indent
* text_transform
* top
* unicode_bidi
* vertical_align
* visibility
* volume
* white_space
* widows
* width
* word_spacing
* writing_mode
* z_index

## Copying

Copyright (C) 2020 FMSoft <https://www.fmsoft.cn>

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

### Commercial License

If you cannot accept GPLv3, you need to be licensed from FMSoft.

For more information about the commercial license, please refer to
<https://hybridos.fmsoft.cn/blog/hybridos-licensing-policy>.

### Special Statement

The above open source or free software license(s) does
not apply to any entity in the Exception List published by
Beijing FMSoft Technologies Co., Ltd.

If you are or the entity you represent is listed in the Exception List,
the above open source or free software license does not apply to you
or the entity you represent. Regardless of the purpose, you should not
use the software in any way whatsoever, including but not limited to
downloading, viewing, copying, distributing, compiling, and running.
If you have already downloaded it, you MUST destroy all of its copies.

The Exception List is published by FMSoft and may be updated
from time to time. For more information, please see
<https://www.fmsoft.cn/exception-list>.

