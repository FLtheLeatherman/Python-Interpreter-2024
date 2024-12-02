#include "Evalvisitor.h"

std::any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {
    
    return 0;
}

std::any EvalVisitor::visitParameters(Python3Parser::ParametersContext *) {
    return 0;
}

std::any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *) {
    return 0;
}

std::any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx) {
    return ctx->NAME()->getText();
}

std::any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx) {
    std::vector<Python3Parser::ArgumentContext*> arg_list = ctx->argument();
    std::vector<std::any> res;
    for (auto &arg: arg_list) {
        std::any val = visit(arg);
        Variable::tryGetValue(val);
        if (val.type() == typeid(std::vector<std::any>)) {
            std::vector<std::any> tmp = std::any_cast<std::vector<std::any>>(val);
            for (auto x: tmp) {
                res.push_back(x);
            }
        } else {
            res.push_back(val);
        }
    }
    return res;
}

std::any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
    std::vector<Python3Parser::TestContext*> test_list = ctx->test();
    if (test_list.size() == 1) {
        std::any val = visit(test_list[0]);
        return val;
    } else {
        return std::make_pair(visit(test_list[0]), visit(test_list[1]));
    }
}