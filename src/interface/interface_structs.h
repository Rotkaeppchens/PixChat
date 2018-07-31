/**
 * @file
 * @brief Structs for easier access
 *
 * @author Lukas Deutscher
 * @date 08.07.2018
 */

#ifndef INTERFACE_STRUCTS_H
#define INTERFACE_STRUCTS_H

#include <string>

struct InterfaceColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    std::string Dump()
    {
        std::string DumpStr;
        DumpStr += "r: ";
        DumpStr += std::to_string(this->r);
        DumpStr += " g: ";
        DumpStr += std::to_string(this->g);
        DumpStr += " b: ";
        DumpStr += std::to_string(this->b);

        return DumpStr;
    }
};

struct InterfaceSize
{
    int x;
    int y;
};

struct InterfaceDimension
{
    int x;
    int y;
    int w;
    int h;
};

#endif
