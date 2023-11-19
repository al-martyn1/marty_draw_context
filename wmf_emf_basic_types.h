#pragma once

#include "wmf_emf_enums.h"

#include <cstdint>
#include <utility>


namespace marty_draw_context {

namespace emf {

using qword_t     = std::uint64_t  ;
using dword_t     = std::uint32_t  ;
using word_t      = std::uint16_t  ;
using byte_t      = std::uint8_t   ;

using longlong_t  = std::int64_t   ;
using int_t       = std::int32_t   ;
using long_t      = std::int32_t   ;
using short_t     = std::int16_t   ;
using tiny_t      = std::int8_t    ;


} // namespace emf


namespace wmf {

using qword_t     = emf::qword_t   ;
using dword_t     = emf::dword_t   ;
using word_t      = emf::word_t    ;
using byte_t      = emf::byte_t    ;
                                   
using longlong_t  = emf::longlong_t;
using int_t       = emf::int_t     ;
using long_t      = emf::long_t    ;
using short_t     = emf::short_t   ;
using tiny_t      = emf::tiny_t    ;


} // namespace wmf

} // namespace marty_draw_context
