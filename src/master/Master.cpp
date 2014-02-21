#include <string>
#include <fmitcp/EventPump.h>
#include <fmitcp/Logger.h>
#include "stdlib.h"
#include "string.h"

#include "master/Master.h"
#include "master/FMIClient.h"
#include "master/StrongConnection.h"
#include "master/WeakConnection.h"
#include "common/url_parser.h"

using namespace fmitcp_master;

Master::Master(){
    init();
}

Master::Master(const fmitcp::Logger& logger){
    m_logger = logger;
    init();
}

void Master::init(){

    m_pump = new fmitcp::EventPump();

    // Set state
    setState(MASTER_STATE_CONNECTING_SLAVES);
    m_slaveIdCounter = 0;

    m_relativeTolerance = 0.0001;
    m_startTime = 0;
    m_endTimeDefined = false;
    m_endTime = 10;
    m_time = 0;
}

Master::~Master(){

    // Delete all connections
    for (int i = 0; i < m_strongConnections.size(); ++i){
        delete m_strongConnections[i];
    }
    for (int i = 0; i < m_weakConnections.size(); ++i){
        delete m_weakConnections[i];
    }

    // Delete all remaining slaves
    for (int i = 0; i < m_slaves.size(); ++i){
        delete m_slaves[i];
    }
}

fmitcp::EventPump * Master::getEventPump(){
    return m_pump;
}

fmitcp::Logger * Master::getLogger(){
    return &m_logger;
};

void Master::transferWeakConnectionData(){
    m_state = MASTER_STATE_TRANSFERRING_WEAK;

    // Assume parallel
    for (int i = 0; i < m_weakConnections.size(); ++i){

        // Start to transfer value
        m_weakConnections[i];
    }
}

FMIClient* Master::connectSlave(std::string uri){
    struct parsed_url * url = parse_url(uri.c_str());
    long port = atoi(url->port);

    FMIClient* client = new FMIClient(this,m_pump);
    client->connect(url->host,port);
    m_slaves.push_back(client);

    int slaveId = m_slaveIdCounter++;
    client->setId(slaveId);

    m_logger.log(fmitcp::Logger::LOG_DEBUG,"Connected slave id=%d: %s\n",slaveId,uri.c_str());

    parsed_url_free(url);

    return client;
}

void Master::simulate(){
    m_pump->startEventLoop();
    tick();
}

FMIClient * Master::getSlave(int id){
    for(int i=0; i<m_slaves.size(); i++){
        if(m_slaves[i]->getId() == id){
            return m_slaves[i];
        }
    }
    return NULL;
}

void Master::slaveConnected(FMIClient * client){
    m_logger.log(fmitcp::Logger::LOG_NETWORK,"Connected to slave %d.\n",client->getId());
    tick();
}

void Master::slaveError(FMIClient * client){
    m_logger.log(fmitcp::Logger::LOG_NETWORK,"Slave %d error!\n", client->getId());
    m_pump->exitEventLoop();
}

void Master::slaveDisconnected(FMIClient* client){
    m_logger.log(fmitcp::Logger::LOG_NETWORK,"Disconnected slave.\n");

    // Remove from slave vector
    for(int i=0; i<m_slaves.size(); i++){
        if(m_slaves[i] == client){
            delete m_slaves[i];
            m_slaves.erase(m_slaves.begin()+i);
            break;
        }
    }

    // No slaves left - exit
    // TODO: Move this to the tick function?
    if(m_slaves.size() == 0)
        m_pump->exitEventLoop();
}

void Master::instantiateSlaves() {
  setState(MASTER_STATE_INSTANTIATING_SLAVES);
  for(int i=0; i<m_slaves.size(); i++){
    m_logger.log(fmitcp::Logger::LOG_DEBUG,"Instantiating slave %d...\n", i);
    m_slaves[i]->m_state = FMICLIENT_STATE_WAITING_INSTANTIATE_SLAVE;
    m_slaves[i]->fmi2_import_instantiate(0);
  }
}

void Master::initializeSlaves() {
    setState(MASTER_STATE_INITIALIZING_SLAVES);
    for(int i=0; i<m_slaves.size(); i++){
        m_logger.log(fmitcp::Logger::LOG_DEBUG,"Initializing slave %d...\n", i);
        m_slaves[i]->m_state = FMICLIENT_STATE_WAITING_INITIALIZE_SLAVE;
        m_slaves[i]->fmi2_import_initialize_slave(0);
    }
}

void Master::fetchDirectionalDerivatives() {
    // TODO: This call needs seeds from the strong coupling library, but that is not available yet!
    setState(MASTER_STATE_GETTING_DIRECTIONAL_DERIVATIVES);
    for(int i=0; i<m_slaves.size(); i++){
        m_logger.log(fmitcp::Logger::LOG_DEBUG,"Getting directional derivatives from slave %d...\n", i);
        m_slaves[i]->m_state = FMICLIENT_STATE_WAITING_DIRECTIONALDERIVATIVES;
        // TODO fill these with seeds
        std::vector<int> v_ref;
        std::vector<int> z_ref;
        std::vector<double> dv;
        m_slaves[i]->fmi2_import_get_directional_derivative(0, 0, v_ref, z_ref, dv);
    }
}

void Master::getSlaveStates() {
    setState(MASTER_STATE_GETTING_STATES);
    for(int i=0; i<m_slaves.size(); i++){
        m_logger.log(fmitcp::Logger::LOG_DEBUG,"Getting state from slave %d...\n", i);
        m_slaves[i]->m_state = FMICLIENT_STATE_WAITING_GET_STATE;
        m_slaves[i]->fmi2_import_get_fmu_state(0,0);
    }
}

void Master::setSlaveStates() {
    setState(MASTER_STATE_SETTING_STATES);
    for(int i=0; i<m_slaves.size(); i++){
        m_logger.log(fmitcp::Logger::LOG_DEBUG,"Setting state for slave %d...\n", i);
        m_slaves[i]->m_state = FMICLIENT_STATE_WAITING_SET_STATE;
        m_slaves[i]->fmi2_import_set_fmu_state(0,0,0);
    }
}

void Master::stepSlaves(bool forFutureVelocities){
    if(forFutureVelocities)
        setState(MASTER_STATE_STEPPING_SLAVES_FOR_FUTURE_VELO);
    else
        setState(MASTER_STATE_STEPPING_SLAVES);
    for(int i=0; i<m_slaves.size(); i++){
        m_logger.log(fmitcp::Logger::LOG_DEBUG,"Stepping slave %d...\n", i);
        //m_slaves[i]->fmi2_import_do_step(0, 0, m_relativeTolerance, m_startTime, m_endTimeDefined, m_endTime);
        m_slaves[i]->m_state = FMICLIENT_STATE_WAITING_DOSTEP;
        m_slaves[i]->fmi2_import_do_step(0,0,m_time,m_timeStep,true);
    }
    if(!forFutureVelocities)
        m_time += m_timeStep;
}

void Master::setStrongCouplingForces(){
    setState(MASTER_STATE_SETTING_STRONG_COUPLING_FORCES);

    for(int i=0; i<m_slaves.size(); i++){
        m_logger.log(fmitcp::Logger::LOG_DEBUG,"Setting strong coupling forces for slave %d...\n", i);
        m_slaves[i]->m_state = FMICLIENT_STATE_WAITING_SET_REAL;
        std::vector<int> valueRefs;
        m_slaves[i]->fmi2_import_get_real(0,0,valueRefs);
    }
}

void Master::setState(MasterState state){
    m_state = state;

    switch(m_state){
    case MASTER_STATE_CONNECTING_SLAVES:                m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_CONNECTING_SLAVES\n");                 break;
    case MASTER_STATE_GETTING_VERSION:                  m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_GETTING_VERSION\n");                   break;
    case MASTER_STATE_GETTING_XML:                      m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_GETTING_XML\n");                       break;
    case MASTER_STATE_INSTANTIATING_SLAVES:             m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_INSTANTIATING_SLAVES\n");              break;
    case MASTER_STATE_INITIALIZING_SLAVES:              m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_INITIALIZING_SLAVES\n");               break;
    case MASTER_STATE_TRANSFERRING_WEAK:                m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_TRANSFERRING_WEAK\n");                 break;
    case MASTER_STATE_GETTING_DIRECTIONAL_DERIVATIVES:  m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_GETTING_DIRECTIONAL_DERIVATIVES\n");   break;
    case MASTER_STATE_SETTING_STRONG_COUPLING_FORCES:   m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_SETTING_STRONG_COUPLING_FORCES\n");    break;
    case MASTER_STATE_STEPPING_SLAVES:                  m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_STEPPING_SLAVES\n");                   break;
    case MASTER_STATE_DONE:                             m_logger.log(fmitcp::Logger::LOG_DEBUG,"MASTER_STATE_DONE\n");                              break;
    default:
        m_logger.log(fmitcp::Logger::LOG_DEBUG,"State not recognized: %d\n",m_state);
        break;
    }

}

bool Master::allClientsHaveState(FMIClientState state){
    for(int i=0; i<m_slaves.size(); i++){
        if(m_slaves[i]->m_state != state)
            return false;
    }
    return true;
}


// Simulation loop logic. TODO: use finite state machine library for this?
void Master::tick(){

    bool allConnected, allInstantiated, allInitialized, allReady;

    switch(m_state){

    case MASTER_STATE_CONNECTING_SLAVES:

        // Check if all slaves are connected.
        allConnected = true;
        for(int i=0; i<m_slaves.size(); i++){
            if(!m_slaves[i]->isConnected()){
                allConnected = false;
                break;
            }
        }

        if(!allConnected)
            break;

        // Enough slaves connected. Start initializing!
        instantiateSlaves();
        break;

    case MASTER_STATE_GETTING_VERSION:
        break;

    case MASTER_STATE_GETTING_XML:
        break;

    case MASTER_STATE_INSTANTIATING_SLAVES:
      // Check if all are ready
      if(!allClientsHaveState(FMICLIENT_STATE_DONE_INSTANTIATE_SLAVE))
        break;

      // All slaves are instantiated.
      // Should set initial values here. TODO!
      initializeSlaves();
      break;

    case MASTER_STATE_INITIALIZING_SLAVES:
        // Check if all are ready
        if(!allClientsHaveState(FMICLIENT_STATE_DONE_INITIALIZE_SLAVE))
            break;
        // If all are ready, just continue to the case below, start simloop

    case MASTER_STATE_START_SIMLOOP:

        // All slaves are initialized.
        if(m_strongConnections.size()){
            // There are strong connections. We must now get states.
            getSlaveStates();

        } else if(m_weakConnections.size()){
            transferWeakConnectionData();

        } else {
            // No connections at all, we can now do final step
            stepSlaves(false);
        }
        break;


    case MASTER_STATE_GETTING_STATES:
        m_logger.log(fmitcp::Logger::LOG_DEBUG,"GOT STATE ......\n");
        if(allClientsHaveState(FMICLIENT_STATE_DONE_GET_STATE))
            stepSlaves(true); // Step to get future velocities
        break;

    case MASTER_STATE_STEPPING_SLAVES_FOR_FUTURE_VELO:
        if(allClientsHaveState(FMICLIENT_STATE_DONE_DOSTEP)){
            // TODO store future velocities!
            setSlaveStates(); // Rewind!
        }
        break;

    case MASTER_STATE_SETTING_STATES:
        if(allClientsHaveState(FMICLIENT_STATE_DONE_SET_STATE)){
            // Done rewinding. Now get directional derivatives.
            fetchDirectionalDerivatives();
        }
        break;

    case MASTER_STATE_GETTING_DIRECTIONAL_DERIVATIVES:
        // All ready?
        if(!allClientsHaveState(FMICLIENT_STATE_DONE_DIRECTIONALDERIVATIVES))
            break;

        // Got directional derivatives and future velocities.
        // TODO: Run strong coupling library

        // Apply strong coupling forces to slaves
        setStrongCouplingForces();

        break;

    case MASTER_STATE_SETTING_STRONG_COUPLING_FORCES:
        // Check if all strong coupling forces are applied
        if(!allClientsHaveState(FMICLIENT_STATE_DONE_SET_REAL))
            break;

        // All strong coupling forces are set. Now transfer weak.
        transferWeakConnectionData();

        break;

    case MASTER_STATE_TRANSFERRING_WEAK:
        if(!allClientsHaveState(FMICLIENT_STATE_DONE_SET_REAL))
            break;

        stepSlaves(false);
        break;

    case MASTER_STATE_STEPPING_SLAVES:
        if(allClientsHaveState(FMICLIENT_STATE_DONE_DOSTEP)){
            // Next step?
            if((m_endTimeDefined && m_time < m_endTime) || !m_endTimeDefined){
                //stepSlaves(false);
                setState(MASTER_STATE_START_SIMLOOP);
                tick();
            } else {
                // We are done with the simulation!
                setState(MASTER_STATE_DONE);
                m_pump->exitEventLoop();
            }
        }
        break;

    case MASTER_STATE_DONE:
        break;
    }
}

void Master::createStrongConnection(FMIClient* slaveA, FMIClient* slaveB, int connectorA, int connectorB){
    m_strongConnections.push_back(new StrongConnection(slaveA,slaveB,connectorA,connectorB));
}

void Master::createWeakConnection(FMIClient* slaveA, FMIClient* slaveB, int valueReferenceA, int valueReferenceB){
    m_weakConnections.push_back(new WeakConnection(slaveA,slaveB,valueReferenceA,valueReferenceB));
}

void Master::setTimeStep(double timeStep){
    m_timeStep = timeStep;
}

void Master::setEnableEndTime(bool enable){
    m_endTimeDefined = enable;
}

void Master::setEndTime(double endTime){
    m_endTime = endTime;
}

void Master::setWeakMethod(WeakCouplingAlgorithm algorithm){
    m_method = algorithm;
}

void Master::onSlaveGetXML(FMIClient * slave){
    tick();
};

void Master::onSlaveInstantiated(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_INSTANTIATE_SLAVE;
    slave->m_isInstantiated = true;
    tick();
};

void Master::onSlaveInitialized(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_INITIALIZE_SLAVE;
    tick();
};

void Master::onSlaveTerminated(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_TERMINATE_SLAVE;
    tick();
};

void Master::onSlaveFreed(FMIClient* slave){
    tick();
};

void Master::onSlaveStepped(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_DOSTEP;
    tick();
};

void Master::onSlaveGotVersion(FMIClient* slave){
    tick();
};

void Master::onSlaveSetReal(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_SET_REAL;
    tick();
};

void Master::onSlaveGotReal(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_GET_REAL;
    tick();
};

void Master::onSlaveGotState(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_GET_STATE;
    tick();
};

void Master::onSlaveSetState(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_SET_STATE;
    tick();
};

void Master::onSlaveFreedState(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_FREE_STATE;
    tick();
};

void Master::onSlaveDirectionalDerivative(FMIClient* slave){
    slave->m_state = FMICLIENT_STATE_DONE_DIRECTIONALDERIVATIVES;
    tick();
};
