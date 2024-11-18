#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_one(void) {
    class servers_t servers(3);
    servers.add_request(1, 1);
    servers.add_request(2, 2);
    servers.add_request(3, 1);
    servers.add_request(4, 2); // dropped
    std::set<long long> result;
    result = servers.get_servers_that_served_maximum_requests();
    std::set<long long> correct_result = {0};
    if (result != correct_result) {
        return false;
    }
    return true;
}
