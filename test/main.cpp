#include <string>
#include <stdlib.h>
#include "master/Master.h"
#include "slave/Slave.h"
#include "common/common.h"

using namespace fmitcp_master;

void printHelp(){
    printf("Usage: ./test [OPTIONS]\n\
\n\
[OPTIONS]\n\
    --host [HOST]\n\
    --port [PORT]\n");
}

int main(int argc, char *argv[] ) {

    printf("FMI Master/Slave tester\n");

    long port = 3000;
    int j;
    string hostName = "localhost";

    Logger logger;
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

    // Set connections
    //master.createStrongConnection(strong_slaveA[i], strong_slaveB[i], strong_connA[i], strong_connB[i]);

    master.simulate();

    return 0;
}
