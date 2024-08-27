// Copyright 2024 Me

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <entt/entt.hpp>

struct Color {
  sf::Color color;
};

struct RectangleBody {
  float width;
  float height;
};

struct Position {
  float x;
  float y;
};

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 360), "My window");
  // If key repeat is not disabled, then the key will repeat at a frequency
  // determined by the OS, which is not practical for this code to predict.
  window.setKeyRepeatEnabled(false);

  entt::registry registry;

  auto paddle = registry.create();
  registry.emplace<Color>(paddle, sf::Color::Blue);
  registry.emplace<RectangleBody>(paddle, 80.f, 40.f);
  registry.emplace<Position>(paddle, 100.f, 200.f);

  bool quit{false};
  while (!quit) {
    // check all the window's events that were triggered since the loop's last
    // iteration
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        quit = true;
      }
    }

    window.clear(sf::Color::Black);

    auto rectangles =
        registry.view<const Position, const RectangleBody, const Color>();

    rectangles.each([&window](const auto &position, const auto &rectangleBody,
                              const auto &color) {
      sf::RectangleShape rectangle(
          sf::Vector2f(rectangleBody.width, rectangleBody.height));
      rectangle.setFillColor(color.color);
      rectangle.setPosition(position.x, position.y);
      window.draw(rectangle);
    });

    window.display();
  }

  return 0;
}
