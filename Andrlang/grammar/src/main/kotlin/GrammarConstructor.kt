package grammar

/**
 * GC means Grammar Constructor
 */

typealias GCSymbol = String

typealias GCProduction = List<GCSymbol>
typealias GCAlternatives = List<GCProduction>
typealias GCRule = Pair<GCSymbol, GCAlternatives>

fun grammarOf(director: IGCRuleBuilder.() -> Unit): Grammar {
    val builder = GCRuleBuilder().apply(director)
    val gcRules = builder.build()
    val gcNonTerminalSymbols = mutableSetOf<String>()
    val gcNewRules: MutableList<Pair<NonTerminal, MutableList<Production>>> = mutableListOf()

    gcRules.forEach {
        gcNonTerminalSymbols.add(it.first)
        gcNewRules.add(NonTerminal(it.first) to mutableListOf())
    }

    gcRules.map { gcRule ->
        val gcRuleNonTerminal = gcRule.first
        val gcAlternatives = gcRule.second
        val productions = gcAlternatives.map { gcProduction ->
            val grammarSymbols = gcProduction.map { gcSymbol ->
                if (gcNonTerminalSymbols.contains(gcSymbol)) {
                    GrammarSymbol.from(NonTerminal(gcSymbol))
                } else {
                    GrammarSymbol.from(Terminal(gcSymbol))
                }
            }
            Production(grammarSymbols)
        }
        gcNewRules.firstOrNull { it.first.symbol == gcRuleNonTerminal }
                ?.second
                ?.addAll(productions)
    }

    return Grammar(gcNewRules.map { Rule(it.first, it.second) })
}

interface IGCRuleBuilder {
    fun nonTerminal(symbol: GCSymbol, director: IGCProductionBuilder.() -> Unit)
}

class GCRuleBuilder : IGCRuleBuilder {

    private val mRules = mutableListOf<GCRule>()

    override fun nonTerminal(symbol: GCSymbol, director: IGCProductionBuilder.() -> Unit) {
        val builder = GCProductionBuilder().apply(director)
        mRules.add(symbol to builder.build())
    }

    internal fun build(): List<GCRule> = mRules

}

interface IGCProductionBuilder {
    fun reproduce(vararg symbols: String)
    fun reproduceEmptySymbol()
}

class GCProductionBuilder : IGCProductionBuilder {

    private val mProductionsSymbols = mutableListOf<GCProduction>()

    override fun reproduce(vararg symbols: String) {
        mProductionsSymbols.add(symbols.toList())
    }

    override fun reproduceEmptySymbol() {
        mProductionsSymbols.add(listOf(Terminal.newEpsilon().symbol))
    }

    internal fun build(): GCAlternatives = mProductionsSymbols

}
