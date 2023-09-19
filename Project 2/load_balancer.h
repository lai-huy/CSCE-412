#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <queue>
#include "server.h"

using std::vector, std::queue, std::string;
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
	vector<Request> handled_requests;
	vector<Server> handled_servers;
	vector<string> handled_times;

	vector<Server> start_webservers() {
		vector<Server> webserver_list;

		cout << "New webservers created: ";
		for (size_t i = 0; i < num_servers; ++i) {
			const string& name = "S" + to_string(i);
			Server new_server(name);
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
		handled_requests{vector<Request>{}}, handled_servers{vector<Server>{}}, handled_times{vector<string>{}} {}

	void initialize() {
		this->webservers = this->start_webservers();
		this->requests = this->populate_requests();
	}

	void run() {
		while (clock < runtime && !requests.empty()) {
			++clock;

			if (!requests.empty() && free_webservers.empty())
				server_sweep();

			while (!free_webservers.empty() && !requests.empty())
				assign_request();
		}
	}

	void assign_request() {
		Server current_server = free_webservers.front();
		free_webservers.pop();

		const Request& current_request = requests.front();
		this->requests.pop();

		current_server.handle_request(current_request, this->clock);
	}

	void server_sweep() {
		for (const Server& server : this->webservers) {
			const Request& request = server.getRequest();
			size_t request_duration = this->clock - server.time();

			if (request_duration >= request.getTime()) {
				//this means the server is done with the request
				handled_requests.push_back(request);
				handled_times.push_back(to_string(request_duration));
				this->free_webservers.push(server);
			}
		}
	}

	void print_log() const {
		for (size_t i = 0; i < this->handled_requests.size(); ++i) {
			cout << "At " << this->handled_times[i] << " "
				<< this->handled_servers[i].getName() << " processed request " << this->handled_requests[i] << "\n";
		}
	}
};

#endif // LOAD_BALANCER_H
