//
//  ParseResponse.cpp
//  Asio-testing3
//
//  Created by Aleksandar Yordanov on 08/12/2021.
//
#include "netCommon.h"

namespace net{
bool ParseResponse(std::string inputStr)
{
    
    int initPos = inputStr.find("$");
    std::string curStr = "";
    //try basic string return from php
    if(initPos != std::string::npos)
    {
        this->parsedResponseJSON == NULL;
        for(int i = 0; i < (inputStr.length()-1)-initPos;i++)
        {
            if(inputStr[initPos+i] == '?'){
                this->parsedResponseVec.push_back(curStr);
            }
            else{
                curStr += inputStr[initPos+i];
            }
        }
    }
}
}
