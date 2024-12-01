/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"


/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);
Statement* parseStatement(const std::string &line);
/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                continue;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */


void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    if (line.empty()) return;

    if (isdigit(line[0])) {
        int i = 0;
        int lineNumber = 0;
        while (i < line.length() && isdigit(line[i])) {
            lineNumber = lineNumber * 10 + (line[i] - '0');
            ++i;
        }
        if (i == line.length()) {
            program.removeSourceLine(lineNumber);
        }
        else {
            while (i < line.length() && isspace(line[i])) ++i;
            std::string statementLine = line.substr(i);
            Statement *stmt = nullptr;
            try {
                stmt = parseStatement(statementLine);
                program.addSourceLine(lineNumber, statementLine);
                program.setParsedStatement(lineNumber, stmt);
            } catch (...) {
                delete stmt;
                throw;
            }
        }
        return;
    }
    std::string command = scanner.nextToken();
    if (command == "RUN") {
        int currentLine = program.getFirstLineNumber();
        while (currentLine != -1) {
            Statement *stmt = program.getParsedStatement(currentLine);
            if (stmt == nullptr) {
                error("SYNTAX ERROR");
            }
            stmt->execute(state, program);
            currentLine = program.getCurrentLineNumber();
        }
    }
    else if (command == "LIST") {
        program.printAllLines();
    }
    else if (command == "CLEAR") {
        program.clear();
        state = EvalState();
    }
    else if (command == "QUIT") {
        exit(0);
    }
    else if (command == "HELP") {
        std::cout << "You are running the basic program.You can use commands to control it.\n";
    }
    else {
        Statement *stmt = parseStatement(line);
        stmt->execute(state, program);
        delete stmt;
    }
}

Statement* parseStatement(const std::string &line) {
    TokenScanner scanner(line);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    std::string command = scanner.nextToken();
    if (command == "REM") return new REM(line);
    if (command == "LET") return new LET(line);
    if (command == "PRINT") return new PRINT(line);
    if (command == "INPUT") return new INPUT(line);
    if (command == "END") return new END(line);
    if (command == "GOTO") return new GOTO(line);
    if (command == "IF") return new IF(line);
    throw ErrorException("Unknown command");
}

