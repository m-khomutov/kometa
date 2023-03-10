/* 
 * File:   main.cpp
 * Author: mkh
 *
 * Created on 23 января 2023 г., 18:31
 */

#include "service/baseservice.h"
#include "../../share/utils.h"
#ifdef QT_CORE_LIB
# include <QApplication>
#endif

#include <stdlib.h>
#include <signal.h>
#include <getopt.h>

#include <iostream>

/*
 * 
 */

namespace
{

void signal_handler( int s )
{
    baseservice::instance().onsignal( s );
}

void show_options_and_exit( const char *prog, int rc )
{
    std::cerr << "Запуск: " << prog <<  "[-h] [-s] [-t] [-p] [-q] [-d] [-w] [-o] [-c]\n\nэмулятор устройства\n\n";
    std::cerr << "обязательные аргументы:\n";
    std::cerr << "\t-s\tкаталог с шейдерами\n"; 
    std::cerr << "\t-t\tкаталог с текстурами\n"; 
    std::cerr << "Опциональные аргументы:\n";
    std::cerr << "\t-p\tпорт прослушки (def. 2232)\n"; 
    std::cerr << "\t-w\tразмеры окна (def. 800x600)\n";
    std::cerr << "\t-q\tкачество сжатия % (def. 80)\n";
    std::cerr << "\t-d\tдлительность кадра мс (def. 40)\n";
    std::cerr << "\t-c\tфайл конфигурации\n";
    std::cerr << "\t-o\tкаталог с объектами blender\n"; 
    std::cerr << "\t-h\tвывод параметров запуска\n";
    ::exit( rc );   
}
}

int main(int argc, char** argv)
{
    try
    {
        utils::config( argc, argv );
        utils::config()["shaders"];
        utils::config()["textures"];
    }
    catch( const std::runtime_error &e )
    {
        std::cerr << e.what() <<std::endl;
        show_options_and_exit( argv[0], EXIT_FAILURE );
    }

    signal( SIGHUP,  signal_handler );
    signal( SIGTERM, signal_handler );
    signal( SIGSEGV, signal_handler);
    signal( SIGINT,  signal_handler);
    
#ifdef QT_CORE_LIB
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL, true);
    QApplication a(argc, argv);
#endif
    try
    {
        std::setlocale( LC_NUMERIC,"C" );

        baseservice::instance().run();
        return baseservice::instance().stop();
    }
    catch( const std::runtime_error &err )
    {
        std::cerr << "1. error: " << err.what() << "\n";
    }
    catch( ...)
    {
        std::exception_ptr ep = std::current_exception();
        if( ep )
        {
            try
            {
                std::rethrow_exception( ep );
            }
            catch( const std::exception& e )
            {
                std::cout << "exception: " << e.what() << "\n";
            }
        }
    }

    return (EXIT_FAILURE);
}
