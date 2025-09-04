#include "get_next_line_bonus.h"

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
	static char *leftover[OPEN_MAX];
	char buff[BUFFER_SIZE + 1];
	char *str;
	int bytes_read;
	
	if((fd < 0) || (BUFFER_SIZE <= 0) || (BUFFER_SIZE > INT_MAX))
		return NULL;		
	if(leftover[fd] == NULL)
	{
		allocate_memory(&str, 1);
		str[0] = '\0';
		leftover[fd] = str;
	}
	bytes_read = 1;
	while((ft_strchr(leftover[fd], '\n') == NULL && bytes_read > 0))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if(bytes_read > 0)
			update_leftover(&leftover[fd], buff, bytes_read);
	}
	if(ft_strchr(leftover[fd], '\n') != NULL)
		return(line_with_newline(&leftover[fd]));
	return(line_without_newline(&leftover[fd]));
}	


// #include <stdio.h>
// #include <fcntl.h>

// int main(int argc, char **argv)
// {
//     int i = 1;
//     int j;
//     int fd;
//     char *line;
//     while(i <= argc)
//     {
//         fd = open(argv[i], O_RDONLY);
//         j = 0;
//         while((line = get_next_line(fd)))
//         {
//             printf("file[%d][%d]: %s", i,j, line);
//             j++;
//             free(line);
//         }
//         printf("\n");
//         close(fd);
//         i++;
//     }
//     return(0);
// }
