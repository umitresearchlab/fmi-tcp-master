#include <string>
#include <fmitcp/Client.h>
#include <fmitcp/common.h>
#include <fmitcp/Logger.h>
#include <stdlib.h>
#include <signal.h>
#include <sstream>
#include "master/Master.h"
#include "master/FMIClient.h"
#include "common/common.h"

using namespace fmitcp_master;

void printHelp(){
    printf("HELP PAGE: TODO\n");fflush(NULL);
}

int main(int argc, char *argv[] ) {

    printf("FMI Master %s\n",FMITCPMASTER_VERSION);fflush(NULL);

    fmitcp::Logger logger;
    Master master(logger);
    master.setTimeStep(0.1);
    master.setEnableEndTime(false);
    master.setWeakMethod(PARALLEL);

    const char* connectionsArg;
    int i, j;
    string hostName = "localhost";
    long port = 3000;

    // Connections
    vector<int> strong_slaveA;
    vector<int> strong_slaveB;
    vector<int> strong_connA;
    vector<int> strong_connB;

    vector<int> weak_slaveA;
    vector<int> weak_slaveB;
    vector<int> weak_connA;
    vector<int> weak_connB;

    vector<FMIClient*> slaves;

    for (j = 1; j < argc; j++) {
        std::string arg = argv[j];
        bool last = (j == argc-1);

        if (arg == "-h" || arg == "--help") {
            printHelp();
            return EXIT_SUCCESS;

        } else if((arg == "--port" || arg == "-p") && !last) {
            std::string nextArg = argv[j+1];

            std::istringstream ss(nextArg);
            ss >> port;

            if (port <= 0) {
                printf("Invalid port.\n");
                return EXIT_FAILURE;
            }

        } else if (arg == "--host" && !last) {
            hostName = argv[j+1];

        } else if (arg == "--timeStep" && !last) {
            std::string nextArg = argv[j+1];
            double timeStepSize = ::atof(nextArg.c_str());
            j++;

            if(timeStepSize <= 0){
                fprintf(stderr,"Invalid timeStepSize.");
                return EXIT_FAILURE;
            }

            master.setTimeStep(timeStepSize);

        } else if (arg == "--version") {
            printf("%s\n",FMITCPMASTER_VERSION);
            return EXIT_SUCCESS;

        } else if ((arg == "-t" || arg == "--stopAfter") && !last) {
            std::string nextArg = argv[j+1];
            double endTime = ::atof(nextArg.c_str());
            j++;

            if (endTime <= 0) {
                fprintf(stderr,"Invalid end time.");
                return EXIT_FAILURE;
            }

            master.setEnableEndTime(true);
            master.setEndTime(endTime);

        } else if ((arg == "-wm" || arg == "--weakMethod") && !last) {
            std::string nextArg = argv[j+1];
            j++;

            if (nextArg == "jacobi") {
                //*method = jacobi;

            } else if (nextArg == "jacobi") {
                //*method = jacobi;

            } else {
                fprintf(stderr,"Method not recognized. Use \"jacobi\" or \"gs\".\n");
                return EXIT_FAILURE;

            }

        } else if ((arg == "-wc" || arg == "--weakConnections") && !last) {

        } else if ((arg == "-sc" || arg == "--strongConnections") && !last) {
            std::string nextArg = argv[j+1];
            j++;

            // Get connections
            vector<string> conns = split(nextArg,':');
            for(i=0; i<conns.size(); i++){
                vector<string> quad = split(conns[i],',');
                strong_slaveA.push_back(string_to_int(quad[0]));
                strong_slaveB.push_back(string_to_int(quad[1]));
                strong_connA .push_back(string_to_int(quad[2]));
                strong_connB .push_back(string_to_int(quad[3]));
            }

        } else if (arg ==  "--debug") {
            // debugFlag = 1;
            // Todo: set flag in logger

        } else {
            // Assume URI to slave
            slaves.push_back(master.connectSlave(arg));
        }
    }

    // Set connections
    for(i=0; i<strong_slaveA.size(); i++)
        master.createStrongConnection(slaves[strong_slaveA[i]], slaves[strong_slaveB[i]], strong_connA[i], strong_connB[i]);

    master.simulate();

    return 0;
}
