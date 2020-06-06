/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: obu_faw.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "obu_faw.pb-c.h"
void   obu_faw__obu_motion__init
                     (ObuFaw__ObuMotion         *message)
{
  static const ObuFaw__ObuMotion init_value = OBU_FAW__OBU_MOTION__INIT;
  *message = init_value;
}
size_t obu_faw__obu_motion__get_packed_size
                     (const ObuFaw__ObuMotion *message)
{
  assert(message->base.descriptor == &obu_faw__obu_motion__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t obu_faw__obu_motion__pack
                     (const ObuFaw__ObuMotion *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &obu_faw__obu_motion__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t obu_faw__obu_motion__pack_to_buffer
                     (const ObuFaw__ObuMotion *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &obu_faw__obu_motion__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ObuFaw__ObuMotion *
       obu_faw__obu_motion__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ObuFaw__ObuMotion *)
     protobuf_c_message_unpack (&obu_faw__obu_motion__descriptor,
                                allocator, len, data);
}
void   obu_faw__obu_motion__free_unpacked
                     (ObuFaw__ObuMotion *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &obu_faw__obu_motion__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   obu_faw__can_info__init
                     (ObuFaw__CanInfo         *message)
{
  static const ObuFaw__CanInfo init_value = OBU_FAW__CAN_INFO__INIT;
  *message = init_value;
}
size_t obu_faw__can_info__get_packed_size
                     (const ObuFaw__CanInfo *message)
{
  assert(message->base.descriptor == &obu_faw__can_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t obu_faw__can_info__pack
                     (const ObuFaw__CanInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &obu_faw__can_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t obu_faw__can_info__pack_to_buffer
                     (const ObuFaw__CanInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &obu_faw__can_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ObuFaw__CanInfo *
       obu_faw__can_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ObuFaw__CanInfo *)
     protobuf_c_message_unpack (&obu_faw__can_info__descriptor,
                                allocator, len, data);
}
void   obu_faw__can_info__free_unpacked
                     (ObuFaw__CanInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &obu_faw__can_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   obu_faw__msg__init
                     (ObuFaw__Msg         *message)
{
  static const ObuFaw__Msg init_value = OBU_FAW__MSG__INIT;
  *message = init_value;
}
size_t obu_faw__msg__get_packed_size
                     (const ObuFaw__Msg *message)
{
  assert(message->base.descriptor == &obu_faw__msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t obu_faw__msg__pack
                     (const ObuFaw__Msg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &obu_faw__msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t obu_faw__msg__pack_to_buffer
                     (const ObuFaw__Msg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &obu_faw__msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ObuFaw__Msg *
       obu_faw__msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ObuFaw__Msg *)
     protobuf_c_message_unpack (&obu_faw__msg__descriptor,
                                allocator, len, data);
}
void   obu_faw__msg__free_unpacked
                     (ObuFaw__Msg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &obu_faw__msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor obu_faw__obu_motion__field_descriptors[9] =
{
  {
    "msgcount",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, msgcount),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "longitude",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, longitude),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "latitude",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, latitude),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "heading",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, heading),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "speed",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, speed),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "acc",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_DOUBLE,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, acc),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "devID",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, devid),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "gpsTime",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, gpstime),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "altitude",
    9,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_DOUBLE,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__ObuMotion, altitude),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned obu_faw__obu_motion__field_indices_by_name[] = {
  5,   /* field[5] = acc */
  8,   /* field[8] = altitude */
  6,   /* field[6] = devID */
  7,   /* field[7] = gpsTime */
  3,   /* field[3] = heading */
  2,   /* field[2] = latitude */
  1,   /* field[1] = longitude */
  0,   /* field[0] = msgcount */
  4,   /* field[4] = speed */
};
static const ProtobufCIntRange obu_faw__obu_motion__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 9 }
};
const ProtobufCMessageDescriptor obu_faw__obu_motion__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "obuFaw.ObuMotion",
  "ObuMotion",
  "ObuFaw__ObuMotion",
  "obuFaw",
  sizeof(ObuFaw__ObuMotion),
  9,
  obu_faw__obu_motion__field_descriptors,
  obu_faw__obu_motion__field_indices_by_name,
  1,  obu_faw__obu_motion__number_ranges,
  (ProtobufCMessageInit) obu_faw__obu_motion__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor obu_faw__can_info__field_descriptors[16] =
{
  {
    "msgcount",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, msgcount),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "devID",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, devid),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "trunLight",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, trunlight),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "hazardLight",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, hazardlight),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "brakeState",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, brakestate),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "gasStatus",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, gasstatus),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "gearState",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, gearstate),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "wheelAngle",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_DOUBLE,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, wheelangle),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "driveState",
    9,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, drivestate),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "abnormalState",
    10,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, abnormalstate),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "gpsTime",
    11,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, gpstime),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "longitude",
    12,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, longitude),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "latitude",
    13,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, latitude),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "altitude",
    14,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_DOUBLE,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, altitude),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "speed",
    15,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, speed),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "heading",
    16,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(ObuFaw__CanInfo, heading),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned obu_faw__can_info__field_indices_by_name[] = {
  9,   /* field[9] = abnormalState */
  13,   /* field[13] = altitude */
  4,   /* field[4] = brakeState */
  1,   /* field[1] = devID */
  8,   /* field[8] = driveState */
  5,   /* field[5] = gasStatus */
  6,   /* field[6] = gearState */
  10,   /* field[10] = gpsTime */
  3,   /* field[3] = hazardLight */
  15,   /* field[15] = heading */
  12,   /* field[12] = latitude */
  11,   /* field[11] = longitude */
  0,   /* field[0] = msgcount */
  14,   /* field[14] = speed */
  2,   /* field[2] = trunLight */
  7,   /* field[7] = wheelAngle */
};
static const ProtobufCIntRange obu_faw__can_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 16 }
};
const ProtobufCMessageDescriptor obu_faw__can_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "obuFaw.CanInfo",
  "CanInfo",
  "ObuFaw__CanInfo",
  "obuFaw",
  sizeof(ObuFaw__CanInfo),
  16,
  obu_faw__can_info__field_descriptors,
  obu_faw__can_info__field_indices_by_name,
  1,  obu_faw__can_info__number_ranges,
  (ProtobufCMessageInit) obu_faw__can_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor obu_faw__msg__field_descriptors[2] =
{
  {
    "motion",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(ObuFaw__Msg, m_case),
    offsetof(ObuFaw__Msg, motion),
    &obu_faw__obu_motion__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "can",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(ObuFaw__Msg, m_case),
    offsetof(ObuFaw__Msg, can),
    &obu_faw__can_info__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned obu_faw__msg__field_indices_by_name[] = {
  1,   /* field[1] = can */
  0,   /* field[0] = motion */
};
static const ProtobufCIntRange obu_faw__msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor obu_faw__msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "obuFaw.Msg",
  "Msg",
  "ObuFaw__Msg",
  "obuFaw",
  sizeof(ObuFaw__Msg),
  2,
  obu_faw__msg__field_descriptors,
  obu_faw__msg__field_indices_by_name,
  1,  obu_faw__msg__number_ranges,
  (ProtobufCMessageInit) obu_faw__msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};