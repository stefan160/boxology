#include <iostream>
#include <boost/uuid/uuid_io.hpp>

#include "json_visitor.hpp"
using namespace std;

void JsonVisitor::startUp()
{
    ss << "{\"nodes\":[";
}

void JsonVisitor::endNodes()
{
    ss.seekp((long)(ss.tellp()) - 1); // remove the last comma
    ss << endl << "], " << endl << "\"connections\":[";
}


void JsonVisitor::tearDown()
{
    ss.seekp((long)(ss.tellp()) - 1); // remove the last comma
    ss << endl << "]" << endl << "}" << endl;

    cout << ss.str();
}


void JsonVisitor::onNode(shared_ptr<const Node> node)
{

    ss << endl << "{\"node\": \"" << node->uuid << "\", ";
    ss << "\"name\": \"" << node->name << "\", ";
    ss << "\"ports\": [";
    for (const auto port : node->ports) {
        ss << "{\"name\": \"" << port.first << "\",";
        ss << " \"direction\": \"" << (port.second ? "in":"out") << "\"},";
    }
    ss.seekp((long)(ss.tellp()) - 1); // remove the last comma
    ss << "]},";

}

void JsonVisitor::onConnection(shared_ptr<const Connection> connection)
{

    ss << endl << "{\"connection\": \"" << connection->uuid << "\", ";
    ss << "\"name\": \"" << connection->name << "\", ";
    ss << "\"from\": \"" << connection->from.first->uuid << ":" << connection->from.second << "\", ";
    ss << "\"to\": \"" << connection->to.first->uuid << ":" << connection->to.second << "\"},";
    //cout << "\"type\": \"" << connection->type << "\"" << endl;

}

