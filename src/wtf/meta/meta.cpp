//
// Created by guozhenxiong on 2021-11-06.
//
#include "meta.h"

#include <unordered_map>

namespace sm {
namespace meta {

int64_t MetaData::next_type_id = 1;

/// | static |
MetaData& MetaUnknown::GetMetaData(const std::string& name) {
    static std::unordered_map<std::string, std::unique_ptr<MetaData>> map;
    if (map.count(name) == 0)
        map[name] = std::make_unique<MetaData>();

    return *map[name];
}
} // namespace meta
} //namespace sm