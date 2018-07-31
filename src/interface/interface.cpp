/**
 * @file
 * @brief The interface source file.
 *
 * @author Lukas Deutscher
 * @date 19.12.2017
 */

#include "interface.h" // The ial header

/**
 * Globals
 */
extern Fl_Window* gMainWindow;
extern Fl_Box* gInfoBox;
extern Fl_Tabs* gChatTabWidget;
extern std::vector<InterfaceChatTab*> gChatTabs;
extern Fl_Window* gFriendListWindow;

/**
 * @brief This func quits the program
 *
 * @return void
 */
void QuitProgram()
{
    exit(0);
}

void SendCallbackMaster(Fl_Widget* Widget, void* Data)
{
    InterfaceChatTab* ChatTab = (InterfaceChatTab*)Data;

    std::string InputMessage(ChatTab->TextInput->buffer()->text());

    InputMessage.erase(std::remove(InputMessage.begin(), InputMessage.end(), '\n'), InputMessage.end());

    ChatTab->AppendTextToOutput("You: " + InputMessage + "\n");
    GnfSendMessage(ChatTab->ChatTarget, InputMessage);

    ChatTab->TextInput->buffer()->text("");
    ChatTab->TextInput->redraw();
}

void NewChatWindowCallback(Fl_Widget* Widget, void* Data)
{
    Fl_Input* NameInput = (Fl_Input*)Data;

    std::string TargetName(NameInput->value());

    DisplayIncomingMessage("", TargetName);

    Fl_Window* ParentWindow = Widget->top_window();
    Fl::delete_widget(ParentWindow);
}

void NewChatCallback(Fl_Widget* Widget, void* Data)
{
    Fl_Window* NewChatWindow = new Fl_Window(300, 130, "New Chat");

    Fl_Box* LabelBox = new Fl_Box(10, 10, 280, 30, "Please enter the name:");
    LabelBox->box(FL_NO_BOX);

    Fl_Input* NameInput = new Fl_Input(10, 50, 280, 30);
    NameInput = NameInput;

    Fl_Button* NewChatButton = new Fl_Button(10, 90, 50, 30, "Ok");
    NewChatButton->box(FL_BORDER_BOX);
    NewChatButton->shortcut(FL_Enter);
    NewChatButton->callback((Fl_Callback*)NewChatWindowCallback, NameInput);

    NewChatWindow->end();
    NewChatWindow->show();
}



void ConnectCallback(Fl_Widget* Widget, void* Data)
{
    fl_message("Connect Callback");
}

void FavoritesCallback(Fl_Widget* Widget, void* Data)
{
    fl_message("Favorites Callback");
}

void AboutCallback(Fl_Widget* Widget, void* Data)
{
    std::string AboutMessage;
    AboutMessage = "About:\n";
    AboutMessage += "Project: ";
    AboutMessage += PROJECT_NAME;
    AboutMessage += "\nAuthor: Lukas Deutscher\n";
    AboutMessage += "Version: ";
    AboutMessage += PROJECT_VERSION_NR;
    AboutMessage += "\nCompile Time: ";
    AboutMessage += __DATE__;
    AboutMessage += " | ";
    AboutMessage += __TIME__;

    fl_message(AboutMessage.c_str());
}

void EditorEnterCallback(Fl_Widget* Widget, void* Data)
{
    //~ if (Fl::event()==FL_KEYBOARD && Fl::event_key()==FL_Enter) {
        //~ SendCallback(Widget, Data);
    //~ }
}

/**
 * @brief Initializes the fltk lib and creates the basic window
 *
 * @return int The init value
 */
int InterfaceInit()
{
    L_INFO("interface", "Started interface init...");

    L_INFO("interface", "Setting base client colors...");
    Fl::background(50, 50, 50);
    Fl::background2(70, 70, 70);
    Fl::foreground(255, 255, 255);

    L_DEBUG("interface", "Creating base window...");
    std::string WindowTitle(PROJECT_NAME);
    WindowTitle += " Ver.: ";
    WindowTitle += PROJECT_VERSION_NR;

    Fl_Window* MainWindow = new Fl_Window(800, 560, WindowTitle.c_str());
    //~ MainWindow->resizable(MainWindow);

    Fl_PNG_Image* MainWindowIcon = new Fl_PNG_Image("../res/icon.png");
    MainWindow->icon(MainWindowIcon);

    L_DEBUG("interface", "Setting message window hotspot.");
    fl_message_hotspot(0);

    L_DEBUG("interface", "Creating menu bar...");
    Fl_Menu_Item MenuItems[] = {
        {"Server", 0, 0, 0, FL_SUBMENU},
            {"Connect", 0, (Fl_Callback*)ConnectCallback},
            {"Favorites", 0, (Fl_Callback*)FavoritesCallback, 0, FL_MENU_DIVIDER},
            {"Quit", 0, (Fl_Callback*)QuitProgram},
            {0},
        {"Chat", 0, 0, 0, FL_SUBMENU},
            {"Friend List", 0, (Fl_Callback*)CreateFriendListWindow},
            {"New Chat", 0, (Fl_Callback*)NewChatCallback},
            {0},
        {"Extra", 0, 0, 0, FL_SUBMENU},
            {"Options", 0, (Fl_Callback*)CreateOptionsWindow},
            {"About", 0, (Fl_Callback*)AboutCallback},
            {0},
        {0}
    };

    Fl_Menu_Bar* MenuBar = new Fl_Menu_Bar(0, 0, 800, 30);
    MenuBar->copy(MenuItems);
    MenuBar->box(FL_BORDER_BOX);

    Fl_Tabs* ChatTabs = new Fl_Tabs(10, 40, 780, 480);
    ChatTabs->end();
    ChatTabs->selection_color(FL_LIGHT1);
    ChatTabs->box(FL_BORDER_BOX);

    gChatTabWidget = ChatTabs;

    //~ DisplayIncomingMessage("Test", "test");

    Fl_Box* InfoBox = new Fl_Box(10, 530, 780, 20);
    InfoBox->box(FL_NO_BOX);
    InfoBox->copy_label("Program started.");
    InfoBox->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT);

    gInfoBox = InfoBox;

    MainWindow->end();
    MainWindow->show();

    gMainWindow = MainWindow;

    L_INFO("interface", "Interface init finished.");

    return 0;
}

/**
 * @brief This function calls the idle callbacks from the window
 *
 * @return int The check value
 */
int InterfaceCheck()
{
    return Fl::check();
}

/**
 * @brief Updates the Info box with the message and scrolls the window
 *
 * @param Message The message to write
 * @return void
 */
void InterfaceSetInfoMsg(const std::string &Message)
{
    gInfoBox->copy_label(Message.c_str());
    gInfoBox->redraw();
}

/**
 * @brief Creates a popup in which the user can answer a question
 *
 * @param Message The message the user gets to see
 * @param If the at sign should be escaped.
 * @return bool The answer
 */
bool InterfaceCreateAskForm(std::string Message, bool ReplaceAtSign)
{
    if (ReplaceAtSign) {
        std::regex RegexStr("@");
        Message = std::regex_replace(Message, RegexStr, "@@");

        L_DEBUG("interface", "Replaced string: " + Message);
    }

    int UserAnswer;
    UserAnswer = fl_choice(Message.c_str(), "Yes", "No", 0);

    if (UserAnswer == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Displays a popup with an error message
 *
 * @param Message The Message to display
 * @param If the at sign should be escaped.
 * @return void
 */
void InterfaceDisplayErrorForm(std::string Message, bool ReplaceAtSign)
{
    if (ReplaceAtSign) {
        std::regex RegexStr("@");
        Message = std::regex_replace(Message, RegexStr, "@@");

        L_DEBUG("interface", "Replaced string: " + Message);
    }

    fl_alert(Message.c_str());
}

/**
 * @brief Display a popup with a message form
 *
 * @param Message the message to display
 * @param If the at sign should be escaped.
 * @return void
 */
void InterfaceDisplayInfoForm(std::string Message, bool ReplaceAtSign)
{
    if (ReplaceAtSign) {
        std::regex RegexStr("@");
        Message = std::regex_replace(Message, RegexStr, "@@");

        L_DEBUG("interface", "Replaced string: " + Message);
    }

    fl_message(Message.c_str());
}

/**
 * @brief This function displays a chat message and creates the display tab
 *
 * @param Text The text to display
 * @param From The String with the username
 * @return void
 */
void DisplayIncomingMessage(const std::string &Text, const std::string &From)
{
    L_DEBUG("interface", "Displaying text message...");

    for (unsigned int i = 0; i != gChatTabs.size(); ++i) {
        if (gChatTabs[i]->ChatTarget == From) {
            gChatTabs[i]->AppendTextToOutput(Text);
            return;
        }
    }

    InterfaceChatTab* ChatTab = new InterfaceChatTab(10, 70, 780, 450, From);
    gChatTabs.push_back(ChatTab);
    gChatTabWidget->add(ChatTab->FlGroup);
    gChatTabWidget->redraw();

    ChatTab->AppendTextToOutput(Text);

    /**
     * If the first tab is opened there would be fragments, so we redraw the window
     */
    if(gChatTabs.size() == 1) {
        gMainWindow->redraw();
    }
}
