import extension.addToList
import grammar.Terminal
import grammar.samples.GRAMMAR
import grammar.samples.KEYWORDS
import org.junit.Test
import parser.Parser
import parser.ParsingTable

class ParserTest {

    private val mTable = ParsingTable(GRAMMAR)
    private val mParser: Parser = Parser()

    @Test
    fun decl() = parse("""
            func id ( ) -> Int :
                var id : Array < Int > ;
        """.trimIndent())

    @Test
    fun loop() = parse("""
        func id ( id : Float ) -> Array < Bool > : {
            var id : Int ;
                id = literal ;
            while ( true ) {
                var id : Float ;
                id = literal ;
            }
        }
        """.trimIndent())

    @Test
    fun arraysInArray() = parse("""
        func id ( id : Int , id : Float ) -> Int : {
            var id : Bool ;
            return id ;
        }

        func id (
            id : Array < Array < Array < Int >  >
        ) -> Int :
            return literal ;
    """.trimIndent())

    private fun parse(text: String) {
        try {
            mParser.execute(GRAMMAR.root, mTable, TestLexer(text + " ${KEYWORDS.EOF}"))
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