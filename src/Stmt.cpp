#include "Evalvisitor.h"

std::any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx) {
    if (ctx->simple_stmt() != nullptr) {
        return visit(ctx->simple_stmt());
    } else {
        return visit(ctx->compound_stmt());
    }
}

std::any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) {
    return visit(ctx->small_stmt());
}

std::any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) {
    if (ctx->expr_stmt() != nullptr) {
        return visit(ctx->expr_stmt());
    } else {
        return visit(ctx->flow_stmt());
    }
}


std::any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {
    std::vector<Python3Parser::TestlistContext*> testlist_list = ctx->testlist();
    if (testlist_list.size() == 1) {
        visit(testlist_list[0]);
    } else {
        if (ctx->augassign() == nullptr) {
            std::vector<std::any> LHS_list;
            std::vector<std::any> RHS_list = std::any_cast<std::vector<std::any>>(visit(testlist_list[testlist_list.size() - 1]));
            for (int i = testlist_list.size() - 2; i >= 0; --i) { // do not use size_t
                LHS_list = std::any_cast<std::vector<std::any>>(visit(testlist_list[i]));
                for (size_t j = 0; j < RHS_list.size(); ++j) {
                    std::any val = RHS_list[j];
                    Variable::tryGetValue(val);
                    Variable::setValue(std::any_cast<std::pair<std::string, int>>(LHS_list[j]).first, val);
                }
                RHS_list.swap(LHS_list);
            }
        } else {
            std::vector<std::any> tmp = std::any_cast<std::vector<std::any>>(visit(testlist_list[0]));
            std::string LHS = std::any_cast<std::pair<std::string, int>>(tmp[0]).first;
            std::any val = Variable::getValue(LHS);
            std::any RHS = std::any_cast<std::vector<std::any>>(visit(testlist_list[1]))[0];
            operatorType opt = std::any_cast<operatorType>(visit(ctx->augassign()));
            if (opt == kAddAssign) {
                if (val.type() == typeid(std::string) || RHS.type() == typeid(std::string)) {
                    val = anyToString(val) + anyToString(RHS);
                } else if (val.type() == typeid(double) || RHS.type() == typeid(double)) {
                    val = anyToDouble(val) + anyToDouble(RHS);
                } else {
                    val = anyToInt(val) + anyToInt(RHS);
                }
            } else if (opt == kSubAssign) {
                if (val.type() == typeid(double) || RHS.type() == typeid(double)) {
                    val = anyToDouble(val) - anyToDouble(RHS);
                } else {
                    val = anyToInt(val) - anyToInt(RHS);
                }
            } else if (opt == kMulAssign) {
                if (val.type() == typeid(std::string)) {
                    val = std::any_cast<std::string>(val) * anyToInt(RHS);
                } else if (RHS.type() == typeid(std::string)) {
                    val = std::any_cast<std::string>(RHS) * anyToInt(val);
                } else if (val.type() == typeid(double) || RHS.type() == typeid(double)) {
                    val = anyToDouble(val) * anyToDouble(RHS);
                } else {
                    val = anyToInt(val) * anyToInt(RHS);
                }
            } else if (opt == kDivAssign) {
                val = anyToDouble(val) / anyToDouble(RHS);
            } else if (opt == kIDivAssign) {
                val = anyToInt(val) / anyToInt(RHS);
            } else {
                val = anyToInt(val) % anyToInt(RHS);
            }
            Variable::setValue(LHS, val);
        }
    }
    return kDefault;
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
        std::vector<std::any> val_list = std::any_cast<std::vector<std::any>>(visit(ctx->testlist()));
        for (size_t i = 0; i < val_list.size(); ++i) {
            Variable::tryGetValue(val_list[i]);
        }
        if (val_list.size() == 1) {
            return val_list[0];
        } else {
            return val_list;
        }
    } else {
        return kReturnVoid;
    }
}

std::any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) {
    if (ctx->if_stmt() != nullptr) {
        std::any tmp = visit(ctx->if_stmt());
        return tmp;
    } else if (ctx->while_stmt() != nullptr) {
        return visit(ctx->while_stmt());
    } else {
        return visit(ctx->funcdef());
    }
}

std::any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
    std::vector<Python3Parser::TestContext*> test_list = ctx->test();
    std::vector<Python3Parser::SuiteContext*> suite_list = ctx->suite();
    for (size_t i = 0; i < test_list.size(); ++i) {
        std::any val = visit(test_list[i]);
        if (anyToBoolean(val)) {
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
        if (val.type() == typeid(endValue)) {
            endValue tmp = std::any_cast<endValue>(val);
            if (tmp == kBreak) {
                break;
            } else if (tmp == kReturnVoid) {
                return kReturnVoid;
            }
        } else {
            return val;
        }
    }
    return kDefault;
}

std::any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {
    if (ctx->simple_stmt() != nullptr) {
        return visit(ctx->simple_stmt());
    } else {
        std::vector<Python3Parser::StmtContext*> stmt_list;
        stmt_list = ctx->stmt();
        for (auto x: stmt_list) {
            std::any val = visitStmt(x);
            if (val.type() != typeid(endValue)) {
                return val;
            }
            
            endValue tmp = std::any_cast<endValue>(val);
            if (tmp != kDefault) {
                return tmp;
            }
        }
        return kDefault;
    }
}