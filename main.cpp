//#include "HTTPRequest.h"

#include "netCommon.h"
#include "HTTPRequest.h"
#include "StringRequest.h"

int main()
{
    json testJs;
    //testJs["test"]=123
    std::string inUser;
    std::string inPass;
    std::string inEmail;
    std::cout << "username:";
    std::cin >> inUser;
    std::cout << "password:";
    std::cin >> inPass;
    std::cout << "new password:";
    std::cin >> inEmail;
    testJs["Username"] = inUser;
    testJs["Password"] = inPass;
    testJs["Updated"] = inEmail;
    //std::cout << testJs.dump();
    net::StringRequest sReq(0,"aleks/reset.php","51.38.80.233",testJs.dump());
    net::Session s1;
    //std::cout << std::string(sReq);
    s1.initialiseEndpoint("51.38.80.233", "http");
    s1.connectAndSend(sReq);
    int loginState = net::parseResponse(s1.returnResponse());
    if(net::mapIntToEnum(loginState)==net::HTTPResponses::loginSuccess){
        std::cout << "login success" << std::endl;
    }
    else std::cout <<"login failure"<<std::endl;
    //std::string x = s1.returnResponse();
    //std::cout << x << std::endl;

    return 0;
    //std::cout << json::meta() << std::endl;
}


