#include <Evalvisitor.h>

std::any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx) {
    std::vector<Python3Parser::StmtContext *> stmt_array = ctx->stmt();
    for (auto &stmt : stmt_array) {
        visit(stmt);
    }
    return 0;
}