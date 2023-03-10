/* 
 * File:   screen.h
 * Author: mkh
 *
 * Created on 24 января 2023 г., 9:19
 */

#ifndef GLFWSCREEN_H
#define GLFWSCREEN_H

#include "../shader.h"
#include "basescreen.h"
#include <GLFW/glfw3.h>
#include <memory>


class glfwscreen: public basescreen {
public:
    explicit glfwscreen( baseframe *frame );
    glfwscreen(const glfwscreen& orig) = delete;
    glfwscreen &operator =(const glfwscreen &rhs) = delete;
    ~glfwscreen();

    void run() override;
    void stop() override;

private:
    struct del { void operator()(GLFWwindow * w) { glfwDestroyWindow( w ); glfwTerminate(); } };
    std::unique_ptr< GLFWwindow, del > window_;
    baseframe *frame_;

private:
    static void error_cb( int error, const GLchar * description );
};

#endif /* GLFWSCREEN_H */
