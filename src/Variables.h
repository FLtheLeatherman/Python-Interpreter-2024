#pragma once
#ifndef PYTHON_INTERPRETER_VARIABLES_H
#define PYTHON_INTERPRETER_VARIABLES_H

#include <map>
#include <string>
#include <any>
#include <vector>

class Variable {
private:
    static std::vector<std::map<std::string, std::any>> vars; // globs in vars[0], locals in vars[>=1]
public:
    static void tryGetValue(std::any &);
    static std::any getValue(const std::string &);
    static void setValue(const std::string &, const std::any &);
    static void addScope();
    static void deleteScope();
};

#endif