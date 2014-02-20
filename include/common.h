#ifndef MASTER_COMMON_H_
#define MASTER_COMMON_H_

#define FMITCPMASTER_VERSION "0.0.1"

#include <string>
#include <vector>

namespace fmitcp_master {

    using namespace std;

    vector<string> &split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);
    int string_to_int(const string& s);

}

#endif
