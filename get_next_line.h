#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
char    *ft_strncpy(char *dst, const char *src, int len);
char	*ft_strcat(char *dst, const char *src);
int		ft_strlen(char *str);

#endif