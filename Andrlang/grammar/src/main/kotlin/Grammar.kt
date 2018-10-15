package grammar

class Grammar internal constructor(rulesList: List<Rule>) {

    companion object {
        internal const val EMPTY_SYMBOL = "#eps"
        internal const val END_OF_INPUT_SYMBOL = "$"
    }

    val rules: GrammarRules = GrammarRules(rulesList)
    val root: GrammarSymbol = rules.root
    val nonTerminals: List<NonTerminal> = rules.nonTerminals
    val terminals: List<Terminal> = rules.terminals

    private val mFirstSetMap: Map<GrammarSymbol, Set<Terminal>> =
            getFirstSetMap(rules)

    private val mFollowSetMap: Map<GrammarSymbol, Set<Terminal>> =
            getFollowSetMap(rules, ::firstSetFor)

    fun firstSetFor(symbol: GrammarSymbol): Set<Terminal> =
            mFirstSetMap.getOrDefault(symbol, emptySet())

    fun followSetFor(symbol: GrammarSymbol): Set<Terminal> =
            mFollowSetMap.getOrDefault(symbol, emptySet())

    fun firstSetFor(symbols: List<GrammarSymbol>): Set<Terminal> {
        val result = mutableSetOf<Terminal>()

        for (symbol in symbols) {
            val symbolFirstSet = firstSetFor(symbol)
            result.addAll(symbolFirstSet)

            if (!symbolFirstSet.contains(Terminal.emptySymbol())) {
                result.remove(Terminal.emptySymbol())
                break
            }
        }

        return result
    }

    fun followSetFor(symbols: List<GrammarSymbol>): Set<Terminal> = TODO()

}

fun first(symbol: GrammarSymbol, rules: GrammarRules): Set<Terminal> {
    val firstSetForSymbol = HashSet<Terminal>()

    if (symbol.isTerminal) {
        firstSetForSymbol.add(symbol.terminal!!)
        return firstSetForSymbol
    }

    rules.productionsFrom(symbol.nonTerminal!!).forEach { production ->
        if (production.isEpsilon) {
            firstSetForSymbol.add(Terminal.emptySymbol())
            return@forEach
        }

        for (productionSymbol in production.symbols) {
            val prodSymbolFirstSet = first(productionSymbol, rules)

            if (prodSymbolFirstSet.isNotEmpty()) {
                firstSetForSymbol.addAll(prodSymbolFirstSet)

                if (prodSymbolFirstSet.contains(Terminal.emptySymbol())) {
                    firstSetForSymbol.remove(Terminal.emptySymbol())
                    continue
                }

                break
            }

            throw IllegalStateException("Function FIRST return empty set!")
        }
    }

    return firstSetForSymbol
}

fun getFirstSetMap(rules: GrammarRules): Map<GrammarSymbol, Set<Terminal>> {
    val resultFirstSetMap = mutableMapOf<GrammarSymbol, Set<Terminal>>()

    rules.terminals.forEach {
        resultFirstSetMap[it.toSymbol()] = first(it.toSymbol(), rules)
    }

    rules.nonTerminals.forEach {
        resultFirstSetMap[it.toSymbol()] = first(it.toSymbol(), rules)
    }

    return resultFirstSetMap
}

fun getFollowSetMap(
        rules: GrammarRules,
        getFirstSet: (List<GrammarSymbol>) -> Set<Terminal>
): Map<GrammarSymbol, Set<Terminal>> {
    val resultFollowSetMap = HashMap<GrammarSymbol, HashSet<Terminal>>()

    rules.nonTerminals.forEach {
        resultFollowSetMap[it.toSymbol()] = hashSetOf()
    }

    resultFollowSetMap[rules.root] = hashSetOf(Terminal.endOfInput())

    fun resultHash(): String {
        return "KEYS:${resultFollowSetMap.keys.count()}" +
                "VALUES:${resultFollowSetMap.values.joinToString { it.size.toString() }}"
    }

    do {
        val hashBefore = resultHash()
        rules.nonTerminals.forEach { nonTerminal ->
            val symbol = nonTerminal.toSymbol()
            rules.rulesWithReproducing(symbol).forEach { rule ->
                val productionsWithSymbol = rule.productions.filter { it.symbols.contains(symbol) }
                for (production in productionsWithSymbol) {
                    println("${rule.nonTerminal} -> $production")
                    val symbolsAfter = production.symbolsAfter(symbol)
                    val firstSetForSymbolsAfter = getFirstSet(symbolsAfter)

                    if (firstSetForSymbolsAfter.isEmpty() || firstSetForSymbolsAfter.contains(Terminal.emptySymbol())) {
                        val parent = rule.nonTerminal.toSymbol()
                        resultFollowSetMap[symbol]?.addAll(resultFollowSetMap[parent]!!)
                    }

                    val firstSetForSymbolsAfterWithoutEps = firstSetForSymbolsAfter.toMutableList()
                    firstSetForSymbolsAfterWithoutEps.remove(Terminal.emptySymbol())
                    resultFollowSetMap[symbol]?.addAll(firstSetForSymbolsAfterWithoutEps)
                }
            }
        }
    } while (hashBefore != resultHash())

    return resultFollowSetMap
}
