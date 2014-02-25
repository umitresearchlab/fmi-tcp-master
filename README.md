fmi-tcp-master
==============
Co-simulates slaves (FMUs) over TCP. Has built in support for weak and strong coupling.

# Typical usage

1. The FMI host starts the slave ```server```.
2. A user that wants to simulate starts the ```master``` application, which connects to one or more slaves.
3. Simulation is run and results are stored on disk.

# Install instructions
Prerequisities are
* [Lacewing](http://lacewing-project.org/) version 0.5.4
* [Protobuf](https://developers.google.com/protocol-buffers)
* [FMITCP](https://github.com/umitresearchlab/fmi-co-simulation)
* [Strong Coupling Core](https://github.com/umitresearchlab/strong-coupling-core)

To build, run:

    cd fmi-tcp-master/;
    mkdir build && cd build;
    cmake .. -DFMITCP_INCLUDE_DIR=<FMITCP include files location> \
             -DFMITCP_LIBS_DIR=<FMITCP libraries location> \
             -DLACEWING_INCLUDE_DIR=<Lacewing include files location> \
             -DLACEWING_LIBS_DIR=<Lacewing libraries location> \
             -DSTRONG_COUPLING_INCLUDE_DIR=<Strong coupling core include files location> \
             -DSTRONG_COUPLING_LIBS_DIR=<Strong coupling core libraries location>

# Usage

    fmi-tcp-master [OPTIONS] [FMU_URLS...]

    OPTIONS

        --port [INTEGER]
            The port to run the server on.

        --host [STRING]
            The host name to run the server on.

        --timeStep [NUMBER]
                Timestep size. Default is 0.1.

        --stopAfter [NUMBER]
            End simulation time in seconds. Default is 1.0.

        --weakMethod [STRING]
            Stepping  method for weak coupling connections. Must be "parallel" or "serial". Default is "parallel".

        --weakConnections [STRING]
            Connection  specification. No connections by default. Quadruples of
            positive integers, representing which FMU and value reference to connect
            from and what to connect to. Syntax is

                CONN1:CONN2:CONN3...

            where CONNX is four comma-separated integers FMUFROM,VRFROM,FMUTO,VRTO.
            An example connection string is

                0,0,1,0:0,1,1,1

            which means: connect FMU0 (value reference 0) to FMU1 (vr 0) and FMU0
            (vr 1) to FMU1 (vr 1).  Default is no  connections.

        --strongConnections

    FMU_URLS

        Urls to FMU servers, separated by spaces. For example "tcp://fmiserver.com:1234".

    EXAMPLES

        (TODO)
```
