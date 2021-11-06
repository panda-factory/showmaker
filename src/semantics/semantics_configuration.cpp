//
// Created by guozhenxiong on 2021-11-05.
//

#include "semantics_configuration.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {

void SemanticsConfiguration::SetIsSemanticBoundary(bool value)
{
    FML_CHECK(!is_merging_semantics_of_descendants || value);
    is_semantic_boundary_ = value;
}
} // namespace sm