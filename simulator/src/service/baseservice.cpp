/* 
 * File:   base.cpp
 * Author: mkh
 * 
 * Created on 5 февраля 2023 г., 16:14
 */

#include "baseservice.h"

#ifdef QT_CORE_LIB
#include "qservice.h"
#else
#include "glfwservice.h"
#endif

std::unique_ptr< baseservice > baseservice::make()
{
#ifdef QT_CORE_LIB
    return std::unique_ptr< baseservice >(new qservice);
#else
    return std::unique_ptr< baseservice >(new glfwservice);
#endif
}

baseservice::baseservice()
: frame_( new jpegframe )
, poll_( frame_.get() )
, poll_thread_( &poll_ )
{
}

baseservice::~baseservice()
{
}

void baseservice::run()
{
    screen_->run();
    f_run();
}

int baseservice::stop()
{
    if( screen_ )
    {
        screen_->stop();
    }
    return f_stop();
}