#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_six(void) {
    std::set<long long> result;
    std::ifstream input("__six.txt");
    if (input.fail()) {
        input.open("testcases/__six.txt");
    }
    if (input.fail()) {
        exit(4);
    }
    long long num_servers, num_requests;
    input >> num_servers >> num_requests;
    class servers_t servers(num_servers);
    for (long long i = 0; i < num_requests; i++) {
        long long arrival, load;
        input >> arrival >> load;
        servers.add_request(arrival, load);
    }
    result = servers.get_servers_that_served_maximum_requests();
    std::set<long long> correct_result = {2529,3563};
    if (result != correct_result) {
        return false;
    }
    return true;
}