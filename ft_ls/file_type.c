#include "ft_ls.h"

char *get_file_type(const char *path)
{
    struct stat file_stat;

    if (lstat(path, &file_stat) == -1)
        return (NULL);
    //if ((file_stat.st_mode & S_IFMT) == S_IFDOOR)
    //    return "do";  // Door
    //else if (S_ISMPC(file_stat.st_mode))
    //    return "mh";  // Multi-hardlink
    //else if (S_ISNAM(file_stat.st_mode))
    //    return "pi";  // Named pipe (FIFO)
    //else if (S_ISPORT(file_stat.st_mode))
    //    return "so";  // Portal
    //else if (S_ISWHT(file_stat.st_mode))
    //    return "do";  // Whiteout
    if (S_ISFIFO(file_stat.st_mode))
        return "pi";  // Pipe (FIFO)
    else if (S_ISSOCK(file_stat.st_mode))
        return "so";  // Socket
    else if (S_ISLNK(file_stat.st_mode))
        return "ln";  // Symbolic link
    else if (S_ISBLK(file_stat.st_mode))
        return "bd";  // Block device
    //else if (S_ISDIR(file_stat.st_mode) && (file_stat.st_mode & S_IFMT) == S_IFDOOR)
    //    return "do";
    else if (S_ISDIR(file_stat.st_mode) && (file_stat.st_mode & S_IWOTH) && (file_stat.st_mode & S_ISVTX))
        return "ow";
    else if ((S_ISDIR(file_stat.st_mode) && (file_stat.st_mode & S_IWOTH)))
        return "tw";
    else if ((file_stat.st_mode & S_ISGID) && (file_stat.st_mode & S_IXGRP))
        return "sg";  // Setgid executable
    else if ((file_stat.st_mode & S_ISUID) && (file_stat.st_mode & S_IXUSR))
        return "su";  // Setuid executable
    else if (S_ISCHR(file_stat.st_mode))
        return "cd";  // Character device
    else if ((file_stat.st_mode & S_ISVTX) && (file_stat.st_mode & S_IWOTH))
        return "ca";
    else if (S_ISVTX & file_stat.st_mode)
        return "st";  // Sticky
    else if (S_ISDIR(file_stat.st_mode))
        return "di";  // Directory
    else if (S_IXUSR & file_stat.st_mode)
        return "ex";  // Executable
    else if (S_ISREG(file_stat.st_mode) && (file_stat.st_nlink > 1))
        return "mh";
    else if (S_ISLNK(file_stat.st_mode) && file_stat.st_nlink <= 1)
        return "or";
    else if (S_ISREG(file_stat.st_mode))
        return "rs";  // Regular file
    else
        return "??";  // Other file type
}