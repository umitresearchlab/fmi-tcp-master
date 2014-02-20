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
        SERIAL = 1,
        PARALLEL = 2
    };

    enum MasterState {
        MASTER_IDLE = 1,
        MASTER_INITIALIZING = 2,
        MASTER_TRANSFERRING_WEAK = 4,
        MASTER_TRANSFERRING_STRONG = 8,
        MASTER_STEPPING = 16
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
        void clientConnected(FMIClient * client);
        //void clientDisconnected(lw_client client);
        //void clientData(lw_client client, const char* data, long size);

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
