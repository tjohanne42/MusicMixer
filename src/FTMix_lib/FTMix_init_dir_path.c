#include "FTMix_lib.h"

static void		FTMix_init_dir_pic(const wchar_t *dir_pic_wpath)
{
	size_t		i;
	size_t		len;
	char		*tmp = NULL;

	if (!(tmp = ft_wstrtstr(dir_pic_wpath)))
		FTMix_ExitWithError("ft_wstrtstr");
	len = ft_strlen(ftmix.DIR_PIC_PATH);
	if (len >= 2 && ftmix.DIR_PIC_PATH[0] == '.' && ftmix.DIR_PIC_PATH[1] == '/')
	{
		i = 0;
		while (i < len)
		{
			ftmix.DIR_PIC_PATH[i] = ftmix.DIR_PIC_PATH[i + 2];
			i++;
		}
		ftmix.DIR_PIC_PATH[i] = '\0';
		len -= 2;
	}
	i = 0;
	while (i < len)
	{
		if (ftmix.DIR_PIC_PATH[i] == '\\')
			ftmix.DIR_PIC_PATH[i] = '/';
		i++;
	}
	if (len != 0)
		i = len - 1;
	while (i > 0 && ftmix.DIR_PIC_PATH[i] != '/')
		i--;
	ftmix.DIR_PIC_PATH[i] = '\0';
	len = ft_strlen(ftmix.DIR_PIC_PATH);
	if (len > 0 && tmp[0] != '/')
	{
		if (!ft_strfreejoin(&tmp, "/", 's'))
			FTMix_ExitWithError("ft_strfreejoin");
	}
	if (!ft_strfreejoin(&ftmix.DIR_PIC_PATH, tmp, 'e'))
		FTMix_ExitWithError("ft_strfreejoin");
	free(tmp);
	len = ft_strlen(ftmix.DIR_PIC_PATH);
	if (len > 0 && ftmix.DIR_PIC_PATH[len - 1] != '/')
	{
		if (!ft_strfreejoin(&ftmix.DIR_PIC_PATH, "/", 'e'))
			FTMix_ExitWithError("ft_strfreejoin");
	}
}

static void			FTMix_init_dir_music(const wchar_t *dir_music_wpath)
{
	size_t		i;
	size_t		len;

	len = ft_wstrlen(ftmix.DIR_MUSIC_WPATH);
	if (len >= 2 && ftmix.DIR_MUSIC_WPATH[0] == L'.' && ftmix.DIR_MUSIC_WPATH[1] == L'/')
	{
		i = 0;
		while (i < len)
		{
			ftmix.DIR_MUSIC_WPATH[i] = ftmix.DIR_MUSIC_WPATH[i + 2];
			i++;
		}
		ftmix.DIR_MUSIC_WPATH[i] = L'\0';
		len -= 2;
	}
	i = 0;
	while (i < len)
	{
		if (ftmix.DIR_MUSIC_WPATH[i] == L'\\')
			ftmix.DIR_MUSIC_WPATH[i] = L'/';
		i++;
	}
	if (len != 0)
		i = len - 1;
	while (i > 0 && ftmix.DIR_MUSIC_WPATH[i] != L'/')
		i--;
	ftmix.DIR_MUSIC_WPATH[i] = L'\0';
	len = ft_wstrlen(ftmix.DIR_MUSIC_WPATH);
	if (len > 0 && dir_music_wpath[0] != L'/')
	{
		if (!ft_wstrfreejoin(&ftmix.DIR_MUSIC_WPATH, L"/", 'e'))
			FTMix_ExitWithError("ft_strfreejoin");
	}
	if (!ft_wstrfreejoin(&ftmix.DIR_MUSIC_WPATH, dir_music_wpath, 'e'))
		FTMix_ExitWithError("ft_strfreejoin");
	len = ft_wstrlen(ftmix.DIR_MUSIC_WPATH);
	if (len > 0 && ftmix.DIR_MUSIC_WPATH[len - 1] != L'/')
	{
		if (!ft_wstrfreejoin(&ftmix.DIR_MUSIC_WPATH, L"/", 'e'))
			FTMix_ExitWithError("ft_strfreejoin");
	}
}

void			FTMix_init_dir_path(const wchar_t *dir_pic_wpath, const wchar_t *dir_music_wpath)
{
	FTMix_init_dir_pic(dir_pic_wpath);
	FTMix_init_dir_music(dir_music_wpath);
}