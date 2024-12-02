#include "Variables.h"

std::vector<std::map<std::string, std::any>> variable::vars;

std::any variable::getValue(const std::string &str) {
    if (vars.size() > 1) {
        if (vars.back().find(str) != vars.back().end()) {
            return vars.back()[str];
        }
    }
    return vars[0][str];
}

void variable::setValue(const std::string &str, const std::any &val) {
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

void variable::addScope() {
    vars.emplace_back();
}

void variable::deleteScope() {
    vars.pop_back();
}