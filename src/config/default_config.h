/**
 * @file
 * @brief In this header there will be the default values for the config keys
 *
 * @author Lukas Deutscher
 * @date 06.07.2018
 */

#include "config.h"

/**
 * @brief Returns the default config map
 *
 * @return map The default map
 */
std::map<std::string, std::string> GetDefaultConfigMap()
{
    // The default map
    std::map<std::string, std::string> DefaultConfigMap;

    // The log options
    DefaultConfigMap["client.log.path"] = "../log/";
    DefaultConfigMap["client.log.file"] = "general.log";
    DefaultConfigMap["client.log.level.default"] = "INFO";

    // The time to wait for a timeout
    DefaultConfigMap["client.gloox.updatetime"] = "10";

    // Possible values disabled, optional, required
    DefaultConfigMap["client.tls.active"] = "required";

    // Locale File options
    DefaultConfigMap["client.locale.path"] = "../loc/";
    DefaultConfigMap["client.locale.file"] = "en";
    DefaultConfigMap["client.locale.post"] = ".loc";
    // This value is the max length of the line read buffer
    DefaultConfigMap["client.locale.bufferlength"] = "256";
    DefaultConfigMap["client.locale.keydelimiter"] = ":";

    // Interface values
    DefaultConfigMap["interface.color.delimiter"]   = ",";
    DefaultConfigMap["interface.color.default"]     = "100,100,100";
    DefaultConfigMap["interface.color.background"]  = "50,50,50";
    DefaultConfigMap["interface.color.background2"] = "70,70,70";
    DefaultConfigMap["interface.color.foreground"]  = "255,255,255";

    DefaultConfigMap["interface.size.delimiter"] = ",";

    DefaultConfigMap["interface.message.hotspot"] = "0";

    DefaultConfigMap["interface.resource.path"] = "../res/";

    DefaultConfigMap["interface.mainwindow.size"] = "800,560";
    DefaultConfigMap["interface.mainwindow.icon"] = "icon.png";

    DefaultConfigMap["interface.newchat.window.size"]       = "300,130";
    DefaultConfigMap["interface.newchat.label.dimension"]   = "10,10,280,30";
    DefaultConfigMap["interface.newchat.button.dimension"]  = "10,90,50,30";

    DefaultConfigMap["interface.options.size"] = "300,130";
    DefaultConfigMap["interface.options.header.dimension"] = "10,10,280,30";
    DefaultConfigMap["interface.options.defaultbutton.dimension"] = "10,50,280,30";
    DefaultConfigMap["interface.options.colorbackground.dimension"] = "10,90,280,30";

    return DefaultConfigMap;
}
