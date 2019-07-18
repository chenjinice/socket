/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LTEV"
 * 	found in "LTEV.asn"
 * 	`asn1c -fskeletons-copy -fnative-types -gen-PER -pdu=auto`
 */

#ifndef	_PositionOffsetLLV_H_
#define	_PositionOffsetLLV_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PositionOffsetLL.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct VerticalOffset;

/* PositionOffsetLLV */
typedef struct PositionOffsetLLV {
	PositionOffsetLL_t	 offsetLL;
	struct VerticalOffset	*offsetV	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PositionOffsetLLV_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PositionOffsetLLV;
extern asn_SEQUENCE_specifics_t asn_SPC_PositionOffsetLLV_specs_1;
extern asn_TYPE_member_t asn_MBR_PositionOffsetLLV_1[2];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "VerticalOffset.h"

#endif	/* _PositionOffsetLLV_H_ */
#include <asn_internal.h>
