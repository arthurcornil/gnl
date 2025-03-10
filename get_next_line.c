#include "get_next_line.h"

void	destroy_packet(t_packet *packet)
{
	if (packet->buffer)
		free(packet->buffer);
	if (packet)
		free(packet);
}

void	destroy_packets(t_packet *packets)
{
	t_packet	*next_packet;
	while (packets)
	{
		next_packet = packets->next;
		destroy_packet(packets);
		packets = next_packet;
	}
}


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

void	append_packet(char *buffer, t_packet **packets)
{
	t_packet *last_packet;
	t_packet *new_packet;

	last_packet = get_last_packet(*packets);
	new_packet = (t_packet *)malloc(sizeof(t_packet));
	if (!new_packet)
	{
		destroy_packets(*packets);
		*packets = NULL;
		free(buffer);
		return ;
	}
	new_packet->buffer = buffer;
	new_packet->next = NULL;
	if (last_packet)
		last_packet->next = new_packet;
	else
		*packets = new_packet;
}

void	add_packets(t_packet **packets, int fd)
{
	char		*buffer;
	ssize_t		chars_read;
	
	chars_read = 1;
	while(!found_new_line(*packets))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
		{
			destroy_packets(*packets);
			*packets = NULL;
			return ;
		}
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[chars_read] = 0;
		append_packet(buffer, packets);
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
			break ;
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
			break ;
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

void	refresh_packets(t_packet **packets)
{
	t_packet	*ptr;
	t_packet	*clean_packet;
	char		*new_str;
	int			i;

	ptr = *packets;
	while (ptr)
	{
		i = 0;
		while (ptr->buffer[i] && ptr->buffer[i] != '\n')
			i ++;
		if (ptr->buffer[i] == '\n')
		{
			new_str = ft_strdup(ptr->buffer + i + 1);
			if (!new_str)
			{
				destroy_packets(*packets);
				*packets = NULL;
				return ;
			}
			clean_packet = (t_packet *)malloc(sizeof(t_packet));
			if (!clean_packet)
			{
				destroy_packets(*packets);
				*packets = NULL;
				return ;
			}
			clean_packet->buffer = new_str;
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
	if (!*curr_line)
	{
		destroy_packets(packets);
		free(curr_line);
		curr_line = NULL;
	}
	return (curr_line);
}
