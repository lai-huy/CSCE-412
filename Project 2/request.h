#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <sstream>

using std::string, std::ostringstream, std::ostream, std::to_string;
using std::move;

/**
 * @brief The Request class represents a network request with source and destination IP addresses and a timestamp.
 */
class Request {
private:
	/**
	 * @brief Source IP Address of the request
	 */
	string ipIn;

	/**
	 * @brief Desination IP Address of the request
	 */
	string ipOut;

	/**
	 * @brief Time stamp of the request.
	 */
	size_t time;

	/**
	 * @brief Generated a random unsigned long within the range [min, max)
	 *
	 * @param min lower bound
	 * @param max higher bound
	 * @return size_t random number generated
	 */
	size_t random(size_t min, size_t max) {
		return min + rand() % (max - min + 1);
	}

	/**
	 * @brief Generates a random Internet Protocall Address
	 *
	 * @return string random IP address
	 */
	string generate_IP() {
		std::ostringstream oss;
		oss << random(1, 255) << "." << random(0, 255) << "." << random(0, 255) << "." << random(1, 255);
		return oss.str();
	}
public:
	/**
	 * @brief Construct a new Request object
	 */
	Request() : ipIn{this->generate_IP()}, ipOut{this->generate_IP()}, time{this->random(0, 3)} {}

	Request(const Request& other) : ipIn{other.ipIn}, ipOut{other.ipOut}, time{other.time} {}

	Request(Request&& other) noexcept : ipIn{move(other.ipIn)}, ipOut{move(other.ipOut)}, time{other.time} {
		other.time = 0;
	}

	Request& operator=(const Request& other) {
		if (this != &other) {
			this->ipIn = other.ipIn;
			this->ipOut = other.ipOut;
			this->time = other.time;
		}

		return *this;
	}

	Request& operator=(Request&& other) noexcept {
		if (this != &other) {
			this->ipIn = move(other.ipIn);
			this->ipOut = move(other.ipOut);
			this->time = other.time;
			other.time = 0;
		}

		return *this;
	}

	/**
	 * @brief Overloaded stream insertion operator to print the Request object.
	 *
	 * @param os The output stream to which the Request object is printed.
	 * @param request The Request object to be printed.
	 * @return ostream& The output stream after printing the Request object.
	 */
	friend ostream& operator<<(ostream& os, const Request& request) {
		os << "Request{ipIn=" << request.ipIn << ", ipOut=" << request.ipOut << ", time=" << to_string(request.time) << "}";
		return os;
	}

	/**
	* @brief Get the timestamp of the Request.
	*
	* @return const size_t& The timestamp of the Request.
	*/
	const size_t& getTime() const {
		return this->time;
	}
};

#endif // REQUEST_H
