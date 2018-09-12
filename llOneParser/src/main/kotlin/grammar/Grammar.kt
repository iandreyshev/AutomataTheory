package grammar

class Grammar internal constructor(
        grammarStr: String
) {

    private val mRules = GrammarParser(grammarStr).parse()

}
