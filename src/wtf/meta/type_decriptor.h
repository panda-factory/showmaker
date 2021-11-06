//
// Created by guozhenxiong on 2021-11-05.
//

#ifndef SHOWMAKER_TYPE_DECRIPTOR_H
#define SHOWMAKER_TYPE_DECRIPTOR_H

namespace sm {
namespace meta {

template<typename T>
class TypeDescriptor {
public:
    static std::string Descriptor() { return "<unknown>"; }
};

static std::string concat(std::initializer_list<std::string>&& strings)
{
    static const std::string space(" ");
    std::string result("<");
    for (auto& string : strings)
        result += (string + space);
    return result;
}

template<typename... A>
class VariadicTypeDescriptor {
public:
    static std::string Descriptor() { return concat({ TypeDescriptor<A>::Descriptor()... }); }
};

#define TYPE_DESCRIPTOR_MACRO(type) \
    template<> class sm::meta::TypeDescriptor<type> { \
    public: \
        static std::string Descriptor() { return #type; } \
    }

#define TYPE_DESCRIPTOR_MACRO_T(type, ...) \
    template<__VA_ARGS__> class sm::meta::TypeDescriptor<type<__VA_ARGS__>> { \
    public: \
        static std::string Descriptor() { static std::string str = std::string(#type) + VariadicTypeDescriptor<__VA_ARGS__>::Descriptor(); return str; } \
    }

#define TYPE_DESCRIPTOR_MACROIS_VOID(type)

#define TYPE_DESCRIBE_CLASSIS_VOID(type)

#define TYPE_DESCRIPTOR_MACROIS_PLAIN(type) TYPE_DESCRIPTOR_MACRO(type)

#define TYPE_DESCRIBE_CLASSIS_PLAIN(type)

#define TYPE_DESCRIPTOR(type, ...) \
    TYPE_DESCRIPTOR_MACRO(type); \
    TYPE_DESCRIPTOR_MACRO(type*); \
    TYPE_DESCRIPTOR_MACRO(const type*); \
    TYPE_DESCRIPTOR_MACRO##__VA_ARGS__(type&); \
    TYPE_DESCRIPTOR_MACRO##__VA_ARGS__(const type&)

#define TYPE_DESCRIPTOR_T(type, ...) \
    TYPE_DESCRIPTOR_MACRO_T(type, __VA_ARGS__);

template<typename>
class Meta;


} // namespace meta
} // namespace sm

TYPE_DESCRIPTOR(void, IS_VOID);
TYPE_DESCRIPTOR(int, IS_PLAIN);
TYPE_DESCRIPTOR(int64_t, IS_PLAIN);
TYPE_DESCRIPTOR(char, IS_PLAIN);
TYPE_DESCRIPTOR(int8_t, IS_PLAIN);
TYPE_DESCRIPTOR(short, IS_PLAIN);
TYPE_DESCRIPTOR(float, IS_PLAIN);
TYPE_DESCRIPTOR(double, IS_PLAIN);
TYPE_DESCRIPTOR(bool, IS_PLAIN);
TYPE_DESCRIPTOR(std::string, IS_PLAIN);

//TYPE_DESCRIPTOR_T(std::pair, typename T, typename U);
//TYPE_DESCRIPTOR_T(std::vector, typename T);
//TYPE_DESCRIPTOR_T(std::unique_ptr, typename T);
//TYPE_DESCRIPTOR_T(std::shared_ptr, typename T);
//TYPE_DESCRIPTOR_T(std::function, typename F);


#endif //SHOWMAKER_TYPE_DECRIPTOR_H
