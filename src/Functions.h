#include <vector>
#include <map>
#include <any>
#include "Python3ParserBaseVisitor.h"
#include "Variables.h"
#include "int2048.h"

// 一个 Func 类，需要一堆 parameters（记录是否初值），和一个 suite
// 能够独立创建一个 local scope，并且其他变量都是 global

enum paramType{
    kNothing
}; // 参数没有值

class Function {
private:
    std::vector<std::pair<std::string, std::any>> parameter_list;
    Python3Parser::SuiteContext *ctx;
public:
    Function(){
        parameter_list = std::vector<std::pair<std::string, std::any>>();
        ctx = nullptr;
    }
    Function(std::vector<std::pair<std::string, std::any>> parameter_list, Python3Parser::SuiteContext *ctx) {
        this->parameter_list.swap(parameter_list);
        this->ctx = ctx;
    }
    std::string getName(int i) {
        return parameter_list[i].first;
    }
    std::vector<std::pair<std::string, std::any>> getParam() {
        return parameter_list;
    }
    Python3Parser::SuiteContext* suite() {
        return ctx;
    }
};

class Functions {
private:
    static std::map<std::string, Function> funcs;
public:
    static void createFunction(std::string, Function);
    static Python3Parser::SuiteContext* visitFunction(std::string, std::vector<std::any>);
};