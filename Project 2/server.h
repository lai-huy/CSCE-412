#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include "request.h"

using std::string, std::ostream;
using std::cout;
using std::move, std::swap;

/**
 * @brief The Server class represents a server that can handle requests.
 */
class Server {
private:
	/**
	 * @brief Name of the server
	 */
	string name;

	/**
	 * @brief The current request being handled by the server.
	 */
	Request current_request;

	/**
	 * @brief Remaining time .
	 */
	size_t time;

	/**
	 * @brief Boolean marking is this server is currently processing its current request.
	 */
	bool active;
public:
	/**
	 * @brief Construct a new Server object
	 */
	Server() : name{string{}}, current_request{Request{"", "", 0}}, time{0}, active{false} {}

	/**
	 * @brief Construct a new Server object
	 *
	 * @param name The name of the server
	 */
	Server(const string& name) : name{name}, current_request{Request{"", "", 0}}, time{0}, active{false} {}

	/**
	 * @brief Construct a new Server object
	 *
	 * @param other Server to copy from
	 */
	Server(const Server& other) : name{other.name}, current_request{other.current_request}, time{other.time}, active{other.active} {}

	/**
	 * @brief Construct a new Server object
	 *
	 * @param other Server to move from
	 */
	Server(Server&& other) : name{move(other.name)}, current_request{move(other.current_request)}, time{other.time}, active{other.active} {
		other.time = 0;
		other.active = false;
	}

	/**
	 * @brief Destroy the Server object
	 */
	~Server() = default;

	/**
	 * @brief Copy assignment operator
	 *
	 * @param other Server to copy from
	 * @return Server& *this
	 */
	Server& operator=(const Server& other) {
		if (this != &other) {
			this->name = other.name;
			this->current_request = other.current_request;
			this->time = other.time;
			this->active = other.active;
		}

		return *this;
	}

	/**
	 * @brief Move assignmnet operator
	 *
	 * @param other Server to move from
	 * @return Server& *this
	 */
	Server& operator=(Server&& other) {
		if (this != &other) {
			this->name = move(other.name);
			this->current_request = move(other.current_request);
			this->time = other.time;
			other.time = 0;

			this->active = other.active;
			other.active = false;
		}

		return *this;
	}

	/**
	 * @brief Handles a request by the server.
	 *
	 * @param request The request to be handled.
	 */
	void setRequest(const Request& request) {
		this->current_request = request;
		this->active = true;
		this->time = 0;
	}

	void handleCurrentRequest() {
		cout << *this << " is handling " << this->current_request << "\n";
		if (++this->time == this->current_request.getTime())
			this->active = false;
	}

	/**
	 * @brief Friend function for outputting server information to an ostream.
	 *
	 * @param os The output stream.
	 * @param server The server to be output.
	 * @return ostream& The output stream after writing server information.
	 */
	friend ostream& operator<<(ostream& os, const Server& server) {
		os << "Server{name=" << server.name << "}";
		return os;
	}

	/**
	 * @brief Gets the current request being handled by the server.
	 * @return const Request& A constant reference to the current request.
	 */
	const Request& getRequest() const {
		return this->current_request;
	}

	/**
	 * @brief Determine if this server is running.
	 *
	 * @return true if this server is busy
	 * @return false otherwise
	 */
	bool isRunning() const {
		return this->active;
	}
};

#endif // SERVER_H
