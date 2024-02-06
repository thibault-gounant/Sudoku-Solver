#include <SFML/Graphics.hpp>

#include "core.h"
#include "utils.h"


int main(int argc, char* argv[]) {

    if (argc != 3) {
        print_usage(argv);
        return EXIT_FAILURE;
    }

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
