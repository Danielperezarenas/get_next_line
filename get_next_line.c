/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danperez <danperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:37:43 by danperez          #+#    #+#             */
/*   Updated: 2024/11/28 13:19:24 by danperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*next_line;
	int			bytes_read;

	bytes_read = 0;
	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (!storage)
			storage = strdup(buffer);
		else
			storage = temp_storage(storage, buffer);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free(buffer);
	if (!storage || storage[0] == '\0')
		return (NULL);
	next_line = line(storage);
	storage = next(storage);
	return (next_line);
}

char	*line(char *storage)
{
	char	*line;
	size_t	len;

	len = 0;
	while (storage[len] && storage[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	strncpy(line, storage, len + 1);
	if (storage[len] == '\n')
		line[len++] = '\n';
	line[len++] = '\0';
	return (line);
}

char	*next(char *storage)
{
	char	*new_line;
	char	*next;

	next = ft_strchr(storage, '\n');
	if (!next)
	{
		free(storage);
		return (NULL);
	}
	new_line = ft_strdup(next + 1);
	free(storage);
	return (new_line);
}

char	*temp_storage(char *storage, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(storage, buffer);
	free(storage);
	storage = temp;
	return (storage);
}

/*
int	main(void)
{
	int		text;
	char	*buffer;

	text = open("text.txt", O_RDONLY | O_CREAT);
	while ((buffer = get_next_line(text)) != NULL)
	{
		printf("%s", buffer);
		free(buffer);
	}
	close(text);
	return (0);
}
*/