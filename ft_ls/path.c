#include "ft_ls.h"

void    attach_current_path(char *name, char **env)
{
    char    *tmp;
    char    *tmp2;

    tmp = ft_getcwd("PWD", env);
    tmp2 = ft_strjoin(tmp, "/");
    name = ft_strjoin(tmp2, name);
    free(tmp2);
}

int    parse_path(char **env)
{
    static int  i;
    static int  x;
    DIR             *fd;

    while (flags.path[i])
    {
        fd = opendir(flags.path[i]);
        if (!fd)
        {
            if (errno == EACCES)
            {
                write(2, "ls: cannot access '", 19);
                write(2, flags.path[i], ft_strlen(flags.path[i]));
                write(2, "': Permission denied\n", 22);
                i++;
                flags.exit_status = 2;
            }
            return 2;
        }
        if (i > 0)
            write(1, "\n", 1);
        i++;
        read_dir(fd, env, flags.path[x]);
        x++;
        parse_path(env);
    }
    return (0);
}

void count_paths(int ac, char **av, char **env)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (++i < ac)
    {
        if (av[i][0] != '-')
            count++;
    }
    if (count == 0)
    {
        flags.path = malloc(sizeof(char *) * 2);
        flags.path[0] = ft_getcwd("PWD", env);
        flags.path[1] = NULL;
    }
    else
        flags.path = ft_calloc(count + 1, sizeof(char *));
    flags.paths_nbr = count;
}