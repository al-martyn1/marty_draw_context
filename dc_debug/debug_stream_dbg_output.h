#pragma once

#include "i_debug_stream_writter.h"

#include <iostream>

#if defined(WIN32) || defined(_WIN32)

    #include <winsock2.h>
    #include <Windows.h>
    #include <debugapi.h>

#endif




namespace marty_draw_context {


class DebugStreamDbgOutput : public DebugStreamImplBase
{

    std::string fromWideString(const wchar_t* str) const
    {
        std::string res;

        for(; str && *str; ++str)
            res.append(1,(char)*str);

        return res;
    }

    std::size_t outputDebugString( const char* str, std::size_t len )
    {
        #if defined(WIN32) || defined(_WIN32)
            if (IsDebuggerPresent())
            {
                OutputDebugStringA(str);
            }
        #endif

        return len;
    }

    std::size_t outputDebugString( const wchar_t* str, std::size_t len )
    {
        #if defined(WIN32) || defined(_WIN32)
            if (IsDebuggerPresent())
            {
                OutputDebugStringW(str);
            }
        #endif

        return len;
    }

    virtual
    std::size_t writeImpl( const char* str, std::size_t len ) override
    {
        if (len==(std::size_t)-1)
            len = std::strlen(str);

        outputDebugString(str, len);
        if (m_useStdcout)
            std::cout<<str;

        return len;
    }

    virtual
    std::size_t writeImpl( const wchar_t* str, std::size_t len ) override
    {
        if (len==(std::size_t)-1)
            len = std::wcslen(str);

        outputDebugString(str, len);
        if (m_useStdcout)
            std::cout<<fromWideString(str);

        return len;
    }

    virtual
    bool isNulStreamWritter() const override
    {
        return false;
    }

    bool m_useStdcout = false;


public:

    DebugStreamDbgOutput( bool useStdcout = false ) : m_useStdcout(useStdcout) {}

};



DebugStreamDbgOutput& getDebugStreamDbgOutput(bool useStdcout = false)
{
    static DebugStreamDbgOutput ds = DebugStreamDbgOutput(useStdcout);
    return ds;
}



} // namespace marty_draw_context

