package grammar

import grammar.Grammar.Companion.DOLLAR_SYMBOL
import grammar.Grammar.Companion.EPSILON_SYMBOL
import grammar.Grammar.Companion.NODE_DELIMITER
import grammar.Grammar.Companion.NODE_PARTS_DELIMITER
import grammar.Grammar.Companion.PRODUCTION_DELIMITER
import grammar.Grammar.Companion.SYMBOLS_DELIMITER

internal class GrammarParser(
        private val grammarStr: String
) {

    private lateinit var mNonTerminal: Set<String>
    private val mRules: List<Rule> by lazy {
        grammarStr.split(NODE_DELIMITER)
                .map { nodeStr ->
                    val nodeParts = nodeStr.split(NODE_PARTS_DELIMITER)
                    return@map RuleNode(
                            nodeParts[0].trim(),
                            nodeParts[1].trim(),
                            nodeParts[2].trim(),
                            nodeParts[3].trim()
                    )
                }
                .let { parseRules(it) }
    }

    fun parse(): List<Rule> = mRules

    private fun parseRules(nodes: List<RuleNode>): List<Rule> {
        mNonTerminal = nodes.map { it.nonTerminal }
                .toHashSet()

        return nodes.map { node ->
            val nonTerminal = GrammarSymbol.nonTerminal(NonTerminal(node.nonTerminal))
            val productions = node.production
                    .split(PRODUCTION_DELIMITER)
                    .map { altProduction ->
                        altProduction.trim()
                                .splitSymbols()
                                .let { Production(it) }
                    }
            val firstSet = node.firstSet.splitSymbols()
                    .mapNotNull { it.terminal }
                    .toHashSet()
            val followSet = node.followSet.splitSymbols()
                    .mapNotNull { it.terminal }
                    .toHashSet()

            Rule(nonTerminal, productions, firstSet, followSet)
        }
    }

    private fun String.splitSymbols(): List<GrammarSymbol> = split(SYMBOLS_DELIMITER)
            .map {
                when {
                    mNonTerminal.contains(it) -> GrammarSymbol.nonTerminal(NonTerminal(it))
                    else -> GrammarSymbol.terminal(it.trim().toTerminal())
                }
            }

    private fun String.toTerminal(): Terminal = when (this) {
        EPSILON_SYMBOL -> Terminal.createEpsilon()
        DOLLAR_SYMBOL -> Terminal.createDollar()
        else -> Terminal.createTerm(this)
    }

    private data class RuleNode(
            val nonTerminal: String,
            val production: String,
            val firstSet: String,
            val followSet: String
    )

}
