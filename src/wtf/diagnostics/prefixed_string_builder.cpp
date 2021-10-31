//
// Created by guozhenxiong on 2021-10-31.
//

#include "prefixed_string_builder.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {

namespace {
static inline std::vector<std::string> Split(const std::string& src, const std::string& token)
{
    size_t nend = 0;
    size_t nbegin = 0;
    size_t tokenSize = token.size();
    std::vector<std::string> vect;
    while(nend != std::string::npos)
    {
        nend = src.find(token, nbegin);
        if(nend == std::string::npos)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + tokenSize;
    }
    return std::move(vect);
}
}


/// | static |
std::vector<std::string> PrefixedStringBuilder::WordWrapLine(std::string message,
                                         std::vector<int> wrap_ranges,
                                         int width,
                                         int start_offset,
                                         int other_line_offset)
{
    std::vector<std::string> result;
    if (message.size() + start_offset < width) {
        // Nothing to do. The line doesn't wrap.
        return result;
    }
    int startForLengthCalculations = -start_offset;
    bool addPrefix = false;
    int index = 0;
    WordWrapParseMode mode = WordWrapParseMode::INSPACE;
    int lastWordStart;
    int lastWordEnd = -1;
    int start = 0;

    int currentChunk = 0;

    auto noWrap = [&] (int index) ->bool {
        while (true) {
            if (currentChunk >= wrap_ranges.size())
                return true;

            if (index < wrap_ranges[currentChunk + 1])
                break; // Found nearest chunk.
            currentChunk+= 2;
        }
        return index < wrap_ranges[currentChunk];
    };

    while (true) {
        switch (mode) {
            case WordWrapParseMode::INSPACE: // at start of break point (or start of line); can't break until next break
                while ((index < message.size()) && (message[index] == ' '))
                    index += 1;
                lastWordStart = index;
                mode = WordWrapParseMode::INWORD;
                break;
            case WordWrapParseMode::INWORD: // looking for a good break point. Treat all text
                while ((index < message.size()) && (message[index] != ' ' || noWrap(index)))
                    index += 1;
                mode = WordWrapParseMode::ATBREAK;
                break;
            case WordWrapParseMode::ATBREAK: // at start of break point
                if ((index - startForLengthCalculations > width) || (index == message.size())) {
                    // we are over the width line, so break
                    if ((index - startForLengthCalculations <= width) || (lastWordEnd == -1)) {
                        // we should use this point, because either it doesn't actually go over the
                        // end (last line), or it does, but there was no earlier break point
                        lastWordEnd = index;
                    }
                    std::string line = message.substr(start, lastWordEnd);
                    result.emplace_back(line);
                    addPrefix = true;
                    if (lastWordEnd >= message.size()) {
                        return result;
                    }
                    // just yielded a line
                    if (lastWordEnd == index) {
                        // we broke at current position
                        // eat all the wrappable spaces, then set our start point
                        // Even if some of the spaces are not wrappable that is ok.
                        while ((index < message.size()) && (message[index] == ' '))
                            index += 1;
                        start = index;
                        mode = WordWrapParseMode::INWORD;
                    } else {
                        // we broke at the previous break point, and we're at the start of a new one
                        FML_CHECK(lastWordStart > lastWordEnd);
                        start = lastWordStart;
                        mode = WordWrapParseMode::ATBREAK;
                    }
                    startForLengthCalculations = start - other_line_offset;
                    FML_CHECK(addPrefix);
                    lastWordEnd = -1;
                } else {
                    // save this break point, we're not yet over the line width
                    lastWordEnd = index;
                    // skip to the end of this break point
                    mode = WordWrapParseMode::INSPACE;
                }
                break;
        }
    }
}


PrefixedStringBuilder::PrefixedStringBuilder(std::string prefix_line_one,
                                             std::string prefix_other_lines,
                                             int wrap_width)
  : prefix_line_one_(prefix_line_one), prefix_other_lines_(prefix_other_lines), wrap_width_(wrap_width)
{}

std::string PrefixedStringBuilder::Build() {
    if (!current_line_.str().empty())
        FinalizeLine(false);

    return buffer_.str();
}

void PrefixedStringBuilder::FinalizeLine(bool add_trailing_line_break)
{
    bool first_line = buffer_.str().empty();
    std::string text = std::move(current_line_.str());

    if (wrappable_ranges_.empty()) {
        // Fast path. There were no wrappable spans of text.
        WriteLine(text, add_trailing_line_break, first_line);
        return;
    }
   auto lines = WordWrapLine(text, wrappable_ranges_, wrap_width_,
                             first_line ? prefix_line_one_.size() : prefix_other_lines_.size(),
                             prefix_other_lines_.size());
   int i = 0;
   const int length = lines.size();
   for (const auto& line : lines) {
       i++;
       WriteLine(line, add_trailing_line_break || i < length, first_line);
   }
   wrappable_ranges_.clear();
}


void PrefixedStringBuilder::IncrementPrefixOtherLines(std::string suffix, bool updateCurrentLine) {
    if (IsCurrentLineEmpty() || updateCurrentLine) {
        prefix_other_lines_ = prefix_other_lines_ + suffix;
        next_prefix_other_lines_ = "";
    } else {
        next_prefix_other_lines_ = prefix_other_lines_ + suffix;
    }
}

void PrefixedStringBuilder::UpdatePrefix() {
    if (next_prefix_other_lines_.empty() != false) {
        prefix_other_lines_ = std::move(next_prefix_other_lines_);
    }
}

void PrefixedStringBuilder::Write(std::string s, bool allow_wrap)
{
    if (s.empty()) {
        return;
    }
    std::vector<std::string> lines = Split(s, "\n");
    for (int i = 0; i < lines.size(); i += 1) {
        if (i > 0) {
            FinalizeLine(true);
            UpdatePrefix();
        }
        const std::string& line = lines[i];
        if (!line.empty()) {
            if (allow_wrap && wrap_width_ != -1) {
                const int wrap_start = current_line_.str().size();
                const int wrap_end = wrap_start + line.size()   ;
                if (!wrappable_ranges_.empty() && wrappable_ranges_.back() == wrap_start) {
                    // Extend last range.
                    wrappable_ranges_.back() = wrap_end;
                } else {
                    wrappable_ranges_.emplace_back(wrap_start);
                    wrappable_ranges_.emplace_back(wrap_end);
                }
            }
            current_line_ << line;
        }
    }
}

void PrefixedStringBuilder::WriteLine(std::string line, bool includeLineBreak, bool firstLine)
{
    line = GetCurrentPrefix(firstLine) + line;
    buffer_ << line;
    if (includeLineBreak) {
        buffer_ << std::endl;
    }
    num_lines++;
}

/// Write lines assuming the lines obey the specified prefixes. Ensures that
/// a newline is added if one is not present.
void PrefixedStringBuilder::WriteRawLines(std::string lines) {
    if (lines.empty())
        return;

    if (!current_line_.str().empty()) {
        FinalizeLine(true);
    }
    FML_CHECK(current_line_.str().empty());

    buffer_ << lines;
    if (!lines.ends_with('\n'))
        buffer_ << '\n';
    num_lines++;
    UpdatePrefix();
}

/// Finishes the current line with a stretched version of text.
void PrefixedStringBuilder::WriteStretched(std::string text, int targetLineLength) {
    Write(text);
    int currentLineLength = current_line_.str().size() + GetCurrentPrefix(buffer_.str().empty()).size();
    FML_CHECK (current_line_.str().size() > 0);
    int targetLength = targetLineLength - currentLineLength;
    if (targetLength > 0) {
        FML_CHECK(!text.empty());
        char lastChar = text[text.size() - 1];
        FML_CHECK(lastChar != '\n');
        current_line_ << (lastChar * targetLength);
    }
    // Mark the entire line as not wrappable.
    wrappable_ranges_.clear();
}

} // namespace sm