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

class MetaGame extends React.Component {
  constructor(props) {
    super(props);
    this.state = {wordLength: null};
    this.playGame = this.playGame.bind(this);
    this.handleRetry = this.handleRetry.bind(this);
  }

  playGame(wordLength) {
    this.setState({wordLength: wordLength});
  }

  handleRetry() {
    this.setState({wordLength: null});
  }
  
  render() {
    if (!this.state.wordLength) {
      return <StartSelector playGame={this.playGame} />;
    } else {
      return (
        <Game
           wordLength={this.state.wordLength}
           placeHolder="_"
           maxMisses={13}
           handleRetry={this.handleRetry}
        />
      );
    }
  }
}

// Simple form to select the word length to play with.
class StartSelector extends React.Component {
  constructor(props) {
    super(props);
    this.state = {value: "8"};
    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleChange(e) {
    e.preventDefault();
    this.setState({value: e.target.value});
  }

  handleSubmit(e) {
    e.preventDefault();
    this.props.playGame(parseInt(this.state.value));
  }

  render() {
    return (
      <div className="start-selector">
        <h1>Fiendish Hangman</h1>
        <form onSubmit={this.handleSubmit}>
          <label>
            Select a word length:
            <select value={this.state.value} onChange={this.handleChange}>
              <option value="4">4</option>
              <option value="5">5</option>
              <option value="6">6</option>
              <option value="7">7</option>
              <option value="8">8</option>
              <option value="9">9</option>
              <option value="10">10</option>
              <option value="11">11</option>
              <option value="12">12</option>
            </select>
          </label>
          <input type="submit" value="Play" />
        </form>
      </div>
    );
  }
}      

// Top-level game component.
class Game extends React.PureComponent {
  constructor(props) {
    super(props)
    this.state = this.initialState();
    this.handleLetter = this.handleLetter.bind(this);
    this.onKeyUp = this.onKeyUp.bind(this);
    this.handleRetry = this.handleRetry.bind(this);
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
      finishMessage: null,
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

    if (this.state.guessedLetters.get(letter)) {
      throw new Error("Already guessed letter: " + letter);
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

    let finishMessage = null;
    if (misses === this.props.maxMisses) {
      finishMessage = (
        "Too many misses. I was thinking of: " + this.randomWord());
    } else if (discoveredLetterCount === this.props.wordLength) {
      finishMessage = "You won! I was thinking of: " + revealedWord.join("");
    }

    this.setState({
        misses: misses,
        discoveredLetterCount: discoveredLetterCount,
        guessedLetters: guessedLetters,
        revealedWord: revealedWord,
        words: words,
        finishMessage: finishMessage,
    });
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

  // Handle a key press. If any letter key is pressed we take it as the next input.
  onKeyUp(e) {
    console.log('Key pressed: ' + e.key);
    if (e.key.length !== 1) {
      return;
    }

    const upperKey = e.key.toUpperCase();
    if ((upperKey < 'A') || (upperKey > 'Z')) {
      return;
    }

    if (this.state.guessedLetters.get(upperKey)) {
      return;
    }

    console.log('Handle key event for letter: ' + upperKey);
    e.preventDefault();
    this.handleLetter(upperKey);
  }

  handleRetry() {
    this.setState(this.initialState());
    this.props.handleRetry();
  }

  // Main render function.
  render() {
    return (
      <div className="game" onKeyUp={this.onKeyUp} tabIndex="0">
        <div className="game-info">
          <Hangman misses={this.state.misses} />
          <StatusColumn
            revealedWord={this.state.revealedWord}
            finishMessage={this.state.finishMessage}
            onRetry={this.handleRetry}
          />
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

// Display the revealed word and any extra status information.
function StatusColumn(props) {
  const revealedWord = props.revealedWord.join(" ");

  let finishInfo = null;
  if (props.finishMessage) {
    finishInfo = (
      <>
        <p>{props.finishMessage}</p>
        <button className="retry-button" onClick={props.onRetry}>
          Retry?
        </button>
      </>
    );
  }   

  return (
    <div className="revealed-word">
      <p>Word:</p>
      <p>{revealedWord}</p>
      {finishInfo}
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
  <MetaGame />,
  document.getElementById("root")
);

