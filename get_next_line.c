/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:59:25 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/14 08:12:17 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_packet	*get_last_packet(t_packet *packets)
{
	while(packets && packets->next)
		packets = packets->next;
	return (packets);
}

bool	found_new_line(t_packet *packets)
{
	t_packet	*last_packet;
	int			i;

	last_packet = get_last_packet(packets);
	i = 0;
	while (last_packet && last_packet->buffer[i])
	{
		if (last_packet->buffer[i] == '\n')
			return (true);
		i ++;
	}
	return (false);
}

void	ft_lstadd_back(t_packet **lst, t_packet *new)
{
	t_packet	*p;

	if (!lst)
		return ;
	p = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (p->next)
		p = p->next;
	p->next = new;
}

void	add_packets(t_packet **packets, int fd)
{
	ssize_t		chars_read;
	t_packet	*new_packet;
	
	while(!found_new_line(*packets))
	{
		new_packet = (t_packet *)malloc(sizeof(t_packet));
		if (!new_packet)
			return ;
		new_packet->next = NULL;
		chars_read = read(fd, new_packet->buffer, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			free(new_packet);
			return ;
		}
		new_packet->buffer[chars_read] = 0;
		ft_lstadd_back(packets, new_packet);
	}
}

char	*packets_to_str(t_packet *packets)
{
	ssize_t		strlen;
	t_packet	*ptr;
	char		*str;
	int			i;
	int			j;

	ptr = packets;
	strlen = 0;
	i = 0;
	while (ptr)
	{
		i = 0;
		while (ptr->buffer[i] && ptr->buffer[i] != '\n')
		{
			i ++;
			strlen ++;
		}
		if (ptr->buffer[i] == '\n')
		{
			strlen ++;
			break ;
		}
		ptr = ptr->next;
	}
	str = (char *)malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (NULL);
	ptr = packets;
	i = 0;
	while (ptr)
	{
		j = 0;
		while (ptr->buffer[j] && ptr->buffer[j] != '\n')
		{
			str[i] = ptr->buffer[j];
			j ++;
			i ++;
		}
		if (ptr->buffer[j] == '\n')
		{
			str[i] = ptr->buffer[j];
			i ++;
			break ;
		}
		ptr = ptr->next;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i])
		i ++;
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i ++;
	}
	new_str[i] = 0;
	return (new_str);
}

void	ft_strcpy(char dst[BUFFER_SIZE + 1], const char *src)
{	
	while (*src != 0)
	{
		*dst = *src;
		dst ++;
		src ++;
	}
	*dst = 0;
}

void	refresh_packets(t_packet **packets)
{
	t_packet	*ptr;
	t_packet	*clean_packet;
	int			i;

	ptr = *packets;
	while (ptr)
	{
		i = 0;
		while (ptr->buffer[i] && ptr->buffer[i] != '\n')
			i ++;
		if (ptr->buffer[i] == '\n')
		{
			clean_packet = (t_packet *)malloc(sizeof(t_packet));
			if (!clean_packet)
			{
				destroy_packets(*packets);
				*packets = NULL;
				return ;
			}
			ft_strcpy(clean_packet->buffer, ptr->buffer + i + 1);
			clean_packet->next = ptr->next;
			destroy_packet(ptr);
			*packets = clean_packet;
			return ;
		}
		clean_packet = ptr->next;
		destroy_packet(ptr);
		*packets = clean_packet;
		ptr = clean_packet;
	}
}

char	*get_next_line(int fd)
{
	static t_packet	*packets = NULL;
	char			*curr_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &curr_line, 0) < 0)
		return (NULL);
	add_packets(&packets, fd);
	if (!packets)
	{
		destroy_packets(packets);
		return (NULL);
	}
	curr_line = packets_to_str(packets);
	if (!curr_line)
	{
		destroy_packets(packets);
		return (NULL);
	}
	refresh_packets(&packets);
	if (!*curr_line && !packets)
	{
		destroy_packets(packets);
		free(curr_line);
		curr_line = NULL;
	}
	return (curr_line);
}
