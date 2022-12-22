/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_finder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:28:39 by aaitouna          #+#    #+#             */
/*   Updated: 2022/11/02 00:28:40 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/leak_finder.h"

char	*get_cur_line(char *holder)
{
	int		i;
	char	*line;

	i = 0;
	if (!holder)
		return (NULL);
	while (holder[i] && holder[i++] != '\n')
		;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
	{
		line[i] = holder[i];
		i++;
	}
	if (holder[i] == '\n')
	{
		line[i] = holder[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*get_n_holder(char *holder)
{
	int		i;
	char	*n_holder;
	int		j;

	i = 0;
	if (!holder)
		return (NULL);
	while (holder[i] && holder[i++] != '\n')
		;
	if (!holder[i])
	{
		free(holder);
		return (NULL);
	}
	n_holder = malloc((gt_strlen(&holder[i]) + 1) * sizeof(char));
	if (!n_holder)
		return (NULL);
	j = 0;
	while (holder[i])
		n_holder[j++] = holder[i++];
	n_holder[j] = 0;
	free(holder);
	return (n_holder);
}

void	on_error(char *cursor, char *holder)
{
	free(cursor);
	if (holder)
		free(holder);
}

char	*get_next_line(int fd)
{
	static char		*holder[1024];
	char			*cursor;
	char			*line;
	ssize_t			reader;

	reader = 1;
	cursor = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (!gt_strchr(holder[fd], '\n') && reader != 0)
	{
		reader = read(fd, cursor, BUFFER_SIZE);
		if (reader == -1)
		{
			on_error(cursor, holder[fd]);
			holder[fd] = NULL;
			return (NULL);
		}
		cursor[reader] = 0;
		if (reader != 0)
			holder[fd] = gt_strjoin(holder[fd], cursor);
	}
	free(cursor);
	line = get_cur_line(holder[fd]);
	holder[fd] = get_n_holder(holder[fd]);
	return (line);
}
