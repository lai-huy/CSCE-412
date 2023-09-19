#include<iostream>
#include <string>

#include "load_balancer.h"

using namespace std;


int main() {
    string user_input{};
    size_t num_servers;
    size_t runtime;

    cout << "Please enter the number of servers: ";
    getline(cin, user_input);
    num_servers = stoul(user_input);

    cout << "Please enter the amount of time you would like to run the load balancer: ";
    getline(cin, user_input);
    runtime = stoul(user_input);

    //start the load balancer
    cout << "Starting load balancer..." << endl;
    LoadBalancer loadbalancer(runtime, num_servers, num_servers * 5);
    loadbalancer.initialize();
    loadbalancer.run();

    //Once the load balancer stops running, it means that time is up or queue is empty
    cout << "Done" << endl;
    loadbalancer.print_log();

    return 0;
}
