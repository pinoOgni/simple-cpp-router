#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>

#include "PathMatch.h"
#include "Details/RegexConverter.h"

namespace Routing {

namespace Details {
class PathTemplate;
}

/**
 * @brief Simple uri router
 */
class Router {
public:
    Router();

    /**
    * @brief register path
    * @param path path (e.g. /routes/path, /routes/:some_var)
    * @returns path id
    */
    void registerPath(std::string const &path, std::string const &http_verb);

    /**
    * @brief match path
    * @param path (e.g. /routes/path)
    * @returns path id if matched, or -1 if no match detected
    */
    PathMatch matchPath(std::string const &path, std::string const &http_verb);
    
    /*

    */
    void RegisterPathGeneric(std::string path, std::string http_verb, void(*method)(std::string,std::string));

    /*

    */
    void RegisterPathPatch(std::string path, void(*method)(std::string,std::string));

    /*

    */
    void RegisterPathDelete(std::string path, void(*method)(std::string,std::string));

    /*

    */
    void RegisterPathGet(std::string path, void(*method)(std::string,std::string));

    /*

    */
    void RegisterPathPost(std::string path, void(*method)(std::string,std::string));

    std::map<std::pair<std::string,std::string>, void(*)(std::string,std::string)>* GetMethodsMap();

private:
    std::vector<Details::PathTemplate> _templates;
    std::unique_ptr<Details::RegexConverter> _regexConverter;
    std::map<std::pair<std::string,std::string>, void(*)(std::string,std::string)> methods_map;  // key = pair fo url and http_verb; value = handler function
    std::string base_url = "/polycube/v1";
};

}