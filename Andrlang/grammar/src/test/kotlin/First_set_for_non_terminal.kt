import grammar.NonTerminal
import grammar.Terminal
import grammar.samples.GRAMMAR
import grammar.samples.KEYWORDS
import org.junit.Test

class First_set_for_non_terminal {

    @Test
    fun Program() = "Program" expected setOf(
            Terminal.newEpsilon(), Terminal(KEYWORDS.EndOfFile), Terminal(KEYWORDS.Function)
    )

    @Test
    fun FunctionList() = "FunctionList" expected setOf(
            Terminal.newEpsilon(), Terminal(KEYWORDS.Function)
    )

    @Test
    fun Function() = "Function" expected setOf(
            Terminal(KEYWORDS.Function)
    )

    @Test
    fun ParamList() = "ParamList" expected setOf(
            Terminal.newEpsilon(), Terminal("id")
    )

    @Test
    fun TailParamList() = "TailParamList" expected setOf(
            Terminal(","), Terminal.newEpsilon()
    )

    private infix fun String.expected(expectedTerminals: Collection<Terminal>) {
        val set = GRAMMAR.firstSetFor(NonTerminal(this))
        assert(set.count() == expectedTerminals.count() && set.containsAll(expectedTerminals))
    }

}