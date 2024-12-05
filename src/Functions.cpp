#include "Functions.h"

std::map<std::string, Function> Functions::funcs;

void Functions::createFunction(std::string name, Function func) {
    funcs[name] = func;
}

Python3Parser::SuiteContext* Functions::visitFunction(std::string name, std::vector<std::any> parameters) {
    Function &fun = funcs[name];
    std::map<std::string, bool> vis;
    for (size_t i = 0; i < parameters.size(); ++i) {
        if (parameters[i].type() != typeid(std::pair<std::any, std::any>)) {
            Variable::setValueLocal(fun.getName(i), parameters[i]);
            vis[fun.getName(i)] = true;
        } else {
            std::pair<std::any, std::any> tmp = std::any_cast<std::pair<std::any, std::any>>(parameters[i]);
            Variable::setValueLocal(std::any_cast<std::pair<std::string, int>>(tmp.first).first, tmp.second);
            vis[std::any_cast<std::pair<std::string, int>>(tmp.first).first] = true;
        }
    }
    std::vector<std::pair<std::string, std::any>> param_list = fun.getParam();
    for (auto param: param_list) {
        if (!vis[param.first]) {
            Variable::setValueLocal(param.first, param.second);
        }
    }
    return fun.suite();
}