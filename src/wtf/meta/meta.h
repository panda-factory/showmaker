//
// Created by guozhenxiong on 2021-11-06.
//

#ifndef SHOWMAKER_META_H
#define SHOWMAKER_META_H

#include <assert.h>

#include "meta_value.h"

namespace sm {
namespace meta {

using MetaIdType = decltype(std::hash<std::string>{}(""));

class Meta {
public:
    virtual bool HitMeta(MetaIdType meta_id) const {
        return false;
    }
    virtual void* SafeCastById(MetaIdType meta_id) {
        return nullptr;
    }
    typedef Meta Certificate;
};

/// ||

template<bool>
struct MetaCertificate {
};

template<>
struct MetaCertificate<true> {
    static constexpr bool Registered() { return true; }
};

#define VERIFY_META_CERTIFICATE(__T) \
    meta::MetaCertificate<std::is_same_v<__T, typename __T::Certificate>>::Registered()

template<class T>
struct Traits {
    static T Cast(Meta* meta) {
        if (meta->HitMeta(T::GetMetaId()))
            return reinterpret_cast<T>(meta->SafeCastById(T::GetMetaId()));

        //assert(false);
        return nullptr;
    }
};

template<class T>
struct Traits<T*> {
    static T* Cast(Meta* meta) {
        VERIFY_META_CERTIFICATE(T);
        return reinterpret_cast<T*>(meta->SafeCastById(T::GetMetaId()));
    }
};


#define DECLARE_META_INFO(__sub_class, ...)                                                         \
public:                                                                                             \
    static const std::string GetMetaName()                                                          \
    {                                                                                               \
        return #__sub_class;                                                                        \
    }                                                                                               \
    static meta::MetaIdType GetMetaId()                                                             \
    {                                                                                               \
        static meta::MetaIdType meta_id =                                                           \
        std::hash<std::string> {}(GetMetaName());                                                   \
        return meta_id;                                                                             \
    }                                                                                               \
    template<class T, class U, class... V>                                                          \
    void* TrySafeCastById(meta::MetaIdType meta_id)                                                 \
    {                                                                                               \
        VERIFY_META_CERTIFICATE(T);                                                                 \
        void* ptr = T::SafeCastById(meta_id);                                                       \
        return ptr != nullptr ? ptr : TrySafeCastById<U, V...>(meta_id);                            \
    }                                                                                               \
    template<class T>                                                                               \
    void* TrySafeCastById(meta::MetaIdType meta_id)                                                 \
    {                                                                                               \
        VERIFY_META_CERTIFICATE(T);                                                                 \
        return T::SafeCastById(meta_id);                                                            \
    }                                                                                               \
    void* SafeCastById(meta::MetaIdType meta_id) override {                                         \
        return __sub_class::GetMetaId() == meta_id ?                                                \
                    reinterpret_cast<void*>(this) : TrySafeCastById<__VA_ARGS__>(meta_id);          \
    }                                                                                               \
    typedef __sub_class Certificate;


} // namespace meta
} // namespace sm
#endif //SHOWMAKER_META_H
