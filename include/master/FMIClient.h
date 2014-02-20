#ifndef MASTER_FMICLIENT_H_
#define MASTER_FMICLIENT_H_

#include <fmitcp/Client.h>
#include <string>

namespace fmitcp_master {

    class Master;

    enum FMIClientState {
        FMICLIENT_STATE_START,
        FMICLIENT_STATE_WAITING_INSTANTIATE_SLAVE,
        FMICLIENT_STATE_WAITING_DOSTEP,
    };

    class FMIClient : public fmitcp::Client {

    private:
        int m_id;
        Master * m_master;
        string m_xml;

    public:
        FMIClient(Master* master, fmitcp::EventPump* pump);
        virtual ~FMIClient();

        int getId();
        void setId(int id);
        void onConnect();
        void onDisconnect();
        void onError(string err);

        void onGetXmlRes(int mid, string xml);
        void on_fmi2_import_instantiate_slave_res               (int mid, fmitcp_proto::jm_status_enu_t status);
        void on_fmi2_import_initialize_slave_res                (int mid, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_terminate_slave_res                 (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_reset_slave_res                     (int mid, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_free_slave_instance_res             (int mid);
        //void on_fmi2_import_set_real_input_derivatives_res      (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_real_output_derivatives_res     (int mid, fmitcp_proto::fmi2_status_t status, const vector<double>& values);
        //void on_fmi2_import_cancel_step_res                     (int mid, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_do_step_res                         (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_status_res                      (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_real_status_res                 (int mid, double value);
        //void on_fmi2_import_get_integer_status_res              (int mid, int value);
        //void on_fmi2_import_get_boolean_status_res              (int mid, bool value);
        //void on_fmi2_import_get_string_status_res               (int mid, string value);
        //void on_fmi2_import_instantiate_model_res               (int mid, fmitcp_proto::jm_status_enu_t status);
        //void on_fmi2_import_free_model_instance_res             (int mid);
        //void on_fmi2_import_set_time_res                        (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_set_continuous_states_res           (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_completed_integrator_step_res       (int mid, bool callEventUpdate, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_initialize_model_res                (int mid, bool iterationConverged, bool stateValueReferencesChanged, bool stateValuesChanged, bool terminateSimulation, bool upcomingTimeEvent, double nextEventTime, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_derivatives_res                 (int mid, const vector<double>& derivatives, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_event_indicators_res            (int mid, const vector<double>& eventIndicators, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_eventUpdate_res                     (int mid, bool iterationConverged, bool stateValueReferencesChanged, bool stateValuesChanged, bool terminateSimulation, bool upcomingTimeEvent, double nextEventTime, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_completed_event_iteration_res       (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_continuous_states_res           (int mid, const vector<double>& states, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_nominal_continuous_states_res   (int mid, const vector<double>& nominal, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_terminate_res                       (int mid, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_get_version_res                     (int mid, string version);
        //void on_fmi2_import_set_debug_logging_res               (int mid, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_set_real_res                        (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_set_integer_res                     (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_set_boolean_res                     (int mid, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_set_string_res                      (int mid, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_get_real_res                        (int mid, const vector<double>& values, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_integer_res                     (int mid, const vector<int>& values, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_boolean_res                     (int mid, const vector<bool>& values, fmitcp_proto::fmi2_status_t status);
        //void on_fmi2_import_get_string_res                      (int mid, const vector<string>& values, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_get_fmu_state_res                   (int mid, int stateId);
        void on_fmi2_import_set_fmu_state_res                   (int mid, fmitcp_proto::fmi2_status_t status);
        void on_fmi2_import_free_fmu_state_res                  (int mid, fmitcp_proto::fmi2_status_t status);
    };
};

#endif
