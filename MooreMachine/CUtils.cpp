#define _CRT_SECURE_NO_WARNINGS
#include "CUtils.h"

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace
{
	class CPipeHandle
	{
	public:
		CPipeHandle(FILE *pipe)
			: m_pipe(pipe)
		{
		}

		~CPipeHandle()
		{
			if (m_pipe)
			{
				pclose(m_pipe);
			}
		}

		operator FILE*()const
		{
			return m_pipe;
		}

	private:
		FILE *m_pipe = nullptr;
	};

	const std::string LOG_PREFIX = "> ";
}

bool CUtils::RunProcess(const std::string &command)
{
	char tmp[512];
	for (int i = 0; i < 512; i++)
	{
		tmp[i] = ' ';
	}
	sprintf(tmp, "\"%s\"", command.c_str());
	CPipeHandle pipe(popen(tmp, "r"));
	if (!pipe)
	{
		return false;
	}

	std::vector<char> buffer(256);

	while (std::fgets(buffer.data(), int(buffer.size()), pipe))
	{
		std::fputs(buffer.data(), stderr);
	}

	if (std::feof(pipe))
	{
		return true;
	}

	std::fputs(std::strerror(errno), stderr);
	return false;
}

XMLElementCollection CUtils::GetAllChilds(const tinyxml2::XMLElement* parent)
{
	const tinyxml2::XMLElement* child = parent->FirstChildElement();
	std::vector<const tinyxml2::XMLElement*> collection;
	while (child)
	{
		collection.push_back(child);
		child = child->NextSiblingElement();
	}
	return collection;
}

std::vector<std::string> CUtils::Split(const std::string &str, char separator)
{
	std::vector<std::string> result;
	std::string newStr;

	auto push_if = [&]() {
		if (newStr.empty()) return;
		result.push_back(newStr);
		newStr = "";
	};

	for (auto &ch : str)
	{
		if (ch == separator)
		{
			push_if();
			continue;
		}
		newStr += ch;
	}

	push_if();
	return result;
}
