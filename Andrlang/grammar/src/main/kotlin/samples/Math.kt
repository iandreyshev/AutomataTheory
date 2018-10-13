package grammar.samples

import grammar.*

/**
 * Syntax   ->   Expr
 * Expr     ->   Term Expr#
 * Expr#    ->   + Term Expr#
 *                 | - Term Expr#
 *                 | #epsilon
 * Term     ->   Factor Term#
 * Term#    ->   * Factor Term#
 *                 | / Factor Term#
 *                 | #epsilon
 * Factor   ->   ( Expr )
 *                 | id
 *                 | - Factor
 **/
val MATH_GRAMMAR = grammarOf {
    nonTerminal("Syntax") {
        reproduce("Expr")
    }
    nonTerminal("Expr") {
        reproduce("Term", "Expr#")
    }
    nonTerminal("Expr#") {
        reproduce("+", "Term", "Expr#")
        reproduce("-", "Term", "Expr#")
        reproduceEmptySymbol()
    }
    nonTerminal("Term") {
        reproduce("Factor", "Term#")
    }
    nonTerminal("Term#") {
        reproduce("*", "Factor", "Term#")
        reproduce("/", "Factor", "Term#")
        reproduceEmptySymbol()
    }
    nonTerminal("Factor") {
        reproduce("(", "Expr", ")")
        reproduce("-", "Factor")
        reproduce("id")
    }
}
