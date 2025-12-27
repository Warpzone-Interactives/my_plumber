/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** map related functions
*/

#include "include/my.hpp"

/* Explication de trucs chelous :
std = "l'origine" de la classe (ici standard)
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

/* Explication de trucs chelous :
std::vector = tableau
<std::string> = char *
std::vector<std::string> = un tableau de char * donc un char **
getline va mettre toute une ligne du fichier dans un string et supprimer le \n
on skip la première ligne car c'est le biome
on rajoute le \n (on peut faire un += frr c'est goatesque)
map.push_back(line) append line à la fin de map.
*/
std::vector<std::string> load_map(std::string filepath)
{
    std::ifstream input(filepath);
    std::vector<std::string> map;
    std::string line;

    getline(input, line);
    while (getline(input, line)) {
        line += '\n';
        map.push_back(line);
    }
    return map;
}
