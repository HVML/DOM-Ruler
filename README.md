# hiLayout

- [Introduction](#introduction)
- [Dependencies](#dependencies)
- [Building](#building)
- [Usage](#usage)
- [CSS property support](#css-property-support)
- [Copying](#copying)

## Introduction

hiDOMLayout is a library to maintain a DOM tree, lay out and stylize the DOM nodes by using CSS (Cascaded Style Sheets).
It integrates LibCSS (MIT licensed), LibParserUtils (MIT licensed) and LibWapcaplet (MIT licensed) from open source community.

## Dependencies

hiDOMLayout depends on the following libraries:

- [GLib](https://developer.gnome.org/glib/stable/)

## Building

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
$ mkdir build
$ cd build
$ cmake ..
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

* align-content
* align-items
* align-self
* azimuth
* background
* background-attachment
* background-color
* background-image
* background-position
* background-repeat
* baseline-shift
* border
* border-bottom
* border-bottom-color
* border-bottom-left-radius
* border-bottom-right-radius
* border-bottom-style
* border-bottom-width
* border-collapse
* border-color
* border-left
* border-left-color
* border-left-style
* border-left-width
* border-right
* border-right-color
* border-right-style
* border-right-width
* border-spacing
* border-style
* border-top
* border-top-color
* border-top-left-radius
* border-top-right-radius
* border-top-style
* border-top-width
* border-width
* bottom
* box-sizing
* break-after
* break-before
* break-inside
* caption-side
* clear
* clip
* clip-path
* clip-rule
* color
* column-count
* column-fill
* column-gap
* column-rule
* column-rule-color
* column-rule-style
* column-rule-width
* column-span
* column-width
* columns
* comp-op
* content
* counter-increment
* counter-reset
* cue
* cue-after
* cue-before
* cursor
* direction
* display
* elevation
* empty-cells
* enable-background
* fill
* fill-opacity
* fill-rule
* filter
* flex
* flex-basis
* flex-direction
* flex-flow
* flex-grow
* flex-shrink
* flex-wrap
* flood-color
* flood-opacity
* font
* font-family
* font-size
* font-stretch
* font-style
* font-variant
* font-weight
* grid-column-end
* grid-column-start
* grid-row-end
* grid-row-start
* grid-template-columns
* grid-template-rows
* height
* justify-content
* left
* letter-spacing
* libcss-float
* line-height
* list-style
* list-style-image
* list-style-position
* list-style-type
* margin
* margin-bottom
* margin-left
* margin-right
* margin-top
* marker-end
* marker-mid
* marker-start
* mask
* max-height
* max-width
* min-height
* min-width
* opacity
* order
* orphans
* outline
* outline-color
* outline-style
* outline-width
* overflow
* overflow-x
* overflow-y
* padding
* padding-bottom
* padding-left
* padding-right
* padding-top
* page-break-after
* page-break-before
* page-break-inside
* pause
* pause-after
* pause-before
* pitch
* pitch-range
* play-during
* position
* quotes
* richness
* right
* shape-rendering
* speak
* speak-header
* speak-numeral
* speak-punctuation
* speech-rate
* stop-color
* stop-opacity
* stress
* stroke
* stroke-dasharray
* stroke-dashoffset
* stroke-linecap
* stroke-linejoin
* stroke-miterlimit
* stroke-opacity
* stroke-width
* table-layout
* text-align
* text-align-last
* text-anchor
* text-decoration
* text-indent
* text-justify
* text-overflow
* text-rendering
* text-shadow
* text-transform
* top
* unicode-bidi
* vertical-align
* visibility
* voice-family
* volume
* white-space
* widows
* width
* word-break
* word-spacing
* word-wrap
* writing-mode
* z-index

## Copying

Copyright (C) 2021 FMSoft <https://www.fmsoft.cn>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General License for more details.

You should have received a copy of the GNU Lesser General License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

### Commercial License

If you cannot accept LGPLv3, you need to be licensed from FMSoft.

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

