#pragma once 
/**
 * @file Packet.h
 *
 * @brief ProtocolEx Packet abstraction
 *
 * @author Balan Narcis
 * Contact: balannarcis96@gmail.com
 *
 */

namespace ProtocolEx {

	//Packet opcode value type
	using TPacketOpcode = uint16_t;

	//Packet size value type
	using TPacketSize = uint16_t;

	//Packet offset value type
	using TPacketOffset = uint16_t;

	//Packet string offset value type
	using TPacketStringOffset = TPacketOffset;

	//Packet header type
	struct TPacketHeader {
		TPacketSize		Size;
		TPacketOpcode	Opcode;
	};

	//Header struct for array of objects inside the packet
	struct TPacketObjectArrayHeader {
		TPacketSize		Count;
		TPacketOffset	Offset;
	};

	using TPacketStringRef = TPacketObjectArrayHeader;

	template<typename T>
	struct TPacketArrayItem {
		TPacketOffset	OffsetToBase;
		TPacketOffset	OffsetToNext;
		T				Item;

		inline T& operator->() noexcept {
			return Item;
		}
	};

	constexpr auto CPacketHeaderSize = sizeof(TPacketHeader);

	/*------------------------------------------------------------
		PacketBodyBase (Base for all packet types)
	  ------------------------------------------------------------*/

	template<TPacketOpcode PacketOpcode, bool _HasWriteMethod = false>
	struct PacketBodyBase {
		static const TPacketOpcode Opcode = PacketOpcode;
		static const bool HasWriteMethod = _HasWriteMethod;
		static const bool IsInternal = !CheckIntegrity;

		//Important: Offset value must be packet based not body based
		inline const uint8_t* GetRaw(uint16_t Offset = 0) const noexcept {
			//Little bit of branchless programming :D
			return (((uint8_t*)this) + (Offset - (CPacketHeaderSize * (Offset != 0))));
		}

		inline uint8_t* GetRaw(uint16_t Offset = 0)  noexcept {
			//Little bit of branchless programming :D
			return (((uint8_t*)this) + (Offset - (CPacketHeaderSize * (Offset != 0))));
		}

		//Important: Offset value must be packet based not body based
		template<typename T>
		inline T* GetRaw(uint16_t Offset = 0) noexcept {
			return reinterpret_cast<T*>(GetRaw(Offset));
		}

		//Important: Offset value must be packet based not body based
		template<typename T>
		inline const T* GetRaw(uint16_t Offset = 0) const noexcept {
			return reinterpret_cast<const T*>(GetRaw(Offset));
		}

		//Important: Offset value must be packet based not body based
		template<typename T>
		inline const TPacketArrayItem<T>* GetArray(uint16_t Offset = 0) const noexcept {
			return GetRaw<TPacketArrayItem<T>>(Offset);
		}

		inline RStream GetStream(size_t PacketSize) noexcept {
			return RStream((uint8_t*)GetRaw<uint8_t>(), (int64_t)PacketSize, (int64_t)0);
		}
	};
}