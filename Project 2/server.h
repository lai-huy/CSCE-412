#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "request.h"

using std::string, std::ostream;

class Server {
private:
    string name;
    Request current_request;
    size_t current_wait;

public:
    Server(const string& name) : name{name}, current_request{Request{}}, current_wait{0} {}

    void handle_request(const Request& request, size_t timestamp) {
        current_request = request;
        current_wait = timestamp;
    }

    friend ostream& operator<<(ostream& os, const Server& server) {
        os << "Server{name=" << server.name << "}";
        return os;
    }

    const Request& getRequest() const {
        return this->current_request;
    }

    const string& getName() const {
        return this->name;
    }

    const size_t& time() const {
        return this->current_wait;
    }
};

#endif // SERVER_H
