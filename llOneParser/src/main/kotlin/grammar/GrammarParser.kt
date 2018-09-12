package grammar

internal class GrammarParser(
        private val grammarStr: String
) {

    fun parse(): List<Rule> = grammarStr
            .split(NODE_DELIMITER)
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

    private fun parseRules(nodes: List<RuleNode>): List<Rule> = nodes.map { node ->
        val determ = GrammarSymbol.determ(Determ(node.determ))
        val productions = node.production
                .split(PRODUCTION_DELIMITER)
                .map { altProduction ->
                    altProduction.splitSymbols()
                            .map { GrammarSymbol.term(it) }
                            .let { Production(it) }
                }
        val firstSet = node.firstSet.splitSymbols()
                .toHashSet()
        val followSet = node.followSet.splitSymbols()
                .toHashSet()

        Rule(determ, productions, firstSet, followSet)
    }

    private fun String.splitSymbols(): List<Term> = split(SYMBOLS_DELIMITER)
            .map { it.trim().toTerm() }

    private fun String.toTerm(): Term = when (this) {
        EPSILON_SYMBOL -> Term.createEpsilon()
        DOLLAR_SYMBOL -> Term.createDollar()
        else -> Term.createTerm(this)
    }

    private data class RuleNode(
            val determ: String,
            val production: String,
            val firstSet: String,
            val followSet: String
    )

    companion object {
        private const val NODE_DELIMITER = "\n"
        private const val NODE_PARTS_DELIMITER = "->"
        private const val PRODUCTION_DELIMITER = "|"
        private const val SYMBOLS_DELIMITER = " "
        private const val EPSILON_SYMBOL = "#epsilon"
        private const val DOLLAR_SYMBOL = "#dollar"
    }

}
