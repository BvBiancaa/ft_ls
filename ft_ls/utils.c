#include "ft_ls.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		n;
	char	*ret;

	i = 0;
	n = 0;
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ret == NULL)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		ret[i + n] = s2[n];
		n++;
	}
	ret[i + n] = '\0';
	return (ret);
}

void    free_double(char **s)
{
    int i;

    i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
}

void	ft_putnbr(ssize_t n)
{
	size_t	nb;

	if (n < 0)
	{
		write(1, "-", 1);
		nb = n * -1;
	}
	else
		nb = n;
	if (nb >= 10)
		ft_putnbr(nb / 10);
	nb = nb % 10 + 48;
	write(1, &nb, 1);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

int	count_nbr_len(ssize_t n)
{
	int	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}