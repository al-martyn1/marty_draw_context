#pragma once

#if !defined(MARTY_IDC_ASSERT)

    #if defined(Q_ASSERT)
    
        #define MARTY_IDC_ASSERT( statement )         Q_ASSERT(statement)
        #define MARTY_IDC_ASSERT_FAIL()               MARTY_IDC_ASSERT( 0 )
        #define MARTY_IDC_ASSERT_FAIL_MSG(msg)        do{ MARTY_IDC_ASSERT_FAIL(); throw std::runtime_error((msg)); } while(0)
    
    #elif defined(WIN32) || defined(_WIN32)
    
        #include <winsock2.h>
        #include <windows.h>
        #include <crtdbg.h>
    
        #define MARTY_IDC_ASSERT( statement )         _ASSERTE(statement)
        #define MARTY_IDC_ASSERT_FAIL()               MARTY_IDC_ASSERT( 0 )
        #define MARTY_IDC_ASSERT_FAIL_MSG(msg)        do{ MARTY_IDC_ASSERT_FAIL(); throw std::runtime_error((msg)); } while(0)
    
    #else
    
        #include <cassert>
    
        #define MARTY_IDC_ASSERT( statement )         assert(condition) 
        #define MARTY_IDC_ASSERT_FAIL()               MARTY_IDC_ASSERT( 0 )
        #define MARTY_IDC_ASSERT_FAIL_MSG(msg)        do { MARTY_IDC_ASSERT_FAIL(); (void)msg; } while(0)
    
    #endif
    
    
#endif

