//
//  StringRequest.cpp
//  Asio-test2
//
//  Created by Aleksandar Yordanov on 29/11/2021.
//

/*
 "GET /pmahidden HTTP/1.1\r\n"
 "Host: 51.38.80.233\r\n"
 "Connection: close\r\n\r\n";
 */
#include "StringRequest.h"
using namespace net;

StringRequest::StringRequest(int method, std::string resource, std::string ipAddress, std::string json = "")
{
    std::string jLength = std::to_string(json.length());
    switch (method)
    {
        case 0:
            this->HTMLRequestString += "POST /"+resource+" HTTP/1.1\r\n";
            this->HTMLRequestString += "Host: "+ipAddress+"\r\n";
            //this->HTMLRequestString += "User-Agent: HTTPTool/1.0\r\n";
            this->HTMLRequestString += "Content-Type: application/x-www-form-urlencoded\r\n";
            //this->HTMLRequestString += "Accept: */*\r\n";
            this->HTMLRequestString += "Content-Length: " + jLength + "\r\n";
            this->HTMLRequestString += "Connection: close\r\n\r\n";  //NOTE THE Double line feed
            this->HTMLRequestString += json;
            //std::cout << this->HTMLRequestString << " ";
            break;
        case 1:
            this->HTMLRequestString += "GET /" + resource +'?'+ json + " HTTP/1.1\r\n";
            this->HTMLRequestString += "Host: " + ipAddress + "\r\n";
            this->HTMLRequestString += "Connection: close\r\n\r\n";
            this->HTMLRequestString += json;
            break;

            
    }
    this->ipAddress = ipAddress;
}

std::string StringRequest::returnString()
{
    return this->HTMLRequestString;
}

StringRequest::operator std::string() const
{
    return this->HTMLRequestString;
}

std::string StringRequest::returnIpAddress()
{
    return this->ipAddress;
}
