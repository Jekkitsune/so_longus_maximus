/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:08:36 by fparis            #+#    #+#             */
/*   Updated: 2023/11/27 16:47:02 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_buffer(char *buffer)
{
	int		i;
	int		i2;
	char	*buff2r;

	i = 0;
	i2 = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer || buffer[i] == '\0')
	{
		ft_free(&buffer, NULL);
		return (NULL);
	}
	while (buffer[i + 1 + i2])
		i2++;
	buff2r = malloc(sizeof(char) * (i2 + 1));
	if (!buff2r)
		return (NULL);
	while (i2 >= 0)
	{
		buff2r[i2] = buffer[i + 1 + i2];
		i2--;
	}
	free(buffer);
	return (buff2r);
}

static char	*fill_line(char *buffer, char *line_src)
{
	int		i;
	char	*line;

	if (!buffer || buffer[0] == '\0')
		return (line_src);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i > 0)
	{
		i--;
		line[i] = buffer[i];
	}
	line_src = ft_mallocat(line_src, line);
	return (line_src);
}

static int	has_full_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*read_next_line(char **buffer, char **line, int fd)
{
	ssize_t		readed;

	readed = BUFFER_SIZE;
	while (readed == BUFFER_SIZE && !has_full_line(*line))
	{
		if (*buffer)
			free(*buffer);
		*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		readed = read(fd, *buffer, BUFFER_SIZE);
		*line = fill_line(*buffer, *line);
		if ((!*buffer || readed < 0) || (readed == 0 && !*line))
		{
			ft_free(buffer, line);
			return (NULL);
		}
		if (*line == NULL)
			return (NULL);
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer = NULL;

	line = NULL;
	if (buffer)
	{
		line = fill_line(buffer, line);
		buffer = clean_buffer(buffer);
		if (buffer)
			return (line);
	}
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = read_next_line(&buffer, &line, fd);
	if (!line)
		return (NULL);
	buffer = clean_buffer(buffer);
	return (line);
}
