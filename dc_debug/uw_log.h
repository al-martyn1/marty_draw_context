#pragma once

#include "debug_stream_dbg_output.h"
#include "debug_stream_nul.h"


#define UW_LOG_DBGOUT()      marty_draw_context::getDebugStreamDbgOutput()
#define UW_LOG_NUL()         marty_draw_context::getDebugStreamNul()


#define UW_LOG() UW_LOG_DBGOUT()

