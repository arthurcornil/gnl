#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <string.h>

int main(void)
{
	//int fd = open("dummy", O_RDONLY);
	char *line = NULL;
	while (1)
	{
		line = get_next_line(1);
		if (!line)
		{
			free(line);
			break ;
		}
		printf("%s", line);
		free(line);
	}
}
