/**
 * @file
 * @brief Globals for the interface code
 *
 * @author Lukas Deutscher
 * @date 11.07.2018
 */

#include "interface.h"

/**
 * Windows
 */
Fl_Window* gMainWindow;
Fl_Window* gFriendListWindow;
Fl_Window* gOptionsWindow;

/**
 * Widgets
 */
// interface.cpp
Fl_Box* gInfoBox;
Fl_Tabs* gChatTabWidget;
std::vector<InterfaceChatTab*> gChatTabs;

// friend_list.cpp
Fl_Select_Browser* gFriendListBrowser;
