//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_DIAGNOSTIC_LEVEL_H
#define SHOWMAKER_DIAGNOSTIC_LEVEL_H

namespace sm {
enum class DiagnosticLevel {
    /// Diagnostics that should not be shown.
    ///
    /// If a user chooses to display [hidden] diagnostics, they should not expect
    /// the diagnostics to be formatted consistently with other diagnostics and
    /// they should expect them to sometimes be misleading. For example,
    /// [FlagProperty] and [ObjectFlagProperty] have uglier formatting when the
    /// property `value` does not match a value with a custom flag
    /// description. An example of a misleading diagnostic is a diagnostic for
    /// a property that has no effect because some other property of the object is
    /// set in a way that causes the hidden property to have no effect.
    HIDDEN,

    /// A diagnostic that is likely to be low value but where the diagnostic
    /// display is just as high quality as a diagnostic with a higher level.
    ///
    /// Use this level for diagnostic properties that match their default value
    /// and other cases where showing a diagnostic would not add much value such
    /// as an [IterableProperty] where the value is empty.
    FINE,

    /// Diagnostics that should only be shown when performing fine grained
    /// debugging of an object.
    ///
    /// Unlike a [fine] diagnostic, these diagnostics provide important
    /// information about the object that is likely to be needed to debug. Used by
    /// properties that are important but where the property value is too verbose
    /// (e.g. 300+ characters long) to show with a higher diagnostic level.
    DEBUG,

    /// Interesting diagnostics that should be typically shown.
    INFO,

    /// Very important diagnostics that indicate problematic property values.
    ///
    /// For example, use if you would write the property description
    /// message in ALL CAPS.
    WARNING,

    /// Diagnostics that provide a hint about best practices.
    ///
    /// For example, a diagnostic describing best practices for fixing an error.
    HINT,

    /// Diagnostics that summarize other diagnostics present.
    ///
    /// For example, use this level for a short one or two line summary
    /// describing other diagnostics present.
    SUMMARY,

    /// Diagnostics that indicate errors or unexpected conditions.
    ///
    /// For example, use for property values where computing the value throws an
    /// exception.
    ERROR,

    /// Special level indicating that no diagnostics should be shown.
    ///
    /// Do not specify this level for diagnostics. This level is only used to
    /// filter which diagnostics are shown.
    OFF,
};
} // namespace sm

#endif //SHOWMAKER_DIAGNOSTIC_LEVEL_H
