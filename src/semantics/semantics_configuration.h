//
// Created by guozhenxiong on 2021-11-05.
//

#ifndef SHOWMAKER_SEMANTICS_CONFIGURATION_H
#define SHOWMAKER_SEMANTICS_CONFIGURATION_H

namespace sm {
class SemanticsConfiguration {
public:
    void SetIsSemanticBoundary(bool value);

private:
    bool is_semantic_boundary_ = false;

    bool is_merging_semantics_of_descendants = false;
};
} // namespace sm

#endif //SHOWMAKER_SEMANTICS_CONFIGURATION_H
