/**
 * @file
 * @brief A factory file to create Widgets from Config
 *
 * @author Lukas Deutscher
 * @date 08.07.2018
 */

#include "interface.h"

Fl_Window *FactNewWindow(const std::string &SizeKey, std::string *WindowTitle)
{
    L_DEBUG("interface", "factory: Creating new window from key: " + SizeKey);

    InterfaceSize *Size = ReadConfigSize(SizeKey);

    Fl_Window *Window = new Fl_Window(Size->x, Size->y, WindowTitle->c_str());

    return Window;
}

Fl_Button *FactNewButton(const std::string &DimensionKey)
{
    L_DEBUG("interface", "factory: Creating new button from key: " + DimensionKey);

    InterfaceDimension *Dimension = ReadConfigDimension(DimensionKey);

    Fl_Button *Button = new Fl_Button(
        Dimension->x,
        Dimension->y,
        Dimension->w,
        Dimension->h
    );

    return Button;
}

Fl_Box *FactNewBox(const std::string &DimensionKey)
{
    L_DEBUG("interface", "factory: Creating new box from key: " + DimensionKey);

    InterfaceDimension *Dimension = ReadConfigDimension(DimensionKey);

    Fl_Box *Box = new Fl_Box(
        Dimension->x,
        Dimension->y,
        Dimension->w,
        Dimension->h
    );

    return Box;
}
