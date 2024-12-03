#include "Evalvisitor.h"

std::any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) {
    std::any res = visit(ctx->or_test());
    // std::cerr << (res.type() == typeid(bool)) << std::endl;
    return res;
}

std::any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
    std::vector<Python3Parser::And_testContext*> andtest_list = ctx->and_test();
    if (andtest_list.size() == 1) {
        return visit(andtest_list[0]);
    } else {
        for (auto &node: andtest_list) {
            if (anyToBoolean(visit(node))) {
                return true;
            }
        }
        return false;
    }
}

std::any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
    std::vector<Python3Parser::Not_testContext*> nottest_list = ctx->not_test();
    if (nottest_list.size() == 1) {
        return visit(nottest_list[0]);
    } else {
        for (auto &node: nottest_list) {
            if (!anyToBoolean(visit(node))) {
                return false;
            }
        }
        return true;
    }
}

std::any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) {
    if (ctx->not_test() != nullptr) {
        std::any val = anyToBoolean(visit(ctx->not_test()));
        // std::cerr << (val.type() == typeid(bool)) << std::endl;
        return !anyToBoolean(val);
    } else {
        return visit(ctx->comparison());
    }
}

std::any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) {
    std::vector<Python3Parser::TestContext*> test_list = ctx->test();
    std::vector<std::any> res;
    // std::cerr << "GOOD!" << std::endl;
    for (auto &node: test_list) {
        std::any val = visit(node);
        // std::cerr << '?' << (val.type() == typeid(std::pair<std::string, int>)) << std::endl;
        if (val.type() == typeid(std::vector<std::any>)) {
            std::vector<std::any> tmp = std::any_cast<std::vector<std::any>>(val);
            // std::cerr << tmp.size() << std::endl;
            for (auto x: tmp) {
                res.push_back(x);
            }
        } else {
            // std::cerr << "?" << (val.type() == typeid(std::pair<std::string, int>)) << ' ' << (val.type() == typeid(int)) << std::endl;
            res.push_back(val);
        }
    }
    // std::cerr << "Testlist!" << std::endl;
    // std::cerr << res.size() << std::endl;
    // std::cerr << (res[0].type() == typeid(int2048)) << std::endl;
    return res;
}