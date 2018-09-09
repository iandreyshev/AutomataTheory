using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace Lexer
{
	class Token
	{
		public Token() { }
		public Token(string text)
		{
			_text = text;
		}

		public override string ToString()
		{
			return _text;
		}

		private string _text;
	}
}
