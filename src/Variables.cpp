#include "Variables.h"

std::vector<std::map<std::string, std::any>> Variable::vars;

void Variable::tryGetValue(std::any &val) {
    if (val.type() == typeid(std::pair<std::string, int>)) {
        val = getValue(std::any_cast<std::pair<std::string, int>>(val).first);
    }
}

std::any Variable::getValue(const std::string &str) {
    if (!vars.size()) {
        vars.emplace_back();
    }
    if (vars.size() > 1) {
        if (vars.back().find(str) != vars.back().end()) {
            return vars.back()[str];
        }
    }
    return vars[0][str];
}

void Variable::setValue(const std::string &str, const std::any &val) {
    if (!vars.size()) {
        vars.emplace_back();
    }
    if (vars.size() > 1 && vars.back().find(str) != vars.back().end()) {
        vars.back()[str] = val;
    } else if (vars[0].find(str) != vars[0].end()) {
        vars[0][str] = val;
    } else if (vars.size() > 1) {
        vars.back()[str] = val;
    } else {
        vars[0][str] = val;
    }
}

void Variable::setValueLocal(const std::string &str, const std::any &val) {
    vars.back()[str] = val;
}

void Variable::addScope() {
    vars.emplace_back();
}

void Variable::deleteScope() {
    vars.pop_back();
}