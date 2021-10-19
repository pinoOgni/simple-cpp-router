#include "Router.h"

#include "Details/PathTemplate.h"
#include "Details/RegexConverter.h"
#include "Exceptions.h"
#include <iostream>

namespace Routing {

using Details::PathTemplate;
using Details::RegexConverter;

Router::Router() {
}

void Router::registerPath(std::string const &path, std::string const &http_verb) {
    std::string uppercase_http_verb(http_verb);
    for (auto & c: uppercase_http_verb) c = std::toupper(c);
    _templates.push_back(PathTemplate(path,uppercase_http_verb));
}

/*
    modification compared to the original, you check the path but also the http verb
*/
PathMatch Router::matchPath(std::string const &path, std::string const &http_verb) {
    std::string uppercase_http_verb(http_verb);
    for (auto & c: uppercase_http_verb) c = std::toupper(c);
    for (auto &tpl: _templates) {
        if (std::regex_match(path, tpl.regex()) && tpl.http_verb() == uppercase_http_verb) {
            std::cout << "path " << path << std::endl;
            return PathMatch(path, tpl,uppercase_http_verb);
        }
    }

    throw PathNotFoundException("Path not found for '" + path + "'");
}

/*
    register a path with http verb given by the user
*/
void Router::RegisterPathGeneric(std::string path, std::string http_verb, void(*method)(std::string,std::string)) {
    std::string uppercase_http_verb(http_verb);
    for (auto & c: uppercase_http_verb) c = std::toupper(c);
    registerPath(base_url+"/"+path,uppercase_http_verb);
    methods_map[std::make_pair(std::string(base_url+"/"+path),uppercase_http_verb)] = method;
}

/*
    register a path with http verb equal to PATCH
*/
void Router::RegisterPathPatch(std::string path, void(*method)(std::string,std::string)) {
    registerPath(base_url+"/"+path,"PATCH");
    methods_map[std::make_pair(std::string(base_url+"/"+path),"PATCH")] = method;
}


/*
    register a path with http verb equal to DEL
*/
void Router::RegisterPathDelete(std::string path, void(*method)(std::string,std::string)) {
    registerPath(base_url+"/"+path,"DELETE");
    methods_map[std::make_pair(std::string(base_url+"/"+path),"DELETE")] = method;
}

/*
    register a path with http verb equal to POST
*/
void Router::RegisterPathPost(std::string path, void(*method)(std::string,std::string)) {
    registerPath(base_url+"/"+path,"POST");
    methods_map[std::make_pair(std::string(base_url+"/"+path),"POST")] = method;
}

/*
    register a path with http verb equal to GET
*/
void Router::RegisterPathGet(std::string path, void(*method)(std::string,std::string)) {
    registerPath(base_url+"/"+path,"GET");
    methods_map[std::make_pair(std::string(base_url+"/"+path),"GET")] = method;
}

/*
    return a simple pointer to the methods_map
*/
std::map<std::pair<std::string,std::string>, void(*)(std::string,std::string)>* Router::GetMethodsMap() {
    return &methods_map;
}



}