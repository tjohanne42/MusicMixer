#include "FTMix_lib.h"

void			ft_wstrncpy(wchar_t *dest, const wchar_t *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = L'\0';
}

wchar_t			*ft_wstrjoin(const wchar_t *s1, const wchar_t *s2)
{
	size_t		len;
	size_t		i;
	size_t		x;
	wchar_t		*str;

	len = ft_wstrlen(s1) + ft_wstrlen(s2);
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
	str[i + x] = L'\0';
	return (str);
}

_Bool			ft_wstrfreejoin(wchar_t **s1, const wchar_t *s2, char statut)
{
	wchar_t		*tmp;
	size_t		len;

	if (statut != 's' && statut != 'e')
		return (SDL_FALSE);
	tmp = NULL;
	len = ft_wstrlen(*s1);
	if (!(tmp = malloc(sizeof(*tmp) * (len + 1))))
		return (SDL_FALSE);
	ft_wstrncpy(tmp, *s1, len);
	free(*s1);
	*s1 = NULL;
	if (statut == 's' && !(*s1 = ft_wstrjoin(s2, tmp)))
		return (SDL_FALSE);
	else if (statut == 'e' && !(*s1 = ft_wstrjoin(tmp, s2)))
		return (SDL_FALSE);
	free(tmp);
	return (SDL_TRUE);
}

size_t			ft_wstrlen(const wchar_t *wstr)
{
	size_t		i;

	i =	0;
	while (wstr[i])
		i++;
	return (i);
}

char			*ft_strnew(size_t i)
{
	char		*str = NULL;
	size_t		z;

	if (!(str = malloc(sizeof(*str) * i)))
		return (NULL);
	z = 0;
	while (z < i)
		str[z++] = '\0';
	return (str);
}

int				ft_power(intmax_t x, intmax_t power)
{
	if (power < 0)
		return (-1);
	if (power == 0)
		return (1);
	return (x * ft_power(x, power - 1));
}

intmax_t		ft_binary_to_decimal(const size_t *tab)
{
	size_t	z;
	int		i;

	i = 0;
	z = 0;
	while (z < 8)
	{
		if (tab[z] == 1)
			i += ft_power(2, (intmax_t)(7 - z));
		z++;
	}
	return (i);
}

static char		*ft_utf8_norme(size_t *tab, size_t nb_octets,
				size_t y, size_t z)
{
	size_t	bin[4][8];
	size_t	x;
	char	*str;

	if (!(str = ft_strnew(5)))
		return (NULL);
	while (y < nb_octets)
	{
		x = 0;
		while (y == 0 && x < nb_octets)
			bin[y][x++] = 1;
		if (x == 0)
			bin[y][x++] = 1;
		bin[y][x++] = 0;
		while (x != 8)
			bin[y][x++] = tab[z++];
		y++;
	}
	x = 0;
	while (x < nb_octets)
	{
		str[x] = (char)ft_binary_to_decimal(bin[x]);
		x++;
	}
	return (str);
}

static char		*ft_utf8_decimal_to_binary(intmax_t i, size_t nb_bytes)
{
	intmax_t	power;
	size_t		*tab;
	char		*ret;

	if (!(tab = malloc(sizeof(*tab) * nb_bytes)))
		exit(0);
	power = nb_bytes - 1;
	while (power >= 0)
	{
		if (i >= ft_power(2, power))
		{
			i -= ft_power(2, power);
			tab[nb_bytes - (power--) - 1] = 1;
		}
		else
			tab[nb_bytes - (power--) - 1] = 0;
	}
	ret = ft_utf8_norme(tab, nb_bytes / 5, 0, 0);
	free(tab);
	return (ret);
}


char			*wchar_utf8(intmax_t i)
{
	char	*ret;
	
	if (i <= 0x7F)
	{
		if (!(ret = ft_strnew(2)))
			return (NULL);
		ret[0] = i;
		return (ret);
	}
	else if (i <= 0x7FF)
		return (ft_utf8_decimal_to_binary(i, 11));
	else if (i <= 0xFFFF)
		return (ft_utf8_decimal_to_binary(i, 16));
	else if (i <= 0x10FFFF)
		return (ft_utf8_decimal_to_binary(i, 21));
	else
		return (NULL);
}

char			*ft_wstrtstr(const wchar_t *wstr)
{
	char		*str;
	char		*tmp1;
	char		*tmp2;
	size_t		i;
	size_t		len;

	if (!wstr)
		return (NULL);
	str = NULL;
	if (!(str = wchar_utf8(wstr[0])))
		return (NULL);
	i = 1;
	tmp1 = NULL;
	tmp2 = NULL;
	while (wstr[i])
	{
		if (!(tmp1 = wchar_utf8(wstr[i])))
			return (NULL);
		len = ft_strlen(str);
		if (!(tmp2 = malloc(sizeof(*tmp2) * (len + 1))))
			return (NULL);
		ft_strncpy(tmp2, str, len);
		free(str);
		str = NULL;
		if (!(str = ft_strjoin(tmp2, tmp1)))
			return (NULL);
		free(tmp1);
		free(tmp2);
		tmp1 = NULL;
		tmp2 = NULL;
		i++;
	}
	return (str);
}
