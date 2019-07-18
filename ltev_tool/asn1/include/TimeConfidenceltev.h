/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LTEV"
 * 	found in "LTEV.asn"
 * 	`asn1c -fskeletons-copy -fnative-types -gen-PER -pdu=auto`
 */

#ifndef	_TimeConfidenceltev_H_
#define	_TimeConfidenceltev_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TimeConfidenceltev {
	TimeConfidenceltev_unavailable	= 0,
	TimeConfidenceltev_time_100_000	= 1,
	TimeConfidenceltev_time_050_000	= 2,
	TimeConfidenceltev_time_020_000	= 3,
	TimeConfidenceltev_time_010_000	= 4,
	TimeConfidenceltev_time_002_000	= 5,
	TimeConfidenceltev_time_001_000	= 6,
	TimeConfidenceltev_time_000_500	= 7,
	TimeConfidenceltev_time_000_200	= 8,
	TimeConfidenceltev_time_000_100	= 9,
	TimeConfidenceltev_time_000_050	= 10,
	TimeConfidenceltev_time_000_020	= 11,
	TimeConfidenceltev_time_000_010	= 12,
	TimeConfidenceltev_time_000_005	= 13,
	TimeConfidenceltev_time_000_002	= 14,
	TimeConfidenceltev_time_000_001	= 15,
	TimeConfidenceltev_time_000_000_5	= 16,
	TimeConfidenceltev_time_000_000_2	= 17,
	TimeConfidenceltev_time_000_000_1	= 18,
	TimeConfidenceltev_time_000_000_05	= 19,
	TimeConfidenceltev_time_000_000_02	= 20,
	TimeConfidenceltev_time_000_000_01	= 21,
	TimeConfidenceltev_time_000_000_005	= 22,
	TimeConfidenceltev_time_000_000_002	= 23,
	TimeConfidenceltev_time_000_000_001	= 24,
	TimeConfidenceltev_time_000_000_000_5	= 25,
	TimeConfidenceltev_time_000_000_000_2	= 26,
	TimeConfidenceltev_time_000_000_000_1	= 27,
	TimeConfidenceltev_time_000_000_000_05	= 28,
	TimeConfidenceltev_time_000_000_000_02	= 29,
	TimeConfidenceltev_time_000_000_000_01	= 30,
	TimeConfidenceltev_time_000_000_000_005	= 31,
	TimeConfidenceltev_time_000_000_000_002	= 32,
	TimeConfidenceltev_time_000_000_000_001	= 33,
	TimeConfidenceltev_time_000_000_000_000_5	= 34,
	TimeConfidenceltev_time_000_000_000_000_2	= 35,
	TimeConfidenceltev_time_000_000_000_000_1	= 36,
	TimeConfidenceltev_time_000_000_000_000_05	= 37,
	TimeConfidenceltev_time_000_000_000_000_02	= 38,
	TimeConfidenceltev_time_000_000_000_000_01	= 39
} e_TimeConfidenceltev;

/* TimeConfidenceltev */
typedef long	 TimeConfidenceltev_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_TimeConfidenceltev_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_TimeConfidenceltev;
extern const asn_INTEGER_specifics_t asn_SPC_TimeConfidenceltev_specs_1;
asn_struct_free_f TimeConfidenceltev_free;
asn_struct_print_f TimeConfidenceltev_print;
asn_constr_check_f TimeConfidenceltev_constraint;
ber_type_decoder_f TimeConfidenceltev_decode_ber;
der_type_encoder_f TimeConfidenceltev_encode_der;
xer_type_decoder_f TimeConfidenceltev_decode_xer;
xer_type_encoder_f TimeConfidenceltev_encode_xer;
oer_type_decoder_f TimeConfidenceltev_decode_oer;
oer_type_encoder_f TimeConfidenceltev_encode_oer;
per_type_decoder_f TimeConfidenceltev_decode_uper;
per_type_encoder_f TimeConfidenceltev_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TimeConfidenceltev_H_ */
#include <asn_internal.h>
