#include "ft_ls.h"

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