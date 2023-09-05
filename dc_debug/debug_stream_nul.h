#pragma once

#include "i_debug_stream_writter.h"

#include <iostream>



namespace marty_draw_context {


class DebugStreamNul : public DebugStreamImplBase
{

    virtual
    std::size_t writeImpl( const char* str, std::size_t len ) override
    {
        MARTY_ARG_USED(str);
        MARTY_ARG_USED(len);
        return len;
    }

    virtual
    std::size_t writeImpl( const wchar_t* str, std::size_t len ) override
    {
        MARTY_ARG_USED(str);
        MARTY_ARG_USED(len);
        return len;
    }

    virtual
    bool isNulStreamWritter() const override
    {
        return true;
    }

};


DebugStreamNul& getDebugStreamNul()
{
    static DebugStreamNul ds = DebugStreamNul();
    return ds;
}



} // namespace marty_draw_context

