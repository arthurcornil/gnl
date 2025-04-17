/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:14:46 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/17 15:14:49 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>

char	*get_next_line(int fd);
void	*ft_memset(void *b, int c, size_t len);
bool	found_nl(char *str);
size_t	ft_linelen(char *str);

#endif
