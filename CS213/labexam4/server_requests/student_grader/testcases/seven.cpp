#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_seven(void) {
    class servers_t servers(50000);
    for (long long i = 0; i < 34296; i++) {
        servers.add_request(i * 1000, 1'000'000'000'000'000);
    }
    servers.add_request(34'296'000, 1'000'000'000);
    for (long long i = 34297; i < 50000; i++) {
        servers.add_request(i * 1000, 1'000'000'000'000'000);
    }
    std::set<long long> result;
    result = servers.get_servers_that_served_maximum_requests();
    std::set<long long> correct_result;
    for (long long i = 0; i < 50000; i++) {
        correct_result.insert(i);
    }
    if (result != correct_result) {
        return false;
    }
    correct_result.clear();
    correct_result.insert(34296);
    for (long long i = 0; i < 50000; i++) {
        servers.add_request(i * 1000 + 1'500'000'000,
                1000); // all back to back
        result = servers.get_servers_that_served_maximum_requests();
        if (result != correct_result) {
            return false;
        }
    }
    return true;
}
