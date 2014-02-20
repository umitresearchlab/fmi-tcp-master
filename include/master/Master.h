#ifndef MASTER_H_
#define MASTER_H_

#include <vector>
#include "lacewing.h"
#include <limits.h>
#include <string>
#include <fmitcp/EventPump.h>
#include <fmitcp/Logger.h>

#include "master/StrongConnection.h"
#include "master/WeakConnection.h"

namespace fmitcp_master {

    class FMIClient;

    enum WeakCouplingAlgorithm {
        SERIAL,
        PARALLEL
    };

    enum MasterState {
        MASTER_STATE_START,
        MASTER_STATE_CONNECTING_SLAVES,
        MASTER_STATE_FETCHING_VERSION,
        MASTER_STATE_FETCHING_XML,
        MASTER_STATE_INSTANTIATING_SLAVES,
        MASTER_STATE_INITIALIZING_SLAVES,
        MASTER_STATE_TRANSFERRING_WEAK,
        MASTER_STATE_FETCHING_DIRECTIONAL_DERIVATIVES,
        MASTER_STATE_TRANSFERRING_STRONG,
        MASTER_STATE_STEPPING_SLAVES
    };

    class Master {

    private:
        std::vector<WeakConnection*> m_weakConnections;
        std::vector<StrongConnection*> m_strongConnections;
        std::vector<FMIClient*> m_slaves;
        std::vector<int> m_slave_ids;
        fmitcp::EventPump * m_pump;
        int m_slaveIdCounter;
        fmitcp::Logger m_logger;
        WeakCouplingAlgorithm m_method;
        MasterState m_state;
        double m_relativeTolerance;
        double m_timeStep;
        double m_startTime;
        double m_endTime;
        bool m_endTimeDefined;
        /// Current time
        double m_time;

    public:
        Master();
        Master(const fmitcp::Logger& logger);
        ~Master();

        void init();

        fmitcp::EventPump * getEventPump();
        fmitcp::Logger * getLogger();

        /// Connects to a slave and gets info about it
        FMIClient* connectSlave(std::string uri);

        /// Get a slave by id
        FMIClient * getSlave(int id);

        void setState(MasterState state);

        // These are callbacks that fire when a slave did something:
        void slaveConnected(FMIClient * slave);
        void slaveDisconnected(FMIClient * slave);
        void slaveError(FMIClient * slave);
        void onSlaveGetXML(FMIClient * slave);
        void onSlaveInstantiated(FMIClient* slave);
        void onSlaveInitialized(FMIClient* slave);
        void onSlaveTerminated(FMIClient* slave);
        void onSlaveFreed(FMIClient* slave);
        void onSlaveStepped(FMIClient* slave);
        void onSlaveGotVersion(FMIClient* slave);
        void onSlaveSetReal(FMIClient* slave);
        void onSlaveGotReal(FMIClient* slave);
        void onSlaveGotState(FMIClient* slave);
        void onSlaveSetState(FMIClient* slave);
        void onSlaveFreedState(FMIClient* slave);

        /// Set communication timestep
        void setTimeStep(double timeStep);

        /// Enable or disable end time
        void setEnableEndTime(bool enable);

        /// Set the simulation end time
        void setEndTime(double endTime);

        /// Set method for weak coupling
        void setWeakMethod(WeakCouplingAlgorithm algorithm);

        void createStrongConnection(int slaveA, int slaveB, int connectorA, int connectorB);
        void createWeakConnection(int slaveA, int slaveB, int valueReferenceA, int valueReferenceB);

        void transferWeakConnectionData();

        /// Start simulation
        void simulate();

        void instantiateSlaves();
        void initializeSlaves();
        void stepSlaves();

        //bool hasAllClientsState(Slave::SlaveState state);

        /// "State machine" tick
        void tick();
    };
};

#endif /* MASTER_H_ */
