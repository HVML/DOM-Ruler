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

#ifndef _LiteLayout_H_
#define _LiteLayout_H_

class LayoutBox {
public:
    LayoutBox(int x, int y, int width, int height);
    LayoutBox();
    ~LayoutBox();

    int x() { return x; }
    int y() { return y; }
    int width() { return width; }
    int height() { return height; }

    int setX();
    int setY();
    int setWidth();
    int setHeight();

private:
    int x;
    int y;
    int width;
    int height;

};


class PageNode {
public:
    PageNode(const char* id, const char* pageStyle);
    ~PageNode();

    int addRunner(const char* runnerType, const char* runnerName, const char *id, const char *classes, const char *inlineStyle);

    LayoutBox& getRunnerLayoutBoxById(const char* id);
    LayoutBox& getRunnerLayoutBoxByName(const char* id);
};


class LiteLayout {
public:
    LiteLayout(int screenWidth, int screenHeight);
    ~LiteLayout();

    int addStylesheet(const char *stylesheet, size_t len);
    int addStylesheetDone();

    int setTitleBoxStyle(const char* boxStyle);
    int setPageBoxStyle(const char* boxStyle);
    int setIndicatorBoxStyle(const char* boxStyle);
    int setDescriptionBoxStyle(const char* boxStyle);

    int layoutRoot();
    int layoutPage(Page& page);

    LayoutBox& getTitleLayoutBox();
    LayoutBox& getPageLayoutBox();
    LayoutBox& getIndicatorLayoutBox();
    LayoutBox& getDescriptionLayoutBox();


};

#endif // _LiteLayout_H_
