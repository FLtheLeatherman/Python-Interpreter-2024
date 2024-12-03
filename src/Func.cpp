#include "Evalvisitor.h"

std::any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {
    std::string str = ctx->NAME()->getText();
    // std::cerr << str << std::endl;
    Functions::createFunction(str, Function(std::any_cast<std::vector<std::pair<std::string, std::any>>>(visit(ctx->parameters())), ctx->suite()));
    // std::cerr << "Funcdef successful!" << std::endl;
    return kDefault;
}

std::any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx) {
    if (ctx->typedargslist() != nullptr) {
        return visit(ctx->typedargslist());
    } else {
        return std::vector<std::pair<std::string, std::any>>();
    }
}

std::any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx) {
    std::vector<Python3Parser::TfpdefContext*> tfpdef_list = ctx->tfpdef();
    std::vector<Python3Parser::TestContext*> test_list = ctx->test();
    std::vector<std::pair<std::string, std::any>> res;
    for (size_t i = 0; i < tfpdef_list.size() - test_list.size(); ++i) {
        std::string str = std::any_cast<std::string>(visit(tfpdef_list[i]));
        // std::cerr << str << ',';
        res.push_back(std::make_pair(str, paramType::kNothing));
    }
    // std::cerr << std::endl;
    for (size_t i = 0; i < test_list.size(); ++i) {
        std::string str = std::any_cast<std::string>(visit(tfpdef_list[i + tfpdef_list.size() - test_list.size()]));
        // std::cerr << str << ',';
        std::any val = visit(test_list[i]);
        res.push_back(std::make_pair(str, val));
    }
    // std::cerr << std::endl;
    return res;
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
            // std::cerr << tmp.size() << std::endl;
            for (auto x: tmp) {
                res.push_back(x);
            }
        } else {
            res.push_back(val);
        }
    }
    // std::cerr << res.size() << std::endl;
    return res;
}

std::any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
    std::vector<Python3Parser::TestContext*> test_list = ctx->test();
    // std::cerr << test_list.size() << std::endl;
    if (test_list.size() == 1) {
        std::any val = visit(test_list[0]);
        Variable::tryGetValue(val);
        return val;
    } else {
        std::any val1 = visit(test_list[0]), val2 = visit(test_list[1]);
        Variable::tryGetValue(val1);
        Variable::tryGetValue(val2);
        // std::cerr << (std::any_cast<std::pair<std::string, int>>(val1).first) << ' ' << (std::any_cast<int2048>(val2)) << std::endl;
        return std::make_pair(val1, val2);
    }
}