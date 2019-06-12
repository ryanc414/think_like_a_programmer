import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';

function Hangman(props) {
  return (
    <img src={"hangman" + props.misses + ".png"}
         alt={"A poor stick man in step "
              + props.misses
              + " of being hanged :("}
    />
  );
}


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

