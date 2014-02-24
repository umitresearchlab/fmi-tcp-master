#include "master/StrongConnection.h"
#include "master/Master.h"

using namespace fmitcp_master;

StrongConnection::StrongConnection( StrongConnector* connA, StrongConnector* connB, StrongConnectionType type ) {
    // Check so that all needed connector values are set
    if(type == CONNECTION_LOCK && !(
        connA->hasPosition() &&
        connB->hasPosition() &&
        connA->hasQuaternion() &&
        connB->hasQuaternion() &&
        connA->hasVelocity() &&
        connB->hasVelocity() &&
        connA->hasAngularVelocity() &&
        connB->hasAngularVelocity() &&
        connA->hasForce() &&
        connB->hasForce() &&
        connA->hasTorque() &&
        connB->hasTorque()
        )){
        fprintf(stderr, "Lock connections need connectors with positions, velocities and forces.\n");
        exit(1);
    }
}
StrongConnection::~StrongConnection(){

}
