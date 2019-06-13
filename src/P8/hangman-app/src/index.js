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

// Top-level game component.
class Game extends React.PureComponent {
  constructor(props) {
    super(props)
    this.state = {misses: 0};
  }

  incrementMisses() {
     const curr_misses = this.state.misses;
     this.setState({misses: curr_misses + 1});
  }

  reset() {
    this.setState({misses: 0})
  }

  render() {
    let info;
    if (this.state.misses > 12) {
      info = (
        <div>
          <p>Stick man is dead</p>
          <button onClick={() => this.reset()}>reset</button>
        </div>
      );
    } else {
      info = (
        <div>
          <p>You have made {this.state.misses} misses.</p>
          <button onClick={() => this.incrementMisses()}>
            Miss
          </button>
        </div>
      );
    }

    return (
      <div className="game">
        <div className="hangman">
          <Hangman misses={this.state.misses} />
        </div>
        <div className="game-info">
          {info}
        </div>
      </div>
    );
  }
}

// ========================================

ReactDOM.render(
  <Game />,
  document.getElementById('root')
);

