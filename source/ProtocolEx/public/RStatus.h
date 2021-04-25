#pragma once
/**
 * @file RStatus.h
 *
 * @brief Simple Result Status abstraction
 *
 * @author Balan Narcis
 * Contact: balannarcis96@gmail.com
 *
 */

namespace ProtocolEx {

#define CONCAT_(x,y) x##y
#define CONCAT(x,y) CONCAT_(x,y)

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

	enum class RStatus : int32_t {
		WorkRemains = -1,
		Success = 0,
		Fail = 1,
		Timedout = 2,
		AlreadyPerformed = 3,
		NotImplemented = 4,
		AcquireFailed = 5,
		ConnectionLost = 6,
		Aborted = 7,

		//Custom

		MAX
	};

	constexpr RStatus RSuccess{ RStatus::Success };
	constexpr RStatus RFail{ RStatus::Fail };
	constexpr RStatus RTimedout{ RStatus::Timedout };
	constexpr RStatus RNotImplemented{ RStatus::NotImplemented };
	constexpr RStatus RWorkRemains{ RStatus::WorkRemains };
	constexpr RStatus RAcquireFailed{ RStatus::AcquireFailed };
	constexpr RStatus RConnectionLost{ RStatus::ConnectionLost };
	constexpr RStatus RAborted{ RStatus::Aborted };

	inline bool operator!(const RStatus& Status) noexcept {
		return Status != RSuccess;
	}

//RTRY_SIMPLE
//If (expr == RFail) { 1.Build a detailed report 2.Return RFail }
#define R_TRY(expr)															\
					const RStatus CONCAT(RTryResult, __LINE__) = expr;		\
					if(0 != (int32_t)CONCAT(RTryResult, __LINE__)) {		\
						return RFail;										\
					} else

//RTRY_SIMPLE
//If (expr == RFail) { 1.Build a detailed report 2.Return [RFailStatus] }
#define RTRY_S(expr, RFailStatus)											\
					const RStatus CONCAT(RTryResult, __LINE__) = expr;		\
					if(0 != (int32_t)CONCAT(RTryResult, __LINE__)) {		\
						return RFailStatus;									\
					} else

//RTRY_SIMPLE_LAST_ERROR
//If (expr == RFail) { 1.Set LastError=[FailMessage] 2.Build a detailed report 3.Return [RFailStatus] }
#define RTRY_S_L(expr, RFailStatus, FailMessage)							\
					const RStatus CONCAT(RTryResult, __LINE__) = expr;		\
					if(0 != (int32_t)CONCAT(RTryResult, __LINE__)) {		\
						printf("Failed withMessage: %s", FailMessage);		\
						return RFailStatus;									\
					} else

//RTRY_LAST_ERROR
//If (expr == RFail) { 1.Set LastError=[FailMessage] 2.Build a detailed report 3.Return RFail }
#define RTRY_L(expr, FailMessage)											\
					const RStatus CONCAT(RTryResult, __LINE__) = expr;		\
					if(0 != (int32_t)CONCAT(RTryResult, __LINE__)) {		\
						printf("Failed withMessage: %s", FailMessage);		\
						return RFail;										\
					} else

//R_TRY_LAST_ERROR
//If (expr == RFail) { 1.Set LastError=[FailMessage] 2.Build a detailed report 3.Return given status }
#define R_TRY_L(expr, FailMessage)											\
					const RStatus CONCAT(RTryResult, __LINE__) = expr;		\
					if(0 != (int32_t)CONCAT(RTryResult, __LINE__)) {		\
						printf("Failed withMessage: %s", FailMessage);		\
						return CONCAT(RTryResult, __LINE__);				\
					} else

//RTRY_LAST_ERROR_FORMAT
//If (expr == RFail) { 1.Set LastError=[fmt(FailMessage, ...)] 2.Build a detailed report 3.Return RFail }
#define RTRY_L_FMT(expr, FailMessage, ...)									\
					const RStatus CONCAT(RTryResult, __LINE__) = expr;		\
					if(0 != (int32_t)CONCAT(RTryResult, __LINE__)) {		\
						printf("Failed withMessage: %s", FailMessage);		\
						return RFail;										\
					} else

//RTRY
//If (expr == RFail) { 1.Set LastError=[FailMessage] 2.Build a detailed report 3.Return [RFailStatus] }
#define RTRY(expr, FailMessage, RFailStatus)								\
					const RStatus CONCAT(RTryResult, __LINE__) = expr;		\
					if(0 != (int32_t)CONCAT(RTryResult, __LINE__)) {		\
						printf("Failed withMessage: %s", FailMessage);		\
						return RFailStatus;									\
					} else

//RTRY_FOMAT
//If (expr == RFail) { 1.Set LastError=[fmt(FailMessage, ...)] 2.Build a detailed report 3.Return [RFailStatus] }
#define RTRY_FMT(expr, FailMessage, RFailStatus, ...)						\
					const RStatus CONCAT(RTryResult, __LINE__) = expr;		\
					if(0 != (int32_t)CONCAT(RTryResult, __LINE__)) {		\
						printf("Failed withMessage: %s", FailMessage);		\
						return RFailStatus;									\
					} else

}