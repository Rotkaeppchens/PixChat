/**
 * @brief The friend list cpp file
 *
 * @author Lukas Deutscher
 * @date 23.12.2017
 */

#include "interface.h"

Fl_Select_Browser* gFriendListBrowser;

/**
 * @brief The callback for the add friend button
 *
 * @param Widget The calling widget
 * @param Data The data
 * @return void
 */
void AddFriendCallback(Fl_Widget* Widget, void* Data)
{
    Fl_Input* NameInput = (Fl_Input*)Data;

    GnfAddFriendToRoster(NameInput->value());

    Fl_Window* WidgetWindow = Widget->top_window();
    Fl::delete_widget(WidgetWindow);
}

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
    AddFriendButton->callback((Fl_Callback*)AddFriendCallback, (void*)NameInput);

    AddFriendWindow->end();
    AddFriendWindow->show();
}

/**
 * @brief The callback function for the start chat button
 *
 * @param Widget* The widget who calls
 * @param void* The data (in this case the friend list browser)
 * @return void
 */
void StartChatCallback(Fl_Widget*, void* Data)
{
    int SelectedLine = gFriendListBrowser->value();

    if (SelectedLine == 0) {
        return;
    }

    std::string* Username = (std::string*)gFriendListBrowser->data(SelectedLine);
    UserId* UserData = GnfGetFriendData(*Username);

    L_DEBUG("interface", "Starting chat with: " + UserData->Username);

    DisplayIncomingMessage("", UserData->Username);
}

/**
 * @brief Line double click callback
 *
 * @param Widget The calling widget
 * @param Data The data
 * @return void
 */
void LineDoubleClickCallback(Fl_Widget* Widget, void* Data)
{
    if (
        Fl::event_clicks() != 0
        && Fl::event_button() == FL_LEFT_MOUSE
    ) {
        int SelectedLine = gFriendListBrowser->value();

        if (SelectedLine == 0) {
            return;
        }

        std::string* Username = (std::string*)gFriendListBrowser->data(SelectedLine);
        UserId* UserData = GnfGetFriendData(*Username);

        L_DEBUG("interface", "Starting chat with: " + UserData->Username);

        DisplayIncomingMessage("", UserData->Username);
    }
}

/**
 * @brief Removes friend from roster and asks for confirmation
 *
 * @param Widget The calling widget
 * @param Data The void pointer to the data
 * @return void
 */
void DeleteFriendCallback(Fl_Widget* Widget, void* Data)
{
    int SelectedLine = gFriendListBrowser->value();

    if (SelectedLine == 0) {
        return;
    }

    std::string* Username = (std::string*) gFriendListBrowser->data(SelectedLine);

    L_INFO("interface", "Asking user to remove friend: " + (*Username));

    if (InterfaceCreateAskForm("Do you really want to unfriend: " + (*Username))) {
        L_INFO("interface", "Removing friend: " + (*Username));
        GnfRemoveFriendFromRoster(*Username);
    } else {
        return;
    }
}

/**
 * @brief The callback function to create the friend list window.
 *
 * @param Widget The widget who calls
 * @param Data The data pointer
 */
void CreateFriendListWindow(Fl_Widget*, void*)
{
    Fl_Window* FriendListWindow = new Fl_Window(250, 600, "Friend List");

    Fl_Box* TitleBox = new Fl_Box(10, 10, 230, 30, "Friend List");
    TitleBox->box(FL_BORDER_BOX);

    Fl_Button* AddFriendButton = new Fl_Button(10, 50, 230, 30, "Add Friend");
    AddFriendButton->box(FL_BORDER_BOX);
    AddFriendButton->callback((Fl_Callback*)CreateAddFriendWindow);

    Fl_Button* StartChatButton = new Fl_Button(10, 90, 70, 30, "SC");
    StartChatButton->box(FL_BORDER_BOX);
    StartChatButton->callback((Fl_Callback*)StartChatCallback);

    Fl_Button* ShowProfileButton = new Fl_Button(90, 90, 70, 30, "SP");
    ShowProfileButton->box(FL_BORDER_BOX);

    Fl_Button* DeleteFriendButton = new Fl_Button(170, 90, 70, 30, "DF");
    DeleteFriendButton->box(FL_BORDER_BOX);
    DeleteFriendButton->callback((Fl_Callback*)DeleteFriendCallback);

    Fl_Select_Browser* FriendListBrowser = new Fl_Select_Browser(10, 140, 230, 450);
    FriendListBrowser->callback((Fl_Callback*)LineDoubleClickCallback);

    Fl_PNG_Image* LightRed = new Fl_PNG_Image("../res/light_red.png");
    Fl_PNG_Image* LightGreen = new Fl_PNG_Image("../res/light_green.png");
    Fl_PNG_Image* LightYellow = new Fl_PNG_Image("../res/light_yellow.png");

    std::vector<UserId> FullRoster = GnfGetFullFriendRoster();
    for (unsigned int i = 0; i != FullRoster.size(); ++i) {
        std::string BareUsername = FullRoster[i].Bare;
        std::string* Username = new std::string(FullRoster[i].Bare);

        FriendListBrowser->add(BareUsername.c_str());
        FriendListBrowser->data(i + 1, (void*)Username);

        if (FullRoster[i].IsOnline) {
            FriendListBrowser->icon(i + 1, LightGreen->copy(15, 15));
        } else {
            FriendListBrowser->icon(i + 1, LightRed->copy(15, 15));
        }
    }

    FriendListBrowser->textsize(15);
    FriendListBrowser->box(FL_BORDER_BOX);

    gFriendListBrowser = FriendListBrowser;

    FriendListWindow->end();
    FriendListWindow->show();
}
