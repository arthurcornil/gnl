#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_packet
{
	char	*buffer;
	struct s_packet	*next;
}	t_packet;

char	*get_next_line(int fd);

#endif
