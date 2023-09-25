#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <queue>
#include <tuple>
#include "server.h"

using std::vector, std::queue;
using std::string;
using std::tuple;
using std::cout;

/**
 * @brief The LoadBalancer class represents a load balancer that distributes requests to servers.
 */
class LoadBalancer {
private:
	/**
	 * @brief Maximum runtime of the load balancer
	 */
	size_t runtime;

	/**
	 * @brief The number of servers in the load balancer
	 */
	size_t num_servers;

	/**
	 * @brief The number of requests to process
	 */
	size_t num_requests;

	/**
	 * @brief Current "system time" of the load balancer
	 */
	size_t clock;

	/**
	 * @brief Queue of requests
	 */
	queue<Request> requests;

	/**
	 * @brief List of servers in the load balancer
	 */
	vector<Server> servers;

	/**
	 * @brief List of completed requests, the server that completed the request and when the request was finished
	 */
	vector<tuple<Request, Server, size_t>> handled;

	/**
	 * @brief Starts a set of web servers and initializes them.
	 */
	void start_webservers() {
		this->servers.clear();
		cout << "New webservers created: ";
		for (size_t i = 0; i < num_servers; ++i) {
			Server new_server("S" + to_string(i));
			cout << new_server;

			if (i != num_servers - 1)
				cout << ", ";

			this->servers.push_back(new_server);
		}

		cout << "\n";
	}

	/**
	 * @brief Populates the request queue with initial requests.
	 */
	void populate_requests() {
		for (size_t i = 0; i < this->num_requests; ++i) {
			Request request{};
			cout << "New Request " << request << "\n";
			this->requests.push(request);
		}

		cout << "Request queue has been populated with " << to_string(this->num_requests) << " requests.\n";
	}
public:
	/**
	 * @brief Constructs a new LoadBalancer object.
	 *
	 * @param run_time The total runtime of the load balancer.
	 * @param num_servers The number of web servers in the load balancer.
	 * @param num_requests The initial number of requests to populate the queue.
	 */
	LoadBalancer(size_t run_time, size_t num_servers, size_t num_requests) : runtime{run_time}, num_servers{num_servers},
		num_requests{num_requests}, clock{0}, requests{queue<Request>{}}, servers{vector<Server>{}},
		handled{vector<tuple<Request, Server, size_t>>{}} {
	}

	~LoadBalancer() = default;

	/**
	 * @brief Initializes the load balancer by creating servers and populating requests.
	 */
	void initialize() {
		this->start_webservers();
		this->populate_requests();
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

			// cout << "Clock:\t" << this->clock << "\n";

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
		for (const auto& [request, server, time] : this->handled)
			cout << "At " << to_string(time) << " " << server << " processed request " << request << "\n";
	}
};

#endif // LOAD_BALANCER_H
