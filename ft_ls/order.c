#include "ft_ls.h"


void    reverse_order(char **content, int len)
{
    int     i;
    char    *tmp;

    i = 0;
    while (i < len / 2)
    {

        tmp = content[len - i - 1];
        content[len - i - 1] = content[i];
        content[i] = tmp;
        i++;
    }
}

void    order_by_time(char **content, int len)
{
    ssize_t seconds[len];
    ssize_t tmp;
    char    *temp;
    struct stat sb;
    int i;

    i = 0;
    while (i < len)
    {
        if (lstat(content[i], &sb) == -1)
        {
            flags.exit_status = 2;
            return ;
        }
        seconds[i] = sb.st_mtime;
        i++;
    }
    i = 0;
    while (i < len - 1)
    {
        if (seconds[i + 1] && seconds[i] < seconds[i + 1])
        {
            temp = content[i];
            content[i] = content[i + 1];
            content[i + 1] = temp;
            tmp = seconds[i];
            seconds[i] = seconds[i + 1];
            seconds[i + 1] = tmp;
            i = -1;
        }
        i++;
    }
}

void    order_dir(char **content, int len)
{
    int i;
    char    *tmp;

    i = 0;
    if (flags.flag_big_u > 0 && flags.flag_t < flags.flag_big_u) //to check??
        return ;
    if (flags.flag_t > 0)
        order_by_time(content, len);
    else
    {
        while (i < len - 1)
        {
            if (content[i + 1] && ft_strcmp_mod(content[i], content[i + 1]) > 0)
            {
                tmp = content[i];
                content[i] = content[i + 1];
                content[i + 1] = tmp;
                i = -1;
            }
            i++;
        }
    }
    if (flags.flag_r > 0)
        reverse_order(content, len);
}

void    order_dir_by_time(void)
{
    ssize_t seconds[flags.paths_nbr];
    ssize_t tmp;
    char    *temp;
    struct stat sb;
    size_t i;

    i = 0;
    while (i < flags.paths_nbr)
    {
        if (lstat(flags.path[i], &sb) == -1)
            return ;
        seconds[i] = sb.st_mtime;
        i++;
    }
    i = 0;
    while (i < flags.paths_nbr - 1)
    {
        if (seconds[i + 1] && seconds[i] < seconds[i + 1])
        {
            temp = flags.path[i];
            flags.path[i] = flags.path[i + 1];
            flags.path[i + 1] = temp;
            tmp = seconds[i];
            seconds[i] = seconds[i + 1];
            seconds[i + 1] = tmp;
            i = -1;
        }
        i++;
    }
}

void    reverse_dir_order(void)
{
    size_t     i;
    char    *tmp;

    i = 0;
    while (i < flags.paths_nbr / 2)
    {
        tmp = flags.path[flags.paths_nbr - i - 1];
        flags.path[flags.paths_nbr - i - 1] = flags.path[i];
        flags.path[i] = tmp;
        i++;
    }
}

void    order_dirs(void)
{
    size_t i;
    char    *tmp;

    if (flags.flag_t > 0 && flags.flag_f == 0)
        order_dir_by_time();
    else if (flags.flag_f == 0)
    {
        i = 0;
        if (flags.flag_big_u > 0 && flags.flag_t < flags.flag_big_u)
            return ;
        while (i < flags.paths_nbr - 1)
        {
            if (flags.path[i + 1] && ft_strcmp_mod(flags.path[i], flags.path[i + 1]) > 0)
            {
                tmp = flags.path[i];
                flags.path[i] = flags.path[i + 1];
                flags.path[i + 1] = tmp;
                i = -1;
            }
            i++;
        }
    }
    if (flags.flag_r > 0 && flags.flag_f == 0)
        reverse_dir_order();
}