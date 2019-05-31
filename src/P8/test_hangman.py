#!/usr/bin/env python3
"""Integration test of hangman via CLI."""
import os
import string

import pexpect

ROOT_DIR = os.path.abspath(os.path.join(
    os.path.dirname(__file__), os.pardir, os.pardir))
HANGMAN_BIN = os.path.join(ROOT_DIR, 'bin', 'P8', 'cheating_hangman')


def main():
    """
    Test the hangman game from the CLI.

    Send in the letters from a-u - the word "outsport" should be guessed.
    """
    child = pexpect.spawn('{bin} {word_len} {num_guesses}'.format(
        bin=HANGMAN_BIN, word_len=8, num_guesses=26))
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

    print('Hangman test passed')


if __name__ == '__main__':
    main()

