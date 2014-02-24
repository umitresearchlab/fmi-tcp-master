#include "master/StrongConnection.h"
#include "master/Master.h"

using namespace fmitcp_master;

StrongConnection::StrongConnection( FMIClient* slaveA,
                                    int vref_positionA_x,           int vref_positionA_y,           int vref_positionA_z,
                                    int vref_quaternionA_x,         int vref_quaternionA_y,         int vref_quaternionA_z,         int vref_quaternionA_w,
                                    int vref_velocityA_x,           int vref_velocityA_y,           int vref_velocityA_z,
                                    int vref_angularVelocityA_x,    int vref_angularVelocityA_y,    int vref_angularVelocityA_z,
                                    int vref_forceA_x,              int vref_forceA_y,              int vref_forceA_z,
                                    int vref_torqueA_x,             int vref_torqueA_y,             int vref_torqueA_z,

                                    FMIClient* slaveB,
                                    int vref_positionB_x,           int vref_positionB_y,           int vref_positionB_z,
                                    int vref_quaternionB_x,         int vref_quaternionB_y,         int vref_quaternionB_z,         int vref_quaternionB_w,
                                    int vref_velocityB_x,           int vref_velocityB_y,           int vref_velocityB_z,
                                    int vref_angularVelocityB_x,    int vref_angularVelocityB_y,    int vref_angularVelocityB_z,
                                    int vref_forceB_x,              int vref_forceB_y,              int vref_forceB_z,
                                    int vref_torqueB_x,             int vref_torqueB_y,             int vref_torqueB_z) : Connection(slaveA,slaveB) {

    m_vref_positionA[0] = vref_positionA_x;
    m_vref_positionA[1] = vref_positionA_y;
    m_vref_positionA[2] = vref_positionA_z;

    m_vref_quaternionA[0] = vref_quaternionA_x;
    m_vref_quaternionA[1] = vref_quaternionA_y;
    m_vref_quaternionA[2] = vref_quaternionA_z;
    m_vref_quaternionA[3] = vref_quaternionA_w;

    m_vref_velocityA[0] = vref_velocityA_x;
    m_vref_velocityA[1] = vref_velocityA_y;
    m_vref_velocityA[2] = vref_velocityA_z;

    m_vref_angularVelocityA[0] = vref_angularVelocityA_x;
    m_vref_angularVelocityA[1] = vref_angularVelocityA_y;
    m_vref_angularVelocityA[2] = vref_angularVelocityA_z;

    m_vref_forceA[0] = vref_forceA_x;
    m_vref_forceA[1] = vref_forceA_y;
    m_vref_forceA[2] = vref_forceA_z;

    m_vref_torqueA[0] = vref_torqueA_x;
    m_vref_torqueA[1] = vref_torqueA_y;
    m_vref_torqueA[2] = vref_torqueA_z;


    m_vref_positionB[0] = vref_positionB_x;
    m_vref_positionB[1] = vref_positionB_y;
    m_vref_positionB[2] = vref_positionB_z;

    m_vref_quaternionB[0] = vref_quaternionB_x;
    m_vref_quaternionB[1] = vref_quaternionB_y;
    m_vref_quaternionB[2] = vref_quaternionB_z;
    m_vref_quaternionB[3] = vref_quaternionB_w;

    m_vref_velocityB[0] = vref_velocityB_x;
    m_vref_velocityB[1] = vref_velocityB_y;
    m_vref_velocityB[2] = vref_velocityB_z;

    m_vref_angularVelocityB[0] = vref_angularVelocityB_x;
    m_vref_angularVelocityB[1] = vref_angularVelocityB_y;
    m_vref_angularVelocityB[2] = vref_angularVelocityB_z;

    m_vref_forceB[0] = vref_forceB_x;
    m_vref_forceB[1] = vref_forceB_y;
    m_vref_forceB[2] = vref_forceB_z;

    m_vref_torqueB[0] = vref_torqueB_x;
    m_vref_torqueB[1] = vref_torqueB_y;
    m_vref_torqueB[2] = vref_torqueB_z;

}
StrongConnection::~StrongConnection(){

}
