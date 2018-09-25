import grammar.Grammar
import lexer.Lexer
import parser.LL1Parser
import parser.PredictParsingTable
import java.io.File

private const val GRAMMAR_FILE_PATH = "grammar.txt"

fun main(args: Array<String>) {
    val grammarStr = File(GRAMMAR_FILE_PATH).readText()
    val grammar = Grammar(grammarStr)
    val parseTable = PredictParsingTable(grammar)
    val parser = LL1Parser()

    try {
        parser.execute(grammar.root, parseTable, Lexer())
        println()
        println("Grammar is OK")
    } catch (ex: Exception) {
        println("Grammar is not good. Message: ${ex.message}")
    }
}
