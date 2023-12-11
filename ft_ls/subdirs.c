#include "ft_ls.h"

void    read_subdir(DIR *dir, char **env, char *path)
{
    struct dirent   *entry;
    char        *tmp;
    char            **content;
    int            index;
    int     file_nbr;
    int     padding;

    index = 0;
    flags.padding = 0;
    flags.tot_len = 0;
    flags.total_size = 0;
    file_nbr = get_files_nbr_flags(path, 1);
    write(1, "\n", 1);
    content = (char **)malloc(sizeof(char *) * (file_nbr + 1));
    if (!content)
    {
        if (flags.exit_status == 0)
            flags.exit_status = 1;
        return ;
    }
    while (index < file_nbr)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (entry->d_name[0] == '.' && flags.flag_a == 0 && flags.flag_f == 0)
            continue ;
        tmp = ft_strjoin(path, "/");
        content[index] = ft_strjoin(tmp, entry->d_name);
        free(tmp);
        padding = ft_strlen(entry->d_name);
        flags.tot_len += padding + 2;
        if (padding > flags.padding)
            flags.padding = padding;
        index++;
    }
    content[index] = NULL;
    if (content)
        print_dir_flags(content, file_nbr, path, env);
    if (flags.flag_rec > 0)
        read_subdirs(path, content, env);
    free_double(content);
    closedir(dir);
}

void    is_subfolder(char *path, char *name, char **env)
{
    char    *full_path;
    char    *tmp;
    DIR     *fd;

    if (ft_strcmp(".", name) == 0 || ft_strcmp("..", name) == 0)
        return ;
    if (name[0] != '/' && path[ft_strlen(path) - 1] != '/')
    {
        tmp = ft_strjoin(path, "/");
        full_path = ft_strjoin(tmp, name);
        free(tmp);
    }
    else if (name[0] != '/')
        full_path = ft_strjoin(path, name);
    else
        full_path = ft_strjoin(name, "");
    fd = opendir(full_path);
    if (fd)
        read_subdir(fd, env, full_path);
    free(full_path);
}

void    read_subdirs(char *path, char **content, char **env)
{
    int i;

    i = 0;
    if (!content)
        return ;
    while (content[i])
    {
        is_subfolder(path, content[i], env);
        i++;
    }
}