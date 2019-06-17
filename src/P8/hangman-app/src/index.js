import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';

import hangman0 from './hangman0.png'
import hangman1 from './hangman1.png'
import hangman2 from './hangman2.png'
import hangman3 from './hangman3.png'
import hangman4 from './hangman4.png'
import hangman5 from './hangman5.png'
import hangman6 from './hangman6.png'
import hangman7 from './hangman7.png'
import hangman8 from './hangman8.png'
import hangman9 from './hangman9.png'
import hangman10 from './hangman10.png'
import hangman11 from './hangman11.png'
import hangman12 from './hangman12.png'
import hangman13 from './hangman13.png'

import allWords from './words_dictionary.json';
console.log(Object.keys(allWords));

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

  initialState() {
    let guessedLetters = new Map();
    const aCode = "a".charCodeAt(0);

    for (let i = 0; i < 26; i++) {
      const letter = String.fromCharCode(aCode + i);
      guessedLetters.set(letter, false);
    }

    const revealedWord = Array(this.props.wordLength).fill(
      this.props.placeHolder);

    return {
      misses: 0,
      guessedLetters: guessedLetters,
      revealedWord: revealedWord,
    };
  }

  incrementMisses() {
    const curr_misses = this.state.misses;
    this.setState({
      ...this.state,
      misses: curr_misses + 1
    });
  }

  handleLetter(letter) {
    if (this.state.guessedLetters.get(letter)) {
      alert("You've already guessed letter " + letter);
    } else {
      let guessedLetters = new Map(this.state.guessedLetters);
      guessedLetters.set(letter, true);
      this.setState({...this.state, guessedLetters: guessedLetters});
    }
  }

  render() {
    return (
      <div className="game">
        <div className="game-info">
          <Hangman misses={this.state.misses} />
          <div className="word-status">
            <Letters guessedLetters={this.state.guessedLetters} />
            <RevealedWord revealedWord={['_', '_', '_', '_', '_']} />
          </div>
        </div>
        <InputBox handleLetter={this.handleLetter}/>
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

// Display guessed letters
function Letters(props) {
  let guessedLetters = [...props.guessedLetters.keys()].filter((key) => {
    return props.guessedLetters.get(key);
  });

  return (
    <div className="guessed-letters">
      <p>Guessed letters:</p>
      <p>{guessedLetters}</p>
    </div>
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

// Box for user input
class InputBox extends React.Component {
  constructor(props) {
    super(props);
    this.state = {value: ''};
    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleChange(event) {
    this.setState({value: event.target.value});
  }

  handleSubmit(event) {
    event.preventDefault();
    if (!this.validValue(this.state.value)) {
      alert('Invalid guess: enter a single lowercase letter');
    } else {
      this.props.handleLetter(this.state.value);
    }
  }

  validValue(val) {
    return (val.length === 1) && (val >= 'a') && (val <= 'z');
  }

  render() {
    return (
      <form onSubmit={this.handleSubmit}>
        <div className="input-box">
          <label>
            Next letter:
            <input type="text"
                   value={this.state.value}
                   onChange={this.handleChange} />
          </label>
          <button>Guess letter</button>
        </div>
      </form>
    );
  }
}

// ========================================

ReactDOM.render(
  <Game wordLength={5} placeHolder='_' />,
  document.getElementById('root')
);

