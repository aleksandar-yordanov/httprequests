//
//  HTTPRequest.h
//  Asio-test2
//
//  Created by Aleksandar Yordanov on 02/12/2021.
//

#pragma once

#include "StringRequest.h"

//std::vector<char> vBuffer(1024*20);

namespace net{
    
    enum class HTTPResponses
    {
        loginSuccess,
        loginFailure,
        databaseDown,
        unknownResponse,
    };
    HTTPResponses mapIntToEnum(int value);
    int parseResponse(std::string inputStr);
}
namespace net
{
class HTTPRequest {
protected:
    std::thread threadContext;
    asio::error_code ec;
    asio::io_context context;
    std::unique_ptr<asio::io_context::work> idleWork;
    std::unique_ptr<asio::ip::tcp::socket> socket; // replace raw pointers with unique_ptrs
    asio::ip::tcp::endpoint socketEndpoint;
    
public:
    explicit HTTPRequest(); //Preps context and keeps it from destruction with idle work on a seperate thread.
    ~HTTPRequest();
public:
    void initialiseEndpoint(StringRequest req, std::string service);
    void initialiseEndpoint(std::string ipAddress, std::string service);
};

class Session : public HTTPRequest
{
    std::string response;
public:
    void grabdata();
    void connectAndSend(StringRequest req);
    void closeConnection();
    std::string returnResponse();
};
}
