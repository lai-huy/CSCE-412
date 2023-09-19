#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <sstream>

using std::string, std::ostringstream, std::ostream, std::to_string;

class Request {
private:
    string ipIn;
    string ipOut;
    size_t time;

    size_t random(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    string generate_IP() {
        std::ostringstream oss;
        oss << random(1, 255) << "." << random(0, 255) << "." << random(0, 255) << "." << random(1, 255);
        return oss.str();
    }
public:
    Request() : ipIn{this->generate_IP()}, ipOut{this->generate_IP()}, time{this->random(0, 3)} {}

    friend ostream& operator<<(ostream& os, const Request& request) {
        os << "Request{ipIn=" << request.ipIn << ", ipOut=" << request.ipOut << ", time=" << to_string(request.time) << "}";
        return os;
    }

    const size_t& getTime() const {
        return this->time;
    }
};

#endif // REQUEST_H