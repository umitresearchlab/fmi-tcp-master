#include "master/FMIClient.h"

using namespace fmitcp_master;

StrongConnector::StrongConnector(FMIClient* slave){

}

StrongConnector::~StrongConnector(){

}

void StrongConnector::setPositionValueRefs(int x, int y, int z){
    m_hasPosition = true;
    m_vref_position[0] = x;
    m_vref_position[1] = y;
    m_vref_position[2] = z;
}

void StrongConnector::setQuaternionValueRefs(int x, int y, int z, int w){
    m_hasQuaternion = true;
    m_vref_quaternion[0] = x;
    m_vref_quaternion[1] = y;
    m_vref_quaternion[2] = z;
    m_vref_quaternion[3] = w;
}

void StrongConnector::setVelocityValueRefs(int x, int y, int z){
    m_hasVelocity = true;
    m_vref_velocity[0] = x;
    m_vref_velocity[1] = y;
    m_vref_velocity[2] = z;
}

void StrongConnector::setAngularVelocityValueRefs(int x, int y, int z){
    m_hasAngularVelocity = true;
    m_vref_angularVelocity[0] = x;
    m_vref_angularVelocity[1] = y;
    m_vref_angularVelocity[2] = z;
}

void StrongConnector::setForceValueRefs(int x, int y, int z){
    m_hasForce = true;
    m_vref_force[0] = x;
    m_vref_force[1] = y;
    m_vref_force[2] = z;
}

void StrongConnector::setTorqueValueRefs(int x, int y, int z){
    m_hasTorque = true;
    m_vref_torque[0] = x;
    m_vref_torque[1] = y;
    m_vref_torque[2] = z;
}


bool StrongConnector::hasPosition(){ return m_hasPosition; };
bool StrongConnector::hasQuaternion(){ return m_hasQuaternion; };
bool StrongConnector::hasVelocity(){ return m_hasVelocity; };
bool StrongConnector::hasAngularVelocity(){ return m_hasAngularVelocity; };
bool StrongConnector::hasForce(){ return m_hasForce; };
bool StrongConnector::hasTorque(){ return m_hasTorque; };

std::vector<int> StrongConnector::getForceValueRefs() const {
    std::vector<int> result;
    for(int i=0; m_hasForce && i<3; i++)
        result.push_back(m_vref_force[i]);
    return result;
};

std::vector<int> StrongConnector::getVelocityValueRefs() const {
    std::vector<int> result;
    if(m_hasVelocity){
        for(int i=0; i<3; i++)
            result.push_back(m_vref_velocity[i]);
    }
    return result;
};

std::vector<int> StrongConnector::getPositionValueRefs() const {
    std::vector<int> result;
    for(int i=0; m_hasPosition && i<3; i++)
        result.push_back(m_vref_position[i]);
    return result;
};

std::vector<int> StrongConnector::getQuaternionValueRefs() const {
    std::vector<int> result;
    for(int i=0; m_hasQuaternion && i<4; i++)
        result.push_back(m_vref_quaternion[i]);
    return result;
};

std::vector<int> StrongConnector::getAngularVelocityValueRefs() const {
    std::vector<int> result;
    for(int i=0; m_hasAngularVelocity && i<3; i++)
        result.push_back(m_vref_angularVelocity[i]);
    return result;
};

std::vector<int> StrongConnector::getTorqueValueRefs() const {
    std::vector<int> result;
    for(int i=0; m_hasTorque && i<3; i++)
        result.push_back(m_vref_torque[i]);
    return result;
};

sc::Connector * StrongConnector::getConnector(){
    return &m_conn;
}
