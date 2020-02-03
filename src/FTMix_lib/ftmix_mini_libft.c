#include "ftmix_lib.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

_Bool			ft_strfreejoin(char **s1, const char *s2, char statut)
{
	char		*tmp;
	size_t		len;

	if (statut != 's' && statut != 'e')
		return (SDL_FALSE);
	tmp = NULL;
	len = ft_strlen(*s1);
	if (!(tmp = malloc(sizeof(*tmp) * (len + 1))))
		return (SDL_FALSE);
	ft_strncpy(tmp, *s1, len);
	free(*s1);
	*s1 = NULL;
	if (statut == 's' && !(*s1 = ft_strjoin(s2, tmp)))
		return (SDL_FALSE);
	else if (statut == 'e' && !(*s1 = ft_strjoin(tmp, s2)))
		return (SDL_FALSE);
	free(tmp);
	return (SDL_TRUE);
}

// mili sec to str
char			*ft_mststr(long int ms)
{
	char		*str;
	size_t		size;
	size_t		i;

	str = NULL;
	ms = ms % (24 * 60 * 60 * 1000);
	if (ms / 1000 / 60 / 60 >= 10)
		size = 8;
	else if (ms / 1000 / 60 / 60 > 0)
		size = 7;
	else if (ms / 1000 / 60 % 60 >= 10)
		size = 5;
	else
		size = 4;
	if (!(str = malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	i = 0;
	if (ms / 1000 / 60 / 60 >= 10)
		str[i++] = ms / 1000 / 60 / 60 / 10 + '0';
	if (ms / 1000 / 60 / 60 > 0)
	{
		str[i++] = ms / 1000 / 60 / 60 % 10 + '0';
		str[i++] = ':';
	}
	if (ms / 1000 / 60 >= 10)
		str[i++] = ms / 1000 / 60 % 60 / 10 + '0';
	str[i++] = ms / 1000 / 60 % 60 % 10 + '0';
	str[i++] = ':';
	str[i++] = ms / 1000 % 60 / 10 + '0';
	str[i++] = ms / 1000 % 60 % 10 + '0';
	str[i] = '\0';
	return (str);
}

void			ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

size_t			ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char			*ft_strjoin(const char *s1, const char *s2)
{
	size_t		len;
	size_t		i;
	size_t		x;
	char		*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	x = 0;
	while (s2[x])
	{
		str[i + x] = s2[x];
		x++;
	}
	str[i + x] = '\0';
	return (str);
}
