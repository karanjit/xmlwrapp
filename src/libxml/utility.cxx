/*
 * Copyright (C) 2001-2003 Peter J Jones (pjones@pmade.org)
 * All Rights Reserved
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifdef _MSC_VER
    // using vsnprintf() under MSVC 2005 or later results in a warning C4996
    // because the function may be used in unsafe ways -- as we do use it
    // correctly here, disable the warning by predefining this symbol before
    // any standard headers are included (we don't bother to test MSVC version
    // here as defining it does no harm for the previous versions anyhow)
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include "utility.h"

#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <string>

// hack to pull in vsnprintf for MSVC
#if defined(_MSC_VER) || (defined(__COMO__) && defined(__WIN32__))
    #undef vsnprintf
    #define vsnprintf _vsnprintf
#endif

namespace xml
{

namespace impl
{

// this function is used by libxsltwrapp too, so we must export it
XMLWRAPP_API void printf2string(std::string& s, const char *message, va_list ap)
{
    char buffer[512];

    std::memset(buffer, 0, sizeof(buffer));

    // XXX vsnprintf is non-standard
    if (vsnprintf(buffer, sizeof(buffer), message, ap) > 0)
    {
        std::string::size_type size = std::strlen(buffer);

        if ( buffer[size-1] == '\n' )
            --size;
        s.assign(buffer, size);
    }
}

} // namespace impl

} // namespace xml
