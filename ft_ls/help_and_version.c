#include "ft_ls.h"

void    display_version(void)
{
    write(1, "ls (ft_ls) 1.0\n", 15);
    write(1, "This is free software: you are free to change and redistribute it.\n", 68);
    write(1, "There is NO WARRANTY, to the extent permitted by law.\n\n", 56);
    write(1, "Written by: bmuni.\n", 20);
    write(1, "Curious about what this program can do? Try ./ft_ls --help.\n", 61);
    free(flags.path);
}

void    display_help(void)
{
    write(1, "Usage: ls [OPTION]... [FILE]...\n", 33);
    write(1, "List information about the FILEs (the current directory by default).\n", 70);
    write(1, "Sort entries alphabetically if none of -ftrU is specified.\n", 60);
    write(1, "\n", 1);
    write(1, "Ft_ls possible arguments:\n", 27);
    write(1, "  -a, (all)                  do not ignore entries starting with '.'.\n", 71);
    write(1, "  -f                         do not sort, equal to -aU, disable ft_ls colors.\n", 79);
    write(1, "  -l                         use a long listing format.\n", 57);
    write(1, "  -r, (reverse)              reverse order while sorting.\n", 59);
    write(1, "  -R, (recursive)            list subdirectories recursively.\n", 63);
    write(1, "  -t                         sort by modification time, newest first.\n", 71);
    write(1, "  -U                         do not sort; list entries in directory order.\n", 76);
    write(1, "  --help                     display this help and exit.\n", 58);
    write(1, "  --version                  output version information and exit.\n", 67);
    write(1, "\n", 1);
    write(1, "ft_ls emits color codes only when standard output is connected to a terminal.\n", 79);
    write(1, "The LS_COLORS environment variable can change the settings.\n", 61);
    write(1, "Use the dircolors command to set it.\n", 38);
    write(1, "Only with -r option colors are disabled by default.\n", 53);
    write(1, "\n", 1);
    write(1, "Exit status:\n", 14);
    write(1, " 0  if OK,\n", 12);
    write(1, " 1  if minor problems (e.g., cannot access subdirectory),\n", 59);
    write(1, " 2  if serious trouble (e.g., cannot access command-line argument).\n", 69);
    free(flags.path);
}