/**
 * @file
 * @brief The option window and logic
 *
 * @author Lukas Deutscher
 * @date 11.07.2018
 */

#include "interface.h"

extern Fl_Window* gOptionsWindow;

void DefaultConfigDisplay()
{
    fl_message("Default button callback");
}

void OptionsColorCallback(Fl_Widget* Widget, void* Data)
{
    std::string *ColorConfigString = (std::string*)Data;

    L_DEBUG("interface", "Options: Setting color: " + *ColorConfigString);

    InterfaceColor *Background = ReadConfigColor(*ColorConfigString);

    L_DEBUG("interface", "Color: " + Background->Dump());

    // 1 Is the byte mode.
    int ColorChooserMode = 1;

    bool ChangedColor = fl_color_chooser(
        GetLocaleStringPtr("options.color.dialog")->c_str(),
        Background->r,
        Background->g,
        Background->b,
        ColorChooserMode
    );

    if (ChangedColor) {
        L_DEBUG("interface", "User changed color. Setting color to: " + Background->Dump());
    } else {

    }
}

void CreateOptionsWindow()
{
    std::string* WindowTitle = GetLocaleStringPtr("options.window.title");
    Fl_Window* OptionsWindow = FactNewWindow("interface.options.size", WindowTitle);

    // Header
    Fl_Box* BoxHeader = FactNewBox("interface.options.header.dimension");
    BoxHeader->box(FL_BORDER_BOX);
    BoxHeader->copy_label(GetLocaleStringPtr("options.header")->c_str());

    // Write Default Config
    Fl_Button* ButtonDefaultConfig = FactNewButton("interface.options.defaultbutton.dimension");
    ButtonDefaultConfig->box(FL_BORDER_BOX);
    ButtonDefaultConfig->copy_label(GetLocaleStringPtr("options.defaultbutton")->c_str());
    ButtonDefaultConfig->callback((Fl_Callback*)DefaultConfigDisplay);

    std::string* ColorBackgroundLabel = GetLocaleStringPtr("options.colorbackground");
    Fl_Button* ButtonColorBackground = FactNewButton("interface.options.colorbackground.dimension");
    ButtonColorBackground->copy_label(ColorBackgroundLabel->c_str());
    std::string *BackgroundColorConfigString = new std::string("interface.color.background");
    ButtonColorBackground->callback((Fl_Callback*)OptionsColorCallback, (void*)BackgroundColorConfigString);

    OptionsWindow->end();
    OptionsWindow->show();

    gOptionsWindow = OptionsWindow;
}
