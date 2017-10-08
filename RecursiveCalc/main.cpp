#include <iostream>
#include <string>

double Calculate(const std::string &expression);
void PrintExpressionResult(const std::string &expression);

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;



	return 0;
}

double Calculate(const std::string &expression)
{
	return 0;
}

void PrintExpressionResult(const std::string &expression)
{
	try
	{
		const double result = Calculate(expression);
		printf("'%s' = %d\n", expression, result);
	}
	catch (const std::exception &ex)
	{
		printf("Error in '%s': %s\n", expression, ex.what());
	}
}