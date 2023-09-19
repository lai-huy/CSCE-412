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
	size_t runtime;
	size_t num_servers;
	size_t initial_requests;
	size_t clock;

	queue<Request> requests;
	vector<Server> webservers;
	queue<Server> free_webservers;
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
				cout << ",";

			webserver_list.push_back(new_server);
			this->free_webservers.push(new_server);
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

		for (size_t i = 0; i < initial_requests; ++i) {
			Request new_request{};
			cout << "New Request " << new_request << "\n";
			requests.push(new_request);
		}

		cout << "Request queue has been populated with " << to_string(initial_requests) << " requests.\n";
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
	LoadBalancer(size_t run_time, size_t num_servers, size_t initial_requests) : runtime{run_time}, num_servers{num_servers},
		initial_requests{initial_requests}, clock{0},
		requests{queue<Request>{}}, webservers{vector<Server>{}}, free_webservers{queue<Server>{}},
		handled{vector<tuple<Server, Request, size_t>>{}} {
	}

	/**
	 * @brief Initializes the load balancer by creating servers and populating requests.
	 */
	void initialize() {
		this->webservers = this->start_webservers();
		this->requests = this->populate_requests();
	}

	/**
	 * @brief Runs the load balancer, distributing requests to available servers.
	 */
	void run() {
		while (this->clock < this->runtime && !requests.empty()) {
			++this->clock;

			if (this->free_webservers.empty())
				this->server_sweep();

			while (!this->free_webservers.empty())
				this->assign_request();
		}
	}

	/**
	 * @brief Assigns a request to an available server.
	 */
	void assign_request() {
		Server current_server{this->free_webservers.front()};
		this->free_webservers.pop();

		Request current_request{this->requests.front()};
		this->requests.pop();

		current_server.handle_request(current_request, this->clock);
	}

	/**
	 * @brief Checks and reclaims servers that have finished processing requests.
	 */
	void server_sweep() {
		for (const Server& server : this->webservers) {
			const Request& request = server.getRequest();
			size_t time = this->clock - server.time();

			if (time >= request.getTime()) {
				this->handled.emplace_back(server, request, time);
				this->free_webservers.push(server);
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
