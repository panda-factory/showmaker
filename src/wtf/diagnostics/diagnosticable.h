//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_DIAGNOSTICABLE_H
#define SHOWMAKER_DIAGNOSTICABLE_H

#include "diagnostic_properties_builder.h"

namespace sm {
class Diagnosticable {
public:
protected:
    virtual void DebugFillProperties(DiagnosticPropertiesBuilder* properties) { }
private:
};
} // namespace sm

#endif //SHOWMAKER_DIAGNOSTICABLE_H
