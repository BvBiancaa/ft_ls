#include "ft_ls.h"

int main(int ac, char **av, char **env)
{
    int return_code;

    if (ac == 1)
        return_code = read_curr_dir(ft_getcwd("PWD", env), env);
    else
        return_code = parse_flags(ac, av, env);
    return (return_code);
}