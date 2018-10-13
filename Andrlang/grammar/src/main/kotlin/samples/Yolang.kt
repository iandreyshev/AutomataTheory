package grammar.samples

import dsl.*

/**
 * <Program>       -> <FunctionList> EndOfFile
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
        reproduce("FunctionList", KEYWORDS.EndOfFile)
    }
    nonTerminal("FunctionList") {
        reproduce("Function", "FunctionList")
        reproduceEmptySymbol()
    }
    nonTerminal("Function") {
        reproduce(KEYWORDS.Function, "id", "(", "ParamList", ")", ":", "Type", ",", "Statement")
    }
    nonTerminal("ParamList") {
        reproduce("Param", "TailParamList")
        reproduceEmptySymbol()
    }
    nonTerminal("TailParamList") {
        reproduce(",", "Param", "TailParamList")
        reproduceEmptySymbol()
    }
    nonTerminal("Param") {
        reproduce("id", ",", "Type")
    }
    nonTerminal("Type") {
        reproduce("Int")
        reproduce("Float")
        reproduce("Bool")
        reproduce("Array", "[", "Type", "]")
    }
    nonTerminal("Statement") {
        reproduce("Condition")
        reproduce("Loop")
        reproduce("Decl")
        reproduce("Assign")
        reproduce("Return")
        reproduce("Composite")
    }
    nonTerminal("Condition") {
        reproduce("if", "(", "Expression", ")", "Statement", "OptionalElse")
    }
    nonTerminal("OptionalElse") {
        reproduce("else", "Statement")
        reproduceEmptySymbol()
    }
    nonTerminal("Loop") {
        reproduce("while", "(", "Expression", ")", "Statement")
    }
    nonTerminal("Decl") {
        reproduce("var", "id", ":", "Type", ";")
    }
    nonTerminal("Assign") {
        reproduce("id", "=", "Expression", ";")
    }
    nonTerminal("Return") {
        reproduce("return", "Expression", ";")
    }
    nonTerminal("Composite") {
        reproduce(KEYWORDS.StatementBracketLeft, "StatementList", KEYWORDS.StatementBracketRight)
    }
    nonTerminal("StatementList") {
        reproduce("Statement", "StatementList")
        reproduceEmptySymbol()
    }
    nonTerminal("Expression") {
        reproduce("id")
        reproduce("literal")
        reproduce("true")
        reproduce("false")
    }
}

object KEYWORDS {
    const val EndOfFile = "EOF"
    const val Function = "Func"
    const val StatementBracketLeft = "{"
    const val StatementBracketRight = "}"
}
