#!/usr/bin/env python3
"""Integration test of hangman via CLI."""
import os
import string

import pexpect

ROOT_DIR = os.path.abspath(os.path.join(
    os.path.dirname(__file__), os.pardir, os.pardir))
CHEATING_HANGMAN_BIN = os.path.join(ROOT_DIR, 'bin', 'P8', 'cheating_hangman')
HANGMAN_GUESSER_BIN = os.path.join(ROOT_DIR, 'bin', 'P8', 'hangman_guesser')


def main():
    """Test all hangman programs."""
    test_cheating_hangman()
    test_hangman_guesser()

    print('Hangman test passed')


def test_cheating_hangman():
    """
    Test the hangman game from the CLI.

    Send in the letters from a-u - the word "outsport" should be guessed.
    """
    child = pexpect.spawn('{bin} {word_len} {num_guesses}'.format(
        bin=CHEATING_HANGMAN_BIN, word_len=8, num_guesses=26))
    child.expect('Guess a letter:\r\n> ')

    # Guess the letters in order from a to t.
    letters = string.ascii_lowercase[:20]
    for letter in letters:
        child.sendline(letter)
        child.expect('Guess a letter:\r\n> ')

    # Finally, guess the letter 'u' - we should have correctly guessed the
    # word.
    child.sendline('u')
    child.expect('Congratulations - you guessed the word!\r\n'
                 'Word was: outsport\r\n')


def test_hangman_guesser():
    """
    Test the hangman guesser.

    It should be able to guess the word "cannibalism" with fewer than 10
    misses.
    """
    child = pexpect.spawn('{bin} {num_guesses}'.format(
        bin=HANGMAN_GUESSER_BIN, num_guesses=10))

    child.expect('Enter a word for me to guess: \r\n> ')
    child.sendline('cannibalism')
    child.expect('I guessed your word was cannibalism', timeout=60)


if __name__ == '__main__':
    main()

