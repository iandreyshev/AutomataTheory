import grammar.Grammar
import parser.LL1Parser
import parser.PredictParsingTable
import java.io.File

private const val GRAMMAR_FILE_PATH = "grammar.txt"

fun main(args: Array<String>) {
    val grammarStr = File(GRAMMAR_FILE_PATH).readText()
    val grammar = Grammar(grammarStr)
    val parseTable = PredictParsingTable(grammar)
    val parser = LL1Parser(parseTable) { "" }
    var input: String? = readLine()

    while (input != null && input != "exit") {
        val isParsingSuccess = parser.execute(input)

        if (isParsingSuccess) {
            print("Input string is correct")
        } else {
            print("Input string is not LL(1)")
        }

        input = readLine()
    }
}
