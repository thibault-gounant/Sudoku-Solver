#include <SFML/Graphics.hpp>

#include <iostream>

#define WIDTH 800
#define HEIGHT 600


int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sudoku Solver");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));
        window.display();
    }

    return EXIT_SUCCESS;
}
