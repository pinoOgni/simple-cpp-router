#include <iostream>
#include <cassert>
#include "Routing/Router.h"
#include "Routing/PathMatch.h"
#include "Routing/Exceptions.h"

#include "Routing/Details/PathTemplate.h"
#include "Routing/Details/RegexConverter.h"
#include "Routing/Details/PathTemplateParser.h"
#include "Routing/Details/StringTokenizer.h"

using namespace std;
using Routing::Router;
using Routing::PathMatch;

Router router;


void example_method_1(std::string template_url, std::string url) {
     std::cout << "example_method_1: url " << url << "; template url:" << template_url << std::endl;
}

void example_method_2(std::string template_url, std::string http_verb) {
     std::cout << "example_method_2: http_verb " << http_verb << "; template url:" << template_url << std::endl;
}


int main()
{
    
    router.RegisterPathPost(":serviceName/",&example_method_1);
    router.RegisterPathGet(":serviceName/:cubeName/",&example_method_2);

    // call example_method1
    PathMatch match1 = router.matchPath("/polycube/v1/helloworld/","post");
    std::cout << "pathTemplate " << match1.pathTemplate() << std::endl; 
    std::cout << "path " << match1.path() << std::endl;   
    
    // retrieve the corret method from the map
    auto method_call1  = router.GetMethodsMap()->at(std::make_pair(match1.pathTemplate(),match1.http_verb()));

    //  call the method
    method_call1(match1.pathTemplate(),match1.http_verb());


    // call example_method2
    PathMatch match2 = router.matchPath("/polycube/v1/helloworld/h1/","get");
    std::cout << "pathTemplate " << match2.pathTemplate() << std::endl; 
    std::cout << "path " << match2.path() << std::endl;   
    
    // retrieve the corret method from the map
    auto method_call2  = router.GetMethodsMap()->at(std::make_pair(match2.pathTemplate(),match2.http_verb()));

    //  call the method
    method_call2(match2.pathTemplate(),match2.http_verb());


    // another test
    std::string service_name = match2["serviceName"];
    std::string cube_name = match2["cubeName"];
    
    std::cout << "service name " << service_name << " and cube name " << cube_name << std::endl;


    return 0;
}
