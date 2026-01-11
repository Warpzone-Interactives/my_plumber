/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "my.hpp"

general_stat init_general(char **av)
{
    general_stat g_stat;

    g_stat.status = 0;
    g_stat.where = get_where(av[1]);
    if (g_stat.where == "error") {
        g_stat.status = 84;
        return g_stat;
    }
    g_stat.map = load_map(av[1]);
    return g_stat;
}