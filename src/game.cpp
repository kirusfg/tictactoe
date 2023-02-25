#include <chrono>
#include <cmath>
#include <thread>

#include "game.h"

Game::Game(unsigned int width, unsigned int height)
    : state(), width(width), height(height),
      settings(sf::ContextSettings(0, 0, 8)),
      window(sf::RenderWindow(sf::VideoMode(width, height), "Tic-Tac-Toe",
                              sf::Style::Default, settings)),
      hasToQuit(false) {
  window.setVerticalSyncEnabled(true);

  center = sf::Vector2f((float)width / 2, (float)height / 2);

  gridDim = (float)height / 2;
  gridPos = sf::Vector2u((width - gridDim) / 2, (height - gridDim) / 2);
  cellDim = gridDim / 3;
  shapeDim = cellDim * 0.5;
}

void Game::delayedMove() {
  int ms = rand() % 2000;
  sf::sleep(sf::milliseconds(ms));
  Move m = state.generateRandom().value();
  state.make(m);
}

void Game::loop() {
  while (window.isOpen()) {
    window.clear(sf::Color::White);
    drawGrid();
    drawState();

    if (!state.ended())
      window.display();

    if (!state.ended() && state.getTurn() == Value::circle) {
      sf::Thread thread(&Game::delayedMove, this);
      thread.launch();
    }

    drawState();

    if (state.ended()) {
      auto winner = state.winner();
      if (winner.has_value())
        drawWinner(winner.value());
      else
        drawTie();
    }

    if (hasToQuit)
      window.close();

    sf::Event event;
    while (window.pollEvent(event)) {
      process(event);
    }

    window.display();
  }
}

void Game::process(sf::Event event) {
  switch (event.type) {
  case sf::Event::KeyPressed:
    if (event.key.code == sf::Keyboard::Key::Q)
      hasToQuit = true;
    if (event.key.code == sf::Keyboard::Key::R && state.ended())
      state = State();
    break;
  case sf::Event::Closed:
    hasToQuit = true;
    break;
  case sf::Event::Resized:
    window.setView(
        sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
    width = event.size.width;
    height = event.size.height;

    center = sf::Vector2f((float)width / 2, (float)height / 2);

    gridDim = (float)height / 2;
    gridPos = sf::Vector2u((width - gridDim) / 2, (height - gridDim) / 2);
    cellDim = gridDim / 3;
    shapeDim = cellDim * 0.5;
    break;
  case sf::Event::LostFocus:
  case sf::Event::GainedFocus:
  case sf::Event::TextEntered:
  case sf::Event::KeyReleased:
  case sf::Event::MouseWheelMoved:
  case sf::Event::MouseWheelScrolled:
  case sf::Event::MouseButtonPressed:
    if (event.mouseButton.button == sf::Mouse::Left) {
      unsigned int x = event.mouseButton.x;
      unsigned int y = event.mouseButton.y;

      if ((x >= gridPos.x && x <= gridPos.x + gridDim) &&
          (y >= gridPos.y && y <= gridPos.y + gridDim)) {
        Value turn = state.getTurn();

        if (turn == Value::cross) {
          sf::Vector2u cell = findClosestCell(x, y);
          Move m = Move(cell.x, cell.y, turn);
          state.make(m);
        }
      }
    }
    break;
  case sf::Event::MouseButtonReleased:
  case sf::Event::MouseMoved:
  case sf::Event::MouseEntered:
  case sf::Event::MouseLeft:
  case sf::Event::JoystickButtonPressed:
  case sf::Event::JoystickButtonReleased:
  case sf::Event::JoystickMoved:
  case sf::Event::JoystickConnected:
  case sf::Event::JoystickDisconnected:
  case sf::Event::TouchBegan:
  case sf::Event::TouchMoved:
  case sf::Event::TouchEnded:
  case sf::Event::SensorChanged:
  case sf::Event::Count:
    break;
  }
}

sf::Vector2u Game::findClosestCell(unsigned int x, unsigned int y) {
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      if (gridPos.x + i * cellDim <= x && x < gridPos.x + (i + 1) * cellDim &&
          gridPos.y + j * cellDim <= y && y < gridPos.y + (j + 1) * cellDim)
        return sf::Vector2u(i, j);
    }
  }

  return sf::Vector2u(0, 0);
}

sf::Vector2f Game::cellCenter(sf::Vector2u cell) {
  unsigned int row = cell.x;
  unsigned int col = cell.y;
  return sf::Vector2f((float)gridPos.x + row * cellDim + cellDim / 2,
                      (float)gridPos.y + col * cellDim + cellDim / 2);
}

void Game::drawCross(sf::Vector2u cell) {
  float lineLength = shapeDim * std::tan(45.f);

  sf::RectangleShape line1(sf::Vector2f(lineLength, 8.f));
  sf::RectangleShape line2(sf::Vector2f(lineLength, 8.f));

  line1.setOrigin(sf::Vector2f(lineLength / 2, 4.f));
  line2.setOrigin(sf::Vector2f(lineLength / 2, 4.f));

  sf::Vector2f cellCenterPos = cellCenter(cell);
  line1.setPosition(cellCenterPos);
  line2.setPosition(cellCenterPos);

  line1.rotate(45.f);
  line2.rotate(135.f);

  line1.setFillColor(sf::Color::Black);
  line2.setFillColor(sf::Color::Black);

  window.draw(line1);
  window.draw(line2);
}

void Game::drawCircle(sf::Vector2u cell) {
  sf::CircleShape circle(shapeDim / 2);
  circle.setOutlineThickness(8.f);

  circle.setFillColor(sf::Color::Transparent);
  circle.setOutlineColor(sf::Color::Black);

  circle.setOrigin(sf::Vector2f(shapeDim / 2, shapeDim / 2));

  sf::Vector2f cellCenterPos = cellCenter(cell);
  circle.setPosition(cellCenterPos);

  window.draw(circle);
}

void Game::drawGrid() {
  sf::RectangleShape vertLine1(sf::Vector2f((float)gridDim, 8.f));
  sf::RectangleShape vertLine2(sf::Vector2f((float)gridDim, 8.f));
  sf::RectangleShape horLine1(sf::Vector2f((float)gridDim, 8.f));
  sf::RectangleShape horLine2(sf::Vector2f((float)gridDim, 8.f));

  vertLine1.setOrigin((float)gridDim / 2, 4.f);
  vertLine2.setOrigin((float)gridDim / 2, 4.f);
  horLine1.setOrigin((float)gridDim / 2, 4.f);
  horLine2.setOrigin((float)gridDim / 2, 4.f);

  vertLine1.setPosition(center);
  vertLine2.setPosition(center);
  horLine1.setPosition(center);
  horLine2.setPosition(center);

  vertLine1.move(sf::Vector2f(-(float)gridDim / 6, 0.0f));
  vertLine2.move(sf::Vector2f((float)gridDim / 6, 0.0f));
  horLine1.move(sf::Vector2f(0.0f, -(float)gridDim / 6));
  horLine2.move(sf::Vector2f(0.0f, (float)gridDim / 6));

  vertLine1.rotate(90.f);
  vertLine2.rotate(90.f);

  vertLine1.setFillColor(sf::Color::Black);
  vertLine2.setFillColor(sf::Color::Black);
  horLine1.setFillColor(sf::Color::Black);
  horLine2.setFillColor(sf::Color::Black);

  window.draw(vertLine1);
  window.draw(vertLine2);
  window.draw(horLine1);
  window.draw(horLine2);
}

void Game::drawState() {
  auto field = state.getField();

  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      auto cell = field[i * 3 + j];
      auto cellIndex = sf::Vector2u(i, j);

      if (cell.has_value())
        cell == Value::circle ? drawCircle(cellIndex) : drawCross(cellIndex);
    }
  }
}

void Game::drawWinner(Value winner) {
  sf::Text text;
  sf::Font font;
  font.loadFromFile("fonts/Roboto-Medium.ttf");

  text.setFont(font);

  if (winner == Value::circle)
    text.setString("Circle won!");
  else
    text.setString("Cross won!");

  text.setCharacterSize(96);

  text.setFillColor(sf::Color::Black);

  text.setStyle(sf::Text::Bold);

  text.setOrigin(text.getGlobalBounds().width / 2,
                 text.getGlobalBounds().height / 2);

  text.setPosition(center.x, 50.f);

  window.draw(text);
}

void Game::drawTie() {
  sf::Text text;
  sf::Font font;
  font.loadFromFile("fonts/Roboto-Medium.ttf");

  text.setFont(font);

  text.setString("Tie!");

  text.setCharacterSize(96);

  text.setFillColor(sf::Color::Black);

  text.setStyle(sf::Text::Bold);

  text.setOrigin(text.getGlobalBounds().width / 2,
                 text.getGlobalBounds().height / 2);

  text.setPosition(center.x, 50.f);

  window.draw(text);
}

void Game::run() { loop(); }