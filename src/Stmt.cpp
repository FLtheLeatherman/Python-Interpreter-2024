#include "Evalvisitor.h"

std::any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx) {
    // std::cerr << "Stmt!" << std::endl;
    if (ctx->simple_stmt() != nullptr) {
        return visit(ctx->simple_stmt());
    } else {
        return visit(ctx->compound_stmt());
    }
}

std::any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) {
    // std::cerr << "Simple_stmt!" << std::endl;
    return visit(ctx->small_stmt());
}

std::any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) {
    // std::cerr << "Small_stmt!" << std::endl;
    if (ctx->expr_stmt() != nullptr) {
        return visit(ctx->expr_stmt());
    } else {
        return visit(ctx->flow_stmt());
    }
}

std::any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {
    // std::cerr << "Expr_stmt!" << std::endl;
    std::vector<Python3Parser::TestlistContext*> testlist_list = ctx->testlist();
    if (testlist_list.size() == 1) {
        visit(testlist_list[0]);
        return kDefault;
    }
    if (ctx->augassign() == nullptr) {
        
    }
}

std::any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) {
    if (ctx->break_stmt() != nullptr) {
        return visit(ctx->break_stmt());
    } else if (ctx->continue_stmt() != nullptr) {
        return visit(ctx->continue_stmt());
    } else {
        return visit(ctx->return_stmt());
    }
}

std::any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) {
    return kBreak;
}

std::any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) {
    return kContinue;
}

std::any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {
    if (ctx->testlist() != nullptr) {
        return visit(ctx->testlist());
    } else {
        return kReturnVoid;
    }
}

std::any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) {
    if (ctx->if_stmt() != nullptr) {
        return visit(ctx->if_stmt());
    } else if (ctx->while_stmt()) {
        return visit(ctx->while_stmt());
    } else {
        return visit(ctx->funcdef());
    }
}

std::any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
    std::vector<Python3Parser::TestContext*> test_list = ctx->test();
    std::vector<Python3Parser::SuiteContext*> suite_list = ctx->suite();
    for (size_t i = 0; i < test_list.size(); ++i) {
        if (anyToBoolean(visit(test_list[i]))) {
            return visit(suite_list[i]);
        }
    }
    if (suite_list.size() == test_list.size()) {
        return kDefault;
    } else {
        return visit(suite_list.back());
    }
}

std::any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
    while (anyToBoolean(visit(ctx->test()))) {
        std::any val = visit(ctx->suite());
        endValue tmp = std::any_cast<endValue>(val);
        if (tmp == kBreak) {
            break;
        } else if (tmp == kContinue) {
            continue;
        } else if (tmp == kReturnVoid) {
            return kReturnVoid;
        }
    }
    return kDefault;
}

std::any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {
    // std::cerr << "suite!" << std::endl;
    if (ctx->simple_stmt() != nullptr) {
        return visit(ctx->simple_stmt());
    } else {
        std::vector<Python3Parser::StmtContext*> stmt_list;
        stmt_list = ctx->stmt();
        for (auto x: stmt_list) {
            std::any val = visitStmt(x);
            // std::cerr << (val.type() == typeid(endValue)) << std::endl;
            // std::cerr << "End" << std::endl;
            endValue tmp = std::any_cast<endValue>(val);
            // std::cerr << tmp << std::endl;
            if (tmp != kDefault) {
                return tmp;
            }
        }
        return kDefault;
    }
}