#ifndef STATE_H_
#define STATE_H_

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum Value {
  cross,
  circle,
};

inline std::ostream &operator<<(std::ostream &out, Value v) {
  out << ((v == Value::cross) ? "x" : "o");
  return out;
}

struct Move {
  size_t row;
  size_t col;
  Value value;

  Move(unsigned row, unsigned col, char v) : row(row), col(col) {
    if (v == 'x')
      value = Value::cross;
    else if (v == 'o')
      value = Value::circle;
  }

  Move(unsigned row, unsigned col, Value value)
      : row(row), col(col), value(value) {}

  void print(std::ostream &out) {
    out << "Put a " << value << " into [" << row << ", " << col << "]";
  }
};

inline std::ostream &operator<<(std::ostream &out, Move m) {
  m.print(out);
  return out;
}

inline std::ostream &operator<<(std::ostream &out,
                                const std::optional<Move> &opt) {
  if (opt.has_value())
    out << opt.value();
  else
    out << "Empty move";
  return out;
}

class State {
  std::vector<std::optional<Value>> field;
  Value turn;

  // Simply passes the turn to the next player (from circle to cross, from cross
  // to circle)
  void rotateTurn();

public:
  // Should initialize an empty field
  State();

  // We do not want to manipulate the field directly, hence it is priivate
  // However, in order to draw it in the Game class, we need to traverse it
  std::vector<std::optional<Value>> getField() const;

  // Checks if the given cell is empty
  // Rows and columns are counted from top-left
  bool empty(size_t row, size_t col);

  // Generates a random move for the computer to make, very similar to what you
  // have done in lab 5
  std::optional<Move> generateRandom();

  // Applies the move on our game state
  void make(Move m);

  // Checks if the game has ended (what conditions are there?)
  bool ended();

  // Checks whether the field has any empty cells or not
  bool hasEmptyCells();

  // Figures out the winner of the game if there is one
  std::optional<Value> winner();

  // We do not want to manage the turn directly, either, that is why we made the
  // field private. The only inconvenience is that we need a getter now.
  // Do not create getters and setters for each and every of your class fields,
  // though. This practice is a menace.
  Value getTurn() const;

  // Do whatever you want
  void print(std::ostream &out) const;
};

#endif