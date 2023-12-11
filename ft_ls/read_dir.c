#include "ft_ls.h"

void    print_dir(char **content, int len, char *path, char **env)
{
    int i;
    char    *tmp;
    char    *full_path;

    i = 0;
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
    i = -1;
    while (content[++i])
    {
        tmp = ft_strjoin(path, "/");
        full_path = ft_strjoin(tmp, content[i]);
        free(tmp);
        print_file(get_file_type(full_path), content[i], env);
        free(full_path);
    }
    write(1, "\n", 1);
}

int get_files_nbr(char *path)
{
    DIR             *dir;
    struct dirent   *entry;
    int             nbr;

    dir = opendir(path);
    if (!dir)
        return (0);
    nbr = 0;
    while (1)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (entry->d_name[0] == '.')
            continue ;
        flags.padding += ft_strlen(entry->d_name);
        nbr++;
    }
    flags.winsize = get_window_size();
    closedir(dir);
    return (nbr);
}

int read_curr_dir(char *path, char **env)
{
    DIR             *dir;
    struct dirent   *entry;
    char            **content;
    int            index;
    int     file_nbr;

    index = 0;
    file_nbr = get_files_nbr(path);
    content = (char **)malloc(sizeof(char *) * (file_nbr + 1));
    if (!content)
        return (2);
    dir = opendir(path);
    if (!dir)
        return (2);
    while (index < file_nbr)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (entry->d_name[0] == '.')
            continue ;
        content[index] = entry->d_name;
        index++;
    }
    content[index] = NULL;
    if (content && content[0])
        print_dir(content, file_nbr, path, env);
    closedir(dir);
    free(content);
    return (0);
}