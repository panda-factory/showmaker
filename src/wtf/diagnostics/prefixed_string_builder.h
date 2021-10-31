//
// Created by guozhenxiong on 2021-10-31.
//

#ifndef SHOWMAKER_PREFIXED_STRING_BUILDER_H
#define SHOWMAKER_PREFIXED_STRING_BUILDER_H

#include <string>
#include <sstream>
#include <vector>

namespace sm {
class PrefixedStringBuilder {
public:
    std::string Build();

    void Write(std::string s, bool allow_wrap = false);

    void WriteStretched(std::string text, int targetLineLength);

    void WriteRawLines(std::string lines);

    void FinalizeLine(bool add_trailing_line_break);

    std::string GetCurrentPrefix(bool firstLine) {
        return buffer_.str().empty() ? prefix_line_one_ : prefix_other_lines_;
    }

    inline bool IsCurrentLineEmpty() { return current_line_.str().empty(); }

    void IncrementPrefixOtherLines(std::string suffix, bool updateCurrentLine);

    inline std::string& prefix_other_lines() { return next_prefix_other_lines_.empty() ? prefix_other_lines_ : next_prefix_other_lines_; }

    inline bool RequiresMultipleLines() {
        return num_lines > 1 ||
               (num_lines == 1 && !current_line_.str().empty()) ||
               (current_line_.str().size() + GetCurrentPrefix(true).size() > wrap_width_);
    }

    inline int wrap_width() { return wrap_width_; }

    PrefixedStringBuilder(std::string prefix_line_one,
                          std::string prefix_other_lines,
                          int wrap_width = -1);

private:
    static std::vector<std::string> WordWrapLine(std::string message, std::vector<int> wrap_ranges, int width, int startOffset = 0, int otherLineOffset = 0);

    void UpdatePrefix();

    void WriteLine(std::string line, bool include_line_break, bool firstLine);

    int wrap_width_ = -1;

    int num_lines = 0;

    std::vector<int> wrappable_ranges_;

    std::string next_prefix_other_lines_;

    std::string prefix_line_one_;

    std::string prefix_other_lines_;

    std::ostringstream current_line_;

    std::ostringstream buffer_;

private:
    enum class WordWrapParseMode {
        INSPACE,
        INWORD,
        ATBREAK
    };
};

} // namespace sm

#endif //SHOWMAKER_PREFIXED_STRING_BUILDER_H
