#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_two(void) {
    class servers_t servers(5);
    std::set<long long> result;
    result = servers.get_servers_that_served_maximum_requests();
    std::set<long long> correct_result = {};
    servers.add_request(0, 5000000);
    servers.add_request(2000000, 9000000);
    servers.add_request(3000000, 9000000);
    servers.add_request(3001000, 6000000);
    servers.add_request(3002000, 5000000);
    servers.add_request(3003000, 5000000); // dropped
    servers.add_request(3004000, 5000000); // dropped
    servers.add_request(5005000, 5000000);
    servers.add_request(8010000, 5000000);
    result = servers.get_servers_that_served_maximum_requests();
    correct_result = {0, 4};
    if (result != correct_result) {
        return false;
    }
    return true;
}
