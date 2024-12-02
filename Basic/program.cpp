/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"


Program::Program() = default;

Program::~Program() {
    clear();
};

void Program::clear() {
    parsedStatements.clear();
}

void Program::addSourceLine(int lineNumber, const std::string& line) {
    parsedStatements[lineNumber] = nullptr;
}

void Program::removeSourceLine(int lineNumber) {
    parsedStatements.erase(lineNumber);
}

std::string Program::getSourceLine(int lineNumber) {
    if (sourceLines.find(lineNumber) != sourceLines.end()) {
        return sourceLines[lineNumber];
    }
    else {
        return "";
    }
}

void Program::setParsedStatement(int lineNumber, Statement* stmt) {
    parsedStatements[lineNumber] = std::shared_ptr<Statement>(stmt);
}

//void Program::removeSourceLine(int lineNumber) {

std::shared_ptr<Statement> Program::getParsedStatement(int lineNumber) {
    auto it = parsedStatements.find(lineNumber);
    if (it != parsedStatements.end()) {
        return it->second;
    }
    return nullptr;
}

int Program::getFirstLineNumber() {
    if (sourceLines.empty()) {
        return -1;
    }
    else {
        return sourceLines.begin() -> first;
    }
}

int Program::getNextLineNumber(int lineNumber) {
    auto it = sourceLines.upper_bound(lineNumber);
    if (it != sourceLines.end()) {
        return it -> first;
    }
    else {
        return -1;
    }
}

int Program::getCurrentLineNumber() {
    return currentLineNumber;
}


void Program::setCurrentLineNumber(int lineNumber) {
    currentLineNumber = lineNumber;
}

void Program::printAllLines() const {
    for (const auto& entry : sourceLines) {
        std::cout << entry.first << " " << entry.second << '\n';
    }
}

void Program::goToNextLine() {
    currentLineNumber = getNextLineNumber(currentLineNumber);
}
