/**
 * @file
 * @brief The functions for the interface chat tab class
 *
 * @author Lukas Deutscher
 * @date 31.12.2017
 */

#include "interface.h"

/**
 * @brief The Inteerface chat tab constructor
 *
 * @param x The x value of the tab
 * @param y The y value of the tab
 * @param w The w value of the tab
 * @param h The h value of the tab
 * @param Target The chat target, will be displayed on the tab
 */
InterfaceChatTab::InterfaceChatTab(int x, int y, int w, int h, const std::string &Target)
{
    L_INFO("interface", "Instantiating chat tab...");
    L_INFO("interface", "Chat target: " + Target);

    this->ChatTarget = Target;

    this->FlGroup = new Fl_Group(x, y, w, h, this->ChatTarget.c_str());
    {
        /**
         * Text Output
         */
        Fl_Text_Display* Display = new Fl_Text_Display(x + 10, y + 10, w - 20, 250);
        Fl_Text_Buffer* DisplayTextBuffer = new Fl_Text_Buffer();
        Display->buffer(DisplayTextBuffer);
        // Style
        Display->box(FL_BORDER_BOX);
        Display->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);

        this->TextOutput = Display;

        /**
         * Text Input
         */
        Fl_Text_Editor* InputEditor = new Fl_Text_Editor(x + 10, y + 270, w - 130, 140);
        Fl_Text_Buffer* InputTextBuffer = new Fl_Text_Buffer();
        InputEditor->buffer(InputTextBuffer);
        // Style
        InputEditor->box(FL_BORDER_BOX);
        InputEditor->cursor_style(Fl_Text_Editor::CARET_CURSOR);
        InputEditor->cursor_color(FL_WHITE);
        InputEditor->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);

        this->TextInput = InputEditor;

        /**
         * Send Button
         */
        Fl_Button* SendButton = new Fl_Button(680, y + 270, 100, 140, "Send");
        SendButton->type(FL_NORMAL_BUTTON);
        SendButton->shortcut(FL_Enter);
        SendButton->callback((Fl_Callback*)SendCallbackMaster, this);
        // Style
        SendButton->box(FL_BORDER_BOX);

        this->SendButton = SendButton;

        /**
         * Event Label
         */
        Fl_Box* EventBox = new Fl_Box(x + 10, y + 420, w - 20, 20, "EVENT");
        EventBox->box(FL_BORDER_BOX);
        EventBox->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT);

        this->EventBox = EventBox;
    }
    // End Fl Group
    this->FlGroup->end();
}

void InterfaceChatTab::AppendTextToOutput(const std::string &Text)
{
    this->TextOutput->buffer()->append(Text.c_str());

    int BufferLength = this->TextOutput->buffer()->length();
    int CntLines = this->TextOutput->buffer()->count_lines(0, BufferLength);

    this->TextOutput->scroll(CntLines, 0);

    this->TextOutput->redraw();
}

void InterfaceChatTab::SetEventMessage(const std::string &Text)
{
    L_INFO("interface", "Set tab event message to: " + Text);

    this->EventBox->copy_label(Text.c_str());
    this->EventBox->redraw();
}
