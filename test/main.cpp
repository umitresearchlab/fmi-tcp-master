#include <string>
#include <sstream>
#include <stdlib.h>
#include <fmitcp/Server.h>
#include "master/Master.h"
#include "common/common.h"

using namespace fmitcp_master;

void printHelp(){
    printf("Usage: ./test [OPTIONS]\n\
\n\
[OPTIONS]\n\
    --host [HOST]   The host. Defaults to 'localhost'.\n\
    --port [PORT]   A free port to use.\n\n");
}

int main(int argc, char *argv[] ) {

    printf("FMI Master/Slave tester\n");

    long port = 3000;
    int j;
    string hostName = "localhost";

    fmitcp::Logger logger;
    Master master(logger);
    master.setTimeStep(0.1);
    master.setEnableEndTime(false);
    master.setWeakMethod(PARALLEL);

    for (j = 1; j < argc; j++) {
        std::string arg = argv[j];
        bool last = (j == argc-1);

        if (arg == "-h" || arg == "--help") {
            printHelp();
            return EXIT_SUCCESS;

        } else if((arg == "--port" || arg == "-p") && !last) {
            std::string nextArg = argv[j+1];

            port = string_to_int(nextArg);

            if (port <= 0) {
                printf("Invalid port.\n");
                return EXIT_FAILURE;
            }

        } else if (arg == "--host" && !last) {
            hostName = argv[j+1];

        }
    }

    // Create a slave
    fmitcp::Server server("", false, jm_log_level_all, master.getEventPump());
    server.getLogger()->setPrefix("Slave: ");
    server.host(hostName,port);

    master.getLogger()->setPrefix("Master:   ");

    // Connect
    ostringstream portStringStream;
    portStringStream << port;
    FMIClient* slave = master.connectSlave("tcp://"+hostName+":"+portStringStream.str());
    slave->getLogger()->setPrefix("Master "+int_to_string(slave->getId())+": ");

    // Set connections
    //master.createStrongConnection(strong_slaveA[i], strong_slaveB[i], strong_connA[i], strong_connB[i]);

    master.simulate();

    return 0;
}
