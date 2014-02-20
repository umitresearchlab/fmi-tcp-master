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
    --port [PORT]   A free port to use.\n\
    fmu");
}

int main(int argc, char *argv[] ) {

    printf("FMI Master/Slave tester\n");

    long port = 3000;
    int j;
    bool debugLogging = false;
    jm_log_level_enu_t log_level = jm_log_level_fatal;
    int logging = jm_log_level_fatal;
    string hostName = "localhost",
        fmuPath = "";

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

        } else if (arg == "-d" || arg == "--debugLogging") {
          debugLogging = true;

        } else if ((arg == "-l" || arg == "--logging") && !last) {
          std::string nextArg = argv[j+1];

          std::istringstream ss(nextArg);
          ss >> logging;

          if (logging < 0) {
            printf("Invalid logging. Possible options are from 0 to 7.\n");fflush(NULL);
            return EXIT_FAILURE;
          }

          switch (logging) {
          case 0:
            log_level = jm_log_level_nothing; break;
          case 1:
            log_level = jm_log_level_fatal; break;
          case 2:
            log_level = jm_log_level_error; break;
          case 3:
            log_level = jm_log_level_warning; break;
          case 4:
            log_level = jm_log_level_info; break;
          case 5:
            log_level = jm_log_level_verbose; break;
          case 6:
            log_level = jm_log_level_debug; break;
          case 7:
            log_level = jm_log_level_all; break;
          }

        } else if((arg == "--port" || arg == "-p") && !last) {
            std::string nextArg = argv[j+1];

            port = string_to_int(nextArg);

            if (port <= 0) {
                printf("Invalid port.\n");
                return EXIT_FAILURE;
            }

        } else if (arg == "--host" && !last) {
            hostName = argv[j+1];

        } else {
          fmuPath = argv[j];
        }
    }

    if(fmuPath == "") {
      printHelp();
      return EXIT_FAILURE;
    }

    // Create a slave
    fmitcp::Server server(fmuPath, debugLogging, log_level, master.getEventPump());
    server.getLogger()->setPrefix("Slave: ");
    server.host(hostName,port);

    master.getLogger()->setPrefix("Master: ");

    // Connect
    ostringstream portStringStream;
    portStringStream << port;
    master.connectSlave("tcp://"+hostName+":"+portStringStream.str());

    // Set connections
    //master.createStrongConnection(strong_slaveA[i], strong_slaveB[i], strong_connA[i], strong_connB[i]);

    master.simulate();

    return 0;
}
