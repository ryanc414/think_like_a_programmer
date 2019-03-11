/*
 * 4-2. For our dynamically allocated strings, create a function substring that takes
 * three parameters: an arrayString, a starting position integer, and an integer
 * length of characters. The function returns a pointer to a new dynamically
 * allocated string array. This string array contains the characters in the original
 * string, starting at the specified position for the specified length. The original
 * string is unaffected by the operation. So if the original string was abcdefg, the
 * position was 3, and the length was 4, then the new string would contain cdef.
 *
 * 4-3. For our dynamically allocated strings, create a function replaceString that takes
 * three parameters, each of type arrayString: source, target, and replaceText.
 * The function replaces every occurrence of target in source with replaceText.
 * For example, if source points to an array containing abcdabee, target points to
 * ab, and replaceText points to xyz, then when the function ends, source should
 * point to an array containing xyzcdxyzee.
 */
#include <cassert>
#include <cstring>
#include <iostream>

char *Substring(const char *str, int start_pos, int len);
void TestSubstring();
char *ReplaceString(
    const char *source, const char *target, const char *replace_text);
int CalculateReplacedLen(const char *source,
                         const char *target,
                         int target_len,
                         int repl_len);
char *MakeReplacements(int out_len,
                       const char *source,
                       const char *target,
                       int target_len,
                       const char *replace_text,
                       int repl_len);
void TestReplaceString();

int main() {
    TestSubstring();
    TestReplaceString();

    return 0;
}

// Test the Substring function.
void TestSubstring() {
    const char *orig = "abcdefg";
    const char *sub = Substring(orig, 3, 4);
    std::cout << "sub = " << sub << std::endl;
    assert(!memcmp(sub, "defg", 4));

    delete sub;
}

// Return a new allocated substring from start_pos of len characters.
char *Substring(const char *in, int start_pos, int len) {
    char *out = new char[len];

    for (int i = 0; i < len; ++i) {
        out[i] = in[i + start_pos];
    }

    return out;
}

void TestReplaceString() {
    const char *orig = "abcdabee";
    const char *replaced = ReplaceString(orig, "ab", "xyz");
    std::cout << "abcdabee -> " << replaced << std::endl;
    assert(!memcmp(replaced, "xyzcdxyzee", 10));
    delete[] replaced;
}

char *ReplaceString(
        const char *source, const char *target, const char *replace_text) {
    const int target_len = strlen(target);
    const int repl_len = strlen(replace_text);

    const int out_len = CalculateReplacedLen(
        source, target, target_len, repl_len);

    return MakeReplacements(
        out_len, source, target, target_len, replace_text, repl_len);
}

// Calculate how much memory we need to allocate for the output.
int CalculateReplacedLen(const char *source,
                         const char *target,
                         int target_len,
                         int repl_len) {
    int out_len = 0;

    const char *src_ptr = source;
    while (*src_ptr != '\0') {
        if (!memcmp(src_ptr, target, target_len)) {
            out_len += repl_len;
            src_ptr += target_len;
        } else {
            ++out_len;
            ++src_ptr;
        }
    }

    return out_len;
}

// Allocate output memory and fill it up, making the replacements from the
// source.
char *MakeReplacements(int out_len,
                       const char *source,
                       const char *target,
                       int target_len,
                       const char *replace_text,
                       int repl_len) {
    char *const output = new char[out_len + 1];
    const char *src_ptr = source;
    char *target_ptr = output;
    while (*src_ptr != '\0') {
        if (!memcmp(src_ptr, target, target_len)) {
            memcpy(target_ptr, replace_text, repl_len);
            target_ptr += repl_len;
            src_ptr += target_len;
        } else {
            *target_ptr = *src_ptr;
            ++target_ptr;
            ++src_ptr;
        }
    }

    *target_ptr = '\0';

    return output;
}

