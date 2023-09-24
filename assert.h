#pragma once

#if !defined(MARTY_IDC_ASSERT)

    #if defined(Q_ASSERT)
    
        #define MARTY_IDC_ASSERT( statement )         Q_ASSERT(statement)
    
    #elif defined(WIN32) || defined(_WIN32)
    
        #include <winsock2.h>
        #include <windows.h>
        #include <crtdbg.h>
    
        #define MARTY_IDC_ASSERT( statement )         _ASSERTE(statement)
    
    #else
    
        #include <cassert>
    
        #define MARTY_IDC_ASSERT( statement )         assert(condition) 
    
    #endif
    
    
    //------------------------------
    //! MARTY_IDC__ASSERT_FAIL срабатывает всегда, и ставится туда, куда, по идее, никогда попадать не должны
    #define MARTY_IDC_ASSERT_FAIL()                        MARTY_IDC_ASSERT( 0 )

#endif

