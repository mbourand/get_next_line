/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:05:03 by mbourand          #+#    #+#             */
/*   Updated: 2019/11/18 14:41:23 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	newline(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	int				bytes;
	static char		buffer[4096][BUFFER_SIZE + 1];

	if (!line)
		return (-1);
	if (BUFFER_SIZE == 0)
	{
		*line = 0;
		return (-1);
	}
	*line = ft_strdup("", 0);
	while (newline(buffer[fd]) == -1)
	{
		if (!(*line = ft_strjoin(*line, buffer[fd], '\n')))
			return (-1);
		ft_bzero(buffer[fd], BUFFER_SIZE + 1);
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes <= 0)
			return (bytes);
	}
	if (!(*line = ft_strjoin(*line, buffer[fd], '\n')))
		return (-1);
	ft_strlcpy(buffer[fd], buffer[fd] + newline(buffer[fd]) + 1, BUFFER_SIZE);
	return (1);
}
