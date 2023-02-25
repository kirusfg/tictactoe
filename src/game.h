#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>

#include "state.h"

class Game {
  State state;

  unsigned int width;
  unsigned int height;
  sf::ContextSettings settings;
  sf::RenderWindow window;

  sf::Vector2f center;

  sf::Vector2u gridPos;
  float gridDim;
  float cellDim;
  float shapeDim;

  bool hasToQuit;
  bool hasEnded;

  void loop();
  void process(sf::Event);

  void delayedMove();

  sf::Vector2u findClosestCell(unsigned int x, unsigned int y);
  sf::Vector2f cellCenter(sf::Vector2u cell);

  void drawCross(sf::Vector2u cell);
  void drawCircle(sf::Vector2u cell);
  void drawGrid();
  void drawState();
  void drawWinner(Value);
  void drawTie();

public:
  Game(unsigned int width = 800, unsigned int height = 600);

  void run();
};

#endif
