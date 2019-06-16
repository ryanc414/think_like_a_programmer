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
    this.state = {
      misses: 0,
      guessedLetters: Array(26),
    };
    this.state.guessedLetters.fill(false);
    this.handleLetter = this.handleLetter.bind(this);
  }

  incrementMisses() {
     const curr_misses = this.state.misses;
     this.setState({misses: curr_misses + 1});
  }

  reset() {
    this.setState({misses: 0, guessedLetters: Array(26)});
  }

  handleLetter(letter) {
    const letterCode = letter.charCodeAt(0);
    const aCode = "a".charCodeAt(0);

    if (this.state.guessedLetters[letterCode - aCode]) {
      alert("You've already guessed letter " + letter);
    } else {
      let guessedLetters = this.state.guessedLetters.slice();
      guessedLetters[letterCode - aCode] = true;
      const misses = this.state.misses;
      this.setState({misses: misses,  guessedLetters: guessedLetters});
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

// TODO... display guessed letters
function Letters(props) {
  const guessedLetters = props.guessedLetters.join(", ");

  return (
    <div className="guessed-letters">
      <p>Guessed letters:</p>
      <p>{guessedLetters}</p>
    </div>
  );
}

// TODO... display the revealed word
function RevealedWord(props) {
  const revealedWord = props.revealedWord.join(" ");
  return (
    <div className="revealed-word">
      <p>Word:</p>
      <p>{revealedWord}</p>
    </div>
  );
}

// TODO... Box for user input
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
  <Game />,
  document.getElementById('root')
);

