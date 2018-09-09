using System;
using System.IO;

namespace Lexer
{
	class Program
	{
		static int Main(string[] args)
		{
			if (args.Length < 1)
			{
				return -1;
			}

			Lexer lexer = new Lexer(new StreamReader(args[0]));
			Token token = new Token();

			while(lexer.GetToken(token))
			{
				Console.WriteLine(token.ToString());
			}

			return 0;
		}
	}
}
