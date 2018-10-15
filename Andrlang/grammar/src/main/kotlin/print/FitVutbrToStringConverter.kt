package grammar.print

import grammar.*
import grammar.samples.GRAMMAR

object FitVutbrToStringConverter {

    fun toString(grammar: Grammar): String {
        var result = "%tokens " + grammar.terminals.joinToString(" ") {
            if (it.isEpsilon) ""
            else it.literal
        }
        result += "\n%% /* LL(1) */\n"

        grammar.rules.rulesList.forEach { rule ->
            result += "${rule.nonTerminal} : "

            val emptyProd = Production(Terminal.emptySymbol().toSymbol())
            result += if (rule.productions.contains(emptyProd)) "/*eps*/\n"
            else "\n"

            result += rule.productions.joinToString("\n|") {
                it.toString()
            }

            result += ";\n"
        }

        return result
    }

}

fun main(args: Array<String>) {
    println(FitVutbrToStringConverter.toString(GRAMMAR))
}