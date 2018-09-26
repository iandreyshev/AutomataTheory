package parser

import extension.addToList
import grammar.*

private typealias TableMap = MutableMap<String, MutableMap<String, Production?>>

class PredictParsingTable(
        private val grammar: Grammar
) {

    private val mTableMap: TableMap

    init {
        fun newTerminalToProductionMap() = grammar.terminals
                .map { it.symbol }
                .addToList(Grammar.DOLLAR_SYMBOL)
                .associate<String, String, Production?> { it to null }
                .toMutableMap()

        val emptyTable = grammar.nonTerminals
                .map { it.symbol }
                .associate { nonTerminalSymbol ->
                    nonTerminalSymbol to newTerminalToProductionMap()
                }
                .toMutableMap()

        mTableMap = fill(emptyTable)
    }

    operator fun get(nonTerminal: NonTerminal, terminal: Terminal) =
            mTableMap[nonTerminal, terminal]

    private fun fill(table: TableMap): TableMap {
        grammar.nonTerminals.forEach { nonTerminal ->
            val firstSet = grammar.firstSetFor(nonTerminal)
            val followSet = grammar.followSetFor(nonTerminal)
            val productions = grammar.productionsFor(nonTerminal)

            firstSet.forEach { terminalFromFirstSet ->
                table.fillFromFirstSet(productions, nonTerminal, terminalFromFirstSet)

                if (terminalFromFirstSet.isEpsilon) {
                    followSet.forEach { terminalFromFollowSet ->
                        table.fillTableFromFollowSet(productions, nonTerminal, terminalFromFollowSet)
                    }
                }
            }
        }

        return table
    }

    private fun TableMap.fillFromFirstSet(productions: List<Production>, nonTerminal: NonTerminal, terminal: Terminal) {
        when (productions.count()) {
            0 -> throw IllegalArgumentException("Can not find productions for newNonTerminal ($nonTerminal)")
            1 -> put(nonTerminal, terminal, productions.first())
            else -> {
                val withoutEpsilon = productions.filter { !it.isEpsilon }
                if (withoutEpsilon.count() == 1) {
                    put(nonTerminal, terminal, withoutEpsilon.first())
                    return
                }

                val startFromTerminal = productions
                        .firstOrNull { it.firstOrNull?.terminal?.symbol == terminal.symbol }
                if (startFromTerminal != null) {
                    put(nonTerminal, terminal, startFromTerminal)
                    return
                }

                val startFromNonTerminal = productions
                        .filter { it.symbols.firstOrNull()?.nonTerminal != null }
                if (startFromNonTerminal.firstOrNull() != null) {
                    put(nonTerminal, terminal, startFromNonTerminal.first())
                    return
                }

                throw IllegalArgumentException("Can not find production for newNonTerminal from first set ($nonTerminal)")
            }
        }
    }

    private fun TableMap.fillTableFromFollowSet(productions: List<Production>, nonTerminal: NonTerminal, terminal: Terminal) {
        when (productions.count()) {
            0 -> throw IllegalArgumentException("Can not find productions for newNonTerminal ($nonTerminal)")
            1 -> put(nonTerminal, terminal, productions.first())
            else -> {
                val production = productions.firstOrNull { production ->
                    production.symbols.firstOrNull { it.terminal?.isEpsilon == true } != null
                }

                if (production != null) {
                    put(nonTerminal, terminal, production)
                    return
                }

                throw IllegalArgumentException("fillTableFromFollowSet: Can not find production for newNonTerminal from follow set ($nonTerminal)")
            }
        }
    }

    private operator fun TableMap.get(nonTerminal: NonTerminal, terminal: Terminal) =
            mTableMap[nonTerminal.symbol]?.get(terminal.symbol)

    private fun TableMap.put(nonTerminal: NonTerminal, terminal: Terminal, production: Production) {
        val terminalIndex = if (terminal.isEpsilon) {
            Terminal.newDollar()
        } else {
            terminal
        }
        get(nonTerminal.symbol)?.put(terminalIndex.symbol, production)
    }

}
