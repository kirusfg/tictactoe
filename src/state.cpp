#include "state.h"

State::State() {}

std::vector<std::optional<Value>> State::getField() const {}

bool State::empty(size_t row, size_t col) {}

std::optional<Move> State::generateRandom() {}

void State::make(Move m) {}

bool State::ended() {}

bool State::hasEmptyCells() {}

std::optional<Value> State::winner() {}

Value State::getTurn() const {}

void State::rotateTurn() {}

void State::print(std::ostream &out) const {}