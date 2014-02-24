#ifndef STRONGCONNECTION_H_
#define STRONGCONNECTION_H_

#include <sc/Constraint.h>
#include "Connection.h"

namespace fmitcp_master {


    class StrongConnection {

    private:
        StrongConnector* m_connA;
        StrongConnector* m_connB;
        sc::Constraint * m_constraint;

    public:

        enum StrongConnectionType {
            CONNECTION_LOCK
        };

        StrongConnection( StrongConnector* connA , StrongConnector* connB, StrongConnectionType type );
        virtual ~StrongConnection();
        sc::Constraint * getConstraint();
    };
};

#endif
