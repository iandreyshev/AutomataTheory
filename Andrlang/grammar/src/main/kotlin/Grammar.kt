package grammar

class Grammar internal constructor(
        private val rules: List<Rule>
) {

    val root: GrammarSymbol =
            GrammarSymbol.from(rules.first().nonTerminal)

    val nonTerminals: Set<NonTerminal> = rules
            .map { it.nonTerminal }
            .toHashSet()

    val terminals: Set<Terminal> = rules
            .flatMap { it.productions }
            .flatMap { it.symbols }
            .mapNotNull { it.terminal }
            .filter { !it.isEpsilon }
            .toHashSet()

    fun firstSetFor(nonTerminal: NonTerminal): List<Terminal> = TODO()

    fun followSetFor(nonTerminal: NonTerminal): List<Terminal> = TODO()

    fun productionsFor(nonTerminal: NonTerminal): List<Production> =
            rules.associate { it.nonTerminal.symbol to it.productions }
                    .getOrDefault(nonTerminal.symbol, listOf())

    companion object {
        internal const val EPSILON_SYMBOL = "#epsilon"
        internal const val DOLLAR_SYMBOL = "#dollar"
    }

}
