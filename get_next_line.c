/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danperez <danperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:37:43 by danperez          #+#    #+#             */
/*   Updated: 2024/12/18 15:10:10 by danperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	storage = temp_storage(fd, storage, buffer);
	free(buffer);
	if (!storage || storage[0] == '\0')
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
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
	if (storage[len] == '\n')
		line = malloc(sizeof(char) * (len + 2));
	else
		line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	memcpy(line, storage, len);
	if (storage[len] == '\n')
	{
		line[len] = '\n';
		line[len + 1] = '\0';
	}
	else
		line[len] = '\0';
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

char	*temp_storage(int fd, char *storage, char *buffer)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && (!storage || !ft_strchr(storage, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(storage);
			return(NULL);
		}
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		if (!storage)
			storage = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(storage, buffer);
			free(storage);
			storage = temp;
		}
	}
	return (storage);
}

/* int	main(void)
{
	int		text;
	char	*buffer;
	size_t		i;

	i = 0;
	text = open("text.txt", O_RDONLY | O_CREAT);
	while ((buffer = get_next_line(text)) != NULL)
	{
		i++;
		printf("%ld %s", i, buffer);
		free(buffer);
	}
	close(text);
	return (0);
}
 */