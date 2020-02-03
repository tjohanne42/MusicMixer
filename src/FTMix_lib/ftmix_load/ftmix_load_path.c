#include "ftmix_lib.h"

static void     ftmix_add_path(const char *dir, const wchar_t *name)
{
    char           **tmp = NULL;
    char            *str = NULL;
    size_t          i = 0;
    size_t          len;

    if (ftmix.music.nb > 0)
    {
        if (!(tmp = malloc(sizeof(*tmp) * ftmix.music.nb)))
            ftmix_exit_error("malloc");
        while (i < ftmix.music.nb)
        {
            tmp[i] = NULL;
            len = ft_strlen(ftmix.music.path[i]);
            if (!(tmp[i] = malloc(sizeof(*tmp[i]) * (len + 1))))
                ftmix_exit_error("malloc");
            ft_strncpy(tmp[i], ftmix.music.path[i], len);
            free(ftmix.music.path[i]);
            i++;
        }
        i = 0;
        free(ftmix.music.path);
        ftmix.music.path = NULL;
    }
    if (!(ftmix.music.path = malloc(sizeof(*ftmix.music.path) * (ftmix.music.nb + 1))))
        ftmix_exit_error("malloc");
    if (ftmix.music.nb > 0)
    {
        while (i < ftmix.music.nb)
        {
            ftmix.music.path[i] = NULL;
            len = ft_strlen(tmp[i]);
            if (!(ftmix.music.path[i] = malloc(sizeof(*ftmix.music.path[i]) * (len + 1))))
                ftmix_exit_error("malloc");
            ft_strncpy(ftmix.music.path[i], tmp[i], len);
            free(tmp[i]);
            i++;
        }
        free(tmp);
    }
    if (!(str = ft_wstrtstr(name)))
        ftmix_exit_error("ft_wstrtstr");
    if (!(ftmix.music.path[i] = ft_strjoin(dir, str)))
        ftmix_exit_error("ft_strjoin");
    free(str);
    ftmix.music.nb++;
}

void			ftmix_load_path(void)
{
	WIN32_FIND_DATA File;
	HANDLE			hSearch;
	wchar_t			*wstr2 = NULL;
    char            *str = NULL;
	size_t			len;
	size_t			i;

	len = ft_wstrlen(ftmix.music_folder);
	if (!(wstr2 = malloc(sizeof(*wstr2) * (len + 4))))
		ftmix_exit_error("malloc");
	i = 0;
	while (i < len)
	{
		wstr2[i] = ftmix.music_folder[i];
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
    if (!(str = ft_wstrtstr(ftmix.music_folder)))
        ftmix_exit_error("ft_wstrtstr");
    if (len > 4 && ((File.cFileName[len - 1] == L'3' && File.cFileName[len - 2] == L'p' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.') ||
    	(File.cFileName[len - 1] == L'v' && File.cFileName[len - 2] == L'a' && File.cFileName[len - 3] == L'w' && File.cFileName[len - 4] == L'.') ||
    	(File.cFileName[len - 1] == L'd' && File.cFileName[len - 2] == L'o' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.') ||
    	(File.cFileName[len - 1] == L'g' && File.cFileName[len - 2] == L'g' && File.cFileName[len - 3] == L'o' && File.cFileName[len - 4] == L'.') ||
    	(File.cFileName[len - 1] == L'c' && File.cFileName[len - 2] == L'a' && File.cFileName[len - 3] == L'l' && File.cFileName[len - 4] == L'f' && File.cFileName[len - 5] == L'.') ||
    	(File.cFileName[len - 1] == L'd' && File.cFileName[len - 2] == L'i' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.')))
    	ftmix_add_path(str, File.cFileName);
    while (FindNextFile(hSearch, &File))
    {
    	len = ft_wstrlen(File.cFileName);
    	if (len > 4 && ((File.cFileName[len - 1] == L'3' && File.cFileName[len - 2] == L'p' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.') ||
    		(File.cFileName[len - 1] == L'v' && File.cFileName[len - 2] == L'a' && File.cFileName[len - 3] == L'w' && File.cFileName[len - 4] == L'.') ||
    		(File.cFileName[len - 1] == L'd' && File.cFileName[len - 2] == L'o' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.') ||
    		(File.cFileName[len - 1] == L'g' && File.cFileName[len - 2] == L'g' && File.cFileName[len - 3] == L'o' && File.cFileName[len - 4] == L'.') ||
    		(File.cFileName[len - 1] == L'c' && File.cFileName[len - 2] == L'a' && File.cFileName[len - 3] == L'l' && File.cFileName[len - 4] == L'f' && File.cFileName[len - 5] == L'.') ||
    		(File.cFileName[len - 1] == L'd' && File.cFileName[len - 2] == L'i' && File.cFileName[len - 3] == L'm' && File.cFileName[len - 4] == L'.')))
    		ftmix_add_path(str, File.cFileName);
    }
    FindClose(hSearch);
    free(str);
}
