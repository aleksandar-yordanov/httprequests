//
//  StringRequest.h
//  Asio-test2
//
//  Created by Aleksandar Yordanov on 29/11/2021.
//



#pragma once
#include "netCommon.h"

namespace net{
class StringRequest{
    std::string HTMLRequestString;
    std::string ipAddress;
public:
    StringRequest(int method, std::string resource, std::string ipAddress,std::string json);
    
    operator std::string() const;
    
    std::string returnString();
    std::string returnIpAddress();
};
}

