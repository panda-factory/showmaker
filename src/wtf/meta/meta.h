//
// Created by guozhenxiong on 2021-11-06.
//

#ifndef SHOWMAKER_META_H
#define SHOWMAKER_META_H

#include <assert.h>

#include "meta_value.h"

namespace sm {
namespace meta {

template<class>
class Meta;

/// | MetaData |
class MetaData {
    template<typename> friend class MetaBase;
public:
    MetaData() : type_id_(next_type_id++) { }

private:
    static int64_t next_type_id;
    int64_t type_id_;
};

/// | MetaUnknown |
class MetaUnknown {
public:
    virtual std::string GetMetaName() const = 0;

    bool IsAssignableFrom(const MetaUnknown& other) const {
        if (GetTypeId() == other.GetTypeId())
            return true;
        return false;
    }

    uintptr_t SafeCast() {
        return reinterpret_cast<uintptr_t>(this);
    }

protected:
    static MetaData& GetMetaData(const std::string& name);

    virtual int64_t GetTypeId() const = 0;
};

/// | MetaBase |
template<typename T>
class MetaBase : public MetaUnknown {
protected:
    MetaBase() {
        if (!MetaBase::shared_data)
            MetaBase::shared_data = &MetaUnknown::GetMetaData(TypeDescriptor<T>::Descriptor());
    }
private:
    static MetaData* shared_data;

    int64_t GetTypeId() const override {
        return shared_data->type_id_;
    }
};

template<typename T>
MetaData* MetaBase<T>::shared_data;

/// | Meta |
template<typename T, bool is_pointer, bool is_reference>
struct remove_const_if_helper {
    typedef T type;
};

template<typename T>
struct remove_const_if_helper<T, false, false> {
    typedef typename std::remove_cv<T>::type type;
};

template<typename T>
struct remove_const_if : public remove_const_if_helper<T, std::is_pointer<T>::value, std::is_reference<T>::value> { };

template<typename T>
Meta<T>& GetMeta()
{
    static bool initialized = false;
    static std::unique_ptr<Meta<T>> singleton;
    if (!initialized) {
        initialized = true;
        singleton = std::make_unique<Meta<T>>();
    }
    return *singleton;
}

template<class T>
class Meta : public MetaBase<typename TypeValueTraits<T>::base_type> {
    friend T;
public:
    Meta() {
        meta::GetMeta<T>();
    }

    std::string GetMetaName() const override { return TypeDescriptor<typename remove_const_if<T>::type>::Descriptor(); }
};

/// ||

template<class T>
T MetaCase(MetaUnknown* meta) {
    if (!meta::GetMeta<T>().IsAssignableFrom(*meta)) {
        assert(false);
    }

    return reinterpret_cast<T>(meta->SafeCast());
}

} // namespace meta
} // namespace sm
#endif //SHOWMAKER_META_H
