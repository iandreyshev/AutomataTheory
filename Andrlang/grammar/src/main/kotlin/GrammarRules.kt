package grammar

class GrammarRules(rules: List<Rule>) {

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

    private val mProductionsMap: Map<NonTerminal, List<Production>> = rules
            .associate { it.nonTerminal to it.productions }

    fun productionsFor(nonTerminal: NonTerminal): List<Production> =
            mProductionsMap.getOrDefault(nonTerminal, listOf())

}
