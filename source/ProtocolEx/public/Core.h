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
#include <string_view>
#include <cstdint>
#include <type_traits>

#define PROTOCOLEX_STATISTICS

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


	//Read macros
#define r_8	(_raw)		( *reinterpret_cast<int8_t*>	(_raw) )
#define r_u8(_raw)		( *reinterpret_cast<uint8_t*>	(_raw) )
#define r_16(_raw)		( *reinterpret_cast<int16_t*>	(_raw) )
#define r_u16(_raw)		( *reinterpret_cast<uint16_t*>	(_raw) )
#define r_32(_raw)		( *reinterpret_cast<int32_t*>	(_raw) )
#define r_u32(_raw)		( *reinterpret_cast<uint32_t*>	(_raw) )
#define r_64(_raw)		( *reinterpret_cast<int64_t*>	(_raw) )
#define r_u64(_raw)		( *reinterpret_cast<uint64_t*>	(_raw) )
#define r_single(_raw)	( *reinterpret_cast<float*>		(_raw) )
#define r_double(_raw)	( *reinterpret_cast<double*>	(_raw) )

	//Write macros
#define w_8	(_raw, data)		( *(reinterpret_cast<int8_t*>	(_raw))	= (data) )
#define w_u8(_raw, data)		( *(reinterpret_cast<uint8_t*>	(_raw))	= (data) )
#define w_16(_raw, data)		( *(reinterpret_cast<int16_t*>	(_raw))	= (data) )
#define w_u16(_raw, data)		( *(reinterpret_cast<uint16_t*>	(_raw))	= (data) )
#define w_32(_raw, data)		( *(reinterpret_cast<int32_t*>	(_raw))	= (data) )
#define w_u32(_raw, data)		( *(reinterpret_cast<uint32_t*>	(_raw))	= (data) )
#define w_64(_raw, data)		( *(reinterpret_cast<int64_t*>	(_raw))	= (data) )
#define w_u64(_raw, data)		( *(reinterpret_cast<uint64_t*>	(_raw))	= (data) )
#define w_single(_raw, data)	( *(reinterpret_cast<float*>	(_raw))	= (data) )
#define w_double(_raw, data)	( *(reinterpret_cast<double*>	(_raw))	= (data) )

	struct SGUID {
		union {
			uint32_t Value;
			struct {
				uint8_t  B1;
				uint8_t  B2;
				uint8_t  B3;
				uint8_t  B4;
			};
		};

		SGUID() noexcept : Value{ 0 } {}
		SGUID(const SGUID& Other) noexcept : Value{ Other.Value } {}
		SGUID(uint32_t Value) noexcept : Value{ Value } {}

		void operator=(const SGUID& Other) { Value = Other.Value; }

		inline static SGUID New() noexcept {
			SGUID SGuid;

			SGuid.B1 = (uint8_t)(std::rand() % UINT8_MAX);
			SGuid.B2 = (uint8_t)(std::rand() % UINT8_MAX);
			SGuid.B3 = (uint8_t)(std::rand() % UINT8_MAX);
			SGuid.B4 = (uint8_t)(std::rand() % UINT8_MAX);

			return SGuid;
		}
		inline static SGUID NewSimple() noexcept{
			return (uint32_t)(std::rand() % LONG_MAX);
		}

		const bool IsNone() const {
			return Value == None.Value;
		}
		const bool operator==(const SGUID Other) const noexcept {
			return Value == Other.Value;
		}
		const bool operator!=(const SGUID Other) const noexcept {
			return Value != Other.Value;
		}

		inline uint32_t GetRaw() const noexcept {
			return Value;
		}

		static const SGUID None;
	};
}
