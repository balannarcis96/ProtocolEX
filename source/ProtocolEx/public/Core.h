#pragma once
/**
 * @file Core.h
 *
 * @brief ProtocolEx core includes and abstractions
 *
 * @author Balan Narcis
 * Contact: balannarcis96@gmail.com
 *
 */

// Standard libs
#include <atomic>
#include <cstdint>
#include <type_traits>
#include <intrin.h>
#include <memory>

#define MEMEX_STATISTICS

#ifndef ALIGNMENT
#define ALIGNMENT alignof(size_t)
#endif

#ifndef FORCEINLINE
#define FORCEINLINE __forceinline
#endif

//Empty macro used to keep Visual Studio from indenting pointer members
#define PTR

namespace ProtocolEx {
	// Void * pointer type.
	using ptr_t = void*;

	using ulong_t = unsigned long;

	using long_t = long;
}
