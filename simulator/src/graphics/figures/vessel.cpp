/* 
 * File:   vessel.cpp
 * Author: mkh
 * 
 * Created on 16 февраля 2023 г., 13:11
 */

#include "vessel.h"

namespace
{
char const shader_name[] = "vessel.glsl";
char const obj_name[] = "/vessel.obj";
}

bool vessel::environment_valid()
{
    return utils::file_exists( (std::string(utils::config()["shaders"]) + "/vert_" + shader_name).c_str() ) &&
           utils::file_exists( (std::string(utils::config()["shaders"]) + "/frag_" + shader_name).c_str() ) &&
           utils::file_exists( (std::string(utils::config()["objs"]) + obj_name).c_str() );
}

vessel::vessel()
{
    speed_ = glm::vec3( 0.00035f, -0.00015f, 0.0f );
    offset_ = initial_offset; 
    
    objreader reader( (std::string(utils::config()["objs"]) + obj_name).c_str() );
    reader.load_position( &position_ );
    facecount_ = reader.facecount();
    
    f_set_model();
}

vessel::~vessel()
{
}

char const *vessel::f_shader_name() const
{
    return shader_name; 
}

void vessel::f_initialize()
{
    glBufferData( GL_ARRAY_BUFFER, position_.size() * sizeof(GLfloat), position_.data(), GL_STATIC_DRAW );
    set_layout( "position", 3, 8, 0 );
    set_layout( "texcoord", 2, 8, 3 );
    set_layout( "normal", 3, 8, 5 );
}

void vessel::f_draw( double currentTime )
{
    f_set_model();
    glDrawArrays( GL_TRIANGLES, 0, facecount_ * 3 );
}

void vessel::f_set_model()
{
    if( angle_ < -maxlurch || angle_ > maxlurch )
    {
        lurch_ *= -1;
    }
    model_ = glm::mat4( glm::scale(
                            glm::translate(
                                glm::rotate( glm::mat4(1.0f),
                                             glm::radians( angle_ ),
                                             glm::vec3( 1.0f, 0.0f, 0.0f ) ),
                                offset_ ),
                            factor_ ) );
    if( offset_.x < 1.4f )
    {
        offset_ += speed_;
        factor_ += factor_offset;
    }
    else
    {
        offset_ = initial_offset; 
        factor_ = initial_factor;
    }
    angle_ += lurch_;
}
