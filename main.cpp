#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

struct Enity
{
  sf::Vector2f position;
  sf::Vector2f velocity;

  sf::Vector2f size;

  sf::Vector3f color;
};

std::string inttostring(int x)
{
  std::stringstream type;
  type << x;
  return type.str();
}

bool checkCollision(int x, int y, int oWidth, int oHeight, int xTwo, int yTwo, int oTwoWidth, int oTwoHeight)
{
    // AABB 1
    int x1Min = x;
    int x1Max = x+oWidth;
    int y1Max = y+oHeight;
    int y1Min = y;

    // AABB 2
    int x2Min = xTwo;
    int x2Max = xTwo+oTwoWidth;
    int y2Max = yTwo+oTwoHeight;
    int y2Min = yTwo;

    // Collision tests
    if( x1Max < x2Min || x1Min > x2Max ) return false;
    if( y1Max < y2Min || y1Min > y2Max ) return false;

    return true;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "PONG game by Patys");
  
  window.setFramerateLimit(60);

  // Declare a new font
  sf::Font font;
  font.loadFromFile("conthrax-sb.ttf");
  

  // Create a text which uses our font
  sf::Text SCORE_TEXT;
  SCORE_TEXT.setFont(font);
  SCORE_TEXT.setCharacterSize(22);
  SCORE_TEXT.setPosition(350, 10);
  SCORE_TEXT.setString("Get a point!");

  Enity paddleone;
  paddleone.position = sf::Vector2f(10, 275);
  paddleone.size = sf::Vector2f(20,50);
  paddleone.color = sf::Vector3f(64,255,64);

  Enity paddletwo;
  paddletwo.position = sf::Vector2f(770, 275);
  paddletwo.size = sf::Vector2f(20,50);
  paddletwo.color = sf::Vector3f(64,64,255);

  sf::RectangleShape rect_paddleone;
  rect_paddleone.setSize(paddleone.size);
  rect_paddleone.setFillColor(sf::Color(paddleone.color.x, paddleone.color.y, paddleone.color.z));
  rect_paddleone.setPosition(paddleone.position);

  sf::RectangleShape rect_paddletwo;
  rect_paddletwo.setSize(paddletwo.size);
  rect_paddletwo.setFillColor(sf::Color(paddletwo.color.x, paddletwo.color.y, paddletwo.color.z));
  rect_paddletwo.setPosition(paddletwo.position);

  Enity ball;
  ball.position = sf::Vector2f(390, 290);
  ball.size = sf::Vector2f(20,20);
  ball.velocity = sf::Vector2f(3,-3);
  ball.color = sf::Vector3f(255,64,64);

  sf::CircleShape circle_ball;
  circle_ball.setRadius(10);
  circle_ball.setFillColor(sf::Color(ball.color.x, ball.color.y, ball.color.z));
  circle_ball.setPosition(ball.position);

  int SCORE_ONE = 0;
  int SCORE_TWO = 0;

  while (window.isOpen())
    {
      // Process events
      sf::Event event;
      while (window.pollEvent(event))
        {
	  // Close window: exit
	  if (event.type == sf::Event::Closed)
	    window.close();
        }

      // PADDLEONE
      
      if(paddleone.velocity.y < 0)
	paddleone.velocity.y += 0.2;
      else if(paddleone.velocity.y > 0)
	paddleone.velocity.y -= 0.2;

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	paddleone.velocity.y += 1;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	paddleone.velocity.y -= 1;

      if(paddleone.velocity.y > 4)
	paddleone.velocity.y = 4;
      else if(paddleone.velocity.y < -4)
	paddleone.velocity.y = -4;

      if(paddleone.position.y > 550)
	paddleone.velocity.y = -0.1;
      else if(paddleone.position.y < 0)
	paddleone.velocity.y = 0.1;

      paddleone.position += paddleone.velocity;

      rect_paddleone.setPosition(paddleone.position);


      //PADDLETWO

      if(paddletwo.velocity.y < 0)
	paddletwo.velocity.y += 0.2;
      else if(paddletwo.velocity.y > 0)
	paddletwo.velocity.y -= 0.2;

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	paddletwo.velocity.y += 1;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	paddletwo.velocity.y -= 1;

      if(paddletwo.velocity.y > 4)
	paddletwo.velocity.y = 4;
      else if(paddletwo.velocity.y < -4)
	paddletwo.velocity.y = -4;

      if(paddletwo.position.y > 550)
	paddletwo.velocity.y = -0.1;
      else if(paddletwo.position.y < 0)
	paddletwo.velocity.y = 0.1;

      paddletwo.position += paddletwo.velocity;

      rect_paddletwo.setPosition(paddletwo.position);

      // BALL

      if(ball.position.y < 0)
	ball.velocity.y = -ball.velocity.y;
      if(ball.position.y > 580)
	ball.velocity.y = -ball.velocity.y;

      if(ball.position.x < 0)
	{
	  ball.position.x = 390;
	  ball.position.y = 290;
	  // add point
	  SCORE_TWO += 1;
	  std::string textpoint = inttostring(SCORE_ONE) + " : " + inttostring(SCORE_TWO);
	  SCORE_TEXT.setString(textpoint);
	}
      if(ball.position.x > 800)
	{
	  ball.position.x = 390;
	  ball.position.y = 290;
	  // add point
	  SCORE_ONE += 1;
	  std::string textpoint = inttostring(SCORE_ONE) + " : " + inttostring(SCORE_TWO);
	  SCORE_TEXT.setString(textpoint);
	}


      if(checkCollision(ball.position.x, ball.position.y, ball.size.x, ball.size.y,
			paddleone.position.x, paddleone.position.y, paddleone.size.x, paddleone.size.y))
	{
	  ball.position.x += 1;
	  ball.velocity.x = -ball.velocity.x;
	}

      if(checkCollision(ball.position.x, ball.position.y, ball.size.x, ball.size.y,
			paddletwo.position.x, paddletwo.position.y, paddletwo.size.x, paddletwo.size.y))
	{
	  ball.position.x -= 1;
	  ball.velocity.x = -ball.velocity.x;
	}


      ball.position += ball.velocity;

      circle_ball.setPosition(ball.position);

      window.clear();
      window.draw(rect_paddleone);
      window.draw(rect_paddletwo);
      window.draw(circle_ball);
      window.draw(SCORE_TEXT);
      window.display();
    }
  return EXIT_SUCCESS;
}
