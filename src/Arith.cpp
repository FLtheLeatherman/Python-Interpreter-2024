#include "Evalvisitor.h"

std::any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx) {
    std::vector<Python3Parser::Arith_exprContext*> arith_list = ctx->arith_expr();
    std::vector<Python3Parser::Comp_opContext*> op_list = ctx->comp_op();
    std::any res = visit(arith_list[0]);
    if (arith_list.size() == 1) {
        return res;
    }
    Variable::tryGetValue(res);
    for (size_t i = 1; i < arith_list.size(); ++i) {
        CompType opt = std::any_cast<CompType>(visit(op_list[i - 1]));
        std::any val = visit(arith_list[i]);
        Variable::tryGetValue(val);
        if (opt == kL) {
            if (res.type() == typeid(std::string)) {
                if (std::any_cast<std::string>(res) >= std::any_cast<std::string>(val)) {
                    return false;
                }
            } else if (res.type() == typeid(double) || val.type() == typeid(double)) {
                if (anyToDouble(res) >= anyToDouble(val)) {
                    return false;
                }
            } else {
                if (anyToInt(res) >= anyToInt(val)) {
                    return false;
                }
            }
        } else if (opt == kG) {
            if (res.type() == typeid(std::string)) {
                if (std::any_cast<std::string>(res) <= std::any_cast<std::string>(val)) {
                    return false;
                }
            } else if (res.type() == typeid(double) || val.type() == typeid(double)) {
                if (anyToDouble(res) <= anyToDouble(val)) {
                    return false;
                }
            } else {
                if (anyToInt(res) <= anyToInt(val)) {
                    return false;
                }
            }
        } else if (opt == kE) {
            if ((res.type() == typeid(valueType)) && (val.type() != typeid(valueType))) {
                return false;
            } else if ((res.type() != typeid(valueType)) && (val.type() == typeid(valueType))) {
                return false;
            } else if ((res.type() == typeid(valueType)) && (val.type() == typeid(valueType))) {
                // do nothing.
            } else if (res.type() == typeid(std::string) || val.type() == typeid(std::string)) {
                if (res.type() != typeid(std::string) || val.type() != typeid(std::string)) {
                    return false;
                }
                if (std::any_cast<std::string>(res) != std::any_cast<std::string>(val)) {
                    return false;
                }
            } else if (res.type() == typeid(double) || val.type() == typeid(double)) {
                if (anyToDouble(res) != anyToDouble(val)) {
                    return false;
                }
            } else {
                if (anyToInt(res) != anyToInt(val)) {
                    return false;
                }
            }
        } else if (opt == kLe) {
            if (res.type() == typeid(std::string)) {
                if (std::any_cast<std::string>(res) > std::any_cast<std::string>(val)) {
                    return false;
                }
            } else if (res.type() == typeid(double) || val.type() == typeid(double)) {
                if (anyToDouble(res) > anyToDouble(val)) {
                    return false;
                }
            } else {
                if (anyToInt(res) > anyToInt(val)) {
                    return false;
                }
            }
        } else if (opt == kGe) {
            if (res.type() == typeid(std::string)) {
                if (std::any_cast<std::string>(res) < std::any_cast<std::string>(val)) {
                    return false;
                }
            } else if (res.type() == typeid(double) || val.type() == typeid(double)) {
                if (anyToDouble(res) < anyToDouble(val)) {
                    return false;
                }
            } else {
                if (anyToInt(res) < anyToInt(val)) {
                    return false;
                }
            }
        } else {
            if ((res.type() == typeid(valueType)) && (val.type() == typeid(valueType))) {
                return false;
            } else if (res.type() == typeid(valueType) || val.type() == typeid(valueType)) {
                // do nothing.
            } else if (res.type() == typeid(std::string) || val.type() == typeid(std::string)) {
                if (res.type() != typeid(std::string) || val.type() != typeid(std::string)) {
                    // do nothing.
                } else if (std::any_cast<std::string>(res) == std::any_cast<std::string>(val)) {
                    return false;
                }
            } else if (res.type() == typeid(double) || val.type() == typeid(double)) {
                if (anyToDouble(res) == anyToDouble(val)) {
                    return false;
                }
            } else {
                if (anyToInt(res) == anyToInt(val)) {
                    return false;
                }
            }
        }
        res = val;
    }
    return true;
}

std::any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx) {
    if (ctx->LESS_THAN() != nullptr) {
        return kL;
    } else if (ctx->GREATER_THAN() != nullptr) {
        return kG;
    } else if (ctx->EQUALS() != nullptr) {
        return kE;
    } else if (ctx->LT_EQ() != nullptr) {
        return kLe;
    } else if (ctx->GT_EQ() != nullptr) {
        return kGe;
    } else {
        return kNe;
    }
}

std::any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {
    std::vector<Python3Parser::TermContext*> term_list = ctx->term();
    std::vector<Python3Parser::Addorsub_opContext*> op_list = ctx->addorsub_op();
    std::any res = visit(term_list[0]);
    if (term_list.size() == 1) {
        return res;
    }
    Variable::tryGetValue(res);
    for (size_t i = 1; i < term_list.size(); ++i) {
        operatorType opt = std::any_cast<operatorType>(visit(op_list[i - 1]));
        std::any val = visit(term_list[i]);
        Variable::tryGetValue(val);
        if (opt == kAdd) {
            if (res.type() == typeid(std::string)) {
                std::string tmp = std::any_cast<std::string>(res) + std::any_cast<std::string>(val);
                res = tmp;
            } else if (res.type() == typeid(double) || val.type() == typeid(double)) {
                double tmp = anyToDouble(res) + anyToDouble(val);
                res = tmp;
            } else {
                int2048 tmp = anyToInt(res) + anyToInt(val);
                res = tmp;
            }
        } else {
            if (res.type() == typeid(double) || val.type() == typeid(double)) {
                double tmp = anyToDouble(res) - anyToDouble(val);
                res = tmp;
            } else {
                int2048 tmp = anyToInt(res) - anyToInt(val);
                res = tmp;
            }
        }
    }
    return res;
}

std::any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) {
    if (ctx->ADD() != nullptr) {
        return kAdd; // +
    } else {
        return kSub; // -
    }
}

std::any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) {
    std::vector<Python3Parser::FactorContext*> factor_list = ctx->factor();
    std::vector<Python3Parser::Muldivmod_opContext*> op_list = ctx->muldivmod_op();
    std::any res = visit(factor_list[0]);
    if (factor_list.size() == 1) {
        return res;
    }
    Variable::tryGetValue(res);
    for (size_t i = 1; i < factor_list.size(); ++i) {
        operatorType opt = std::any_cast<operatorType>(visit(op_list[i - 1]));
        std::any val = visit(factor_list[i]);
        Variable::tryGetValue(val);
        if (opt == kMul) {
            if (res.type() == typeid(std::string)) {
                res = std::any_cast<std::string>(res) * std::any_cast<int2048>(val);
            } else if (val.type() == typeid(std::string)){
                res = std::any_cast<std::string>(val) * std::any_cast<int2048>(res);
            } else if (val.type() == typeid(double) || res.type() == typeid(double)) {
                res = anyToDouble(res) * anyToDouble(val);
            } else {
                res = anyToInt(res) * anyToInt(val);
            }
        } else if (opt == kDiv) {
            res = anyToDouble(res) / anyToDouble(val);
        } else if (opt == kIDiv) {
            res = anyToInt(res) / anyToInt(val);
        } else {
            res = anyToInt(res) % anyToInt(val);
        }
    }
    return res;
}

std::any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) {
    if (ctx->STAR() != nullptr) {
        return kMul; // *
    } else if (ctx->DIV() != nullptr) {
        return kDiv; // /
    } else if (ctx->IDIV() != nullptr) {
        return kIDiv; // //
    } else {
        return kMod; // %
    }
}

std::any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {
    if (ctx->ADD() != nullptr) {
        std::any val = visit(ctx->factor());
        Variable::tryGetValue(val);
        return val;
    } else if (ctx->MINUS() != nullptr) {
        std::any val = visit(ctx->factor());
        Variable::tryGetValue(val);
        if (val.type() == typeid(double)) {
            return -std::any_cast<double>(val);
        } else {
            return -anyToInt(val);
        }
    } else {
        std::any tmp = visit(ctx->atom_expr());
        return tmp;
    }
}

std::any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {
    if (ctx->trailer() != nullptr) {
        std::string str = (std::any_cast<std::pair<std::string, int>>(visit(ctx->atom()))).first;
        std::vector<std::any> arg_list = std::any_cast<std::vector<std::any>>(visit(ctx->trailer()));
        if (str == "print") {
            for (size_t i = 0; i < arg_list.size(); ++i) {
                if (arg_list[i].type() == typeid(std::string)) {
                    std::string tmp = std::any_cast<std::string>(arg_list[i]);
                    for (size_t j = 0; j < tmp.size(); ++j) {
                        if (tmp[j] == '\\') {
                            if (tmp[j + 1] == 'n') {
                                std::cout << '\n';
                            } else if (tmp[j + 1] == 't'){
                                std::cout << '\t';
                            } else {
                                std::cout << tmp[j + 1];
                            }
                            j += 1;
                        } else {
                            std::cout << tmp[j];
                        }
                    }
                } else if (arg_list[i].type() == typeid(double)) {
                    std::cout << std::fixed << std::setprecision(6) << std::any_cast<double>(arg_list[i]);
                } else if (arg_list[i].type() == typeid(int2048)) {
                    std::cout << std::any_cast<int2048>(arg_list[i]);
                } else if (arg_list[i].type() == typeid(bool)) {
                    std::cout << (std::any_cast<bool>(arg_list[i]) ? "True" : "False");
                } else {
                    std::cout << "None";
                }
                if (i < arg_list.size() - 1) {
                    std::cout << ' ';
                }
            }
            std::cout << '\n';
            return kDefault;
        } else if (str == "int") {
            return anyToInt(arg_list[0]);
        } else if (str == "float") {
            return anyToDouble(arg_list[0]);
        } else if (str == "str") {
            return anyToString(arg_list[0]);
        } else if (str == "bool"){
            return anyToBoolean(arg_list[0]);
        } else {
            Variable::addScope();
            std::any res = visit(Functions::visitFunction(str, arg_list));
            Variable::deleteScope();
            return res;
        }
    } else {
        return visit(ctx->atom());
    }
}

std::any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx) {
    if (ctx->arglist() != nullptr) {
        return visit(ctx->arglist());
    } else {
        return std::vector<std::any>();
    }
}

std::any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {
    if (ctx->NAME() != nullptr) {
        return std::make_pair(ctx->NAME()->getText(), 0);
    } else if (ctx->NUMBER() != nullptr) {
        std::string tmp = ctx->NUMBER()->getText();
        bool isDouble = false;
        for (size_t i = 0; i < tmp.size(); ++i) {
            if (tmp[i] == '.') {
                isDouble = true;
                break;
            }
        }
        if (isDouble) {
            return anyToDouble(tmp);
        } else {
            return anyToInt(tmp);
        }
    } else if (ctx->NONE() != nullptr) {
        return valueType::kNone;
    } else if (ctx->TRUE() != nullptr) {
        return true;
    } else if (ctx->FALSE() != nullptr) {
        return false;
    } else if (ctx->test() != nullptr) {
        return visit(ctx->test());
    } else if (ctx->format_string() != nullptr) {
        return visit(ctx->format_string());
    } else {
        std::string res = "";
        std::vector<antlr4::tree::TerminalNode*> str_list = ctx->STRING();
        for (size_t i = 0; i < str_list.size(); ++i) {
            std::string tmp = str_list[i]->getText();
            for (size_t j = 1; j < tmp.size() - 1; ++j) {
                res += tmp[j];
            }
        }
        return res;
    }
}

std::any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx) {
    if (ctx->ADD_ASSIGN() != nullptr) {
        return kAddAssign;
    } else if (ctx->SUB_ASSIGN() != nullptr) {
        return kSubAssign;
    } else if (ctx->MULT_ASSIGN() != nullptr) {
        return kMulAssign;
    } else if (ctx->DIV_ASSIGN() != nullptr) {
        return kDivAssign;
    } else if (ctx->IDIV_ASSIGN() != nullptr) {
        return kIDivAssign;
    } else {
        return kModAssign;
    }
}