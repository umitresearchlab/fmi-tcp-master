#ifndef MASTER_FMICLIENT_H_
#define MASTER_FMICLIENT_H_

#include <fmitcp/Client.h>

namespace fmitcp_master {

    class Master;

    class FMIClient : public fmitcp::Client {

    private:
        int m_id;
        Master * m_master;

    public:
        FMIClient(Master* master, fmitcp::EventPump* pump);
        virtual ~FMIClient();

        int getId();
        void setId(int id);
        void onConnect();
        void onDisconnect();
        void onError(string err);

        void on_fmi2_import_do_step_res(int message_id, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_instantiate_slave_res(int message_id, fmitcp_proto::jm_status_enu_t status);
    };
};

#endif
