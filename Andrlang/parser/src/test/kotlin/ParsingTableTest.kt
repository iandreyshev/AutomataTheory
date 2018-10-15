import grammar.GrammarSymbol
import grammar.NonTerminal
import grammar.Terminal
import grammar.samples.GRAMMAR
import grammar.samples.KEYWORDS
import org.junit.Assert.assertEquals
import org.junit.Test
import parser.ParsingTable

class ParsingTableTest {

    private val mTable = ParsingTable(GRAMMAR)

    @Test
    fun program() = testTableRow("Program") {
        KEYWORDS.EOF expected listOf(
                nonTerminal("FunctionList"), terminal(KEYWORDS.EOF)
        )
        KEYWORDS.Function expected listOf(
                nonTerminal("FunctionList"), terminal(KEYWORDS.EOF)
        )
    }

    @Test
    fun functionList() = testTableRow("FunctionList") {
        KEYWORDS.EOF.expectedEmptySymbol()
        KEYWORDS.Function expected listOf(
                nonTerminal("Function"), nonTerminal("FunctionList")
        )
    }

    @Test
    fun function() = testTableRow("Function") {
        KEYWORDS.Function expected listOf(
                terminal(KEYWORDS.Function), terminal("id"), terminal("("), nonTerminal("ParamList") ,terminal(")"),
                terminal(":"), nonTerminal("Type"), terminal(">"), nonTerminal("Statement")
        )
    }

    @Test
    fun paramList() = testTableRow("ParamList") {
        "id" expected listOf(
                nonTerminal("Param"), nonTerminal("TailParamList")
        )
        ")".expectedEmptySymbol()
    }

    @Test
    fun tailParamList() = testTableRow("TailParamList") {
        ")".expectedEmptySymbol()
        "," expected listOf(
                terminal(","), nonTerminal("Param"), nonTerminal("TailParamList")
        )
    }

    @Test
    fun param() = testTableRow("Param") {
        "id" expected listOf(
                terminal("id"), terminal(","), nonTerminal("Type")
        )
    }

    @Test
    fun type() = testTableRow("Type") {
        KEYWORDS.TypeInt expected listOf(
                terminal(KEYWORDS.TypeInt)
        )
        KEYWORDS.TypeFloat expected listOf(
                terminal(KEYWORDS.TypeFloat)
        )
        KEYWORDS.TypeBoolean expected listOf(
                terminal(KEYWORDS.TypeBoolean)
        )
        KEYWORDS.TypeArray expected listOf(
                terminal(KEYWORDS.TypeArray), terminal("["), nonTerminal("Type"), terminal("]")
        )
    }

    @Test
    fun statement() = testTableRow("Statement") {
        "id" expected listOf(
                nonTerminal("Assign")
        )
        KEYWORDS.Condition expected listOf(
                nonTerminal("Condition")
        )
        KEYWORDS.CycleWithPreCondition expected listOf(
                nonTerminal("Loop")
        )
        "var" expected listOf(
                nonTerminal("Decl")
        )
        "return" expected listOf(
                nonTerminal("Return")
        )
        "{" expected listOf(
                nonTerminal("CompositeStatement")
        )
    }

    private inner class TestBuilder(private val row: NonTerminal) {

        private val mTestData: MutableMap<Terminal, List<GrammarSymbol>> = mutableMapOf()

        fun test() {
            mTestData.forEach { data ->
                val productionFromTable = mTable[row, data.key]?.symbols
                assertEquals(data.value.count(), productionFromTable?.count())
                assertEquals(data.value.toHashSet(), productionFromTable?.toHashSet())
            }

            GRAMMAR.terminals.toMutableList().apply {
                removeAll(mTestData.keys)
            }.forEach { emptyColl ->
                val tableCell = mTable[row, emptyColl]
                assertEquals(null, tableCell)
            }
        }

        infix fun String.expected(symbols: List<GrammarSymbol>) {
            mTestData[Terminal(this)] = symbols
        }

        fun String.expectedEmptySymbol() {
            mTestData[Terminal(this)] = listOf(Terminal.emptySymbol().toSymbol())
        }

        fun terminal(literal: String) = Terminal(literal).toSymbol()

        fun nonTerminal(literal: String) = NonTerminal(literal).toSymbol()

    }

    private fun testTableRow(nonTerminal: String, director: TestBuilder.() -> Unit) {
        TestBuilder(NonTerminal(nonTerminal)).apply(director).test()
    }

}