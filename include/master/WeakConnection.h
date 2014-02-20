#ifndef WEAKCONNECTION_H_
#define WEAKCONNECTION_H_

#include "Connection.h"
#include "FMIClient.h"

namespace fmitcp_master {

    class WeakConnection : public Connection {

    protected:
        int m_valueRefA;
        int m_valueRefB;

    public:
        WeakConnection( FMIClient* slaveA,
                        FMIClient* slaveB,
                        int valueRefA,
                        int valueRefB );
        ~WeakConnection();

        int getValueRefA();
        int getValueRefB();

    };
};

#endif
