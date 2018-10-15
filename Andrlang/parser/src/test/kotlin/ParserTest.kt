import extension.addToList
import grammar.Terminal
import grammar.samples.GRAMMAR
import org.junit.Test
import parser.Parser
import parser.ParsingTable

class ParserTest {

    private val mTable = ParsingTable(GRAMMAR)
    private val mParser: Parser = Parser()

    @Test
    fun decl() {
        parse("""
            Func id ( ) : Int >
            var id : Array [ Int ] ;
            EOF
        """.trimIndent())
    }

    @Test
    fun loop() {
        parse("""
            Func id ( id : Float ) : Array [ Bool ] > {
                var id : Int ;
                id = literal ;
                while ( true ) {
                    var id : Float ;
                    id = literal ;
                }
            }
            EOF
        """.trimIndent())
    }

    private fun parse(text: String) {
        try {
            mParser.execute(GRAMMAR.root, mTable, TestLexer(text))
            println("Input is OK")
        } catch (ex: Exception) {
            println("Error:\n ${ex.message}")
        }
    }

    class TestLexer(input: String) : Iterator<Terminal> {

        private val mTokens: MutableList<Terminal> = input.split(" ", "\r", "\n", "\t")
                .filter { it.isNotBlank() && it.isNotEmpty() }
                .map { it.trim() }
                .map { Terminal(it) }
                .addToList(Terminal.endOfInput())
                .toMutableList()

        override fun next(): Terminal {
            val next = mTokens.first()
            mTokens.removeAt(0)
            return next
        }

        override fun hasNext(): Boolean =
                mTokens.isNotEmpty()

        override fun toString(): String =
                mTokens.joinToString(separator = " ")

    }

}