/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:09:04 by arcornil          #+#    #+#             */
/*   Updated: 2025/05/01 17:09:39 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat_packet(char *packet, char *str)
{
	char	*newstr;
	size_t	packet_len;
	size_t	strlen;
	size_t	i;
	size_t	j;

	packet_len = ft_linelen(packet);
	strlen = ft_linelen(str);
	newstr = (char *)malloc(sizeof(char) * (packet_len + strlen + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		newstr[i] = str[i];
		i ++;
	}
	j = 0;
	while (packet[j] && packet[j] != '\n')
		newstr[i++] = packet[j++];
	if (packet[j] == '\n')
		newstr[i++] = packet[j];
	newstr[i] = 0;
	free(str);
	return (newstr);
}

void	clean_packet(char *packet)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (packet[i] && packet[i] != '\n')
		i ++;
	if (!packet[i])
	{
		ft_memset(packet, 0, (size_t)BUFFER_SIZE);
		return ;
	}
	i ++;
	j = 0;
	while (i < BUFFER_SIZE)
		packet[j++] = packet[i++];
	ft_memset(packet + j, 0, i - j);
}

bool	packets_to_str(char *packet, int fd, char **str)
{
	ssize_t	read_chars;
	ssize_t	i;
	size_t	j;

	read_chars = 1;
	j = 0;
	while ((j == 0 || !found_nl(packet)) && read_chars > 0)
	{
		i = 0;
		if (!(j == 0 && ft_linelen(packet)))
		{
			read_chars = read(fd, packet, BUFFER_SIZE);
			if (read_chars < 0 || (read_chars == 0 && (*str || !*packet)))
				return (false);
			i += read_chars;
			ft_memset(packet + i, 0, (size_t)(BUFFER_SIZE - i));
		}
		*str = concat_packet(packet, *str);
		if (!*str)
			return (false);
		j ++;
	}
	return (true);
}

char	*get_next_line(int fd)
{
	char		*curr_line;
	static char	*packets[OPEN_MAX] = {NULL};	

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0
		|| read(fd, &curr_line, 0) < 0)
		return (NULL);
	curr_line = NULL;
	if (!packets[fd])
	{
		packets[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!packets[fd])
			return (NULL);
		ft_memset(packets[fd], 0, (sizeof(char) * (BUFFER_SIZE + 1)));
	}
	if (!packets_to_str(packets[fd], fd, &curr_line))
	{
		free(packets[fd]);
		packets[fd] = NULL;
	}
	if (packets[fd])
		clean_packet(packets[fd]);
	return (curr_line);
}
