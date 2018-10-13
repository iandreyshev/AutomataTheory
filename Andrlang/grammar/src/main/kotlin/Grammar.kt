package grammar

class Grammar internal constructor(rulesList: List<Rule>) {

    companion object {
        internal const val EPSILON_SYMBOL = "#epsilon"
        internal const val DOLLAR_SYMBOL = "#dollar"
    }

    val rules: GrammarRules = GrammarRules(rulesList)
    val root: GrammarSymbol = rules.root
    val nonTerminals: Set<NonTerminal> = rules.nonTerminals
    val terminals: Set<Terminal> = rules.terminals

    private val mFirstSetMap: Map<GrammarSymbol, Set<Terminal>> =
            getFirstSetMap(rules)

    private val mFollowSetMap: Map<GrammarSymbol, Set<Terminal>> =
            getFollowSetMap(rules, mFirstSetMap)

    fun firstSetFor(nonTerminal: NonTerminal): Set<Terminal> =
            mFirstSetMap[nonTerminal.toSymbol()] ?: setOf()

    fun firstSetFor(terminal: Terminal): Set<Terminal> =
            mFirstSetMap[terminal.toSymbol()] ?: setOf()

    fun firstSetFor(symbol: GrammarSymbol): Set<Terminal> =
            mFirstSetMap[symbol] ?: setOf()

    fun firstSetFor(production: Production): Set<Terminal> = TODO()

    fun followSetFor(nonTerminal: NonTerminal): Set<Terminal> =
            mFollowSetMap[nonTerminal.toSymbol()] ?: setOf()

    fun followSetFor(symbol: GrammarSymbol): Set<Terminal> =
            mFollowSetMap[symbol] ?: setOf()

    fun followSetFor(production: Production): Set<Terminal> = TODO()

    fun productionsFor(nonTerminal: NonTerminal): List<Production> =
            rules.productionsFor(nonTerminal)

}

fun first(symbol: GrammarSymbol, rules: GrammarRules): Set<Terminal> {
    val firstSetForSymbol = HashSet<Terminal>()

    if (symbol.isTerminal) {
        firstSetForSymbol.add(symbol.terminal!!)
        return firstSetForSymbol
    }

    rules.productionsFor(symbol.nonTerminal!!)
            .forEach { production ->
                if (production.isEpsilon) {
                    firstSetForSymbol.add(Terminal.newEpsilon())
                    return@forEach
                }

                for (productionSymbol in production.symbols) {
                    val prodSymbolFirstSet = first(productionSymbol, rules)

                    if (prodSymbolFirstSet.count() == 1 && prodSymbolFirstSet.first().isEpsilon) {
                        continue
                    }

                    if (prodSymbolFirstSet.isNotEmpty()) {
                        firstSetForSymbol.addAll(prodSymbolFirstSet)
                        break
                    }

                    throw IllegalArgumentException("Function FIRST return empty set!")
                }
            }

    return firstSetForSymbol
}

fun getFirstSetMap(rules: GrammarRules): Map<GrammarSymbol, Set<Terminal>> {
    val resultFirstSet = mutableMapOf<GrammarSymbol, Set<Terminal>>()

    rules.terminals.forEach {
        resultFirstSet[it.toSymbol()] = first(it.toSymbol(), rules)
    }

    rules.nonTerminals.forEach {
        resultFirstSet[it.toSymbol()] = first(it.toSymbol(), rules)
    }

    return resultFirstSet
}

fun getFollowSetMap(rules: GrammarRules, firstSetMap: Map<GrammarSymbol, Set<Terminal>>): Map<GrammarSymbol, Set<Terminal>> {
    return mapOf()
}
