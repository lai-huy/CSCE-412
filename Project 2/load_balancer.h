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
	LoadBalancer(size_t run_time, size_t num_servers, size_t initial_requests) : runtime{run_time}, num_servers{num_servers},
		initial_requests{initial_requests}, clock{0},
		requests{queue<Request>{}}, webservers{vector<Server>{}}, free_webservers{queue<Server>{}},
		handled{vector<tuple<Server, Request, size_t>>{}} {
	}

	void initialize() {
		this->webservers = this->start_webservers();
		this->requests = this->populate_requests();
	}

	void run() {
		while (this->clock < this->runtime && !requests.empty()) {
			++this->clock;

			if (this->free_webservers.empty())
				this->server_sweep();

			while (!this->free_webservers.empty())
				this->assign_request();
		}
	}

	void assign_request() {
		Server current_server = this->free_webservers.front();
		this->free_webservers.pop();

		const Request& current_request = this->requests.front();
		this->requests.pop();

		current_server.handle_request(current_request, this->clock);
	}

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

	void print_log() const {
		for (const auto& [server, request, time] : this->handled) {
			cout << "At " << to_string(time) << " " << server << " processed request " << request << "\n";
		}
	}
};

#endif // LOAD_BALANCER_H
