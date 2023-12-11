#include "ft_ls.h"

struct s_flags flags = {
    .flag_a = 0,
    .flag_f = 0,
    .flag_l = 0,
    .flag_r = 0,
    .flag_rec = 0,
    .flag_t = 0,
    .flag_big_T = 0,
    .flag_big_u = 0,
    .total_size = 0,
    .exit_status = 0
};

void    print_dir_flags(char **content, int len, char *path, char **env)
{
    int i;
    char    *tmp;
    char    *full_path;

    if (flags.flag_f == 0)
        order_dir(content, len);
    if (flags.flag_rec > 0 && flags.paths_nbr == 0 && path == ft_getcwd("PWD", env))
        write(1, ".:\n", 3);
    else if (flags.paths_nbr == 0 && flags.flag_rec > 0)
    {
        tmp = get_dir_name(path);
        write(1, ".", 1);
        write(1, tmp, ft_strlen(tmp));
        write(1, ":\n", 2);
    }
    else if (flags.flag_rec > 0 || flags.paths_nbr > 1)
    {
        write(1, ".", 1);
        write(1, path, ft_strlen(path));
        write(1, ":\n", 2);
    }
    i = -1;
    if (flags.flag_l > 0)
        get_total_size(path, content);
    flags.winsize = get_window_size();
    if (!(*content) || *content == NULL)
    {
        flags.exit_status = 2;
        return ;
    }
    while (content[++i])
    {
        if (content[i][0] == '/')
            full_path = ft_strjoin(content[i], "");
        else
        {
            tmp = ft_strjoin(path, "/");
            full_path = ft_strjoin(tmp, content[i]);
            free(tmp);
        }
        print_file(get_file_type(full_path), full_path, env);
        free(full_path);
    }
    if (get_files_nbr_flags(path, 2) && flags.flag_l < 1)
        write(1, "\n", 1);
}

void    read_dir(DIR *dir, char **env, char *path)
{
    struct dirent   *entry;
    char            **content;
    int            index;
    int     file_nbr;
    int     print_flag;

    index = 0;
    flags.padding = 0;
    flags.tot_len = 0;
    flags.total_size = 0;
    file_nbr = get_files_nbr_flags(path, 2);
    content = (char **)malloc(sizeof(char *) * (file_nbr + 1));
    if (!content)
    {
        flags.exit_status = 2;
        return ;
    }
    while (index < file_nbr)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        //printf("ENTRY %s\n", entry->d_name);
        if (entry->d_name[0] == '.' && flags.flag_a == 0 && flags.flag_f == 0)
            continue ;
        content[index] = entry->d_name;
        print_flag =  ft_strlen(content[index]);
        flags.tot_len += print_flag + 2;
        if (print_flag > flags.padding)
            flags.padding = print_flag;
        index++;
    }
    content[index] = NULL;
    if (content)
        print_dir_flags(content, file_nbr, path, env);
    if (flags.flag_rec > 0)
        read_subdirs(path, content, env);
    closedir(dir);
    free(content);
}

int parse_flags(int ac, char **av, char **env)
{
    int i;
    int y;
    size_t count;
    
    count_paths(ac, av, env);
    count = 1;
    i = 0;
    while (++i < ac)
    {
        y = -1;
        while (av[i][++y] && ((av[i][y] >= 9 && av[i][y] <= 13) || av[i][y] == 32))
            ;
        if (av[i][y] == '-')
        {
            if (ft_strcmp_mod(av[i], "--help") == 0)
            {
                display_help();
                return (0) ;
            }
            if (ft_strcmp_mod(av[i], "--version") == 0)
            {
                display_version();
                return (0) ;
            }
            while (av[i][++y])
            {
                if (check_flag(av[i][y], count))
                    return (flags.exit_status = 2);
                count++;
            }
        }
        else
            set_path(av[i]);
    }
    if (flags.paths_nbr > 0)
    {
        flags.path[flags.paths_nbr] = NULL;
        order_dirs();
    }
    parse_path(env);
    free(flags.path);
    return (flags.exit_status);
}