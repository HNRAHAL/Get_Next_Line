#ifndef GET_NEXT_LINE_BONUS_H
#define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

#define FD_MAX 1024

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char    *ft_strncpy(char *dst, const char *src, int len);
char	*ft_strcat(char *dst, const char *src);
int		ft_strlen(char *str);
char    *ft_strdup(char *str);


#endif