/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <string>
#include <memory>
#include <unordered_set>
#include <sstream>
#include <limits>
#include "evalstate.hpp"
#include "exp.hpp"
#include "Utils/tokenScanner.hpp"
#include "program.hpp"
#include "parser.hpp"
#include "Utils/error.hpp"
#include "Utils/strlib.hpp"

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState &state, Program &program) = 0;
protected:
    std::string str_line;//当前行正在解析的内容
};


/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */
class REM: public Statement {
public:
    REM();//默认构造函数
    explicit REM (const std::string &input);//字符串构造函数
    ~REM() override;//析构函数
    void execute (EvalState &state, Program &program) override;
};

class LET: public Statement {
public:
    LET();
    explicit  LET (const std::string &input);
    ~LET() override;
    void execute (EvalState &state, Program &program) override;
};

class PRINT:public Statement {
public:
    PRINT();
    explicit  PRINT (const std::string &input);
    ~PRINT() override;
    void execute (EvalState &state, Program &program) override;
};

class GOTO:public Statement {
public:
    GOTO();
    explicit  GOTO (const std::string &input);
    ~GOTO() override;
    void execute (EvalState &state, Program &program) override;
};

class INPUT:public Statement {
public:
    INPUT();
    explicit  INPUT (const std::string &input);
    ~INPUT() override;
    void execute (EvalState &state, Program &program) override;
};

class END:public Statement {
public:
    END();
    explicit  END (const std::string &input);
    ~END() override;
    void execute (EvalState &state, Program &program) override;
};

class IF:public Statement {
public:
    IF();
    explicit  IF (const std::string &input);
    ~IF() override;
    void execute (EvalState &state, Program &program) override;
};
#endif
