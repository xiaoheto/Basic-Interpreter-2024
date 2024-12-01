/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */


#include "evalstate.hpp"
#include "error.hpp"

//using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() {
    /* Empty */
}

EvalState::~EvalState() {
    /* Empty */
}

void EvalState::setValue(std::string var, int value) {
    if(isDefined(var)) symbolTable[var] = value;
    else symbolTable.emplace(var,value);
}

int EvalState::getValue(std::string var) {
    if(isDefined(var)) return symbolTable[var];
    else throw ErrorException("VARIABLE NOT DEFINED");
}

bool EvalState::isDefined(std::string var) {
    return symbolTable.find(var)!=symbolTable.end();
}

void EvalState::Clear() {
    symbolTable.clear();
}
