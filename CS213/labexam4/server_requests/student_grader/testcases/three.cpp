#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_three(void) {
    class servers_t servers(10);
    std::set<long long> result;
    result = servers.get_servers_that_served_maximum_requests();
    std::set<long long> correct_result = {};
    if (result != correct_result) {
        return false;
    }
    for (long long i = 0; i < 10000; i++) {
        servers.add_request(i * 1000, 10'000);
    }
    result = servers.get_servers_that_served_maximum_requests();
    for (long long i = 0; i < 10; i++) {
        correct_result.insert(i);
    }
    for (long long i = 0; i < 1000; i++) {
        servers.add_request(i * 10000 + 10'000'000, 9990);
        servers.add_request(i * 10000 + 10'000'001, 9980);
        servers.add_request(i * 10000 + 10'000'002, 9970);
        servers.add_request(i * 10000 + 10'000'003, 9960);
        servers.add_request(i * 10000 + 10'000'004, 950);
        servers.add_request(i * 10000 + 10'000'005, 9940);
        servers.add_request(i * 10000 + 10'000'060, 9930);
        servers.add_request(i * 10000 + 10'000'061, 9920);
        servers.add_request(i * 10000 + 10'000'062, 9910);
        servers.add_request(i * 10000 + 10'000'063, 9900);
        servers.add_request(i * 10000 + 10'000'079, 9890); // dropped
        servers.add_request(i * 10000 + 10'000'193, 980); // dropped
        servers.add_request(i * 10000 + 10'000'954, 600);
        servers.add_request(i * 10000 + 10'000'975, 500); // dropped
        servers.add_request(i * 10000 + 10'001'000, 9000); // dropped
        servers.add_request(i * 10000 + 10'001'001, 800); // dropped
        servers.add_request(i * 10000 + 10'001'005, 700); // dropped
        servers.add_request(i * 10000 + 10'001'010, 1000); // dropped
        servers.add_request(i * 10000 + 10'003'000, 50);
        servers.add_request(i * 10000 + 10'005'000, 4000);
    }
    result = servers.get_servers_that_served_maximum_requests();
    correct_result.clear();
    correct_result.insert(4);
    if (result != correct_result) {
        return false;
    }
    return true;
}