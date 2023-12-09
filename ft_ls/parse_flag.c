#include "ft_ls.h"

struct s_flags flags = {
    .flag_a = 0,
    .flag_f = 0,
    .flag_g = 0,
    .flag_l = 0,
    .flag_r = 0,
    .flag_rec = 0,
    .flag_t = 0,
    .flag_big_T = 0,
    .flag_big_u = 0,
    .total_size = 0
};

void set_path(char *path)
{
    int i;

    i = 0;
    if (flags.path)
    {
        while (flags.path[i])
            i++;
    }
    flags.path[i] = path;
}

void    display_version(void)
{
    write(1, "ls (ft_ls) 1.0\n", 15);
    write(1, "This is free software: you are free to change and redistribute it.\n", 68);
    write(1, "There is NO WARRANTY, to the extent permitted by law.\n\n", 56);
    write(1, "Written by: bmuni.\n", 20);
}

void    display_help(void)
{
    write(1, "Usage: ls [OPTION]... [FILE]...\n", 33);
    write(1, "List information about the FILEs (the current directory by default).\n", 70);
    write(1, "Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n", 75);
    write(1, "\n", 1);
    write(1, "Mandatory arguments to long options are mandatory for short options too.\n", 74);
/*     write(1, "  -a, --all                  do not ignore entries starting with .\n", 68);
    write(1, "  -d, --directory            list directories themselves, not their contents\n", 78);
    write(1, "  -f                         do not sort, enable -aU, disable -ls --color\n", 75);
    write(1, "  -g                         like -l, but do not list owner\n", 62);
    write(1, "  -l                         use a long listing format\n", 56);
    write(1, "  -r, --reverse              reverse order while sorting\n", 59);
    write(1, "  -R, --recursive            list subdirectories recursively\n", 63);
    write(1, "  -t                         sort by modification time, newest first\n", 69);
    write(1, "  -u                         with -lt: sort by, and show, access time\n", 70);
    write(1, "                             with -l: show access time and sort by name\n", 73);
    write(1, "                             otherwise: sort by access time\n", 62);
    write(1, "  -U                         do not sort; list entries in directory order\n", 74);
    write(1, "  --color[=WHEN]             colorize the output; WHEN can be 'always' (default\n", 80);
    write(1, "                             if omitted), 'auto', or 'never'; more info below\n", 80);
    write(1, "  --help                     display this help and exit\n", 58);
    write(1, "  --version                  output version information and exit\n", 68);
    write(1, "\n", 1); */
}

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
            return ;
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
    return ;
}

void    order_dir(char **content, int len)
{
    int i;
    char    *tmp;

    i = 0;
    if (flags.flag_big_u > 0 && flags.flag_t < flags.flag_big_u)
        return ;
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
    if (flags.flag_t > 0)
        order_by_time(content, len);
    if (flags.flag_r > 0)
        reverse_order(content, len);
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
        write(1, "\n.", 2);
        write(1, tmp, ft_strlen(tmp));
        write(1, ":\n", 2);
    }
    else if (flags.flag_rec > 0)
    {
        write(1, "\n.", 2);
        write(1, path, ft_strlen(path));
        write(1, ":\n", 2);
    }
    i = -1;
    if (flags.flag_l > 0)
        get_total_size(path, content);
    flags.winsize = get_window_size();
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
    if (get_files_nbr_flags(path) && flags.flag_l < 1)
        write(1, "\n", 1);
}

int get_files_nbr_flags(char *path)
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
        if (entry->d_name[0] == '.' && flags.flag_a == 0 && flags.flag_f == 0)
            continue ;
        nbr++;
    }
    closedir(dir);
    return (nbr);
}

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
    file_nbr = get_files_nbr_flags(path);
    content = (char **)malloc(sizeof(char *) * (file_nbr + 1));
    if (!content)
        return ;
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
    file_nbr = get_files_nbr_flags(path);
    content = (char **)malloc(sizeof(char *) * (file_nbr + 1));
    if (!content)
        return ;
    while (index < file_nbr)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
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

void    attach_current_path(char *name, char **env)
{
    char    *tmp;
    char    *tmp2;

    tmp = ft_getcwd("PWD", env);
    tmp2 = ft_strjoin(tmp, "/");
    free(tmp);
    name = ft_strjoin(tmp2, name);
    free(tmp2);
}

void    parse_path(char **env)
{
    static int  i;
    static int  x;
    DIR             *fd;

    while (flags.path[i])
    {
        if (flags.path[i][0] == '~')
            flags.path[i] = ft_getenv("HOME", env);
        if (flags.path[i][0] != '/')
            attach_current_path(flags.path[i], env);
        fd = opendir(flags.path[i]);
        if (!fd)
        {
            write(2, "ls: cannot access '", 19);
            write(2, flags.path[i], ft_strlen(flags.path[i]));
            write(2, "': No such file or directory\n", 29);
            i++;
            return ;
        }
        i++;
        parse_path(env);
        read_dir(fd, env, flags.path[x]);
        x++;
    }
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

int    check_flag(char c, size_t count)
{
    switch (c)
    {
        case 'a':
            flags.flag_a = count;
            break;
        case 'f':
            flags.flag_f = count;
            break;
        case 'g':
            flags.flag_g = count;
            break;
        case 'l':
            flags.flag_l = count;
            break;
        case 'r':
            flags.flag_r = count;
            break;
        case 'R':
            flags.flag_rec = count;
            break;
        case 't':
            flags.flag_t = count;
            break;
        case 'T':
            flags.flag_big_T = count;
            break;
        case 'U':
            flags.flag_big_u = count;
            break;
        default:
            FLAG_ERROR(flags);
    }
    return (0);
}

int parse_flags(int ac, char **av, char **env)
{
    int i;
    int y;
    size_t count;
    
    count_paths(ac, av, env);
    i = 0;
    count = 1;
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
                    return -1;
                count++;
            }
        }
        else
            set_path(av[i]);
    }
    parse_path(env);
    free(flags.path);
    return (0);
}