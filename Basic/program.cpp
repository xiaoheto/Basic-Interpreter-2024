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
    for(auto &entry:parsedStatements) {
        delete entry.second;
    }
    parsedStatements.clear();
    sourceLines.clear();
    currentLineNumber = -1;
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    if (sourceLines.count(lineNumber)) {
        delete parsedStatements[lineNumber];
        parsedStatements.erase(lineNumber);
        sourceLines[lineNumber] = line;
    }
    else {
        sourceLines[lineNumber] = line;
    }
}

void Program::removeSourceLine(int lineNumber) {
    sourceLines.erase(lineNumber);
    delete parsedStatements[lineNumber];
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

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if (sourceLines.find(lineNumber) == sourceLines.end()) {
        throw std::runtime_error("Error: Line number does not exist.");
    }
    else {
        delete parsedStatements[lineNumber];
        parsedStatements.erase(lineNumber);
        parsedStatements[lineNumber] = stmt;
    }
}

//void Program::removeSourceLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
    if (parsedStatements.find(lineNumber) == parsedStatements.end()) {
        return nullptr;
    }
    else {
        return parsedStatements[lineNumber];
    }
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


int Program::setCurrentLineNumber(int lineNumber) {
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
