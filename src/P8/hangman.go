package main

import (
	"bufio"
	"errors"
	"flag"
	"fmt"
	"math/rand"
	"os"
	"strings"
)

const WORDS_FILE = "data/words_alpha.txt"
const PLACEHOLDER = '_'
const NUM_LETTERS = 26

// Parse command-line arguments and play a single game of hangman.
func main() {
	word_len, num_misses, err := parse_args()
	check(err)

	words := read_words_file(WORDS_FILE)
	fmt.Println("word_len", word_len)
	fmt.Println("num_misses", num_misses)
	fmt.Println("words map length", len(words))

	game_words, ok := words[word_len]
	if !ok {
		err = errors.New("Invalid word length")
		panic(err)
	}

	play_hangman(game_words, word_len, num_misses)
}

// Helper function to check for a non-nil error.
func check(err error) {
	if err != nil {
		panic(err)

	}
}

// Parse command-line args.
func parse_args() (int, int, error) {
	word_len := flag.Int("length", 8, "word length")
	num_misses := flag.Int("num-misses", 15, "number of wrong guesses allowed")
	flag.Parse()

	if *word_len < 1 {
		return 0, 0, errors.New("Word length must be > 0")
	}

	if *num_misses < 1 {
		return 0, 0, errors.New("Number of misses must be > 0")
	}

	return *word_len, *num_misses, nil
}

// Open the words file and store them in a map keyed by their length.
func read_words_file(filename string) map[int][]string {
	words := make(map[int][]string)

	file, err := os.Open(filename)
	check(err)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		word := scanner.Text()
		length := len(word)
		words[length] = append(words[length], word)
	}

	return words
}

// Play a game of hangman.
func play_hangman(words []string, word_len, max_misses int) {
	var misses int = 0
	var discovered_letter_count int = 0
	revealed_word := strings.Repeat(string(PLACEHOLDER), word_len)
	var guessed_letters [NUM_LETTERS]bool

	for (discovered_letter_count < word_len) && (misses < max_misses) {
		fmt.Println("Discovered word:", revealed_word)
		fmt.Println("You have", max_misses-misses, "guesses remaining.")

		next_letter := prompt_next_letter()
		if guessed_letters[next_letter-'a'] {
			fmt.Println("You already guessed that letter. Try again.")
			continue
		}
		guessed_letters[next_letter-'a'] = true

		words_without_letter, words_with_letter := split_words_by_letter(
			words, next_letter)
		without_letter_count := len(words_without_letter)

		pattern, matching_pattern_words :=
			most_frequent_pattern(words_with_letter, next_letter)
		with_letter_count := len(matching_pattern_words)

		if without_letter_count > with_letter_count {
			misses++
			words = words_without_letter
			fmt.Println("Bad guess")
		} else {
			words = matching_pattern_words
			revealed_word = pattern.Reveal(revealed_word)
			discovered_letter_count += pattern.size
			fmt.Println("Correct guess!")
		}
	}

	if discovered_letter_count == word_len {
		fmt.Println("Congratulations - you guessed the word!")
		fmt.Println("Word was:", revealed_word)
	} else {
		fmt.Println("Out of guesses...")
		fmt.Println("I was thinking of:", random_choice(words))
	}
}

// Prompt for the next letter to be input. Loops until a valid lowercase
// letter is entered.
func prompt_next_letter() byte {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Guess a letter:\n> ")
	text, err := reader.ReadString('\n')
	check(err)
	text = strings.TrimSpace(text)

	for (len(text) != 1) || (text[0] < 'a') || (text[0] > 'z') {
		fmt.Println("Bad choice: only lowercase a-z is allowed.")
		fmt.Print("Try again:\n> ")
		text, err = reader.ReadString('\n')
		check(err)
		text = strings.TrimSpace(text)
	}

	return text[0]
}

// Split a slice of words into two slices: one which does not contain the
// given letter, and one which does.
func split_words_by_letter(words []string, letter byte) ([]string, []string) {
	words_with_letter := make([]string, 0, len(words))
	words_without_letter := make([]string, 0, len(words))

	for _, word := range words {
		found_letter := false
		for _, c := range word {
			if byte(c) == letter {
				found_letter = true
				words_with_letter = append(words_with_letter, word)
				break
			}
		}

		if !found_letter {
			words_without_letter = append(words_without_letter, word)
		}
	}

	return words_without_letter, words_with_letter
}

// Find the letter pattern that matches the most words. Return the most
// frequent pattern and the words that match that pattern.
func most_frequent_pattern(words []string, letter byte) (
	*LetterPattern, []string) {
	var most_frequent_pattern *LetterPattern
	var most_frequent_matching_words []string

	// Copy the slice of words so that we can mutate it freely.
	words_copy := make([]string, len(words))
	copy(words_copy, words)

	// Algorithm for finding the most frequent pattern:
	//
	// 1. Pop the first word off
	// 2. Find all other words that match that pattern.
	// 3. Remove matching words
	// 4. Update the running count of most frequent pattern.
	// 5. Repeat until all words are exhausted.
	for len(words_copy) != 0 {
		next_word := words_copy[0]
		words_copy = words_copy[1:]

		next_pattern := NewLetterPattern(next_word, letter)
		if next_pattern.size < 1 {
			panic("Pattern did not match word")
		}

		matching_words := make([]string, 0, 1)
		matching_words = append(matching_words, next_word)

		// Iterate through the rest of the words. For any words that match
		// the current pattern, incremenet the count and move them into a
		// seperate slice.
		for i := 0; i < len(words_copy); {
			if next_pattern.Matches(words_copy[i]) {
				matching_words = append(matching_words, words_copy[i])
				words_copy[i] = words_copy[len(words_copy)-1]
				words_copy = words_copy[:len(words_copy)-1]
			} else {
				i++
			}
		}

		// Update the most frequent pattern and slice of matching words if
		// necessary.
		if len(matching_words) > len(most_frequent_matching_words) {
			most_frequent_pattern = next_pattern
			most_frequent_matching_words = matching_words
		}
	}

	return most_frequent_pattern, most_frequent_matching_words
}

// Select a word at random from a slice.
func random_choice(words []string) string {
	return words[rand.Intn(len(words))]
}

// Type representing a pattern of a letter matching words.
type LetterPattern struct {
	letter  byte
	size    int
	pattern []bool
}

// Construct a LetterPattern matching the given word and letter.
func NewLetterPattern(word string, letter byte) *LetterPattern {
	pattern := new(LetterPattern)
	pattern.letter = letter
	pattern.pattern = make([]bool, len(word))
	pattern.size = 0

	for i := range word {
		if byte(word[i]) == letter {
			pattern.pattern[i] = true
			pattern.size++
		} else {
			pattern.pattern[i] = false
		}
	}

	return pattern
}

// Reveals letters matching a pattern in a word.
func (pattern *LetterPattern) Reveal(word string) string {
	if len(word) != len(pattern.pattern) {
		panic("Cannot reveal word - lengths do not match.")
	}

	var new_word string

	for i := 0; i < len(word); i++ {
		if pattern.pattern[i] {
			if word[i] != PLACEHOLDER {
				panic("Letter already revealed")
			}

			new_word += string(pattern.letter)
		} else {
			new_word += string(word[i])
		}
	}

	return new_word
}

// Check if a word matches a given letter pattern.
func (pattern *LetterPattern) Matches(word string) bool {
	if len(word) != len(pattern.pattern) {
		panic("Word length does not match pattern")
	}

	for i := 0; i < len(word); i++ {
		if pattern.pattern[i] && (word[i] != pattern.letter) {
			return false
		} else if !pattern.pattern[i] && (word[i] == pattern.letter) {
			return false
		}
	}

	return true
}
