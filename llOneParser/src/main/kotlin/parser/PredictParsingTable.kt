package parser

import extension.addToList
import grammar.*

class PredictParsingTable(
        private val grammar: Grammar
) {

    private val mTable: Map<String, Map<String, Production?>>

    init {
        val table = createEmptyTable()
        mTable = fillTable(table)
    }

    operator fun get(nonTerminal: NonTerminal, terminal: Terminal): Production? =
            mTable[nonTerminal.symbol]?.get(terminal.symbol)

    private fun createEmptyTable(): MutableMap<String, MutableMap<String, Production?>> =
            grammar.nonTerminals
                    .map { it.symbol }
                    .associate { nonTerminalSymbol ->
                        nonTerminalSymbol to grammar.terms
                                .map { it.symbol }
                                .addToList(Grammar.DOLLAR_SYMBOL)
                                .associate<String, String, Production?> { nonTerminalSymbol to null }
                                .toMutableMap()
                    }
                    .toMutableMap()

    private fun fillTable(table: MutableMap<String, MutableMap<String, Production?>>): Map<String, Map<String, Production?>> {
        grammar.nonTerminals.forEach { nonTerminal ->
            fillTable(table, nonTerminal)
        }

        return table
    }

    private fun fillTable(table: MutableMap<String, MutableMap<String, Production?>>, nonTerminal: NonTerminal) {
    }

}
