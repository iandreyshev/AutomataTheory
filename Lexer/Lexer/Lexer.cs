using System;
using System.Collections.Generic;
using System.IO;

namespace Lexer
{
	class Lexer
	{
		public Lexer(TextReader reader)
		{
			_reader = reader;
		}

		public void NextLine()
		{
		}

		public bool GetToken(Token token)
		{
			SkipSpaces();
			SkipComments();

			if (_reader == null || _reader.Peek() == -1)
			{
				return false;
			}
			token = ReadToken();

			return true;
		}

		private static readonly String COMMENT_START = "/*";
		private static readonly String COMMENT_END = "*/";

		private int _position;
		private TextReader _reader;
		private readonly Dictionary<string, int> WORDS = new Dictionary<string, int>
		{
			// Key-words
			{ "static", 0 },
			{ "main", 1 },
			{ "extends", 2 },
			{ "return", 3 },
			{ "new", 4 },
			{ "this", 5 },
			// Protect level
			{ "public", 6 },
			// Type
			{ "void", 7 },
			{ "class", 8 },
			{ "String", 9 },
			{ "int", 10 },
			{ "boolean", 11 },
			// Statement
			{ "if", 12 },
			{ "else", 13 },
			// Loop
			{ "while", 14 },
			// Write, Read
			{ "Print", 15 },
			{ "Read", 16 },
			// Logic
			{ "true", 17 },
			{ "false", 18 },
			{ "&&", 19 },
			{ "<", 20 },
			{ ">", 21 },
			{ "!", 22 },
			// Assign
			{ "=", 23 },
			// Arithmetic
			{ "+", 24 },
			{ "-", 25 },
			{ "*", 26 },
			{ "/", 27 },
			// Brackets
			{ "{", 28 },
			{ "}", 29 },
			{ "(", 30 },
			{ ")", 31 },
			{ "[", 32 },
			{ "]", 33 },
			// Special symbols
			{ ";", 34 },
			{ ",", 35 },
			{ ".", 36 },
		};
		private readonly HashSet<int> SPACES = new HashSet<int>
		{
			'\n',
			'\t',
			' '
		};

		private char Next()
		{
			++_position;
			return Convert.ToChar(_reader.Read());
		}

		private void SkipSpaces()
		{
			while (SPACES.Contains(_reader.Peek()))
			{
				Next();
			}
		}

		private void SkipComments()
		{
		}

		private Token ReadToken()
		{
			string tokenText = "";

			if (ReadIdentifier(ref tokenText) ||
				ReadNumber(ref tokenText) ||
				ReadOther(ref tokenText))
			{

			}

			return new Token(tokenText);
		}

		private bool ReadIdentifier(ref string text)
		{
			char ch = Convert.ToChar(_reader.Peek());

			if (!Char.IsLetter(ch))
			{
				return false;
			}

			while (Char.IsLetter(ch) || Char.IsDigit(ch))
			{
				ch = Next();
				text += ch;
			}

			return true;
		}

		private bool ReadNumber(ref string text)
		{
			char ch = Convert.ToChar(_reader.Peek());
			bool result = false;

			while (Char.IsDigit(ch))
			{
				result = true;
				ch = Next();
				text += ch;
			}

			return result;
		}

		private bool ReadOther(ref string text)
		{
			char ch = Convert.ToChar(_reader.Peek());
			bool result = false;

			while (!Char.IsDigit(ch) || !Char.IsLetter(ch))
			{
				result = true;
				ch = Next();
				text += ch;
			}

			return result;
		}
	}
}
