/**
 * @file
 * @brief The main file.
 *
 * Here in this file we start the program,
 * and select the specific main function to run.
 *
 * @author Lukas Deutscher
 * @date 07.12.2017
 */

#include "client_main.h" // The client main

/**
 * @brief The standard main function.
 *
 * The standard main function in which we select the specific main to run.
 *
 * @param argc The number of arguments
 * @param argv The array of string params
 * @return int The return value
 */
int main(int argc, char** argv)
{
    /**
     * At the moment we select for default the client main.
     * @warning Change this at a later date in the project to hold a test.
     */
    return ClientMain(argc, argv);
}
