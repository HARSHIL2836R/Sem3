#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_four(void) {
    class servers_t servers(10);
    std::set<long long> result;
    std::set<long long> correct_result = {};
    for (long long i = 0; i < 10000; i++) {
        servers.add_request(i * 1000, 100'000); // 9 of 10 are dropped
    }
    for (long long i = 0; i < 1000; i++) {
        servers.add_request(i * 10000 + 100'000'000, 9990);
        servers.add_request(i * 10000 + 100'000'001, 9980);
        servers.add_request(i * 10000 + 100'000'002, 9970);
        servers.add_request(i * 10000 + 100'000'003, 9960);
        servers.add_request(i * 10000 + 100'000'004, 950);
        servers.add_request(i * 10000 + 100'000'005, 9940);
        servers.add_request(i * 10000 + 100'000'060, 9930);
        servers.add_request(i * 10000 + 100'000'061, 9920);
        servers.add_request(i * 10000 + 100'000'062, 9910);
        servers.add_request(i * 10000 + 100'000'063, 9900);
        servers.add_request(i * 10000 + 100'000'079, 9890); // dropped
        servers.add_request(i * 10000 + 100'000'193, 980); // dropped
        servers.add_request(i * 10000 + 100'000'954, 600);
        servers.add_request(i * 10000 + 100'000'975, 500); // dropped
        servers.add_request(i * 10000 + 100'001'000, 9000); // dropped
        servers.add_request(i * 10000 + 100'001'001, 800); // dropped
        servers.add_request(i * 10000 + 100'001'005, 700); // dropped
        servers.add_request(i * 10000 + 100'001'010, 1000); // dropped
        servers.add_request(i * 10000 + 100'003'000, 5000);
        servers.add_request(i * 10000 + 100'005'000, 4000); // dropped
    }
    result = servers.get_servers_that_served_maximum_requests();
    correct_result.clear();
    correct_result.insert(4);
    if (result != correct_result) {
        return false;
    }
    for (long long i = 10000; i < 11000; i++) {
        servers.add_request(i * 10000 + 500'000'000, 990);
        servers.add_request(i * 10000 + 500'000'001, 9980);
        servers.add_request(i * 10000 + 500'000'002, 9970);
        servers.add_request(i * 10000 + 500'000'003, 9960);
        servers.add_request(i * 10000 + 500'000'004, 9950);
        servers.add_request(i * 10000 + 500'000'005, 9940);
        servers.add_request(i * 10000 + 500'000'060, 9930);
        servers.add_request(i * 10000 + 500'000'061, 9920);
        servers.add_request(i * 10000 + 500'000'062, 9910);
        servers.add_request(i * 10000 + 500'000'063, 900);
        servers.add_request(i * 10000 + 500'000'079, 9890); // dropped
        servers.add_request(i * 10000 + 500'000'193, 980); // dropped
        servers.add_request(i * 10000 + 500'001'000, 6000);
        servers.add_request(i * 10000 + 500'001'100, 500);
        servers.add_request(i * 10000 + 500'001'200, 8000); // dropped
        servers.add_request(i * 10000 + 500'001'300, 800); // dropped
        servers.add_request(i * 10000 + 500'001'305, 700); // dropped
        servers.add_request(i * 10000 + 500'001'310, 1000); // dropped
        servers.add_request(i * 10000 + 500'003'000, 5000);
        servers.add_request(i * 10000 + 500'005'000, 4000); // dropped
    }
    result = servers.get_servers_that_served_maximum_requests();
    correct_result.insert(0);
    if (result != correct_result) {
        return false;
    }
    return true;
}