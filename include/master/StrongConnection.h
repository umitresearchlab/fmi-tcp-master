#ifndef STRONGCONNECTION_H_
#define STRONGCONNECTION_H_

#include "Connection.h"

namespace fmitcp_master {

    class StrongConnection : public Connection {
    private:
        int m_connectorRefA;
        int m_connectorRefB;

        bool m_usePositions;
        int  m_vref_positionA[3];
        int  m_vref_positionB[3];

        bool m_useQuaternions;
        int  m_vref_quaternionA[4];
        int  m_vref_quaternionB[4];

        bool m_useVelocities;
        int  m_vref_velocityA[3];
        int  m_vref_velocityB[3];

        bool m_useAngularVelocities;
        int  m_vref_angularVelocityA[3];
        int  m_vref_angularVelocityB[3];

        bool m_useForce;
        int  m_vref_forceA[3];
        int  m_vref_forceB[3];

        bool m_useTorque;
        int  m_vref_torqueA[3];
        int  m_vref_torqueB[3];

    public:
        StrongConnection(   FMIClient* slaveA,
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
                            int vref_torqueB_x,             int vref_torqueB_y,             int vref_torqueB_z);
        virtual ~StrongConnection();
    };
};

#endif
