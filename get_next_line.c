#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void allocate_memory(char **str, int len)
{
	*str = malloc(len + 1);
	if(!*str)
		return;
}

static char *line_with_newline(char **leftover)
{
	int i;
	int len;
	int total_len;
	char *temp;
	char *line;
	char *str;
	i = 0;
	while((*leftover)[i] != '\n')
		i++;
	len = i + 1;
	allocate_memory(&line, len);
	ft_strncpy(line, *leftover, len);
	total_len = ft_strlen(*leftover);
	total_len -= i;
	allocate_memory(&str, total_len);
	ft_strncpy(str, *leftover + len, total_len);
	temp = str;
	free(*leftover);
	*leftover = temp;
	return line;
}

static char *line_without_newline(char **leftover)
{
	int len;
	char *line;
	if(*leftover && **leftover)
	{
		len = ft_strlen(*leftover);
		allocate_memory(&line, len);
		ft_strcpy(line, *leftover);
		free(*leftover);
		*leftover = NULL;
		return line;
	}

	free(*leftover);
	*leftover = NULL;
	return NULL;
}

static void	update_leftover(char **static_var, char *buff, int bytes_read)
{
	char *temp;
	int total_len = 0;
	char *str;

	if(bytes_read < 0)
	{
		free(*static_var);
		*static_var = NULL;
	}
	buff[bytes_read] = '\0';
	total_len = (ft_strlen(*static_var) + bytes_read);
	allocate_memory(&str, total_len);
	ft_strcpy(str, *static_var);
	ft_strcat(str, buff);
	temp = str;
	free(*static_var);
	*static_var = temp;
}

char *get_next_line(int fd)
{
	static char *leftover = NULL;
	char buff[BUFFER_SIZE + 1];
	char *str;
	int bytes_read;
	
	if((fd < 0) || (BUFFER_SIZE <= 0) || (BUFFER_SIZE > INT_MAX))
		return NULL;		
	if(leftover == NULL)
	{
		allocate_memory(&str, 1);
		str[0] = '\0';
		leftover = str;
	}
	bytes_read = 1;
	while((ft_strchr(leftover, '\n') == NULL && bytes_read > 0))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if(bytes_read > 0)
			update_leftover(&leftover, buff, bytes_read);
	}
	if(ft_strchr(leftover, '\n') != NULL)
		return(line_with_newline(&leftover));
	return(line_without_newline(&leftover));
}	

// #include <fcntl.h>
// int main()
// {
// 	int i;
// 	int fd;
// 	char *line;
// 	fd = open("text.txt", O_RDONLY);
// 	if(fd == -1)
// 		perror("Error");
// 	i = 1;
// 	while((line = get_next_line(fd)))
// 	{
// 		printf("line[%d]: %s",i, line);
// 		i++;
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
