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

  void rotateTurn();

public:
  State();

  std::vector<std::optional<Value>> getField() const;

  bool empty(size_t row, size_t col);
  std::optional<Move> generateRandom();

  void make(Move m);

  bool ended();
  bool hasEmptyCells();
  std::optional<Value> winner();

  Value getTurn() const;

  void print(std::ostream &out) const;
};

#endif