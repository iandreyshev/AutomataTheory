package grammar

class GrammarRules(val rulesList: List<Rule>) {

    val root: GrammarSymbol =
            GrammarSymbol.from(rulesList.first().nonTerminal)

    val nonTerminals: List<NonTerminal> = rulesList
            .map { it.nonTerminal }

    val terminals: List<Terminal> = rulesList
            .flatMap { it.productions }
            .flatMap { it.symbols }
            .mapNotNull { it.terminal }
            .filter { !it.isEpsilon }

    private val mProductionsMap: Map<NonTerminal, List<Production>> = rulesList
            .associate { it.nonTerminal to it.productions }

    fun productionsFrom(nonTerminal: NonTerminal): List<Production> =
            mProductionsMap.getOrDefault(nonTerminal, listOf())

    fun rulesWithReproducing(symbol: GrammarSymbol): List<Rule> =
            rulesList.filter {
                it.productions.firstOrNull { production ->
                    production.symbols.contains(symbol)
                } != null
            }

}
