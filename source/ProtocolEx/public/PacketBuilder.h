#pragma once
/**
 * @file PacketBuilder.h
 *
 * @brief ProtocolEx PacketBuilder abstractions
 *
 * @author Balan Narcis
 * Contact: balannarcis96@gmail.com
 *
 */

namespace ProtocolEx {

	using PacketContextFlags = uint64_t;
	using TPacketCount = uint16_t;

	enum EPacketContextFlags : PacketContextFlags {
		EPacketContextFlags_FixedLength = 1 << 0,
		EPacketContextFlags_WriteHeader = 1 << 1,
		EPacketContextFlags_List = 1 << 2,
		EPacketContextFlags_Routed = 1 << 3,
	};

	constexpr PacketContextFlags CDefaultPacketContextFlags = EPacketContextFlags_WriteHeader;

	constexpr auto CPacketContextWriteIgnore = 0;
	constexpr auto CPacketContextFirstItem = 1;
	constexpr auto CPacketContextLastItem = 1;

	consteval bool PacketContextHasFlag(const PacketContextFlags Flags, const PacketContextFlags TestFlags) {
		return (Flags & TestFlags) == TestFlags;
	}


	/*------------------------------------------------------------
		Packet context base class
	  ------------------------------------------------------------*/
	template<
		typename Super, 
		typename PacketData, 
		size_t _PacketBaseSize, 
		PacketContextFlags _Flags = CDefaultPacketContextFlags, 
		TPacketOpcode _Opcode = PacketData::Opcode>
	struct PacketContext {

#pragma region Type traits

		using PacketContextType = PacketContext<Super, PacketData, _PacketBaseSize, _Flags, _Opcode>;
		using PacketDataType = PacketData;

		static const size_t	PacketBaseSize = _PacketBaseSize;
		static const PacketContextFlags	Flags = _Flags;
		static const TPacketOpcode Opcode = _Opcode;

#pragma endregion

		static_assert(std::is_base_of_v<PacketBaseTag, PacketData>, "ProtocolEx:PacketContext<> PacketData must be a derived class of [InternalPacketBodyBase] or [PacketDataBase]");

		EntityId	TargetConnectionId = EntityId::None;
		PacketData	Data;

		inline PacketData* operator->()noexcept {
			return &Data;
		}

		inline size_t GetPacketSize() const noexcept {
			return ((Super*)this)->GetPacketSize();
		}

		inline RStatus BuildPacket(TStream& Stream) const noexcept {
			if constexpr (PacketContextHasFlag(Flags, P_CONTEXT_WRITE_HEADER)) {
				WritePacketHead(Stream);
			}

			return ((Super*)this)->BuildPacket(Stream);
		}

		inline RStatus BuildPacketOnly(TStream& Stream) const noexcept {
			return ((Super*)this)->BuildPacket(Stream);
		}

	protected:
		inline void WritePacketHead(TStream& Stream) const noexcept {
			Stream.Write((TPacketSize)0); //Size placeholder
			Stream.Write((TPacketOpcode)Opcode); //Opcode
		}
	};


}