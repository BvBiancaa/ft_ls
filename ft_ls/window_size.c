#include "ft_ls.h"

int get_window_size(void)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    {
        write(2, "ioctl error\n", 12);
        return (0);
    }
    return (ws.ws_col);
}