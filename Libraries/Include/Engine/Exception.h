#pragma once

#include<locale.h>

class Exception
{
public:
    Exception() = default;
    Exception(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber)
        : ErrorCode(hr), FunctionName(functionName), Filename(filename), LineNumber(lineNumber)
    {
        wstring fileNameBuffer = L"";
        u64     fileNameSize = Filename.size();
        u64     ptr = 0;

        for (u64 i = fileNameSize - 1; i >= 0; --i)
        {
            if (Filename[i] == '\\')
            {
                ptr = i;
                break;
            }
        }
        for (u64 i = ptr + 1; i < fileNameSize; ++i)
        {
            fileNameBuffer.push_back(Filename[i]);
        }

        Filename = fileNameBuffer;
    }
public:
    std::string ToString() const
    {
        _com_error err(ErrorCode);
        std::wstring msg = err.ErrorMessage();

        wstring errMsg = L"Failed in " + Filename + L"[Line " + std::to_wstring(LineNumber) + L"] Error: " + msg;

        const wchar_t* str = errMsg.c_str();
        char mbs[512] = { 0 };
        mbstate_t shiftState = mbstate_t();
        setlocale(LC_ALL, "");
        wcsrtombs(mbs, &str, sizeof(mbs), &shiftState);

        return string(mbs);
    }

    HRESULT ErrorCode = S_OK;
    std::wstring FunctionName;
    std::wstring Filename;
    int LineNumber = -1;
};

inline std::wstring AnsiToWString(const std::string& str)
{
    WCHAR buffer[512];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
    return std::wstring(buffer);
}

#ifndef CHECK
#define CHECK(x)                                                      \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw Exception(hr__, L#x, wfn, __LINE__); }   \
}
#endif

