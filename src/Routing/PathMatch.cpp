#include "PathMatch.h"
#include "Exceptions.h"

namespace Routing {

PathMatch::PathMatch(std::string path, Details::PathTemplate const &tpl, std::string http_verb)
: _path(path), _pathTemplate(tpl), _tokenizer(path, '/'), _http_verb(http_verb) {

}

std::string PathMatch::getVar(std::string const &name) const {
    if (!_pathTemplate.parser().hasDynVar(name)) {
        return "";
    }

    int pos = _pathTemplate.parser().getDynVarPos(name);
    return _tokenizer.getToken(pos);
}

std::string PathMatch::pathTemplate() const {
    return _pathTemplate.templ();
}

std::string PathMatch::operator[](std::string const &name) const {
    return getVar(name);
}

}