package grammar.samples

import dsl.grammarOf

/**
 * E    ->   T E'
 * E'   ->   + T E'
 *             | e
 * T    ->   F T'
 * T'   ->   * F T'
 *             | e
 * F    ->   ( E )
 *             | id
 **/
val MATH_EASY_GRAMMAR = grammarOf {
    nonTerminal("E") {
        reproduce("T", "E#")
    }
    nonTerminal("E#") {
        reproduce("+", "T", "E#")
        reproduceEmptySymbol()
    }
    nonTerminal("T") {
        reproduce("F", "T#")
    }
    nonTerminal("T#") {
        reproduce("*", "F", "T#")
        reproduceEmptySymbol()
    }
    nonTerminal("F") {
        reproduce("(", "E", ")")
        reproduce("id")
    }
}
