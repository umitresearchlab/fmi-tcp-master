#ifndef STRONGCONNECTION_H_
#define STRONGCONNECTION_H_

#include "Connection.h"

namespace fmitcp_master {

    class StrongConnection : public Connection {
    private:
        int m_connectorRefA;
        int m_connectorRefB;

    public:
        StrongConnection(FMIClient* slaveA,
                         FMIClient* slaveB,
                         int connectorRefA,
                         int connectorRefB );
        ~StrongConnection();
    };
};

#endif
