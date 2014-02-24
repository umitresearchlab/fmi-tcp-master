#include "master/FMIClient.h"

using namespace fmitcp_master;

StrongConnector::StrongConnector(FMIClient* slave){

}

StrongConnector::~StrongConnector(){

}

void StrongConnector::setPositionValueRefs(int x, int y, int z){
    m_usePosition = true;
    m_vref_position[0] = x;
    m_vref_position[1] = y;
    m_vref_position[2] = z;
}

void StrongConnector::setQuaternionValueRefs(int x, int y, int z, int w){
    m_useQuaternion = true;
    m_vref_quaternion[0] = x;
    m_vref_quaternion[1] = y;
    m_vref_quaternion[2] = z;
    m_vref_quaternion[3] = w;
}

void StrongConnector::setVelocityValueRefs(int x, int y, int z){
    m_useVelocity = true;
    m_vref_velocity[0] = x;
    m_vref_velocity[1] = y;
    m_vref_velocity[2] = z;
}

void StrongConnector::setAngularVelocityValueRefs(int x, int y, int z){
    m_useAngularVelocity = true;
    m_vref_angularVelocity[0] = x;
    m_vref_angularVelocity[1] = y;
    m_vref_angularVelocity[2] = z;
}

void StrongConnector::setForceValueRefs(int x, int y, int z){
    m_useForce = true;
    m_vref_force[0] = x;
    m_vref_force[1] = y;
    m_vref_force[2] = z;
}

void StrongConnector::setTorqueValueRefs(int x, int y, int z){
    m_useTorque = true;
    m_vref_torque[0] = x;
    m_vref_torque[1] = y;
    m_vref_torque[2] = z;
}
