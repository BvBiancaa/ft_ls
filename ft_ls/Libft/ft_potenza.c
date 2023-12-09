/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_potenza.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuni <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:22:07 by bmuni             #+#    #+#             */
/*   Updated: 2022/11/06 12:31:27 by bmuni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_potenza(ssize_t n)
{
	int	res;

	res = 1;
	while (n < 0)
	{
		res /= 10;
		n--;
	}
	while (n > 0)
	{
		res *= 10;
		n--;
	}
	return (res);
}
