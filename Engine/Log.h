#pragma once

enum class LogLevel
{
	LOG_LEVEL_INIT,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
};

#ifdef _DEBUG
#define LOG_INIT(...)    Log::Instance().AddLog(LogLevel::LOG_LEVEL_INIT,    __FILE__, __LINE__, __VA_ARGS__);
#define LOG_INFO(...)    Log::Instance().AddLog(LogLevel::LOG_LEVEL_INFO,    __FILE__, __LINE__, __VA_ARGS__);
#define LOG_WARNING(...) Log::Instance().AddLog(LogLevel::LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_ERROR(...)   Log::Instance().AddLog(LogLevel::LOG_LEVEL_ERROR,   __FILE__, __LINE__, __VA_ARGS__);
#else
#define LOG_INIT(...)    return;
#define LOG_INFO(...)    return;
#define LOG_WARNING(...) return;
#define LOG_ERROR(...)   return;
#endif

class Log : public Singleton<Log>
{
public:
	struct LogMessage
	{
		LogLevel level;
		string   message;
		string   timeStamp;
		string   sourceFile;
		i32      lineNumber;
	};
public:
	virtual void Awake() override
	{
		Clear();
	}
public:
	void Clear()
	{
		_messages.clear();
	}
public:
	List<LogMessage>& GetLogs()
	{
		return _messages;
	}
public:
	template<typename T>
	void AddLog(LogLevel level, string sourceFile, i32 lineNumber, const T& message, ...)
	{
		std::stringstream message_to_string;
		message_to_string << message;

		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		const tm* localtime = std::localtime(&in_time_t);

		std::stringstream ss;
		ss << std::put_time(localtime, "%X");

		_messages.push_back({ level, message_to_string.str(), ss.str(), sourceFile, lineNumber});
		// 여기까지 해놓고 ImGui로 넘겨서 거기서 출력하면 됨

		// 아래부턴 콘솔 출력 로직임

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD color = 7;

		switch (level)
		{
		case LogLevel::LOG_LEVEL_INIT:    color = 10; break;
		case LogLevel::LOG_LEVEL_INFO:    color = 7;  break;
		case LogLevel::LOG_LEVEL_WARNING: color = 14; break;
		case LogLevel::LOG_LEVEL_ERROR:   color = 12; break;
		}

		SetConsoleTextAttribute(hConsole, color);

		const char* simplePath = strrchr(sourceFile.c_str(), '\\') + 1;

		std::cout << "[" << ss.str() << "] "
			<< simplePath << ":" << lineNumber << " : "
			<< message_to_string.str() << std::endl;

		SetConsoleTextAttribute(hConsole, 7);
	}
//public:
//	void AddLog(LogLevel level, string sourceFile, i32 lineNumber, const char* fmt, ...) IM_FMTARGS(3)
//	{
//		char buf[1024];
//		va_list args;
//		va_start(args, fmt);
//		vsnprintf(buf, sizeof(buf), fmt, args);
//		va_end(args);
//		buf[sizeof(buf) - 1] = 0;
//
//		auto now       = chrono::system_clock::now();
//		auto in_time_t = chrono::system_clock::to_time_t(now);
//
//		const tm* localtime = std::localtime(&in_time_t);
//
//		stringstream ss;
//		ss << std::put_time(localtime, "%X");
//		// 인자 정보 : https://en.cppreference.com/w/cpp/io/manip/put_time
//
//		_messages.push_back({ level, buf, ss.str(), sourceFile, lineNumber });
//	}
private:
	List<LogMessage> _messages;
};




// Only Text, No Color

//class JLog
//{
//	SINGLETON(JLog);
//public:
//	void Init()
//	{
//		Clear();
//	}
//public:
//	void Clear()
//	{
//		_buffer.clear();
//	}
//	void AddLog(const char* fmt, ...) IM_FMTARGS(2)
//	{
//		va_list args;
//		va_start(args, fmt);
//		AddLog(fmt, args);
//		va_end(args);
//	}
//	void AddLog(const char* fmt, va_list args)
//	{
//		i32 old_size = _buffer.size();
//		_buffer.appendfv(fmt, args);
//
//		for (i32 new_size = _buffer.size(); old_size < new_size; old_size++)
//		{
//			if (_buffer[old_size] == '\n')
//			{
//				_lineOffsets.push_back(old_size + 1);
//			}
//		}
//	}
//	void Draw(const char* title = "Log", bool* p_open = nullptr)
//	{
//		if (!ImGui::Begin(title, p_open))
//		{
//			ImGui::End();
//			return;
//		}
//
//		if (ImGui::Button("Clear"))
//		{
//			Clear();
//		}
//		ImGui::SameLine();
//		bool copy = ImGui::Button("Copy");
//		ImGui::SameLine();
//
//		ImGui::Text("Logs: %d lines", _lineOffsets.Size);
//
//		ImGui::Separator();
//
//		ImGui::BeginChild("Log");
//		if (copy == true)
//		{
//			ImGui::LogToClipboard();
//		}
//
//		ImGui::TextUnformatted(_buffer.begin());
//
//		if (_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
//		{
//			ImGui::SetScrollHereY(1.0f);
//		}
//
//		ImGui::EndChild();
//		ImGui::End();
//	}
//private:
//	ImGuiTextBuffer _buffer;
//	ImVector<i32>   _lineOffsets;
//	bool            _autoScroll = true;
//};
