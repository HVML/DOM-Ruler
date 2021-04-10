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

#include "hilayout.h"
#include "node.h"
/*
 
   <div id="root">
        <div id="title"></div>
        <div id="description"></div>
        <div id="page">
            <hiweb></hiweb>
            <hijs></hijs>
        </div>
        <div id="indicator"></div>
   </div>


 */
 
#define FPCT_OF_INT_TOINT(a, b) (FIXTOINT(FDIV((a * b), F_100)))

int _hl_element_node_set_inner_attr(HLDomElementNode* node, const char* attr_name, const char* attr_value);
const char* _hl_element_node_get_inner_attr(HLDomElementNode* node, const char* attr_name);

char* readCSS(char* filename)
{
    char* text;
    FILE* fp = fopen(filename,"r");
    fseek(fp,0,SEEK_END);

    long size = ftell(fp);
    text = (char*)malloc(size+1);
    rewind(fp); 
    fread(text, sizeof(char), size, fp);
    text[size] = '\0';
    return text;
}

void destory_user_data(void* data)
{
    fprintf(stderr, "................................user data is callback\n");
    fprintf(stderr, "data is %s\n", (char*)data);
    free(data);

}

int main(int argc, char **argv)
{
	size_t size;
    const char html[] = " \
           <div id=\"root\"> \n\
                <div id=\"title\"></div> \n\
                <div id=\"description\"></div>\n\
                <div id=\"page\"> \n\
                    <hiweb></hiweb> \n\
                    <hijs></hijs>\n \
                </div> \n\
                <div id=\"indicator\"></div>\n\
           </div> \
        ";
	const char data[] = "h1 { color: red } \n"
        "#root { display: block; } \n"
        "#title { position: relative; left:20%; width: 100%; height: 10%; color: #123; } \n"
        "#page { position: relative; width: 100%; height: 80%; color: #125; } \n"
        "#indicator { position: relative; width: 100%; height: 10%; color: #126; } \n"
        "#description { position: relative; width: 100%; height: 0%; color: #124; } \n"
        "hiweb { position: relative; width: 50%; height: 50%; color: #127; font-family: \"Times New Roman\", Times, serif; font-size:10;} \n"
        "hiweb2 { position: relative; width: 50%; height: 50%; color: #127; font-family: \"Times New Roman\", Times, serif; font-size:10;} \n"
        "hijs { position: relative; width: 50%; height: 50%; color: #127; } \n"
        "hijs2 { position: relative; width: 50%; height: 50%; color: #128; background:red;} \n";

    fprintf(stderr, "####################################### html ###########################\n");
    fprintf(stderr, "%s\n", html);


    fprintf(stderr, "####################################### css  ###########################\n");
    const char* css_data = data;
    if (argc > 1)
    {
        css_data = readCSS(argv[1]);
    }
    fprintf(stderr, "%s\n", css_data);

    HLCSS* css = hilayout_css_create(HL_ATTR_GROUP_ALL);
    if (css == NULL)
    {
        HL_LOGE("create HLCSS failed.\n");
        return HILAYOUT_INVALID;
    }

    hilayout_css_append_data(css, css_data, strlen(css_data));


    HLDomElementNode* root = hilayout_element_node_create("div");
    hilayout_element_node_set_id(root, "root");

    HLDomElementNode* title = hilayout_element_node_create("div");
    hilayout_element_node_set_id(title, "title");

    HLDomElementNode* description = hilayout_element_node_create("div");
    hilayout_element_node_set_id(description, "description");

    char page_inline_style[] = "display:grid;";
    HLDomElementNode* page = hilayout_element_node_create("div");
    hilayout_element_node_set_id(page, "page");
//    hilayout_element_node_set_style(page, page_inline_style);

    HLDomElementNode* indicator = hilayout_element_node_create("div");
    hilayout_element_node_set_id(indicator, "indicator");


    HLDomElementNode* hiweb = hilayout_element_node_create("hiweb");
    hilayout_element_node_set_id(hiweb, "hiweb");

    HLDomElementNode* hiweb2 = hilayout_element_node_create("hiweb");
    hilayout_element_node_set_id(hiweb2, "hiweb2");

    HLDomElementNode* hijs = hilayout_element_node_create("hijs");
    hilayout_element_node_set_id(hijs, "hijs");

    HLDomElementNode* hijs2 = hilayout_element_node_create("hijs");
    hilayout_element_node_set_id(hijs2, "hijs2");

    hilayout_element_node_append_as_last_child(title, root);
    hilayout_element_node_append_as_last_child(description, root);
    hilayout_element_node_append_as_last_child(page, root);
    hilayout_element_node_append_as_last_child(indicator, root);

    hilayout_element_node_append_as_last_child(hiweb, page);
    hilayout_element_node_append_as_last_child(hiweb2, page);
    hilayout_element_node_append_as_last_child(hijs, page);
    hilayout_element_node_append_as_last_child(hijs2, page);

    HLMedia hl_media = {
        .width = 1280,
        .height = 720,
        .dpi = 72,
        .density = 72
    };

    fprintf(stderr, "####################################### layout ###########################\n");
    hilayout_do_layout(&hl_media, css, root);

    const HLUsedTextValues* txtVaule = hilayout_element_node_get_used_text_value(hijs);
    fprintf(stderr, "############### txtVaule=%p|txt->family=%s\n", txtVaule, txtVaule->family);

    hilayout_element_node_set_user_attr(hijs, "xsmKey", "xsmValue");
    fprintf(stderr, "############### test get attr =%s\n", hilayout_element_node_get_user_attr(hijs, "xsmKey"));

    hilayout_element_node_set_user_attr(hijs, "xsmKey", "xsmValue2222222");
    fprintf(stderr, "############### test get attr =%s\n", hilayout_element_node_get_user_attr(hijs, "xsmKey"));
    
    fprintf(stderr, ".......................HL_ATTR_GROUP_BOX=%d\n", HL_ATTR_GROUP_BOX);
    hilayout_element_node_set_private_attr(hijs, HL_ATTR_ID_WIDTH, "privateValue1111");
    fprintf(stderr, "############### test get attr id=%ld | value =%s\n", HL_ATTR_ID_WIDTH, hilayout_element_node_get_private_attr(hijs, HL_ATTR_ID_WIDTH));

    fprintf(stderr, "############### test get attr id=%ld | value =%s\n", HL_ATTR_ID_BACKGROUND_COLOR, hilayout_element_node_get_private_attr(hijs, HL_ATTR_ID_BACKGROUND_COLOR));

    _hl_element_node_set_inner_attr(hijs, "innerKey", "innerValue2222");
    fprintf(stderr, "############### test get attr id=%ld | value =%s\n", HL_ATTR_ID_WIDTH, _hl_element_node_get_inner_attr(hijs, "innerKey2"));

    char* buf = (char*)malloc(100);
    strcpy(buf, "this is test buf for userdata.\n");
    hilayout_element_node_set_user_data(hijs, "userData", buf, destory_user_data);
    void* udata = hilayout_element_node_get_user_data(hijs, "userData");
    fprintf(stderr, "############### test get user data key=userData | value =%s\n",  (char*)udata);

    buf = (char*)malloc(100);
    strcpy(buf, "this is test buf for inner data.\n");
    _hl_element_node_set_inner_data(hijs, "innerData", buf, destory_user_data);
    udata = _hl_element_node_get_inner_data(hijs, "innerData");
    fprintf(stderr, "############### test get user data key=innerData | value =%s\n",  (char*)udata);

    hilayout_css_destroy(css);

    hilayout_element_node_destroy(root);
    hilayout_element_node_destroy(title);
    hilayout_element_node_destroy(page);
    hilayout_element_node_destroy(description);
    hilayout_element_node_destroy(indicator);
    hilayout_element_node_destroy(hiweb);
    hilayout_element_node_destroy(hiweb2);
    hilayout_element_node_destroy(hijs);
    hilayout_element_node_destroy(hijs2);

	return 0;
}

