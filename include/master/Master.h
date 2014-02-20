#ifndef MASTER_H_
#define MASTER_H_

#include <vector>
#include "lacewing.h"
#include <limits.h>
#include <string>
#include <fmitcp/EventPump.h>

#include "StrongConnection.h"
#include "WeakConnection.h"
#include "Slave.h"
#include "Logger.h"

namespace fmitcp_master {

    class FMIClient;

    enum WeakCouplingAlgorithm {
        SERIAL,
        PARALLEL
    };

    enum MasterState {
        MASTER_IDLE,
        MASTER_INITIALIZING,
        MASTER_TRANSFERRING_WEAK,
        MASTER_TRANSFERRING_STRONG,
        MASTER_STEPPING
    };

    class Master {

    private:
        std::vector<WeakConnection*> m_weakConnections;
        std::vector<StrongConnection*> m_strongConnections;
        std::vector<FMIClient*> m_slaves;
        std::vector<int> m_slave_ids;
        fmitcp::EventPump * m_pump;
        int m_slaveIdCounter;
        fmitcp_master::Logger m_logger;
        WeakCouplingAlgorithm m_method;
        MasterState m_state;
        double m_relativeTolerance;
        double m_timeStep;
        double m_startTime;
        double m_endTime;
        bool m_endTimeDefined;

    public:
        Master();
        Master(const Logger& logger);
        ~Master();

        void init();

        /// Connects to a slave and gets info about it
        int connectSlave(std::string uri);

        FMIClient * getSlave(int id);
        void slaveConnected(FMIClient * slave);
        void slaveDisconnected(FMIClient * slave);
        void slaveError(FMIClient * slave);

        void setTimeStep(double timeStep);
        void setEnableEndTime(bool enable);
        void setEndTime(double endTime);
        void setWeakMethod(WeakCouplingAlgorithm algorithm);

        void createStrongConnection(int slaveA, int slaveB, int connectorA, int connectorB);
        void createWeakConnection(int slaveA, int slaveB, int valueReferenceA, int valueReferenceB);

        void transferWeakConnectionData();

        /// Start simulation
        void simulate();

        void initializeSlaves();

        //bool hasAllClientsState(Slave::SlaveState state);
    };
};

#endif /* MASTER_H_ */
