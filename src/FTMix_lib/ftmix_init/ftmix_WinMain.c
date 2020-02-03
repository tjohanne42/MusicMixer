#include "ftmix_lib.h"

static _Bool		ftmix_norme_folder(void)
{
	size_t		len = ft_wstrlen(ftmix.music_folder);
	size_t		i = 0;

	while (i < len)
	{
		if (ftmix.music_folder[i] == L'\\')
			ftmix.music_folder[i] = L'/';
		i++;
	}
	i = 0;
	if (len > 2 && ftmix.music_folder[0] == L'.' && ftmix.music_folder[1] == L'/')
	{
		while (i < len - 1)
		{
			ftmix.music_folder[i] = ftmix.music_folder[i + 2];
			i++;
		}
	}
	len = ft_wstrlen(ftmix.music_folder);
	while (ftmix.music_folder[len] != L'/' && len > 0)
		len--;
	if (len == 0)
		ftmix.music_folder[len] = L'\0';
	else
		ftmix.music_folder[len + 1] = L'\0';
	if (!(ftmix.pic_folder = ft_wstrtstr(ftmix.music_folder)))
		return (SDL_FALSE);
	return (SDL_TRUE);
}

int WINAPI 		WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdline, int cmdshow)
{
	if (!hInst && !hPrevInst && !cmdline && !cmdshow)
		return (EXIT_FAILURE);
	HWND 		hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE);
	ShowWindow(hWnd, SW_HIDE);
	int 		argc = 0;
	char		**my_argv = NULL;
	wchar_t		**w_argv = NULL;
	int			i = 0;;
	int			len;
	int			ret;

	if (!(w_argv = CommandLineToArgvW(GetCommandLineW(), &argc)))
		return (EXIT_FAILURE);
	if (!(my_argv = malloc(sizeof(*my_argv) * argc)))
			return (EXIT_FAILURE);
	ftmix.pic_folder = NULL;
	ftmix.music_folder = NULL;
	while (i < argc)
	{
		if (i == 0)
		{
			len = ft_wstrlen(w_argv[i]);
			if (!(ftmix.music_folder = malloc(sizeof(*ftmix.music_folder) * (len + 1))))
				return (EXIT_FAILURE);
			while (i <= len)
			{
				ftmix.music_folder[i] = w_argv[0][i];
				i++;
			}
			i = 0;
		}
		my_argv[i] = NULL;
		if (!(my_argv[i] = ft_wstrtstr(w_argv[i])))
			return (EXIT_FAILURE);
		i++;
	}
	if (!ftmix_norme_folder())
		return (EXIT_FAILURE);
	ret = main(argc, my_argv);
	i = 0;
	while (i < argc)
	{
		free(w_argv[i]);
		free(my_argv[i]);
		i++;
	}
	if (argc)
		free(my_argv);
	if (ftmix.music_folder)
		free(ftmix.music_folder);
	if (ftmix.pic_folder)
		free(ftmix.pic_folder);
	return (ret);
}
