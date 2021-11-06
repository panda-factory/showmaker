//
// Created by guozhenxiong on 2021-11-06.
//

#ifndef SHOWMAKER_META_VALUE_H
#define SHOWMAKER_META_VALUE_H

#include <sstream>

namespace sm {
namespace meta {

template<typename T>
struct TypeValueTraits {
    typedef typename std::remove_cv<typename std::remove_reference<typename T>::type>::type base_type;
};

} // namespace meta
} // namespace sm
#endif //SHOWMAKER_META_VALUE_H
