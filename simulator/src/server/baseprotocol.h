/* 
 * File:   baseprotocol.h
 * Author: mkh
 *
 * Created on 25 января 2023 г., 14:59
 */

#ifndef BASEPROTOCOL_H
#define BASEPROTOCOL_H

#include <stdexcept>

class protocol_error: public std::runtime_error
{
public:
    protocol_error( const std::string & what );
};

class baseprotocol {
public:
    explicit baseprotocol( int sock );
    baseprotocol(const baseprotocol& orig) = delete;
    baseprotocol &operator =(const baseprotocol& orig) = delete;
    virtual ~baseprotocol();

    virtual void on_data( const uint8_t * data, int size ) = 0;
    virtual void do_write() = 0;
    virtual void send_frame( const uint8_t * data, int size, float duration ) = 0;
    
protected:
    int fd_;

private:

};

#endif /* BASEPROTOCOL_H */

