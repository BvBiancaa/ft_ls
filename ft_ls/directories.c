#include "ft_ls.h"

void set_path(char *path)
{
    int i;
    DIR *a;

    i = 0;
    if (flags.path)
    {
        while (flags.path[i])
            i++;
    }
    a = opendir(path);
    if (!a)
    {
        if (errno == ENOENT)
        {
            write(2, "ls: cannot access '", 19);
            write(2, path, ft_strlen(path));
            write(2, "': No such file or directory\n", 29);
            flags.paths_nbr--;
            flags.exit_status = 2;
        }
        else
            flags.path[i] = path;
    }
    else
        flags.path[i] = path;
    closedir(a);
}

char    *get_dir_name(char *s)
{
    int i;

    i = ft_strlen(s);
    while (s[--i])
        if (s[i] == '/')
            return (s + i);
    return (s);
}

void    get_total_size(char *path, char **content)
{
    int i;
    int len;
    struct stat file_stat;
    char    *tmp;
    char    *temp;

    i = 0;
    while (content[i])
    {
        if (content[i][0] == '/')
            tmp = ft_strjoin(content[i], "");
        else
        {
            temp = ft_strjoin(path, "/");
            tmp = ft_strjoin(temp, content[i]);
            free(temp);
        }
        if (lstat(tmp, &file_stat) == -1)
            return (free(tmp));
        flags.total_size += file_stat.st_blocks;
        len = count_nbr_len((long long)file_stat.st_size);
        if (flags.longest_nbr < len)
            flags.longest_nbr = len;
        free(tmp);
        i++;
    }
    write(1, "total ", 7);
    ft_putnbr(flags.total_size / 2);
    write(1, "\n", 1);
}

int get_files_nbr_flags(char *path, int err)
{
    DIR             *dir;
    struct dirent   *entry;
    int             nbr;

    dir = opendir(path);
    if (!dir)
    {
        if (flags.exit_status == 0)
            flags.exit_status = err;
        return (0);
    }
    nbr = 0;
    while (1)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (entry->d_name[0] == '.' && flags.flag_a == 0 && flags.flag_f == 0)
            continue ;
        nbr++;
    }
    closedir(dir);
    return (nbr);
}
