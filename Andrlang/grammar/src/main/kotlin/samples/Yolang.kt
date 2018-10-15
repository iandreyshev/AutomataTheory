package grammar.samples

import dsl.*

/**
 * <Program>       -> <FunctionList> EOF
 * <FunctionList>  -> <Function> <FunctionList>
 * <FunctionList>  -> #Eps#
 * <Function>      -> FUNC IDENTIFIER LPAREN <ParamList> RPAREN ARROW <Type> COLON <Statement>
 * <ParamList>     -> <Param> <TailParamList>
 * <ParamList>     -> #Eps#
 * <TailParamList> -> COMMA <Param> <TailParamList>
 * <TailParamList> -> #Eps#
 * <Param>         -> IDENTIFIER COLON <Type>
 * <Type>          -> INT
 * <Type>          -> FLOAT
 * <Type>          -> BOOL
 * <Type>          -> ARRAY LABRACKET <Type> RABRACKET
 * <Statement>     -> <Condition>
 * <Statement>     -> <Loop>
 * <Statement>     -> <Decl>
 * <Statement>     -> <Assign>
 * <Statement>     -> <Return>
 * <Statement>     -> <Composite>
 * <Condition>     -> IF LPAREN <Expression> RPAREN <Statement> <OptionalElse>
 * <OptionalElse>  -> ELSE <Statement>
 * <OptionalElse>  -> #Eps#
 * <Loop>          -> WHILE LPAREN <Expression> RPAREN <Statement>
 * <Decl>          -> VAR IDENTIFIER COLON <Type> SEMICOLON
 * <Assign>        -> IDENTIFIER ASSIGN <Expression> SEMICOLON
 * <Return>        -> RETURN <Expression> SEMICOLON
 * <Composite>     -> LCURLY <StatementList> RCURLY
 * <StatementList> -> <Statement> <StatementList>
 * <StatementList> -> #Eps#
 * <Expression>    -> IDENTIFIER
 * <Expression>    -> INTLITERAL
 * <Expression>    -> FLOATLITERAL
 * <Expression>    -> TRUE
 * <Expression>    -> FALSE
 **/
val GRAMMAR = grammarOf {
    nonTerminal("Program") {
        reproduced("FunctionList", KEYWORDS.EOF)
    }
    nonTerminal("FunctionList") {
        reproduced("Function", "FunctionList")
        reproducedEmptySymbol()
    }
    nonTerminal("Function") {
        reproduced(KEYWORDS.Function, "id", "(", "ParamList", ")", "->", "Type", ":", "Statement")
    }
    nonTerminal("ParamList") {
        reproduced("Param", "TailParamList")
        reproducedEmptySymbol()
    }
    nonTerminal("TailParamList") {
        reproduced(",", "Param", "TailParamList")
        reproducedEmptySymbol()
    }
    nonTerminal("Param") {
        reproduced("id", ":", "Type")
    }
    nonTerminal("Type") {
        reproduced(KEYWORDS.TypeInt)
        reproduced(KEYWORDS.TypeFloat)
        reproduced(KEYWORDS.TypeBoolean)
        reproduced(KEYWORDS.TypeArray, "<", "Type", ">")
    }
    nonTerminal("Statement") {
        reproduced("Condition")
        reproduced("Loop")
        reproduced("Decl")
        reproduced("Assign")
        reproduced("Return")
        reproduced("CompositeStatement")
    }
    nonTerminal("Condition") {
        reproduced(KEYWORDS.Condition, "(", "Expression", ")", "Statement", "OptionalElse")
    }
    nonTerminal("OptionalElse") {
        reproduced("else", "Statement")
        reproducedEmptySymbol()
    }
    nonTerminal("Loop") {
        reproduced(KEYWORDS.CycleWithPreCondition, "(", "Expression", ")", "Statement")
    }
    nonTerminal("Decl") {
        reproduced("var", "id", ":", "Type", ";")
    }
    nonTerminal("Assign") {
        reproduced("id", "=", "Expression", ";")
    }
    nonTerminal("Return") {
        reproduced("return", "Expression", ";")
    }
    nonTerminal("CompositeStatement") {
        reproduced("{", "StatementList", "}")
    }
    nonTerminal("StatementList") {
        reproduced("Statement", "StatementList")
        reproducedEmptySymbol()
    }
    nonTerminal("Expression") {
        reproduced("id")
        reproduced("literal")
        reproduced("true")
        reproduced("false")
    }
}

object KEYWORDS {
    const val EOF = "EOF"
    const val Function = "func"
    const val TypeInt = "Int"
    const val TypeFloat = "Float"
    const val TypeBoolean = "Bool"
    const val TypeArray = "Array"
    const val Condition = "if"
    const val ConditionElse = "else"
    const val CycleWithPreCondition = "while"
}
