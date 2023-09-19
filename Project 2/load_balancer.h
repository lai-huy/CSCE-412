#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <queue>
#include <tuple>
#include "server.h"

using std::array, std::vector, std::queue;
using std::string;
using std::tuple;
using std::cout;

/**
 * @brief The LoadBalancer class represents a load balancer that distributes requests to servers.
 */
class LoadBalancer {
private:
	size_t runtime;
	size_t num_servers;
	size_t num_requests;
	size_t clock;

	queue<Request> requests;
	vector<Server> servers;
	vector<tuple<Server, Request, size_t>> handled;

	/**
	 * @brief Starts a set of web servers and initializes them.
	 *
	 * @return vector<Server> A vector of initialized web servers.
	 */
	vector<Server> start_webservers() {
		vector<Server> webserver_list;

		cout << "New webservers created: ";
		for (size_t i = 0; i < num_servers; ++i) {
			Server new_server("S" + to_string(i));
			cout << new_server;

			if (i != num_servers - 1)
				cout << ", ";

			webserver_list.push_back(new_server);
		}
		cout << "\n";
		return webserver_list;
	}

	/**
	 * @brief Populates the request queue with initial requests.
	 *
	 * @return queue<Request> The queue of initial requests.
	 */
	queue<Request> populate_requests() {
		queue<Request> requests;

		for (size_t i = 0; i < num_requests; ++i) {
			Request new_request{};
			cout << "New Request " << new_request << "\n";
			requests.push(new_request);
		}

		cout << "Request queue has been populated with " << to_string(num_requests) << " requests.\n";
		return requests;
	}
public:
	/**
	 * @brief Constructs a new LoadBalancer object.
	 *
	 * @param run_time The total runtime of the load balancer.
	 * @param num_servers The number of web servers in the load balancer.
	 * @param initial_requests The initial number of requests to populate the queue.
	 */
	LoadBalancer(size_t run_time, size_t num_servers, size_t num_requests) : runtime{run_time}, num_servers{num_servers},
		num_requests{num_requests}, clock{0}, requests{queue<Request>{}}, servers{vector<Server>(num_servers)},
		handled{vector<tuple<Server, Request, size_t>>{}} {
	}

	/**
	 * @brief Initializes the load balancer by creating servers and populating requests.
	 */
	void initialize() {
		this->servers = this->start_webservers();
		this->requests = this->populate_requests();
	}

	/**
	 * @brief Runs the load balancer, distributing requests to available servers.
	 */
	void run() {
		for (Server& server : this->servers) {
			server.setRequest(this->requests.front());
			this->requests.pop();
		}

		while (!requests.empty()) {
			if (++this->clock >= this->runtime)
				break;

			cout << "Clock:\t" << this->clock << "\n";

			for (Server& server : this->servers) {
				if (server.isRunning())
					server.handleCurrentRequest();
				else {
					this->handled.emplace_back(server, server.getRequest(), this->clock);
					server.setRequest(this->requests.front());
					this->requests.pop();
				}
			}
		}
	}

	/**
	 * @brief Prints the log of processed requests.
	 */
	void print_log() const {
		for (const auto& [server, request, time] : this->handled) {
			cout << "At " << to_string(time) << " " << server << " processed request " << request << "\n";
		}
	}
};

#endif // LOAD_BALANCER_H
