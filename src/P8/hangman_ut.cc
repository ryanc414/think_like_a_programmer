/* Unit tests for hangman core logic. */

#include "hangman.hh"

void TestLetterPatterns();
void TestWords();


int main() {
    TestLetterPatterns();
    TestWords();

    std::cout << "All hangman UTs pased." << std::endl;

    return 0;
}

// Test the LetterPatterns class
void TestLetterPatterns() {
    LetterPattern pattern("abracadabra", 'a');

    assert(pattern.letter() == 'a');
    assert(pattern.size() == 5);

    assert(pattern.Matches("abracadabra"));
    assert(pattern.Matches("axxaxaxaxxa"));
    assert(!pattern.Matches("xxxxxxxxxxx"));
    assert(!pattern.Matches("abracadabro"));
    assert(!pattern.Matches("aaaaaaaaaaa"));

    try {
        pattern.Matches("");
        throw std::runtime_error("No exception thrown");
    } catch (std::length_error) {}

    assert(pattern.Reveal("___________") == "a__a_a_a__a");
    assert(pattern.Reveal("_br_c_d_br_") == "abracadabra");

    try {
        pattern.Reveal("abracadabra");
        assert(false);
    } catch (std::runtime_error) {}

    try {
        pattern.Reveal("");
        assert(false);
    } catch (std::length_error) {}
}

// Test reading words from file and related functions.
void TestWords() {
    auto words_map = ReadWordsFile(kWordFile);

    assert(words_map.size() == 29);

    auto words = words_map[8];
    assert(words.size() == 51627);

    auto [words_without_letter, words_with_letter] =
        SplitWordsByLetter(words, 'a');
    assert(words_without_letter.size() == 23447);
    assert(words_with_letter.size() == 28180);

    auto [pattern_count, pattern, words_match_pattern] =
        MostFrequentPattern(words_with_letter, 'a');
    assert(pattern_count == words_match_pattern.size());
    assert(pattern_count == 4575);
    assert(pattern.letter() == 'a');

    assert(pattern.Reveal("________") == "_a______");
}

