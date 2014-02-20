#include "master/Logger.h"
#include "stdio.h"

fmitcp_master::Logger::Logger(){

}

fmitcp_master::Logger::~Logger(){

}

void fmitcp_master::Logger::log(fmitcp_master::Logger::LogMessageType type, const char * format, ...){
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}
