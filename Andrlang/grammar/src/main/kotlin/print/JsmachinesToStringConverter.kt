package grammar.print

import grammar.Grammar
import grammar.samples.GRAMMAR

/**
 * http://jsmachines.sourceforge.net/machines/ll1.html
 */
object JsmachinesToStringConverter {

    private const val EPSILON = "''"

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

fun main(args: Array<String>) {
    println(JsmachinesToStringConverter.toString(GRAMMAR))
}