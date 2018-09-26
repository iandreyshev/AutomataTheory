import lexer.TestLexer

const val EASY_MATH_GRAMMAR = "math_grammar_easy.txt"
const val HARD_MATH_GRAMMAR = "math_grammar.txt"

val EASY_GRAMMAR_LEXERS: List<TestLexer> = listOf(
        "id",
        "id + id",
        "id * id",
        "*",
        "+",
        "+ id",
        "* id",
        "id +",
        "id *",
        "invalid token"
).map { TestLexer(it) }

val HARD_GRAMMAR_LEXERS: List<TestLexer> = listOf(
        "",
        "1",
        "1 + 1",
        "+ 1",
        "1 +",
        "1 / 1",
        "1 * 1",
        "1 * 1 / 1",
        "1 * ( 1 / 1 )",
        "( 1 * ( 1 ) / 1 )",
        "( 1 ) * ( 1 ) / ( 1 )",
        "( 1 + 2 ) / 3 * ( 4 + 5 )",
        "1 * * 2",
        "( ) + 1",
        "1 2 3 4 5 6 7 8 9",
        "( 1 )"
        ).map { TestLexer(it) }
