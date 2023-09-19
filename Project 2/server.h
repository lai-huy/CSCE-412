#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include "request.h"

using std::string, std::ostream;
using std::cout;

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
	 * @brief The timestamp when the current request started to be handled.
	 */
	size_t current_wait;
public:
	/**
	 * @brief Construct a new Server object
	 *
	 * @param name The name of the server
	 */
	Server(const string& name) : name{name}, current_request{Request{}}, current_wait{0} {}

	/**
	 * @brief Handles a request by the server.
	 *
	 * @param request The request to be handled.
	 * @param timestamp The timestamp when the request is received.
	 */
	void handle_request(const Request& request, size_t timestamp) {
		this->current_request = request;
		this->current_wait = timestamp;
		cout << *this << " is handling Request:\t" << this->current_request << "\n";
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
	 * @brief Get the Name object
	 *
	 * @return const string& A constant reference to the name of the server.
	 */
	const string& getName() const {
		return this->name;
	}

	/**
	 * @brief Gets the timestamp when the current request started to be handled.
	 *
	 * @return const size_t& A constant reference to the timestamp.
	 */
	const size_t& time() const {
		return this->current_wait;
	}
};

#endif // SERVER_H
