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
    void* SafeCast() {
        return reinterpret_cast<void*>(this);
    }
};

/// ||

template<class T>
struct Traits {
    static T Cast(Meta* meta) {
        if (meta->HitMeta(T::GetMetaId()))
            return reinterpret_cast<T>(meta->SafeCast());

        //assert(false);
        return nullptr;
    }
};

template<bool>
struct MetaCertificate {
};

template<>
struct MetaCertificate<true> {
    static constexpr bool Registered() { return true; }
};

template<class T>
struct Traits<T*> {
    static T* Cast(Meta* meta) {
        MetaCertificate<std::is_same_v<T, typename T::Certificate>>::Registered();
        if (meta->HitMeta(T::GetMetaId()))
            return reinterpret_cast<T*>(meta->SafeCast());

        //assert(false);
        return nullptr;
    }
};


#define DECLARE_META_INFO(__sub_class, __base_class)                                \
public:                                                                             \
    static const std::string GetMetaName()                                          \
    {                                                                               \
        return #__sub_class;                                                        \
    }                                                                               \
    static meta::MetaIdType GetMetaId()                                             \
    {                                                                               \
        static meta::MetaIdType meta_id =                                           \
        std::hash<std::string> {}(GetMetaName());                                   \
        return meta_id;                                                             \
    }                                                                               \
    bool HitMeta(meta::MetaIdType meta_id) const override                           \
    {                                                                               \
        return __sub_class::GetMetaId() == meta_id ?                                \
                    true : __base_class::HitMeta(meta_id);                          \
    }                                                                               \
    typedef __sub_class Certificate;


} // namespace meta
} // namespace sm
#endif //SHOWMAKER_META_H
