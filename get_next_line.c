#include "get_next_line.h"

static char	*null_check(char **leftover, char *line)
{
	free(*leftover);
	*leftover = NULL;
	return (line);
}

static char	*line_with_newline(char **leftover)
{
	int			i;
	int			len;
	int			total_len;
	char		*line;
	char		*str;

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
		return (null_check(leftover, NULL));
	ft_strncpy(str, *leftover + len, total_len);
	free(*leftover);
	*leftover = str;
	return (line);
}

static char	*line_without_newline(char **leftover)
{
	int		len;
	char	*line;
	int 	total_len;

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
	int			bytes_read;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (BUFFER_SIZE > INT_MAX))
		return (NULL);
	if (leftover == NULL)
		leftover = ft_strdup("");
	bytes_read = 1;
	while ((ft_strchr(leftover, '\n') == NULL && bytes_read > 0))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if(!buff)	
			return NULL;
		bytes_read = read(fd, buff , BUFFER_SIZE);
		update_leftover(&leftover, buff, bytes_read);
		free(buff);
	}
	if (ft_strchr(leftover, '\n') != NULL)
		return (line_with_newline(&leftover));
	return (line_without_newline(&leftover));
}


#include <stdio.h>
#include <fcntl.h>
int main()
{
	int i;
	int fd;
	// char buf[10] = {0};
	char *line;
	fd = open("t.txt", O_RDONLY);
	if(fd == -1)
		perror("Error");
	i = 1;
	while((line = get_next_line(fd)))
	{
		printf("line[%d]: %s",i, line);
		i++;
		free(line);
	}
	close(fd);
	return (0);
}