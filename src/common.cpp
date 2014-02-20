#include "common.h"
#include "stdlib.h"
#include <vector>
#include <string>
#include <sstream>

using namespace fmitcp_master;
using namespace std;

vector<string>& fmitcp_master::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> fmitcp_master::split(const string &s, char delim) {
    vector<string> elems;
    fmitcp_master::split(s, delim, elems);
    return elems;
}

int fmitcp_master::string_to_int(const string& s){
    int result;
    std::istringstream ss(s);
    ss >> result;
    return result;
}
