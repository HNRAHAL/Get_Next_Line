#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strncpy(char *dst, const char *src, int len)
{
	int	i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *dst, const char *src)

{
	int	len;
	int	i;

	if (!dst || !src)
		return (NULL);
	len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (dst);
}

char *ft_strdup(char *str)
{
	char *new_str;
	int len;
	int i;
	if(!str)
		return NULL;
	len = ft_strlen(str);
	new_str = malloc(len + 1);

	i = 0;
	while(str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return new_str;
}