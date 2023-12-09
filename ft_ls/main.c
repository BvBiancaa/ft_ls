#include "ft_ls.h"

int main(int ac, char **av, char **env)
{
    (void)av;
    if (ac == 1)
        read_curr_dir(ft_getcwd("PWD", env), env);
    else
        parse_flags(ac, av, env);
    return (0);
}