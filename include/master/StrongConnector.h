#ifndef MASTER_STRONGCONNECTOR_H_
#define MASTER_STRONGCONNECTOR_H_

#include <sc/Connector.h>

namespace fmitcp_master {

    class FMIClient;

    /// Container for value references, that specify a mechanical connector in a simulation slave.
    class StrongConnector {

    protected:

        FMIClient* m_client;
        sc::Connector m_conn;

        bool m_hasPosition;
        int  m_vref_position[3];

        bool m_hasQuaternion;
        int  m_vref_quaternion[4];

        bool m_hasVelocity;
        int  m_vref_velocity[3];

        bool m_hasAngularVelocity;
        int  m_vref_angularVelocity[3];

        bool m_hasForce;
        int  m_vref_force[3];

        bool m_hasTorque;
        int  m_vref_torque[3];

    public:
        StrongConnector(FMIClient* slave);
        virtual ~StrongConnector();

        FMIClient * getSlave();
        sc::Connector * getConnector();

        void setPositionValueRefs(int,int,int);
        void setQuaternionValueRefs(int,int,int,int);
        void setVelocityValueRefs(int,int,int);
        void setAngularVelocityValueRefs(int,int,int);
        void setForceValueRefs(int,int,int);
        void setTorqueValueRefs(int,int,int);

        bool hasPosition();
        bool hasQuaternion();
        bool hasVelocity();
        bool hasAngularVelocity();
        bool hasForce();
        bool hasTorque();

        std::vector<int> getPositionValueRefs() const;
        std::vector<int> getQuaternionValueRefs() const;
        std::vector<int> getVelocityValueRefs() const;
        std::vector<int> getAngularVelocityValueRefs() const;
        std::vector<int> getForceValueRefs() const;
        std::vector<int> getTorqueValueRefs() const;
    };
};

#endif
