#ifndef MASTER_STRONGCONNECTOR_H_
#define MASTER_STRONGCONNECTOR_H_

namespace fmitcp_master {

    class FMIClient;

    /// Container for value references, that specify a mechanical connector in a simulation slave.
    class StrongConnector {

    protected:

        FMIClient* m_client;

        bool m_usePosition;
        int  m_vref_position[3];

        bool m_useQuaternion;
        int  m_vref_quaternion[4];

        bool m_useVelocity;
        int  m_vref_velocity[3];

        bool m_useAngularVelocity;
        int  m_vref_angularVelocity[3];

        bool m_useForce;
        int  m_vref_force[3];

        bool m_useTorque;
        int  m_vref_torque[3];

    public:
        StrongConnector(FMIClient* slave);
        virtual ~StrongConnector();
        FMIClient * getSlave();

        void setPositionValueRefs(int,int,int);
        void setQuaternionValueRefs(int,int,int,int);
        void setVelocityValueRefs(int,int,int);
        void setAngularVelocityValueRefs(int,int,int);
        void setForceValueRefs(int,int,int);
        void setTorqueValueRefs(int,int,int);
    };
};

#endif
