/**
 * @file
 * @brief The interface Header file
 *
 * @author Lukas Deutscher
 * @date 19.12.2017
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "../includes/interface.h"
#include "../includes/log.h"
#include "../includes/config.h"
#include "../includes/locale.h"
#include "../includes/gnf.h"
#include "../includes/globals.h"

#include "interface_structs.h"

#include <algorithm>
#include <vector>
#include <string>
#include <regex>

#include <FL/Fl.H> // The fltk base
#include <FL/Fl_Window.H> // The fltk Window widget
#include <FL/Fl_Menu.H> // The fltk Menu
#include <FL/Fl_Menu_Bar.H> // The fltk Menu Bar
#include <FL/Fl_Menu_Item.H> // The fltk Menu Item
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/fl_ask.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Color_Chooser.H>

/**
 * Classes
 */
class InterfaceChatTab
{
    public:
    Fl_Group* FlGroup;
    Fl_Text_Display* TextOutput;
    Fl_Text_Editor* TextInput;
    Fl_Button* SendButton;
    Fl_Box* EventBox;

    std::string ChatTarget;
    std::string ChatHost;

    void AppendTextToOutput(const std::string &Text);
    void SetEventMessage(const std::string &Text);

    InterfaceChatTab(int x, int y, int w, int h, const std::string &Target);
};

void SendCallbackMaster(Fl_Widget* Widget, void* Data);

/**
 * friend_list.cpp
 */
void CreateFriendListWindow(Fl_Widget*, void*);

/**
 * interface_utils.cpp
 */
InterfaceColor *ReadConfigColor(const std::string &Key);
Fl_PNG_Image *GetPngImgResource(const std::string &ConfigKey);
InterfaceSize *ReadConfigSize(const std::string &Key);
InterfaceDimension *ReadConfigDimension(const std::string &ConfigKey);

/**
 * interface.factory.cpp
 */
Fl_Window *FactNewWindow(const std::string &SizeKey, std::string *WindowTitle);
Fl_Button *FactNewButton(const std::string &DimensionKey);
Fl_Box *FactNewBox(const std::string &DimensionKey);

/**
 * interface_options.cpp
 */
void CreateOptionsWindow();

#endif
