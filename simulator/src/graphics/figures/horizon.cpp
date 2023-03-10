/* 
 * File:   horizon.cpp
 * Author: mkh
 * 
 * Created on 13 февраля 2023 г., 17:58
 */

#include "horizon.h"

horizon::horizon( const std::vector< std::string > &settings )
: figure( settings )
{
    f_check_environment();
    avi_.reset( new avi( (std::string(utils::config()["textures"]) + "/" + spec_.texture_name).c_str() ) );
}

horizon::~horizon()
{
}

void horizon::f_check_environment() const
{
    if( ! (utils::file_exists( (std::string(utils::config()["shaders"]) + "/vert_" + spec_.shader_name).c_str() ) &&
           utils::file_exists( (std::string(utils::config()["shaders"]) + "/frag_" + spec_.shader_name).c_str() ) &&
           utils::file_exists( (std::string(utils::config()["textures"]) + "/" + spec_.texture_name).c_str() )) )
    {
        throw  std::runtime_error( std::string("invalid environment in {") + spec_.shader_name + " " + spec_.texture_name + "}"  );
    }
}

char const *horizon::f_shader_name() const
{
    return spec_.shader_name.c_str(); 
}

void horizon::f_initialize()
{
    texture_.reset( new texture( avi_->next_image() ) );

    glBufferData( GL_ARRAY_BUFFER, spec_.viewport.size() * sizeof(float), spec_.viewport.data(), GL_STATIC_DRAW );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW); 
    set_layout( "position", 3, 5, 0 );
    set_layout( "texcoord", 2, 5, 3 );
}

void horizon::f_draw( double current_time )
{
    if( last_frame_time_ < 0.01f )
    {
        last_frame_time_ = current_time;
    }
    if( current_time - last_frame_time_ >= avi_->frame_duration() )
    {
        *texture_ = avi_->next_image();
        last_frame_time_ = current_time;
    }
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}
