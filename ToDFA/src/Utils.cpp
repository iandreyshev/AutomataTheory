#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

#include "Utils.h"

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
	const std::string CONVERT_COMMAND = "dot -Tpng -o";
}

namespace Utils
{
	const std::string GRAPH_TYPE = ".dot";
	const std::string IMG_TYPE = ".png";

	bool RunProcess(const std::string &command)
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
	std::string ToImage(const CDotWriter &dotWriter, const std::string &fileName)
	{
		const std::string &dotName = fileName + GRAPH_TYPE;
		const std::string &imageName = fileName + IMG_TYPE;

		std::ofstream dotFile(dotName);
		dotFile << dotWriter.Get();
		dotFile.close();

		RunProcess(CONVERT_COMMAND + imageName + " " + dotName);
		return imageName;
	}
	void TrimString(std::string &str)
	{
		while (isspace(*str.begin())) str.erase(0, 1);
		while (isspace(*--str.end())) str.erase(str.length() - 1, 1);
	}
}