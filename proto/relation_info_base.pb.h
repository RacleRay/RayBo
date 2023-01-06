// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: relation_info_base.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_relation_5finfo_5fbase_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_relation_5finfo_5fbase_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3020000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3020001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_relation_5finfo_5fbase_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_relation_5finfo_5fbase_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_relation_5finfo_5fbase_2eproto;
namespace raybo {
class RelationInfoBase;
struct RelationInfoBaseDefaultTypeInternal;
extern RelationInfoBaseDefaultTypeInternal _RelationInfoBase_default_instance_;
}  // namespace raybo
PROTOBUF_NAMESPACE_OPEN
template<> ::raybo::RelationInfoBase* Arena::CreateMaybeMessage<::raybo::RelationInfoBase>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace raybo {

// ===================================================================

class RelationInfoBase final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:raybo.RelationInfoBase) */ {
 public:
  inline RelationInfoBase() : RelationInfoBase(nullptr) {}
  ~RelationInfoBase() override;
  explicit PROTOBUF_CONSTEXPR RelationInfoBase(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  RelationInfoBase(const RelationInfoBase& from);
  RelationInfoBase(RelationInfoBase&& from) noexcept
    : RelationInfoBase() {
    *this = ::std::move(from);
  }

  inline RelationInfoBase& operator=(const RelationInfoBase& from) {
    CopyFrom(from);
    return *this;
  }
  inline RelationInfoBase& operator=(RelationInfoBase&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RelationInfoBase& default_instance() {
    return *internal_default_instance();
  }
  static inline const RelationInfoBase* internal_default_instance() {
    return reinterpret_cast<const RelationInfoBase*>(
               &_RelationInfoBase_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(RelationInfoBase& a, RelationInfoBase& b) {
    a.Swap(&b);
  }
  inline void Swap(RelationInfoBase* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RelationInfoBase* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  RelationInfoBase* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<RelationInfoBase>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const RelationInfoBase& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const RelationInfoBase& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RelationInfoBase* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "raybo.RelationInfoBase";
  }
  protected:
  explicit RelationInfoBase(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFriendListFieldNumber = 3,
    kBlackListFieldNumber = 4,
    kVerFieldNumber = 1,
    kUserIdFieldNumber = 2,
  };
  // repeated uint32 friend_list = 3;
  int friend_list_size() const;
  private:
  int _internal_friend_list_size() const;
  public:
  void clear_friend_list();
  private:
  uint32_t _internal_friend_list(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      _internal_friend_list() const;
  void _internal_add_friend_list(uint32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      _internal_mutable_friend_list();
  public:
  uint32_t friend_list(int index) const;
  void set_friend_list(int index, uint32_t value);
  void add_friend_list(uint32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      friend_list() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      mutable_friend_list();

  // repeated uint32 black_list = 4;
  int black_list_size() const;
  private:
  int _internal_black_list_size() const;
  public:
  void clear_black_list();
  private:
  uint32_t _internal_black_list(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      _internal_black_list() const;
  void _internal_add_black_list(uint32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      _internal_mutable_black_list();
  public:
  uint32_t black_list(int index) const;
  void set_black_list(int index, uint32_t value);
  void add_black_list(uint32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      black_list() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      mutable_black_list();

  // optional uint32 ver = 1;
  bool has_ver() const;
  private:
  bool _internal_has_ver() const;
  public:
  void clear_ver();
  uint32_t ver() const;
  void set_ver(uint32_t value);
  private:
  uint32_t _internal_ver() const;
  void _internal_set_ver(uint32_t value);
  public:

  // optional uint32 user_id = 2;
  bool has_user_id() const;
  private:
  bool _internal_has_user_id() const;
  public:
  void clear_user_id();
  uint32_t user_id() const;
  void set_user_id(uint32_t value);
  private:
  uint32_t _internal_user_id() const;
  void _internal_set_user_id(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:raybo.RelationInfoBase)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t > friend_list_;
    mutable std::atomic<int> _friend_list_cached_byte_size_;
    ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t > black_list_;
    mutable std::atomic<int> _black_list_cached_byte_size_;
    uint32_t ver_;
    uint32_t user_id_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_relation_5finfo_5fbase_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RelationInfoBase

// optional uint32 ver = 1;
inline bool RelationInfoBase::_internal_has_ver() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool RelationInfoBase::has_ver() const {
  return _internal_has_ver();
}
inline void RelationInfoBase::clear_ver() {
  _impl_.ver_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline uint32_t RelationInfoBase::_internal_ver() const {
  return _impl_.ver_;
}
inline uint32_t RelationInfoBase::ver() const {
  // @@protoc_insertion_point(field_get:raybo.RelationInfoBase.ver)
  return _internal_ver();
}
inline void RelationInfoBase::_internal_set_ver(uint32_t value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.ver_ = value;
}
inline void RelationInfoBase::set_ver(uint32_t value) {
  _internal_set_ver(value);
  // @@protoc_insertion_point(field_set:raybo.RelationInfoBase.ver)
}

// optional uint32 user_id = 2;
inline bool RelationInfoBase::_internal_has_user_id() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool RelationInfoBase::has_user_id() const {
  return _internal_has_user_id();
}
inline void RelationInfoBase::clear_user_id() {
  _impl_.user_id_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline uint32_t RelationInfoBase::_internal_user_id() const {
  return _impl_.user_id_;
}
inline uint32_t RelationInfoBase::user_id() const {
  // @@protoc_insertion_point(field_get:raybo.RelationInfoBase.user_id)
  return _internal_user_id();
}
inline void RelationInfoBase::_internal_set_user_id(uint32_t value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.user_id_ = value;
}
inline void RelationInfoBase::set_user_id(uint32_t value) {
  _internal_set_user_id(value);
  // @@protoc_insertion_point(field_set:raybo.RelationInfoBase.user_id)
}

// repeated uint32 friend_list = 3;
inline int RelationInfoBase::_internal_friend_list_size() const {
  return _impl_.friend_list_.size();
}
inline int RelationInfoBase::friend_list_size() const {
  return _internal_friend_list_size();
}
inline void RelationInfoBase::clear_friend_list() {
  _impl_.friend_list_.Clear();
}
inline uint32_t RelationInfoBase::_internal_friend_list(int index) const {
  return _impl_.friend_list_.Get(index);
}
inline uint32_t RelationInfoBase::friend_list(int index) const {
  // @@protoc_insertion_point(field_get:raybo.RelationInfoBase.friend_list)
  return _internal_friend_list(index);
}
inline void RelationInfoBase::set_friend_list(int index, uint32_t value) {
  _impl_.friend_list_.Set(index, value);
  // @@protoc_insertion_point(field_set:raybo.RelationInfoBase.friend_list)
}
inline void RelationInfoBase::_internal_add_friend_list(uint32_t value) {
  _impl_.friend_list_.Add(value);
}
inline void RelationInfoBase::add_friend_list(uint32_t value) {
  _internal_add_friend_list(value);
  // @@protoc_insertion_point(field_add:raybo.RelationInfoBase.friend_list)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
RelationInfoBase::_internal_friend_list() const {
  return _impl_.friend_list_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
RelationInfoBase::friend_list() const {
  // @@protoc_insertion_point(field_list:raybo.RelationInfoBase.friend_list)
  return _internal_friend_list();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
RelationInfoBase::_internal_mutable_friend_list() {
  return &_impl_.friend_list_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
RelationInfoBase::mutable_friend_list() {
  // @@protoc_insertion_point(field_mutable_list:raybo.RelationInfoBase.friend_list)
  return _internal_mutable_friend_list();
}

// repeated uint32 black_list = 4;
inline int RelationInfoBase::_internal_black_list_size() const {
  return _impl_.black_list_.size();
}
inline int RelationInfoBase::black_list_size() const {
  return _internal_black_list_size();
}
inline void RelationInfoBase::clear_black_list() {
  _impl_.black_list_.Clear();
}
inline uint32_t RelationInfoBase::_internal_black_list(int index) const {
  return _impl_.black_list_.Get(index);
}
inline uint32_t RelationInfoBase::black_list(int index) const {
  // @@protoc_insertion_point(field_get:raybo.RelationInfoBase.black_list)
  return _internal_black_list(index);
}
inline void RelationInfoBase::set_black_list(int index, uint32_t value) {
  _impl_.black_list_.Set(index, value);
  // @@protoc_insertion_point(field_set:raybo.RelationInfoBase.black_list)
}
inline void RelationInfoBase::_internal_add_black_list(uint32_t value) {
  _impl_.black_list_.Add(value);
}
inline void RelationInfoBase::add_black_list(uint32_t value) {
  _internal_add_black_list(value);
  // @@protoc_insertion_point(field_add:raybo.RelationInfoBase.black_list)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
RelationInfoBase::_internal_black_list() const {
  return _impl_.black_list_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
RelationInfoBase::black_list() const {
  // @@protoc_insertion_point(field_list:raybo.RelationInfoBase.black_list)
  return _internal_black_list();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
RelationInfoBase::_internal_mutable_black_list() {
  return &_impl_.black_list_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
RelationInfoBase::mutable_black_list() {
  // @@protoc_insertion_point(field_mutable_list:raybo.RelationInfoBase.black_list)
  return _internal_mutable_black_list();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace raybo

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_relation_5finfo_5fbase_2eproto
