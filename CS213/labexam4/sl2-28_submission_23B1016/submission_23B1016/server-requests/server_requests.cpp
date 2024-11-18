#include "server_requests.h"
// You should NOT add ANY other includes in this file.
// You also should NOT add `using namespace std;`.

servers_t::servers_t(long long __num_servers) {
    // TODO: Write your code here
    servers = std::vector<long long>(__num_servers,-1);
    num_servers = __num_servers;

    for (long long i = 0; i < num_servers; i++){
        requests[i] = 0;
    }

    next_request_id = 0;
    
    // End TODO
}

servers_t::~servers_t(void) {
    // TODO: Write your code here

    // End TODO
}

void servers_t::add_request(long long __timestamp, long long __duration) {
    // TODO: Write your code here
    int id = next_request_id++;
    for (long long k = 0; k<num_servers;k++){
        if (servers[k]>0) servers[k] = servers[k] -  (__timestamp - last_timestamp);
    }
    long long i = id;
    long long count = 0;
    while (servers[i]>0 && count < num_servers+1) {
        i = (i + 1)%num_servers;
        count++;
    }
    if (count == num_servers +1) return; //drop the request
    
    requests[i] = requests[i] + 1;
    servers[i] = __duration;
    last_timestamp = __timestamp;
    // End TODO
}

std::set<long long> servers_t::get_servers_that_served_maximum_requests(void) {
    // TODO: Write your code here
    std::set<long long> res;
    int max = requests[0];
    for (long long i = 0; i < num_servers; i++)
    {
        if (max < requests[i]){
            res.clear();
            res.insert(i);
            max = requests[i];
        }
        else if (max == requests[i]) res.insert(i);
    }
    // std::cerr<<*res.begin();
    // std::cerr<<requests[1];
    return res; // dummy return
    // End TODO
}

// TODO: Implement any private methods and helper functions here (if needed).

// End TODO
