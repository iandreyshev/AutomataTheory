@file:JvmName("Main")

import grammar.Grammar
import parser.LLOneParser

private const val GRAMMAR_FILE_PATH = ""
private const val INPUT_FILE_PATH = ""

fun main(args: Array<String>) {

    args.forEach {
        print(it)
    }

    GRAMMAR_FILE_PATH.byteInputStream().use { grammarStream ->
        val grammarStr = grammarStream.readBytes().contentToString()
        val grammar = Grammar.Parser().parse(grammarStr)

        INPUT_FILE_PATH.byteInputStream().use { inputStream ->
            val input = inputStream.readBytes().contentToString()
            val isSuccess = LLOneParser.parse(grammar, input)

            if (isSuccess) print("Success!")
            else print("Error!")
        }
    }
}
