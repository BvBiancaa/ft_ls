/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuni <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:57:23 by bmuni             #+#    #+#             */
/*   Updated: 2022/12/05 17:52:59 by bmuni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

ssize_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str || str == NULL)
		return (1);
	while (str[i])
		i++;
	return (i);
}
