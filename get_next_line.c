/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahal <hrahal@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:59:18 by hrahal            #+#    #+#             */
/*   Updated: 2025/09/10 13:44:11 by hrahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*null_check(char **leftover, char *line)
{
	free(*leftover);
	*leftover = NULL;
	return (line);
}

static char	*line_with_newline(char **leftover)
{
	int		i;
	int		len;
	int		total_len;
	char	*line;
	char	*str;

	i = 0;
	while ((*leftover)[i] && (*leftover)[i] != '\n')
		i++;
	len = i + 1;
	line = malloc(len + 1);
	if (!line)
		return (null_check(leftover, NULL));
	ft_strncpy(line, *leftover, len);
	total_len = (ft_strlen(*leftover) - len);
	if (total_len == 0)
		return (null_check(leftover, line));
	str = malloc(total_len + 1);
	if (!str)
		return (free(line), null_check(leftover, NULL));
	ft_strncpy(str, *leftover + len, total_len);
	free(*leftover);
	*leftover = str;
	return (line);
}

static char	*line_without_newline(char **leftover)
{
	int		len;
	char	*line;
	int		total_len;

	if (*leftover && **leftover)
	{
		total_len = ft_strlen(*leftover);
		len = ft_strlen(*leftover);
		line = malloc(len + 1);
		if (!line)
			return (null_check(leftover, NULL));
		ft_strncpy(line, *leftover, total_len);
		return (null_check(leftover, line));
	}
	return (null_check(leftover, NULL));
}

static char	*update_leftover(char **leftover, char *buff, int bytes_read)
{
	char	*temp;
	int		total_len;
	char	*str;

	total_len = 0;
	if (bytes_read < 0)
	{
		return (null_check(leftover, NULL));
	}
	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		total_len = (ft_strlen(*leftover) + bytes_read);
		str = malloc(total_len + 1);
		if (!str)
			return (null_check(leftover, NULL));
		ft_strncpy(str, *leftover, total_len);
		ft_strcat(str, buff);
		temp = str;
		free(*leftover);
		*leftover = temp;
	}
	return (*leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		*buff;
	ssize_t		bytes_read;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || ((size_t)BUFFER_SIZE > INT_MAX - 1))
		return (NULL);
	if (leftover == NULL)
		leftover = ft_strdup("");
	if (leftover == NULL)
		return (NULL);
	bytes_read = 1;
	while ((ft_strchr(leftover, '\n') == NULL && bytes_read > 0))
	{
		buff = malloc((size_t)BUFFER_SIZE + 1);
		if (!buff)
			return (free(leftover), leftover = NULL, NULL);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (!update_leftover(&leftover, buff, bytes_read))
			return (free(buff), NULL);
		free(buff);
	}
	if (ft_strchr(leftover, '\n') != NULL)
		return (line_with_newline(&leftover));
	return (line_without_newline(&leftover));
}
