//***************************************************************************
//
//
// @PROJECT  :    Vulkan Basis Klasse
// @VERSION  :    1.0
// @FILENAME :    main.cpp
// @DATE     :    23.06.2020
//
// @AUTHOR   :    Martin Steen
// @EMAIL    :    martin.steen@ksti.de
//
//
//***************************************************************************

#include <iostream>
#include <CVulkanApp.h>


int main() 
{
    CVulkanApp app;

    try 
    {
        app.run();
    } 
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
