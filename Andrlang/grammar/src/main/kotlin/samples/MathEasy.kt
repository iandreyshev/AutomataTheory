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
        reproduced("T", "E#")
    }
    nonTerminal("E#") {
        reproduced("+", "T", "E#")
        reproducedEmptySymbol()
    }
    nonTerminal("T") {
        reproduced("F", "T#")
    }
    nonTerminal("T#") {
        reproduced("*", "F", "T#")
        reproducedEmptySymbol()
    }
    nonTerminal("F") {
        reproduced("(", "E", ")")
        reproduced("id")
    }
}
