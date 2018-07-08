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
