// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: trigger.proto

#ifndef PROTOBUF_INCLUDED_trigger_2eproto
#define PROTOBUF_INCLUDED_trigger_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3006001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_trigger_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_trigger_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[4]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_trigger_2eproto();
namespace trigger {
class Base;
class BaseDefaultTypeInternal;
extern BaseDefaultTypeInternal _Base_default_instance_;
class SnapMsg;
class SnapMsgDefaultTypeInternal;
extern SnapMsgDefaultTypeInternal _SnapMsg_default_instance_;
class SnapObj;
class SnapObjDefaultTypeInternal;
extern SnapObjDefaultTypeInternal _SnapObj_default_instance_;
class Timestamp;
class TimestampDefaultTypeInternal;
extern TimestampDefaultTypeInternal _Timestamp_default_instance_;
}  // namespace trigger
namespace google {
namespace protobuf {
template<> ::trigger::Base* Arena::CreateMaybeMessage<::trigger::Base>(Arena*);
template<> ::trigger::SnapMsg* Arena::CreateMaybeMessage<::trigger::SnapMsg>(Arena*);
template<> ::trigger::SnapObj* Arena::CreateMaybeMessage<::trigger::SnapObj>(Arena*);
template<> ::trigger::Timestamp* Arena::CreateMaybeMessage<::trigger::Timestamp>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace trigger {

enum ID {
  DEFAULT = 0,
  SNAP = 1
};
bool ID_IsValid(int value);
constexpr ID ID_MIN = DEFAULT;
constexpr ID ID_MAX = SNAP;
constexpr int ID_ARRAYSIZE = ID_MAX + 1;

const ::google::protobuf::EnumDescriptor* ID_descriptor();
inline const ::std::string& ID_Name(ID value) {
  return ::google::protobuf::internal::NameOfEnum(
    ID_descriptor(), value);
}
inline bool ID_Parse(
    const ::std::string& name, ID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ID>(
    ID_descriptor(), name, value);
}
// ===================================================================

class SnapObj final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:trigger.SnapObj) */ {
 public:
  SnapObj();
  virtual ~SnapObj();

  SnapObj(const SnapObj& from);

  inline SnapObj& operator=(const SnapObj& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  SnapObj(SnapObj&& from) noexcept
    : SnapObj() {
    *this = ::std::move(from);
  }

  inline SnapObj& operator=(SnapObj&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const SnapObj& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SnapObj* internal_default_instance() {
    return reinterpret_cast<const SnapObj*>(
               &_SnapObj_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(SnapObj* other);
  friend void swap(SnapObj& a, SnapObj& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SnapObj* New() const final {
    return CreateMaybeMessage<SnapObj>(nullptr);
  }

  SnapObj* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<SnapObj>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const SnapObj& from);
  void MergeFrom(const SnapObj& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SnapObj* other);
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::google::protobuf::StringPiece FullMessageName() {
    return "trigger.SnapObj";
  }
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 lng = 1;
  bool has_lng() const;
  void clear_lng();
  static const int kLngFieldNumber = 1;
  ::google::protobuf::int32 lng() const;
  void set_lng(::google::protobuf::int32 value);

  // required int32 lat = 2;
  bool has_lat() const;
  void clear_lat();
  static const int kLatFieldNumber = 2;
  ::google::protobuf::int32 lat() const;
  void set_lat(::google::protobuf::int32 value);

  // required int32 speed = 3;
  bool has_speed() const;
  void clear_speed();
  static const int kSpeedFieldNumber = 3;
  ::google::protobuf::int32 speed() const;
  void set_speed(::google::protobuf::int32 value);

  // required int32 camera = 4;
  bool has_camera() const;
  void clear_camera();
  static const int kCameraFieldNumber = 4;
  ::google::protobuf::int32 camera() const;
  void set_camera(::google::protobuf::int32 value);

  // required int32 type = 5;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 5;
  ::google::protobuf::int32 type() const;
  void set_type(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:trigger.SnapObj)
 private:
  class HasBitSetters;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 lng_;
  ::google::protobuf::int32 lat_;
  ::google::protobuf::int32 speed_;
  ::google::protobuf::int32 camera_;
  ::google::protobuf::int32 type_;
  friend struct ::TableStruct_trigger_2eproto;
};
// -------------------------------------------------------------------

class Timestamp final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:trigger.Timestamp) */ {
 public:
  Timestamp();
  virtual ~Timestamp();

  Timestamp(const Timestamp& from);

  inline Timestamp& operator=(const Timestamp& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Timestamp(Timestamp&& from) noexcept
    : Timestamp() {
    *this = ::std::move(from);
  }

  inline Timestamp& operator=(Timestamp&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Timestamp& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Timestamp* internal_default_instance() {
    return reinterpret_cast<const Timestamp*>(
               &_Timestamp_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Timestamp* other);
  friend void swap(Timestamp& a, Timestamp& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Timestamp* New() const final {
    return CreateMaybeMessage<Timestamp>(nullptr);
  }

  Timestamp* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Timestamp>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Timestamp& from);
  void MergeFrom(const Timestamp& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Timestamp* other);
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::google::protobuf::StringPiece FullMessageName() {
    return "trigger.Timestamp";
  }
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int64 seconds = 1;
  bool has_seconds() const;
  void clear_seconds();
  static const int kSecondsFieldNumber = 1;
  ::google::protobuf::int64 seconds() const;
  void set_seconds(::google::protobuf::int64 value);

  // required int32 nanos = 2;
  bool has_nanos() const;
  void clear_nanos();
  static const int kNanosFieldNumber = 2;
  ::google::protobuf::int32 nanos() const;
  void set_nanos(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:trigger.Timestamp)
 private:
  class HasBitSetters;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int64 seconds_;
  ::google::protobuf::int32 nanos_;
  friend struct ::TableStruct_trigger_2eproto;
};
// -------------------------------------------------------------------

class Base final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:trigger.Base) */ {
 public:
  Base();
  virtual ~Base();

  Base(const Base& from);

  inline Base& operator=(const Base& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Base(Base&& from) noexcept
    : Base() {
    *this = ::std::move(from);
  }

  inline Base& operator=(Base&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Base& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Base* internal_default_instance() {
    return reinterpret_cast<const Base*>(
               &_Base_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Base* other);
  friend void swap(Base& a, Base& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Base* New() const final {
    return CreateMaybeMessage<Base>(nullptr);
  }

  Base* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Base>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Base& from);
  void MergeFrom(const Base& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Base* other);
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::google::protobuf::StringPiece FullMessageName() {
    return "trigger.Base";
  }
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .trigger.ID id = 1;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::trigger::ID id() const;
  void set_id(::trigger::ID value);

  // @@protoc_insertion_point(class_scope:trigger.Base)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  int id_;
  friend struct ::TableStruct_trigger_2eproto;
};
// -------------------------------------------------------------------

class SnapMsg final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:trigger.SnapMsg) */ {
 public:
  SnapMsg();
  virtual ~SnapMsg();

  SnapMsg(const SnapMsg& from);

  inline SnapMsg& operator=(const SnapMsg& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  SnapMsg(SnapMsg&& from) noexcept
    : SnapMsg() {
    *this = ::std::move(from);
  }

  inline SnapMsg& operator=(SnapMsg&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const SnapMsg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SnapMsg* internal_default_instance() {
    return reinterpret_cast<const SnapMsg*>(
               &_SnapMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(SnapMsg* other);
  friend void swap(SnapMsg& a, SnapMsg& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SnapMsg* New() const final {
    return CreateMaybeMessage<SnapMsg>(nullptr);
  }

  SnapMsg* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<SnapMsg>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const SnapMsg& from);
  void MergeFrom(const SnapMsg& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SnapMsg* other);
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::google::protobuf::StringPiece FullMessageName() {
    return "trigger.SnapMsg";
  }
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .trigger.SnapObj array = 2;
  int array_size() const;
  void clear_array();
  static const int kArrayFieldNumber = 2;
  ::trigger::SnapObj* mutable_array(int index);
  ::google::protobuf::RepeatedPtrField< ::trigger::SnapObj >*
      mutable_array();
  const ::trigger::SnapObj& array(int index) const;
  ::trigger::SnapObj* add_array();
  const ::google::protobuf::RepeatedPtrField< ::trigger::SnapObj >&
      array() const;

  // required .trigger.Timestamp time = 3;
  bool has_time() const;
  void clear_time();
  static const int kTimeFieldNumber = 3;
  const ::trigger::Timestamp& time() const;
  ::trigger::Timestamp* release_time();
  ::trigger::Timestamp* mutable_time();
  void set_allocated_time(::trigger::Timestamp* time);

  // required .trigger.ID id = 1;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::trigger::ID id() const;
  void set_id(::trigger::ID value);

  // @@protoc_insertion_point(class_scope:trigger.SnapMsg)
 private:
  class HasBitSetters;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::trigger::SnapObj > array_;
  ::trigger::Timestamp* time_;
  int id_;
  friend struct ::TableStruct_trigger_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SnapObj

// required int32 lng = 1;
inline bool SnapObj::has_lng() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SnapObj::clear_lng() {
  lng_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::google::protobuf::int32 SnapObj::lng() const {
  // @@protoc_insertion_point(field_get:trigger.SnapObj.lng)
  return lng_;
}
inline void SnapObj::set_lng(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  lng_ = value;
  // @@protoc_insertion_point(field_set:trigger.SnapObj.lng)
}

// required int32 lat = 2;
inline bool SnapObj::has_lat() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SnapObj::clear_lat() {
  lat_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::google::protobuf::int32 SnapObj::lat() const {
  // @@protoc_insertion_point(field_get:trigger.SnapObj.lat)
  return lat_;
}
inline void SnapObj::set_lat(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  lat_ = value;
  // @@protoc_insertion_point(field_set:trigger.SnapObj.lat)
}

// required int32 speed = 3;
inline bool SnapObj::has_speed() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SnapObj::clear_speed() {
  speed_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::google::protobuf::int32 SnapObj::speed() const {
  // @@protoc_insertion_point(field_get:trigger.SnapObj.speed)
  return speed_;
}
inline void SnapObj::set_speed(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000004u;
  speed_ = value;
  // @@protoc_insertion_point(field_set:trigger.SnapObj.speed)
}

// required int32 camera = 4;
inline bool SnapObj::has_camera() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SnapObj::clear_camera() {
  camera_ = 0;
  _has_bits_[0] &= ~0x00000008u;
}
inline ::google::protobuf::int32 SnapObj::camera() const {
  // @@protoc_insertion_point(field_get:trigger.SnapObj.camera)
  return camera_;
}
inline void SnapObj::set_camera(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000008u;
  camera_ = value;
  // @@protoc_insertion_point(field_set:trigger.SnapObj.camera)
}

// required int32 type = 5;
inline bool SnapObj::has_type() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void SnapObj::clear_type() {
  type_ = 0;
  _has_bits_[0] &= ~0x00000010u;
}
inline ::google::protobuf::int32 SnapObj::type() const {
  // @@protoc_insertion_point(field_get:trigger.SnapObj.type)
  return type_;
}
inline void SnapObj::set_type(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000010u;
  type_ = value;
  // @@protoc_insertion_point(field_set:trigger.SnapObj.type)
}

// -------------------------------------------------------------------

// Timestamp

// required int64 seconds = 1;
inline bool Timestamp::has_seconds() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Timestamp::clear_seconds() {
  seconds_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000001u;
}
inline ::google::protobuf::int64 Timestamp::seconds() const {
  // @@protoc_insertion_point(field_get:trigger.Timestamp.seconds)
  return seconds_;
}
inline void Timestamp::set_seconds(::google::protobuf::int64 value) {
  _has_bits_[0] |= 0x00000001u;
  seconds_ = value;
  // @@protoc_insertion_point(field_set:trigger.Timestamp.seconds)
}

// required int32 nanos = 2;
inline bool Timestamp::has_nanos() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Timestamp::clear_nanos() {
  nanos_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::google::protobuf::int32 Timestamp::nanos() const {
  // @@protoc_insertion_point(field_get:trigger.Timestamp.nanos)
  return nanos_;
}
inline void Timestamp::set_nanos(::google::protobuf::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  nanos_ = value;
  // @@protoc_insertion_point(field_set:trigger.Timestamp.nanos)
}

// -------------------------------------------------------------------

// Base

// required .trigger.ID id = 1;
inline bool Base::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Base::clear_id() {
  id_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::trigger::ID Base::id() const {
  // @@protoc_insertion_point(field_get:trigger.Base.id)
  return static_cast< ::trigger::ID >(id_);
}
inline void Base::set_id(::trigger::ID value) {
  assert(::trigger::ID_IsValid(value));
  _has_bits_[0] |= 0x00000001u;
  id_ = value;
  // @@protoc_insertion_point(field_set:trigger.Base.id)
}

// -------------------------------------------------------------------

// SnapMsg

// required .trigger.ID id = 1;
inline bool SnapMsg::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SnapMsg::clear_id() {
  id_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::trigger::ID SnapMsg::id() const {
  // @@protoc_insertion_point(field_get:trigger.SnapMsg.id)
  return static_cast< ::trigger::ID >(id_);
}
inline void SnapMsg::set_id(::trigger::ID value) {
  assert(::trigger::ID_IsValid(value));
  _has_bits_[0] |= 0x00000002u;
  id_ = value;
  // @@protoc_insertion_point(field_set:trigger.SnapMsg.id)
}

// repeated .trigger.SnapObj array = 2;
inline int SnapMsg::array_size() const {
  return array_.size();
}
inline void SnapMsg::clear_array() {
  array_.Clear();
}
inline ::trigger::SnapObj* SnapMsg::mutable_array(int index) {
  // @@protoc_insertion_point(field_mutable:trigger.SnapMsg.array)
  return array_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::trigger::SnapObj >*
SnapMsg::mutable_array() {
  // @@protoc_insertion_point(field_mutable_list:trigger.SnapMsg.array)
  return &array_;
}
inline const ::trigger::SnapObj& SnapMsg::array(int index) const {
  // @@protoc_insertion_point(field_get:trigger.SnapMsg.array)
  return array_.Get(index);
}
inline ::trigger::SnapObj* SnapMsg::add_array() {
  // @@protoc_insertion_point(field_add:trigger.SnapMsg.array)
  return array_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::trigger::SnapObj >&
SnapMsg::array() const {
  // @@protoc_insertion_point(field_list:trigger.SnapMsg.array)
  return array_;
}

// required .trigger.Timestamp time = 3;
inline bool SnapMsg::has_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SnapMsg::clear_time() {
  if (time_ != nullptr) time_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::trigger::Timestamp& SnapMsg::time() const {
  const ::trigger::Timestamp* p = time_;
  // @@protoc_insertion_point(field_get:trigger.SnapMsg.time)
  return p != nullptr ? *p : *reinterpret_cast<const ::trigger::Timestamp*>(
      &::trigger::_Timestamp_default_instance_);
}
inline ::trigger::Timestamp* SnapMsg::release_time() {
  // @@protoc_insertion_point(field_release:trigger.SnapMsg.time)
  _has_bits_[0] &= ~0x00000001u;
  ::trigger::Timestamp* temp = time_;
  time_ = nullptr;
  return temp;
}
inline ::trigger::Timestamp* SnapMsg::mutable_time() {
  _has_bits_[0] |= 0x00000001u;
  if (time_ == nullptr) {
    auto* p = CreateMaybeMessage<::trigger::Timestamp>(GetArenaNoVirtual());
    time_ = p;
  }
  // @@protoc_insertion_point(field_mutable:trigger.SnapMsg.time)
  return time_;
}
inline void SnapMsg::set_allocated_time(::trigger::Timestamp* time) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete time_;
  }
  if (time) {
    ::google::protobuf::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      time = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, time, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  time_ = time;
  // @@protoc_insertion_point(field_set_allocated:trigger.SnapMsg.time)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace trigger

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::trigger::ID> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::trigger::ID>() {
  return ::trigger::ID_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_trigger_2eproto
