#include "FTMix_lib.h"

static void		FTMix_AddPathToMusicPath(wchar_t *s1, wchar_t *s2)
{
	char		**tmp;
	size_t		i;
	size_t		len;
	char		*str2 = NULL;
	char		*str1 = NULL;

	if (ftmix.MUSIC_NB > 0)
	{
		tmp = NULL;
		if (!(tmp = malloc(sizeof(*tmp) * ftmix.MUSIC_NB)))
			FTMix_ExitWithError("malloc");
		i = 0;
		while (i < ftmix.MUSIC_NB)
		{
			tmp[i] = NULL;
			len = ft_strlen(ftmix.MUSIC_PATH[i]);
			if (!(tmp[i] = malloc(sizeof(*tmp[i]) * (len + 1))))
				FTMix_ExitWithError("malloc");
			ft_strncpy(tmp[i], ftmix.MUSIC_PATH[i], len);
			i++;
		}
	}
	FTMix_free_music_path();
	if (!(ftmix.MUSIC_PATH = malloc(sizeof(*ftmix.MUSIC_PATH) * (ftmix.MUSIC_NB + 1))))
		FTMix_ExitWithError("malloc");
	i = 0;
	while (i < ftmix.MUSIC_NB)
	{
		ftmix.MUSIC_PATH[i] = NULL;
		len = ft_strlen(tmp[i]);
		if (!(ftmix.MUSIC_PATH[i] = malloc(sizeof(*ftmix.MUSIC_PATH[i]) * (len + 1))))
			FTMix_ExitWithError("malloc");
		ft_strncpy(ftmix.MUSIC_PATH[i], tmp[i], len);
		i++;
	}
	ftmix.MUSIC_PATH[i] = NULL;
	if (!(str1 = ft_wstrtstr(s1)))
		FTMix_ExitWithError("ft_wstrtstr");
	if (!(str2 = ft_wstrtstr(s2)))
		FTMix_ExitWithError("ft_wstrtstr");
	if (!(ftmix.MUSIC_PATH[i] = ft_strjoin(str1, str2)))
		FTMix_ExitWithError("ft_strjoin");
	i = 0;
	while (i < ftmix.MUSIC_NB)
	{
		free(tmp[i]);
		i++;
	}
	if (i != 0)
		free(tmp);
	free(str2);
	free(str1);
	ftmix.MUSIC_NB++;
}

void				FTMix_load_music_path(void)
{
	WIN32_FIND_DATA File;
	HANDLE			hSearch; 
	wchar_t			*wstr2;
	size_t			len;
	size_t			i;

	FTMix_free_music_path();
	len = ft_wstrlen(ftmix.DIR_MUSIC_WPATH);
	if (!(wstr2 = malloc(sizeof(*wstr2) * (len + 4))))
		FTMix_ExitWithError("malloc");
	i = 0;
	while (i < len)
	{
		wstr2[i] = ftmix.DIR_MUSIC_WPATH[i];
		i++;
	}
	wstr2[i] = L'*';
	wstr2[i + 1] = L'.';
	wstr2[i + 2] = L'*';
	wstr2[i + 3] = L'\0';
	hSearch = FindFirstFile(wstr2, &File);
    if (hSearch == INVALID_HANDLE_VALUE)
    	exit(EXIT_FAILURE);
    free(wstr2);
	len = ft_wstrlen(File.cFileName);
    if (len > 4 && ((File.cFileName[len - 1] == L'3' && File.cFileName[len - 2] == L'p' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.') ||
    	(File.cFileName[len - 1] == L'v' && File.cFileName[len - 2] == L'a' && File.cFileName[len - 3] == L'w' && File.cFileName[len - 4] == L'.') ||
    	(File.cFileName[len - 1] == L'd' && File.cFileName[len - 2] == L'o' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.') ||
    	(File.cFileName[len - 1] == L'g' && File.cFileName[len - 2] == L'g' && File.cFileName[len - 3] == L'o' && File.cFileName[len - 4] == L'.') ||
    	(File.cFileName[len - 1] == L'c' && File.cFileName[len - 2] == L'a' && File.cFileName[len - 3] == L'l' && File.cFileName[len - 4] == L'f' && File.cFileName[len - 5] == L'.') ||
    	(File.cFileName[len - 1] == L'd' && File.cFileName[len - 2] == L'i' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.')))
    	FTMix_AddPathToMusicPath(ftmix.DIR_MUSIC_WPATH, File.cFileName);
    while (FindNextFile(hSearch, &File))
    {
    	len = ft_wstrlen(File.cFileName);
    	if (len > 4 && ((File.cFileName[len - 1] == L'3' && File.cFileName[len - 2] == L'p' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.') ||
    		(File.cFileName[len - 1] == L'v' && File.cFileName[len - 2] == L'a' && File.cFileName[len - 3] == L'w' && File.cFileName[len - 4] == L'.') ||
    		(File.cFileName[len - 1] == L'd' && File.cFileName[len - 2] == L'o' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.') ||
    		(File.cFileName[len - 1] == L'g' && File.cFileName[len - 2] == L'g' && File.cFileName[len - 3] == L'o' && File.cFileName[len - 4] == L'.') ||
    		(File.cFileName[len - 1] == L'c' && File.cFileName[len - 2] == L'a' && File.cFileName[len - 3] == L'l' && File.cFileName[len - 4] == L'f' && File.cFileName[len - 5] == L'.') ||
    		(File.cFileName[len - 1] == L'd' && File.cFileName[len - 2] == L'i' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.')))
    		FTMix_AddPathToMusicPath(ftmix.DIR_MUSIC_WPATH, File.cFileName);
    }
    FindClose(hSearch);
}
