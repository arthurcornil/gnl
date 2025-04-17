/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:14:32 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/17 15:14:33 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*p;

	p = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char) c;
		i ++;
	}
	b = (void *) p;
	return (b);
}

bool	found_nl(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (true);
		str ++;
	}
	return (false);
}

size_t	ft_linelen(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] && str[i] != '\n')
		i ++;
	if (str[i] == '\n')
		i ++;
	return (i);
}
