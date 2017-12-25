/**
 * @brief The friend list cpp file
 *
 * @author Lukas Deutscher
 * @date 23.12.2017
 */

#include "interface.h"

/**
 * @brief The callback for the add friends window
 *
 * @param Widget The calling widget
 * @param Data The datapointer
 * @return void
 */
void CreateAddFriendWindow(Fl_Widget*, void*)
{
    Fl_Window* AddFriendWindow = new Fl_Window(300, 130, "Add Friend");

    Fl_Box* LabelBox = new Fl_Box(10, 10, 280, 30, "Please enter the username:");
    LabelBox->box(FL_NO_BOX);

    Fl_Input* NameInput = new Fl_Input(10, 50, 280, 30);
    NameInput->box(FL_BORDER_BOX);

    Fl_Button* AddFriendButton = new Fl_Button(125, 90, 50, 30, "Ok");
    AddFriendButton->box(FL_BORDER_BOX);
    AddFriendButton->shortcut(FL_ENTER);

    AddFriendWindow->end();
    AddFriendWindow->show();
}

/**
 * @brief The callback function to create the friend list window.
 *
 * @param Widget The widget who calls
 * @param Data The data pointer
 */
void CreateFriendListWindow(Fl_Widget*, void*)
{
    Fl_Window* FriendListWindow = new Fl_Window(200, 600, "Friend List");

    Fl_Box* TitleBox = new Fl_Box(10, 10, 180, 30, "Friend List");
    TitleBox->box(FL_BORDER_BOX);

    Fl_Button* AddFriendButton = new Fl_Button(10, 50, 180, 30, "Add Friend");
    AddFriendButton->box(FL_BORDER_BOX);
    AddFriendButton->callback((Fl_Callback*)CreateAddFriendWindow);

    Fl_Select_Browser* FriendListBrowser = new Fl_Select_Browser(10, 90, 180, 500);

    Fl_PNG_Image* LightRed = new Fl_PNG_Image("../res/light_red.png");
    Fl_PNG_Image* LightGreen = new Fl_PNG_Image("../res/light_green.png");
    Fl_PNG_Image* LightYellow = new Fl_PNG_Image("../res/light_yellow.png");

    std::vector<UserId> FullRoster = GnfGetFullFriendRoster();
    for (unsigned int i = 0; i != FullRoster.size(); ++i) {
        FriendListBrowser->add(FullRoster[i].Bare.c_str());

        if (FullRoster[i].IsOnline) {
            FriendListBrowser->icon(i + 1, LightGreen->copy(15, 15));
        } else {
            FriendListBrowser->icon(i + 1, LightRed->copy(15, 15));
        }
    }

    FriendListBrowser->textsize(15);

    FriendListBrowser->box(FL_BORDER_BOX);

    FriendListWindow->end();
    FriendListWindow->show();
}
