import React from "react";
import ReactDOM from "react-dom";
import "./index.css";

import hangman0 from "./hangman0.png"
import hangman1 from "./hangman1.png"
import hangman2 from "./hangman2.png"
import hangman3 from "./hangman3.png"
import hangman4 from "./hangman4.png"
import hangman5 from "./hangman5.png"
import hangman6 from "./hangman6.png"
import hangman7 from "./hangman7.png"
import hangman8 from "./hangman8.png"
import hangman9 from "./hangman9.png"
import hangman10 from "./hangman10.png"
import hangman11 from "./hangman11.png"
import hangman12 from "./hangman12.png"
import hangman13 from "./hangman13.png"

import allWords from "./words_dictionary.json";

const hangman_images = [
  hangman0,
  hangman1,
  hangman2,
  hangman3,
  hangman4,
  hangman5,
  hangman6,
  hangman7,
  hangman8,
  hangman9,
  hangman10,
  hangman11,
  hangman12,
  hangman13,
]

// Top-level game component.
class Game extends React.PureComponent {
  constructor(props) {
    super(props)
    this.state = this.initialState();
    this.handleLetter = this.handleLetter.bind(this);
  }

  // Construct initial state, also used for reset.
  initialState() {
    let guessedLetters = new Map();
    const aCode = "A".charCodeAt(0);

    for (let i = 0; i < 26; i++) {
      const letter = String.fromCharCode(aCode + i);
      guessedLetters.set(letter, false);
    }

    const revealedWord = Array(this.props.wordLength).fill(
      this.props.placeHolder);

    const words = this.wordsOfLength(this.props.wordLength);

    return {
      misses: 0,
      discoveredLetterCount: 0,
      guessedLetters: guessedLetters,
      revealedWord: revealedWord,
      words: words,
    };
  }

  // Filter words by length.
  wordsOfLength(n) {
    return (Object.keys(allWords)
			.filter((word) => word.length === n)
			.map((word) => word.toUpperCase())
		);
  }

  // Handle a guessed letter.
  handleLetter(letter) {
    if ((letter.length !== 1) || (letter < 'A') || (letter > 'Z')) {
      throw new Error("Not a letter: " + letter);
		}

    let guessedLetters = new Map(this.state.guessedLetters);
    guessedLetters.set(letter, true);
    console.log("guessedLetters:");
    console.log(guessedLetters);

    const splitWords = this.splitWordsByLetter(letter);
    console.log("splitWords:");
    console.log(splitWords);
    const patternWords = this.mostFrequentPattern(
      splitWords.wordsWithLetter, letter);
    console.log("patternWords:");
    console.log(patternWords);

    let revealedWord;
    let misses;
    let discoveredLetterCount;
    let words;

    if (splitWords.wordsWithoutLetter.length >
        patternWords.mostFrequentMatchingWords.length) {
      console.log("Bad guess");
      revealedWord = this.state.revealedWord;
      misses = this.state.misses + 1;
      discoveredLetterCount = this.state.discoveredLetterCount;
      words = splitWords.wordsWithoutLetter;
    } else {
      console.log("Good guess!");
      revealedWord = patternWords.mostFrequentPattern.reveal(
        this.state.revealedWord);
      misses = this.state.misses;
      discoveredLetterCount = (
        this.state.discoveredLetterCount
        + patternWords.mostFrequentPattern.size
      );
      words = patternWords.mostFrequentMatchingWords;
    }

    if (misses === this.props.maxMisses) {
      alert("Too many misses. I was thinking of: " + this.randomWord());
      this.setState(this.initialState());
    } else if (discoveredLetterCount === this.props.wordLength) {
      alert("You won! I was thinking of: "
            + revealedWord.join(""));
      this.setState(this.initialState());
    } else {
      this.setState({
        misses: misses,
        discoveredLetterCount: discoveredLetterCount,
        guessedLetters: guessedLetters,
        revealedWord: revealedWord,
        words: words,
      });
    }
  }

  // Split our current words list into two, one with and one without a certain
  // letter.
  splitWordsByLetter(letter) {
    let wordsWithoutLetter = [];
    let wordsWithLetter = [];

    this.state.words.forEach((word) => {
      if (word.indexOf(letter) === -1) {
        wordsWithoutLetter.push(word);
      } else {
        wordsWithLetter.push(word);
      }
    });

    return {
      wordsWithoutLetter: wordsWithoutLetter,
      wordsWithLetter: wordsWithLetter,
    }
  }

  // Find the letter pattern that matches the most words.
  mostFrequentPattern(wordsWithLetter, letter) {
    let mostFrequentPattern;
    let mostFrequentMatchingWords = [];

    // Algorithm for finding the most frequent pattern:
    //
    // 1. Pop the first word off
    // 2. Find all other words that match that pattern.
    // 3. Remove matching words
    // 4. Update the running count of most frequent pattern.
    // 5. Repeat until all words are exhausted.
    while (wordsWithLetter.length > 0) {
      const word = wordsWithLetter.shift();
      const pattern = new LetterPattern(word, letter);
      if (pattern.size === 0) {
        throw new Error("Pattern did not match");
      }

      let matchingWords = [word];

      for (let i = 0; i < wordsWithLetter.length; ) {
        if (pattern.matches(wordsWithLetter[i])) {
          matchingWords.push(wordsWithLetter[i]);
          wordsWithLetter[i] = wordsWithLetter[wordsWithLetter.length - 1];
          wordsWithLetter.pop();
        } else {
          i++;
        }
      }

      if (matchingWords.length > mostFrequentMatchingWords.length) {
        mostFrequentMatchingWords = matchingWords;
        mostFrequentPattern = pattern;
      }
    }

    return {
      mostFrequentPattern: mostFrequentPattern,
      mostFrequentMatchingWords: mostFrequentMatchingWords,
    };
  }

  // Select a word at random from our list of possibles.
  randomWord() {
    return this.state.words[
      Math.floor(Math.random() * this.state.words.length)
    ];
  }

  // Main render function.
  render() {
    return (
      <div className="game">
        <div className="game-info">
          <Hangman misses={this.state.misses} />
          <RevealedWord revealedWord={this.state.revealedWord} />
        </div>
        <Keyboard handleLetter={this.handleLetter} guessedLetters={this.state.guessedLetters} />
        <p>Click keys or use your keyboard to guess a letter.</p>
      </div>
    );
  }
}

// Selects and renders a hangman image depending on the number of misses.
function Hangman(props) {
  const img_src = hangman_images[props.misses]
  return (
    <img
      src={img_src}
      alt={
        "A poor stick man in stage "
        + props.misses
        + " of being hanged :("
      }
    />
  );
}

// Display the revealed word
function RevealedWord(props) {
  const revealedWord = props.revealedWord.join(" ");
  return (
    <div className="revealed-word">
      <p>Word:</p>
      <p>{revealedWord}</p>
    </div>
  );
}

// Represents a pattern of a letter matching a word.
class LetterPattern {

  // Construct a pattern for a particular letter in a word.
  constructor(word, letter) {
    this.letter = letter;
    let size = 0;
    let pattern = Array(word.length);

    for (let i = 0; i < word.length; i++) {
      if (word[i] === letter) {
        pattern[i] = true;
        size++
      } else {
        pattern[i] = false;
      }
    }

    this.size = size;
    this.pattern = pattern;
  }

  // Check if a word matches this pattern.
  matches(word) {
    if (word.length !== this.pattern.length) {
      throw new Error("Word length does not match pattern");
    }

    for (let i = 0; i < word.length; i++) {
      if (this.pattern[i] && (word[i] !== this.letter)) {
        return false;
      } else if (!this.pattern[i] && (word[i] === this.letter)) {
        return false;
      }
    }

    return true;
  }

  // Reveals letters in this pattern in the word.
  reveal(revealedSoFar) {
    if (revealedSoFar.length !== this.pattern.length) {
      throw new Error("Word length does not match pattern");
    }

    let newRevealed = Array(revealedSoFar.length);

    for (let i = 0; i < revealedSoFar.length; i++) {
      if (this.pattern[i]) {
        newRevealed[i] = this.letter;
      } else {
        newRevealed[i] = revealedSoFar[i];
      }
    }

    return newRevealed;
  }
}

class Keyboard extends React.Component {
  render() {
    return (
      <div className="keyboard">
        <KeyboardRow
           letters={["Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"]}
           handleLetter={this.props.handleLetter}
           guessedLetters={this.props.guessedLetters}
        />
        <KeyboardRow
          letters={["A", "S", "D", "F", "G", "H", "J", "K", "L"]}
          handleLetter={this.props.handleLetter}
          guessedLetters={this.props.guessedLetters}
        />
        <KeyboardRow
          letters={["Z", "X", "C", "V", "B", "N", "M"]}
          handleLetter={this.props.handleLetter} 
          guessedLetters={this.props.guessedLetters}
        />
      </div>
    );
  }
}

class KeyboardRow extends React.Component {
  constructor(props) {
    super(props);
    this.renderLetter = this.renderLetter.bind(this);
  }

  renderLetter(letter) {
    if (this.props.guessedLetters.get(letter)) {
      return (
        <Key
          key={letter}
          letter={letter}
          onClick={() => null}
          className="key-guessed"
        />);
    } else {
      return (
        <Key
          key={letter}
          letter={letter}
          onClick={() => this.props.handleLetter(letter)}
          className="key"
        />);
    }
  }

  render() {
    return (
      <div className="keyboard-row">
        {this.props.letters.map(this.renderLetter)}
      </div>
    );
  }
}

class Key extends React.Component {
  render() {
    return (
      <button className={this.props.className} onClick={this.props.onClick}>
        {this.props.letter}
      </button>
    );
  }
}

// ========================================

ReactDOM.render(
  <Game wordLength={8} placeHolder="_" maxMisses={13} />,
  document.getElementById("root")
);

