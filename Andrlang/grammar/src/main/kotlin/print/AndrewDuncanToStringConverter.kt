package grammar.print

import grammar.Grammar

/**
 * Print grammar for http://andrewduncan.net/parsing/index.html
 */
object AndrewDuncanToStringConverter {

    private const val EPSILON = "ε"

    fun toString(grammar: Grammar): String {
        var result = ""

        grammar.rules.rulesList.forEach { rule ->
            val nonTerminal = rule.nonTerminal
            rule.productions.forEach { production ->
                result += "$nonTerminal -> "
                result += production.symbols.joinToString(separator = " ") {
                    if (it.terminal?.isEpsilon == true) {
                        EPSILON
                    } else {
                        it.toString()
                    }
                }
                result += "\n"
            }
        }

        return result
    }

}