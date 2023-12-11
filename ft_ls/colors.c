#include "ft_ls.h"

int	find_color(const char *s, const char *s1)
{
	int i;
    int j;

    i = -1;
    j = 0;
	while (s[++i])
    {
		if (s[i] == s1[j])
        {
		    while (s[i + j] == s1[j] && s1[j])
                j++;
            if (s[i + j] == '=' && s1[j] == '\0')
                return (i + j);
            j = 0;
        }
    }
	return (-1);
}

char    *parse_ls_colors(char *sign, char **env)
{
    char    ret[10] = {0};
    char    *env_color;
    int     tmp;
    int     index;
    int     bg_check;

    bg_check = 0;
    env_color = ft_getenv("LS_COLORS", env);
    if (!env_color)
        return (NULL);
    tmp = find_color(env_color, sign) + 1;
    if (tmp <= 0)
        return (NULL);
    index = 0;
    while (env_color[tmp] && env_color[tmp] != ':')
    {
        ret[index] = env_color[tmp];
        if (ret[index] == ';')
            bg_check += 1;
        index++;
        tmp++;
    }
    if (index <= 1)
        return (NULL);
    ret[index] = 'm';
    env_color = ft_strjoin("\x1b[", ret);
    return (env_color);
}

char   *parse_extention(char *name, char *sign, char **env)
{
    int i;
    char    *ret;

    i = 0;
    while (name[i])
        i++;
    while (name[i] != '.' && i > 0)
        i--;
    if (i == 0)
        return (parse_ls_colors(sign, env));
    ret = parse_ls_colors(name + i, env);
    if (ret != NULL)
        return (ret);
    return (parse_ls_colors(sign, env));
}

char    *get_name(char *s)
{
    int i;

    i = ft_strlen(s);
    while (s[--i])
        if (s[i] == '/')
            return (s + i + 1);
    return (s);
}

char    *no_day(char *s)
{
    int i;
    int count;

    i = -1;
    count = 0;
    while (s[++i])
    {
        while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
            i++;
        count++;
        while ((s[i] < 9 || s[i] > 13) && s[i] != 32)
            i++;
    }
    i = -1;
    if (count >= 5)
    {
        while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
            i++;
        while ((s[i] < 9 || s[i] > 13) && s[i] != 32)
            i++;
        while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
            i++;
    }
    return (s + i);
}

char    *year_or_hour(char *s, int *flag)
{
    char    year[6] = {0};
    int     i;
    int     y;
    int     date_year;
    time_t current_time;

    current_time = time(NULL);
    date_year = current_time / (365.25 * 24 * 60 * 60);
    i = ft_strlen(s) - 2;
    while (s[i] >= '0' && s[i] <= '9')
        i--;
    y = -1;
    while (s[i++] && ++y < 4)
        year[y] = s[i];
    i = ft_atoi(year);
    y = 1;
    if (i < date_year + 1970)
    {
        date_year = i;
        i = ft_strlen(s);
        while (s[--i])
        {
            if (s[i] == ':')
            {
                i -= 5;
                while (s[i] && y < 5)
                {
                    s[i] = date_year / (10000 / (ft_potenza(y))) + 48;
                    date_year = date_year - (date_year / (10000 / (ft_potenza(y))) * (10000 / (ft_potenza(y))));
                    y++;
                    i++;
                }
                s[++i] = '\0';
            }
        }
        *flag = 1;
    }
    else
    {
        i = ft_strlen(s) - 8;
        s[i] = '\0';
        *flag = 0;
    }
    return (s);
}

void    handle_acl(char *path)
{
    ssize_t acl_size;
    char *acl_buffer;
    ssize_t result;

    acl_size = getxattr(path, "system.posix_acl_default", NULL, 0);

    if (acl_size == -1)
        return;
    acl_buffer = (char *)malloc(acl_size);
    result = getxattr(path, "system.posix_acl_default", acl_buffer, acl_size);
    if (result > 0)
        write(1, acl_buffer, acl_size);
}

void    handle_extendedattr(char *path)
{
    ssize_t xattr_size;
    char *xattr_buffer;
    ssize_t result;

    xattr_size = listxattr(path, NULL, 0);
    if (xattr_size == -1)
        return;
    xattr_buffer = (char *)malloc(xattr_size);
    result = listxattr(path, xattr_buffer, xattr_size);
    if (result == -1)
        return (free(xattr_buffer));
    write(1, xattr_buffer, xattr_size);
    free(xattr_buffer);
}

void    print_file_info(char *name)
{
    struct stat file_stat;
    struct passwd *user_info;
    struct group *group_info;
    char    *time;
    int     padding;

    if (lstat(name, &file_stat) == -1)
        return ;
    group_info = getgrgid(file_stat.st_gid);
    user_info = getpwuid(file_stat.st_uid);
    write(1, (S_ISDIR(file_stat.st_mode)) ? "d" : S_ISLNK(file_stat.st_mode)? "l" : "-", 1);
    write(1, (file_stat.st_mode & S_IRUSR) ? "r" : "-", 1);
    write(1, (file_stat.st_mode & S_IWUSR) ? "w" : "-", 1);
    write(1, (file_stat.st_mode & S_IXUSR) ? "x" : "-", 1);
    write(1, (file_stat.st_mode & S_IRGRP) ? "r" : "-", 1);
    write(1, (file_stat.st_mode & S_IWGRP) ? "w" : "-", 1);
    write(1, (file_stat.st_mode & S_IXGRP) ? "x" : "-", 1);
    write(1, (file_stat.st_mode & S_IROTH) ? "r" : "-", 1);
    write(1, (file_stat.st_mode & S_IWOTH) ? "w" : "-", 1);
    write(1, (file_stat.st_mode & S_IXOTH) ? "x" : "-", 1);
    handle_acl(name);
    handle_extendedattr(name);
    write(1, " ", 1);
    ft_putnbr((unsigned long)file_stat.st_nlink);
    write(1, " ", 1);
    write(1, group_info->gr_name, ft_strlen(group_info->gr_name));
    write(1, " ", 1);
    write(1, user_info->pw_name, ft_strlen(user_info->pw_name));
    write(1, " ", 1);
    padding = flags.longest_nbr - count_nbr_len((long long)file_stat.st_size) + 1;
    while (--padding > 0)
        write(1, " ", 1);
    ft_putnbr((long long)file_stat.st_size);
    write(1, " ", 1);
    time = ctime(&file_stat.st_mtime);
    if (flags.flag_big_T < 1)
    {
        time = no_day(time);
        time = year_or_hour(time, &padding);
    }
    write(1, time, ft_strlen(time) - 1);
    if (padding == 1)
        write(1, " ", 1);
    write(1, " ", 1);
}

void    get_link_info(char *name)
{
    char target[4096];

    ssize_t len = readlink(name, target, sizeof(target) - 1);

    if (len > 0)
    {
        write(1, " -> ", 4);
        write(1, target, len);
    }
    write(1, "\n", 1);
}

void    print_file(char *sign, char *name, char **env)
{
    char    *color;
    int     len;

    if (sign == NULL)
        return ;
    if (flags.flag_l > 0)
        print_file_info(name);
    if (name[0] == '/')
        name = get_name(name);
    if (flags.flag_f == 0)
        color = parse_extention(name, sign, env);
    if (color != NULL)
        write(1, color, ft_strlen(color));
    write(1, name, ft_strlen(name));
    write(1, ANSI_COLOR_RESET, sizeof(ANSI_COLOR_RESET) - 1);
    free(color);
    if (flags.flag_l > 0)
        get_link_info(name);
    if (flags.tot_len > flags.winsize)
    {
        flags.winsize -= ft_strlen(name);
        len = flags.padding - ft_strlen(name) + 1;
        if (len > flags.winsize)
        {
            flags.winsize = get_window_size();
            write(1, "\n", 1);
        }
        else
            while (--len >= 0)
            {
                flags.winsize--;
                write(1, " ", 1);
            }
    }
    else if (flags.flag_l < 1)
        write(1, "  ", 2);
}