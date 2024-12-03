#pragma once
#ifndef PYTHON_INTERPRETER_EVALVISITOR_H
#define PYTHON_INTERPRETER_EVALVISITOR_H

#include <iostream>
#include <iomanip>
#include "Python3ParserBaseVisitor.h"
#include "Variables.h"
#include "Trans.h"
#include "int2048.h"
#include "Functions.h"

enum endValue {
    kDefault, kBreak, kContinue, kReturnVoid
};

enum operatorType {
    kAdd, kSub, kMul, kDiv, kIDiv, kMod,
    kAddAssign, kSubAssign, kMulAssign, kDivAssign, kIDivAssign, kModAssign
};

enum CompType {
    kL, kG, kE, kLe, kGe, kNe 
};

enum valueType {
    kNone
};

class EvalVisitor : public Python3ParserBaseVisitor{

    // TODO: override all methods of Python3ParserBaseVisitor

    std::any visitFile_input(Python3Parser::File_inputContext *ctx) override;

    std::any visitFuncdef(Python3Parser::FuncdefContext *ctx) override;

    std::any visitParameters(Python3Parser::ParametersContext *ctx) override;

    std::any visitTypedargslist(Python3Parser::TypedargslistContext *ctx) override;

    std::any visitTfpdef(Python3Parser::TfpdefContext *ctx) override;

    std::any visitStmt(Python3Parser::StmtContext *ctx) override;

    std::any visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) override;

    std::any visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) override;

    std::any visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) override;

    std::any visitAugassign(Python3Parser::AugassignContext *ctx) override;

    std::any visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) override;

    std::any visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) override;

    std::any visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) override;

    std::any visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) override;

    std::any visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) override;

    std::any visitIf_stmt(Python3Parser::If_stmtContext *ctx) override;

    std::any visitWhile_stmt(Python3Parser::While_stmtContext *ctx) override;

    std::any visitSuite(Python3Parser::SuiteContext *ctx) override;

    std::any visitTest(Python3Parser::TestContext *ctx) override;

    std::any visitOr_test(Python3Parser::Or_testContext *ctx) override;

    std::any visitAnd_test(Python3Parser::And_testContext *ctx) override;

    std::any visitNot_test(Python3Parser::Not_testContext *ctx) override;

    std::any visitComparison(Python3Parser::ComparisonContext *ctx) override;

    std::any visitComp_op(Python3Parser::Comp_opContext *ctx) override;

    std::any visitArith_expr(Python3Parser::Arith_exprContext *ctx) override;

    std::any visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) override;

    std::any visitTerm(Python3Parser::TermContext *ctx) override;

    std::any visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) override;

    std::any visitFactor(Python3Parser::FactorContext *ctx) override;

    std::any visitAtom_expr(Python3Parser::Atom_exprContext *ctx) override;

    std::any visitTrailer(Python3Parser::TrailerContext *ctx) override;

    std::any visitAtom(Python3Parser::AtomContext *ctx) override;

    std::any visitFormat_string(Python3Parser::Format_stringContext *ctx) override;

    std::any visitTestlist(Python3Parser::TestlistContext *ctx) override;

    std::any visitArglist(Python3Parser::ArglistContext *ctx) override;

    std::any visitArgument(Python3Parser::ArgumentContext *ctx) override;

};

#endif//PYTHON_INTERPRETER_EVALVISITOR_H
