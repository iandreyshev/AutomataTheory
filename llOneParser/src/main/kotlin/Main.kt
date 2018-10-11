import grammar.Grammar
import lexer.TestLexer
import parser.LL1Parser
import parser.PredictParsingTable
import java.io.File

fun main(args: Array<String>) {
//    MATH_GRAMMAR testWith MATH_LEXERS
    YOLANG_GRAMMAR testWith YOLANG_LEXERS
}

infix fun String.testWith(lexers: List<TestLexer>) {
    println("Test grammar from file '$this':")

    val grammarStr = File(this).readText()
    val grammar = Grammar(grammarStr)
    val parseTable = PredictParsingTable(grammar)
    val parser = LL1Parser()

    println("Table created")

    lexers.forEach { lexer ->
        println("  Input:")
        println(lexer.input)

        try {
            parser.execute(grammar.root, parseTable, lexer)
            println("    Input is OK")
        } catch (ex: Exception) {
            println("${ex.message}")
        }

        println()
    }
}
