/*
 * For our dynamically allocated strings, create a function substring that takes
 * three parameters: an arrayString, a starting position integer, and an integer
 * length of characters. The function returns a pointer to a new dynamically
 * allocated string array. This string array contains the characters in the original
 * string, starting at the specified position for the specified length. The original
 * string is unaffected by the operation. So if the original string was abcdefg, the
 * position was 3, and the length was 4, then the new string would contain cdef.
 */
#include <iostream>

char *Substring(const char *str, int start_pos, int len);

int main() {
    const char *orig = "abcdefg";
    const char *sub = Substring(orig, 3, 4);
    std::cout << "sub = " << sub << std::endl;

    delete sub;

    return 0;
}

// Return a new allocated substring from start_pos of len characters.
char *Substring(const char *in, int start_pos, int len) {
    char *out = new char[len];

    for (int i = 0; i < len; ++i) {
        out[i] = in[i + start_pos];
    }

    return out;
}

