import grammar.Grammar
import lexer.TestLexer
import parser.LL1Parser
import parser.PredictParsingTable
import java.io.File

fun main(args: Array<String>) {
    println("Easy grammar results:")
    test(MATH_GRAMMAR_EASY, EASY_GRAMMAR_LEXERS)
    println("Hard grammar results:")
    test(MATH_GRAMMAR_HARD, HARD_GRAMMAR_LEXERS)
}

fun test(grammarFile: String, lexers: List<TestLexer>) {
    lexers.forEach { lexer ->
        val grammarStr = File(grammarFile).readText()
        val grammar = Grammar(grammarStr)
        val parseTable = PredictParsingTable(grammar)

        try {
            println("   Input '${lexer.input}'")
            println("   Table created")
            LL1Parser().execute(grammar.root, parseTable, lexer)
            println("   Input is OK")
        } catch (ex: Exception) {
            println("   Input is not good")
        }
        println()
    }
}
