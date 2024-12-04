#include "Evalvisitor.h"

std::any EvalVisitor::visitFormat_string(Python3Parser::Format_stringContext *ctx) {
    std::string res;
    std::vector<antlr4::tree::ParseTree*> node_list = ctx->children;
    for(size_t i = 1; i < node_list.size() - 1; ++i) {
        std::string tmp = node_list[i]->getText();
        if (tmp == "{") {
            std::vector<std::any> tmp = std::any_cast<std::vector<std::any>>(visit(node_list[i + 1]));
            res += anyToString(tmp[0]);
            i += 2;
        } else {
            for (size_t j = 0; j < tmp.size(); ++j) {
                res += tmp[j];
                if (tmp[j] == '{' || tmp[j] == '}') {
                    j++;
                }
            }
        }
    }
    return res;
}