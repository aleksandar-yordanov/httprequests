//
//  HTTPRequest.cpp
//  Asio-test2
//
//  Created by Aleksandar Yordanov on 02/12/2021.
//

#include "HTTPRequest.h"

using namespace std::chrono_literals;
using namespace net;

std::vector<char> vBuffer(1024*20);

HTTPRequest::HTTPRequest()
{
    this->idleWork = std::make_unique<asio::io_context::work>(this->context);
    this->threadContext = std::thread([&](){context.run();});
    this->socket = std::make_unique<asio::ip::tcp::socket>(this->context);
}
HTTPRequest::~HTTPRequest()
{
    this->context.stop();
    if(this->threadContext.joinable()) this->threadContext.join();
}

void HTTPRequest::initialiseEndpoint(StringRequest req, std::string service)
{
    asio::ip::tcp::resolver resolver(this->context);
    asio::ip::tcp::resolver::query query(req.returnIpAddress(),service);
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    
    this->socketEndpoint = iter->endpoint();
}
void HTTPRequest::initialiseEndpoint(std::string ipAddress, std::string service)
{
    asio::ip::tcp::resolver resolver(this->context);
    asio::ip::tcp::resolver::query query(ipAddress,service);
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    
    this->socketEndpoint = iter->endpoint();
}

void Session::grabdata()
{
    this->socket->async_read_some(asio::buffer(vBuffer.data(),vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if(!ec){
                std::cout << "\nRead " << length << " bytes\n";
                for(int i =0; i < length; i++){
                    std::cout << vBuffer[i];
                    this->response.push_back(vBuffer[i]);
                }
                grabdata();
            }
        }
    );
}

void Session::connectAndSend(StringRequest req)
{
    if(this->socket == nullptr)
    {
        std::cout << "nullptr:socket";
    }
    this->socket->connect(this->socketEndpoint,this->ec);
    if(!this->ec)
    {
        std::cout<<"service resolved" << '\n';
    }
    else if(this->ec)
    {
        std::cout << this->ec.message() << '\n';
        socket->close();
        return;
    }
    if(this->socket->is_open())
    {
        std::cout << "socket open" << '\n';
        this->grabdata();
        
        std::string sReq = std::string(req);
        this->socket->write_some(asio::buffer(sReq.data(),sReq.size()),this->ec);
        
        //std::this_thread::sleep_for(2000ms);
        this->socket->wait(this->socket->wait_read,this->ec);
        size_t bytes = this->socket->available();
        std::cout << "bytes available: " << bytes << '\n';
        if(bytes > 0)
        {
            std::vector<char> vBuffer(bytes);
            this->socket->read_some(asio::buffer(vBuffer.data(),vBuffer.size()),this->ec);
            for(auto c : vBuffer)
            {
                std::cout << c;
            }
        }
        
        this->context.stop();
        
        if(this->threadContext.joinable()) this->threadContext.join();
    }
    /*
    this->socket->wait(this->socket->wait_read,this->ec);
    size_t bytes = this->socket->available();
    std::cout << "bytes available: " << bytes << '\n';
    if(bytes > 0)
    {
        std::vector<char> vBuffer(bytes);
        this->socket->read_some(asio::buffer(vBuffer.data(),vBuffer.size()),this->ec);
        for(auto c : vBuffer)
        {
            std::cout << c;
        }
    }
     */
    else if(this->socket->is_open() == false)
    {
        std::cout << "socket closed" << std::endl;
    }
}

std::string Session::returnResponse()
{
    return this->response;
}

void Session::closeConnection()
{
    this->socket->close(this->ec);
}

HTTPResponses net::mapIntToEnum(int value)
{
    switch(value)
    {
        case 0:
            return net::HTTPResponses::loginFailure;
            break;
        case 1:
            return net::HTTPResponses::loginSuccess;
            break;
        case 2:
            return net::HTTPResponses::databaseDown;
            break;
        case 3:
            return net::HTTPResponses::unknownResponse;
            break;
        default:
            return net::HTTPResponses::unknownResponse;
            break;
    }
}

int net::parseResponse(std::string inputStr)
{
    
    int initPos = inputStr.find("$"); //Not unsigned long as 
    std::string curStr = "";
    //try basic string return from php
    if(initPos != std::string::npos)
    {
        for(int i = 1; i < (inputStr.length()-1)-initPos;i++)
        {
            if(inputStr[initPos+i] == '?'){
                break;
            }
            else{
                curStr += inputStr[initPos+i];
            }
        }
    }
    try {
        return std::stoi(curStr);
    } catch (std::invalid_argument) {
        return std::stoi("3");
    }
    //std::cout << curStr << " debug" <<std::endl;
}

