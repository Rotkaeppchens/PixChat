/**
 * @file
 * @brief Utils for the internal use in the interface.
 *
 * @author Lukas Deutscher
 * @date 08.07.2018
 */

#include "interface.h"

InterfaceColor *ReadConfigColor(const std::string &Key)
{
    InterfaceColor *Color = new InterfaceColor();

    std::string ConfigDelimiter = ReadConfigString("interface.color.delimiter");

    std::vector<int> ConfigVec = ReadConfigIntVec(Key, ConfigDelimiter);

    if (ConfigVec.size() != 3) {
        L_WARNING("interface", "Color key: " + Key + " doesnt exist. Using fallback.");

        ConfigVec = ReadConfigIntVec("interface.color.default", ConfigDelimiter);
    }

    Color->r = ConfigVec[0];
    Color->g = ConfigVec[1];
    Color->b = ConfigVec[2];

    return Color;
}

InterfaceSize *ReadConfigSize(const std::string &ConfigKey)
{
    InterfaceSize *Size = new InterfaceSize();

    std::string Delimiter = ReadConfigString("interface.size.delimiter");

    std::vector<int> ConfigVec = ReadConfigIntVec(ConfigKey, Delimiter);

    if (ConfigVec.size() != 2) {
        L_WARNING("interface", "Size key: " + ConfigKey + " doesnt exist.");

        return Size;
    }

    Size->x = ConfigVec[0];
    Size->y = ConfigVec[1];

    return Size;
}

InterfaceDimension *ReadConfigDimension(const std::string &ConfigKey)
{
    InterfaceDimension *Dimension = new InterfaceDimension();

    std::string Delimiter = ReadConfigString("interface.size.delimiter");

    std::vector<int> ConfigVec = ReadConfigIntVec(ConfigKey, Delimiter);

    if (ConfigVec.size() != 4) {
        L_WARNING("interface", "Dimension key: " + ConfigKey + " doesnt exist.");

        return Dimension;
    }

    Dimension->x = ConfigVec[0];
    Dimension->y = ConfigVec[1];
    Dimension->w = ConfigVec[2];
    Dimension->h = ConfigVec[3];

    return Dimension;
}

Fl_PNG_Image *GetPngImgResource(const std::string &ConfigKey)
{
    std::string File = ReadConfigString(ConfigKey);
    std::string Path = ReadConfigString("interface.resource.path") + File;

    L_DEBUG("interface", "Loading png resource: " + Path);

    Fl_PNG_Image *Image = new Fl_PNG_Image(Path.c_str());

    return Image;
}
