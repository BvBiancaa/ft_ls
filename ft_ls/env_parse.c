#include "ft_ls.h"

int	ft_strcmp_mod(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
    char    c;
    char    c1;

	i = 0;
	j = 0;
	while (s1[i])
    {
        c = s1[i];
        c1 = s2[j];
		if (c1 == '.' && c != '.')
		{
			j++;
			continue ;
		}
		if (c == '.' && c1 != '.')
		{
			i++;
			continue ;
		}
        if (c >= 65 && c <= 90)
            c += 32;
        if (c1 >= 65 && c1 <= 90)
            c1 += 32;
        if (c != c1)
            return (c - c1);
		i++;
		j++;
    }
	return (0);
}

int	find_str(const char *s, const char *s1)
{
	int i = 0;
	for (; s[i] && s1[i] && s[i] == s1[i]; i++)
		;
	if (s[i] == '\0' || s1[i] == '=')
		return (i + 1);
	return (-1);
}

char	*ft_getenv(const char *s, char **env)
{
	char	*ret;
	ssize_t	index;
	
	index = 0;
	ret = NULL;
	for (ssize_t i = 0; env[i]; i++)
	{
		index = find_str(s, env[i]);
		if (index > 0 && index <= ft_strlen(env[i]))
		{
			ret = env[i] + index;
			index = i;
			break ;
		}
	}
	return (ret);
}

char    *ft_getcwd(char *s, char **env)
{
    char    *cwd;

    cwd = ft_getenv(s, env);
    if (!cwd)
        return (NULL);
    return (cwd);
}