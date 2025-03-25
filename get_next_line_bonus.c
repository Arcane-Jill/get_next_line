/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:28:57 by nmeintje          #+#    #+#             */
/*   Updated: 2025/03/25 11:59:48 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_join_free(char *buff1, char *buff2)
{
	char	*temp;

	if (!buff1 || ! buff2)
		return (NULL);
	temp = ft_strjoin(buff1, buff2);
	if (!temp)
	{
		free(buff1);
		buff1 = NULL;
		return (NULL);
	}
	free(buff1);
	return (temp);
}

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
	{
		free(buffer);
		free(line);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer [i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer [i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_read_file(int fd, char *res)
{
	char	*buffer;
	int		bytes_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (ft_clean(res, buffer));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = 0;
		res = ft_join_free(res, buffer);
		if (!res)
			return (ft_clean(res, buffer));
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char    *get_next_line(int fd)
{
        static char     *buffer[OPEN_MAX];
        char            *line;

        if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || fd >= OPEN_MAX)
                return (NULL);
	if (buffer[fd] == NULL)
	{
		buffer[fd] = malloc(BUFFER_SIZE + 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = 0;
	}
        buffer[fd] = ft_read_file(fd, buffer[fd]);
        if (!buffer[fd])
        {
                free(buffer[fd]);
                return (NULL);
        }
        line = ft_line(buffer[fd]);
        if (!line)
        {
                free(buffer[fd]);
                buffer[fd] = NULL;
                return (NULL);
        }
        buffer[fd] = ft_next(buffer[fd]);
        return (line);
}


/* This is my original version, but it has some problems improvements above
 *
char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
	{
		free(buffer[fd]);
		return (NULL);
	}
	line = ft_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}*/
