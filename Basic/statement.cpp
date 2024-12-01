/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"


/* Implementation of the Statement class */
bool check(const char op, const int lhs, const int rhs);
int stringToInt(std::string str);
bool isKeyword(const std::string &var);//检查是否是关键字
bool isValidIdentifier(const std::string &var);//检查变量名称是否合法
bool isVaribleValid(const std::string &var);//验证变量名是否正确

Statement::Statement() = default;

Statement::~Statement() = default;


 REM::REM() = default;
REM::REM(const std::string& input) {
    str_line = input;
}
REM::~REM() = default;
void REM::execute(EvalState &state, Program &program) {
    program.goToNextLine();//处于注释状态的时候，移动到下一行
}


 LET::LET() = default;
LET::LET(const std::string& input) {
    str_line = input;
}
LET::~LET() = default;
void LET::execute(EvalState &state, Program &program) {
    TokenScanner scanner(str_line);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(str_line);

    if (scanner.nextToken() != "LET") {
        error("SYNTAX ERROR");
    }
    std::string var = scanner.nextToken();
    if (!isVaribleValid(var)) {
        error("SYNTAX ERROR");
    }
    if (scanner.nextToken() != "=") {
        error("SYNTAX ERROR");
    }
    Expression *exp = nullptr;
    try {
        exp = parseExp(scanner);
        int value = exp->eval(state);
        state.setValue(var, value);
    } catch (...) {
        delete exp;
        throw;
    }
    delete exp;
    program.goToNextLine();
}



 PRINT::PRINT() = default;
PRINT::PRINT(const std::string& input) {
    str_line = input;
}
PRINT::~PRINT() = default;
void PRINT::execute(EvalState &state, Program &program) {
    TokenScanner scanner(str_line);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    if (scanner.nextToken() != "PRINT") {
        error("SYNTAX ERROR");
    }
    Expression *expr = nullptr;
    try {
        expr = parseExp(scanner);
    } catch (const std::runtime_error &e) {
        error("SYNTAX ERROR");
    }
    if (scanner.hasMoreTokens()) {
        delete expr;
        error("SYNTAX ERROR");
    }
    try {
        int value = expr->eval(state);
        std::cout << value << std::endl;
    } catch (const std::runtime_error &e) {
        delete expr;
        error("RUNTIME ERROR");
    }
    delete expr;
    program.goToNextLine();
}


 GOTO::GOTO() =default;
GOTO::GOTO(const std::string& input) {
    str_line = input;
}
GOTO::~GOTO() = default;
void GOTO::execute(EvalState &state, Program &program) {
    TokenScanner scanner(str_line);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    if (scanner.nextToken() != "GOTO") {
        error("SYNTAX ERROR");
    }
    int targetLine;
    try {
        std::string lineToken = scanner.nextToken();
        targetLine = stringToInt(lineToken);
    } catch (...) {
        error("SYNTAX ERROR");
    }
    if (program.getSourceLine(targetLine).empty()) {
        error("LINE NUMBER ERROR");
    }
    if (scanner.hasMoreTokens()) {
        error("SYNTAX ERROR");
    }
    program.setCurrentLineNumber(targetLine);
}


 INPUT::INPUT() =default;
INPUT::INPUT(const std::string& input) {
    str_line = input;
}
INPUT::~INPUT() = default;
void INPUT::execute(EvalState &state, Program &program) {
    TokenScanner scanner(str_line);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(str_line);
    if (scanner.nextToken() != "INPUT") {
        error("SYNTAX ERROR");
    }
    std::string var = scanner.nextToken();
    if (!isVaribleValid(var)) {
        error("SYNTAX ERROR");
    }
    if (scanner.hasMoreTokens()) {
        error("SYNTAX ERROR");
    }
    std::cout << " ? ";
    int value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "INVALID NUMBER" << std::endl << " ? ";
            continue;
        }
        char extra;
        if (std::cin.get(extra) && extra != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "INVALID NUMBER" << std::endl << " ? ";
            continue;
        }
        break;
    }
    state.setValue(var, value);
    program.goToNextLine();
}


 END::END() = default;
END::END(const std::string& input) {
    str_line = input;
}
END::~END() = default;
void END::execute(EvalState &state, Program &program) {
    program.setCurrentLineNumber(-1);
}


 IF::IF() = default;
IF::IF(const std::string& input) {
    str_line = input;
}
IF::~IF() = default;
void IF::execute(EvalState &state, Program &program) {
    TokenScanner scanner(str_line);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(str_line);
    if (scanner.nextToken() != "IF") {
        error("SYNTAX ERROR");
    }
    Expression* lhExp = nullptr;
    try {
        lhExp = parseExp(scanner);
    } catch (...) {
        error("SYNTAX ERROR");
    }
    
    if (!scanner.hasMoreTokens()) {
        delete lhExp;
        error("SYNTAX ERROR");
    }
    std::string op = scanner.nextToken();
    if (op != "=" && op != "<" && op != ">") {
        delete lhExp;
        error("SYNTAX ERROR");
    }
    Expression* rhsExp = nullptr;
    try {
        rhsExp = parseExp(scanner);
    } catch (...) {
        delete lhExp;
        error("SYNTAX ERROR");
    }
    
    if (!scanner.hasMoreTokens() || scanner.nextToken() != "THEN") {
        delete lhExp;
        delete rhsExp;
        error("SYNTAX ERROR");
    }
    if (!scanner.hasMoreTokens()) {
        delete lhExp;
        delete rhsExp;
        error("SYNTAX ERROR");
    }
    std::string lineNumberToken = scanner.nextToken();
    int targetLine;
    try {
        targetLine = stringToInt(lineNumberToken);
    } catch (...) {
        delete lhExp;
        delete rhsExp;
        error("SYNTAX ERROR");
    }
    if (program.getSourceLine(targetLine).empty()) {
        delete lhExp;
        delete rhsExp;
        error("LINE NUMBER ERROR");
    }
    if (scanner.hasMoreTokens()) {
        delete lhExp;
        delete rhsExp;
        error("SYNTAX ERROR");
    }
    try {
        int lhs = lhExp->eval(state);
        int rhs = rhsExp->eval(state);
        if (check(op[0], lhs, rhs)) {
            program.setCurrentLineNumber(targetLine);
        } else {
            program.goToNextLine();
        }
    } catch (...) {
        delete lhExp;
        delete rhsExp;
        error("RUNTIME ERROR");
    }

    delete lhExp;
    delete rhsExp;
}


int stringToInt(std::string s) {
    int sign = 1;
    int num = 0;
    if (s[0] == '-') {
        sign = -1;
        s = s.substr(1);
    }
    for(char i:s) {
        if (i < '0' || i > '9') {
            error("INVALID NUMBER");
        }
        else {
            num = num * 10 + i - '0';
        }
    }
    return num;
}

bool check(const char op, const int lhs, const int rhs) {
    if (op == '=') {
        return lhs == rhs;
    }
    if (op == '<') {
        return lhs < rhs;
    }
    if (op == '>') {
        return lhs > rhs;
    }
    error("SYNTAX ERROR");
    return false;
}

bool isKeyword(const std::string &var) {
    static const std::unordered_set<std::string> keywords = {
        "REM", "LET", "PRINT", "INPUT", "END", "GOTO",
        "IF", "THEN", "RUN", "LIST", "CLEAR", "QUIT", "HELP"
    };
    return keywords.count(var) > 0;
}

bool isValidIdentifier(const std::string &var) {
    if (var.empty()) return false; // 变量名不能为空
    for (char ch : var) {
        if (!isalnum(ch) && ch != '_') { // 仅允许字母、数字、下划线
            return false;
        }
    }
    return true;
}

bool isVaribleValid(const std::string &var) {
    if (!isValidIdentifier(var)) return false; // 检查字符合法性
    if (isKeyword(var)) return false;          // 检查是否为关键字
    return true;
}
