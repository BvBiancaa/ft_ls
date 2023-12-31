#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <sys/ioctl.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>

#include "Libft/libft.h"

#ifndef FT_LS_H
# define FT_LS_H


//# ifndef S_ISPORT
//#  define S_ISPORT(mode) (((mode) & S_IFMT) == S_IFPORT)
//# endif

#define ANSI_COLOR_RESET   "\x1b[0m"

#define FLAG_ERROR(flags) \
    ({ \
            write(2, "ls: invalid option -- \'e\'\nTry \'ls --help\' for more information.\n", 65); \
            free(flags.path); \
            return -1; \
    })

typedef struct s_flags
{
    size_t flag_a;
    size_t flag_f;
    size_t flag_l;
    size_t flag_r;
    size_t flag_rec;
    size_t flag_t;
    size_t flag_big_T;
    size_t flag_big_u;
    size_t total_size;
    char    **path;
    size_t paths_nbr;
    int     longest_nbr;
    char    *ln_name;
    int     padding;
    int     winsize;
    int     tot_len;
    int     exit_status;
} t_flags;

extern struct s_flags flags;

char    *ft_getcwd(char *s, char **env);
int read_curr_dir(char *path, char **env);
int	ft_strcmp_mod(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
int parse_flags(int ac, char **av, char **env);
char	*ft_getenv(const char *s, char **env);
int	find_str(const char *s, const char *s1);
int get_window_size(void);
void    free_double(char **s);
char *get_file_type(const char *path);
void    print_file(char *sign, char *name, char **env);
void	ft_putnbr(ssize_t n);
void    is_subfolder(char *path, char *name, char **env);
void    attach_current_path(char *name, char **env);
void    read_dir(DIR *dir, char **env, char *path);
int    parse_path(char **env);
int get_files_nbr_flags(char *path, int err);
int	ft_strcmp(char *s1, char *s2);
void    read_subdirs(char *path, char **content, char **env);
int	count_nbr_len(ssize_t n);
void    order_dir(char **content, int len);
void    order_dirs(void);
void set_path(char *path);
char    *get_dir_name(char *s);
void    get_total_size(char *path, char **content);
int get_files_nbr_flags(char *path, int err);
int    check_flag(char c, size_t count);
void count_paths(int ac, char **av, char **env);
int    parse_path(char **env);
void    attach_current_path(char *name, char **env);
void    display_version(void);
void    display_help(void);
void    read_subdirs(char *path, char **content, char **env);
void    is_subfolder(char *path, char *name, char **env);
void    read_subdir(DIR *dir, char **env, char *path);
void    print_dir_flags(char **content, int len, char *path, char **env);

#endif