#ifndef MASTER_LOGGER_H_
#define MASTER_LOGGER_H_

#include <stdarg.h>

namespace fmitcp_master {

    class Logger {
    public:

        enum LogMessageType {
            DEBUG,
            NETWORK
        };

        Logger();
        virtual ~Logger();
        virtual void log(fmitcp_master::Logger::LogMessageType type, const char * format, ...);
    };

};

#endif
