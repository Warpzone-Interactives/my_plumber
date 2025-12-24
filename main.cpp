/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "include/my.hpp"

/* Explication de trucs chelous :
std = "l'origine" de la classe
ifstream = classe Input File Stream (c'est dans le nom)
(filepath) c'est un input.open(filepath) en plus simple
input.get(c) ça va chopper les caractères et les mettre dans la variable c un par un jusqu'à '\0'.
*/
void read_file(char *filepath)
{
    std::ifstream input(filepath);
    char c;

    if (!input.is_open())
        return;
    while (input.get(c))
        printf("%c", c);
    return;
}

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "First window");
    read_file(av[1]);
    while (window.isOpen())
        handle_window(&window);
    return 0;
}
