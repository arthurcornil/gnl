/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:32:16 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/11 11:32:37 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	destroy_packet(t_packet *packet)
{
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

