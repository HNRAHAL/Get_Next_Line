#include "get_next_line.h"

int ft_strlen(char *str)
{
	int i;
    i = 0;
	while(str[i])
		i++;
	return i;
}

char *ft_strchr(const char *s, int c)
{
	while(*s)
	{
		if(*s == (char)c)	
			return (char *)s;
		s++;
	}
	if((char)c == '\0')
		return (char *)s;
	return NULL;
}

char *ft_strcpy(char *dst, const char *src)
{
	int i;
	i = 0;
	while(src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return dst;
}

char *ft_strncpy(char *dst, const char *src, int len)
{
	int i;
	i = 0;
	while(src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return dst;
}

char *ft_strcat(char *dst, const char *src)
{
	int len;
	int i;
	len = ft_strlen(dst);
	i = 0;
	while(src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return dst;
}
