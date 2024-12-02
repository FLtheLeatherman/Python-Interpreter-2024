#include "Evalvisitor.h"

std::any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) {
    std::any res = visit(ctx->or_test());
    // std::cerr << (res.type() == typeid(endValue)) << std::endl;
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
        return !anyToBoolean(visit(ctx->not_test()));
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
        if (val.type() == typeid(std::vector<std::any>)) {
            std::vector<std::any> tmp = std::any_cast<std::vector<std::any>>(val);
            for (size_t i = 0; i < tmp.size(); ++i) {
                res.push_back(tmp[i]);
            }
        } else {
            // std::cerr << '?' << (val.type() == typeid(std::pair<std::string, int>)) << std::endl;
            res.push_back(val);
        }
    }
    // std::cerr << "Testlist!" << std::endl;
    return res;
}