#include "master/StrongConnection.h"
#include "master/Master.h"

using namespace fmitcp_master;

StrongConnection::StrongConnection( FMIClient* slaveA,
                                    FMIClient* slaveB,
                                    int connectorRefA,
                                    int connectorRefB ) : Connection(slaveA,slaveB) {
    m_connectorRefA = connectorRefA;
    m_connectorRefB = connectorRefB;
}
StrongConnection::~StrongConnection(){

}
