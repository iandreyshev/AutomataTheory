import grammar.GrammarSymbol
import grammar.NonTerminal
import grammar.Terminal
import grammar.samples.GRAMMAR
import grammar.samples.KEYWORDS
import org.junit.Assert.assertEquals
import org.junit.Test

class FirstSetTest {

    @Test
    fun program() = "Program" expected setOf(
            Terminal(KEYWORDS.EOF), Terminal(KEYWORDS.Function)
    )

    @Test
    fun functionList() = "FunctionList" expected setOf(
            Terminal.emptySymbol(), Terminal(KEYWORDS.Function)
    )

    @Test
    fun function() = "Function" expected setOf(
            Terminal(KEYWORDS.Function)
    )

    @Test
    fun paramList() = "ParamList" expected setOf(
            Terminal.emptySymbol(), Terminal("id")
    )

    @Test
    fun tailParamList() = "TailParamList" expected setOf(
            Terminal.emptySymbol(), Terminal(",")
    )

    @Test
    fun param() = "Param" expected setOf(
            Terminal("id")
    )

    @Test
    fun type() = "Type" expected setOf(
            Terminal(KEYWORDS.TypeInt), Terminal(KEYWORDS.TypeFloat), Terminal(KEYWORDS.TypeBoolean),
            Terminal(KEYWORDS.TypeArray)
    )

    @Test
    fun statement() = "Statement" expected setOf(
            Terminal("id"), Terminal(KEYWORDS.Condition), Terminal(KEYWORDS.CycleWithPreCondition),
            Terminal("var"), Terminal("return"), Terminal("{")
    )

    @Test
    fun condition() = "Condition" expected setOf(
            Terminal(KEYWORDS.Condition)
    )

    @Test
    fun optionalElse() = "OptionalElse" expected setOf(
            Terminal.emptySymbol(), Terminal("else")
    )

    @Test
    fun loop() = "Loop" expected setOf(
            Terminal("while")
    )

    @Test
    fun decl() = "Decl" expected setOf(
            Terminal("var")
    )

    @Test
    fun assign() = "Assign" expected setOf(
            Terminal("id")
    )

    @Test
    fun `return`() = "Return" expected setOf(
            Terminal("return")
    )

    @Test
    fun compositeStatement() = "CompositeStatement" expected setOf(
            Terminal("{")
    )

    @Test
    fun statementList() = "StatementList" expected setOf(
            Terminal.emptySymbol(), Terminal("id"), Terminal(KEYWORDS.Condition), Terminal(KEYWORDS.CycleWithPreCondition),
            Terminal("var"), Terminal("return"), Terminal("{")
    )

    @Test
    fun expression() = "Expression" expected setOf(
            Terminal("id"), Terminal("literal"), Terminal("true"), Terminal("false")
    )

    private infix fun String.expected(expectedTerminals: Collection<Terminal>) {
        val set = GRAMMAR.firstSetFor(GrammarSymbol.from(NonTerminal(this)))
        assertEquals(expectedTerminals.count(), set.count())
        assertEquals(expectedTerminals, set)
    }

}