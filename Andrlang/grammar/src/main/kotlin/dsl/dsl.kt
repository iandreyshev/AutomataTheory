package dsl

import grammar.*

typealias GDSLSymbol = String
typealias GDSLProduction = List<GDSLSymbol>
typealias GDSLAlternatives = List<GDSLProduction>
typealias GDSLRule = Pair<GDSLSymbol, GDSLAlternatives>

fun grammarOf(director: IGDSLRuleBuilder.() -> Unit): Grammar {
    val builder = RuleBuilder().apply(director)
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
        gcNewRules.firstOrNull { it.first.literal == gcRuleNonTerminal }
                ?.second
                ?.addAll(productions)
    }

    val rulesList = gcNewRules.map {
        Rule(it.first, it.second)
    }

    return Grammar(rulesList)
}

interface IGDSLRuleBuilder {
    fun nonTerminal(symbol: GDSLSymbol, director: IGDSLProductionBuilder.() -> Unit)
}

private class RuleBuilder : IGDSLRuleBuilder {

    private val mRules = mutableListOf<GDSLRule>()

    override fun nonTerminal(symbol: GDSLSymbol, director: IGDSLProductionBuilder.() -> Unit) {
        val builder = ProductionBuilder().apply(director)
        mRules.add(symbol to builder.build())
    }

    fun build(): List<GDSLRule> = mRules

}

interface IGDSLProductionBuilder {
    fun reproduce(vararg symbols: String)
    fun reproduceEmptySymbol()
}

private class ProductionBuilder : IGDSLProductionBuilder {

    private val mProductionsSymbols = mutableListOf<GDSLProduction>()

    override fun reproduce(vararg symbols: String) {
        mProductionsSymbols.add(symbols.toList())
    }

    override fun reproduceEmptySymbol() {
        mProductionsSymbols.add(listOf(Terminal.newEpsilon().literal))
    }

    fun build(): GDSLAlternatives = mProductionsSymbols

}
