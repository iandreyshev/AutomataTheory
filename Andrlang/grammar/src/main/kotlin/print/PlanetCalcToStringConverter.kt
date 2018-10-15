package grammar.print

import grammar.Grammar
import grammar.samples.GRAMMAR

/**
 * https://planetcalc.com/5600/
 */
object PlanetCalcToStringConverter {

    fun toString(grammar: Grammar): String {
        var result = ""

        grammar.rules.rulesList.forEach { rule ->
            val nonTerminal = rule.nonTerminal
            result += "$nonTerminal="
            result += rule.productions.joinToString("|") { production ->
                production.symbols.joinToString(",") {
                    when {
                        it.terminal?.isEpsilon == true -> ""
                        it.isTerminal -> "\"$it\""
                        else -> it.toString()
                    }
                }
            }
            result += ";\n"
        }

        return result
    }

}
