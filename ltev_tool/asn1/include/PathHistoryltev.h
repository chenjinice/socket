/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LTEV"
 * 	found in "LTEV.asn"
 * 	`asn1c -fskeletons-copy -fnative-types -gen-PER -pdu=auto`
 */

#ifndef	_PathHistoryltev_H_
#define	_PathHistoryltev_H_


#include <asn_application.h>

/* Including external dependencies */
#include "GNSSstatus.h"
#include "PathHistoryPointList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct FullPositionVectorltev;

/* PathHistoryltev */
typedef struct PathHistoryltev {
	struct FullPositionVectorltev	*initialPosition	/* OPTIONAL */;
	GNSSstatus_t	*currGNSSstatus	/* OPTIONAL */;
	PathHistoryPointList_t	 crumbData;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PathHistoryltev_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PathHistoryltev;
extern asn_SEQUENCE_specifics_t asn_SPC_PathHistoryltev_specs_1;
extern asn_TYPE_member_t asn_MBR_PathHistoryltev_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "FullPositionVectorltev.h"

#endif	/* _PathHistoryltev_H_ */
#include <asn_internal.h>
