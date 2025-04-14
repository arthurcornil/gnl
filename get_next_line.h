#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_packet
{
	char			buffer[BUFFER_SIZE + 1];
	struct s_packet	*next;
}	t_packet;

char	*get_next_line(int fd);
void	destroy_packet(t_packet *packet);
void	destroy_packets(t_packet *packets);

#endif
