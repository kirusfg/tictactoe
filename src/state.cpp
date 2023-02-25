#include <algorithm>

#include "state.h"

State::State() : field(9), turn(Value::cross) {}

std::vector<std::optional<Value>> State::getField() const { return field; }

bool State::empty(size_t row, size_t col) {
  return !field[row * 3 + col].has_value();
}

std::optional<Move> State::generateRandom() {
  if (!hasEmptyCells())
    return std::nullopt;

  size_t row = rand() % 3;
  size_t col = rand() % 3;

  while (!empty(row, col)) {
    row = rand() % 3;
    col = rand() % 3;
  }

  return Move(row, col, turn);
}

void State::make(Move m) {
  if (!empty(m.row, m.col))
    return;
  if (m.row > 2 || m.col > 2)
    return;

  field[m.row * 3 + m.col] = m.value;

  rotateTurn();
}

bool State::ended() {
  if (!hasEmptyCells())
    return true;
  if (winner() != std::nullopt)
    return true;

  return false;
}

bool State::hasEmptyCells() {
  return std::find(field.begin(), field.end(), std::nullopt) != field.end();
}

std::optional<Value> State::winner() {
  for (size_t i = 0; i < 3; i++)
    if (field[i * 3 + 0] == field[i * 3 + 1] &&
        field[i * 3 + 1] == field[i * 3 + 2])
      return field[i * 3 + 0];

  for (size_t i = 0; i < 3; i++)
    if (field[0 * 3 + i] == field[1 * 3 + i] &&
        field[1 * 3 + i] == field[2 * 3 + i])
      return field[0 * 3 + i];

  if (field[0] == field[4] && field[4] == field[8])
    return field[0];
  if (field[2] == field[4] && field[4] == field[6])
    return field[2];

  return std::nullopt;
}

Value State::getTurn() const { return turn; }

void State::rotateTurn() {
  turn = turn == Value::circle ? Value::cross : Value::circle;
}

void State::print(std::ostream &out) const {
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      if (field[i * 3 + j].has_value())
        out << field[i * 3 + j].value();
      else
        out << " ";
    }
    out << std::endl;
  }
}