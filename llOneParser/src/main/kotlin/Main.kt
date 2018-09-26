import grammar.Grammar
import lexer.TestLexer
import parser.LL1Parser
import parser.PredictParsingTable
import java.io.File

fun main(args: Array<String>) {
    EASY_MATH_GRAMMAR testWith EASY_GRAMMAR_LEXERS
    HARD_MATH_GRAMMAR testWith HARD_GRAMMAR_LEXERS
}

infix fun String.testWith(lexers: List<TestLexer>) {
    println("\nTest grammar from file '$this'")
    lexers.forEach { lexer ->
        val grammarStr = File(this).readText()
        val grammar = Grammar(grammarStr)
        val parseTable: PredictParsingTable
        println("  Input '${lexer.input}'")

        try {
            parseTable = PredictParsingTable(grammar)
            println("    Table created")
        } catch (ex: Exception) {
            println("    Error during table building")
            return
        }

        try {
            LL1Parser().execute(grammar.root, parseTable, lexer)
            println("    Input is OK")
        } catch (ex: Exception) {
            println("    Input is BAD")
        }
    }
}
