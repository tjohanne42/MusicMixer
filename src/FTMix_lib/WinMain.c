#include "FTMix_lib.h"

int WINAPI 		WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdline, int cmdshow)
{
	if (!hInst && !hPrevInst && !cmdline && !cmdshow)
		return (EXIT_FAILURE);

	// hide console
	HWND 		hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE);
	ShowWindow(hWnd, SW_HIDE);

	int 		argc = 0;
	char		**my_argv;
	wchar_t		**w_argv;
	int			i;
	int			len;
	int			ret;

	w_argv = NULL;
	if (!(w_argv = CommandLineToArgvW(GetCommandLineW(), &argc)))
		return (EXIT_FAILURE);
	my_argv = NULL;
	if (!(my_argv = malloc(sizeof(*my_argv) * argc)))
			return (EXIT_FAILURE);
	i = 0;
	ftmix.DIR_PIC_PATH = NULL;
	ftmix.DIR_MUSIC_WPATH = NULL;
	while (i < argc)
	{
		if (i == 0)
		{
			len = ft_wstrlen(w_argv[i]);
			if (!(ftmix.DIR_MUSIC_WPATH = malloc(sizeof(*ftmix.DIR_MUSIC_WPATH) * (len + 1))))
				return (EXIT_FAILURE);
			while (i < len)
			{
				ftmix.DIR_MUSIC_WPATH[i] = w_argv[0][i];
				i++;
			}
			ftmix.DIR_MUSIC_WPATH[i] = L'\0';
			if (!(ftmix.DIR_PIC_PATH = ft_wstrtstr(ftmix.DIR_MUSIC_WPATH)))
				return (EXIT_FAILURE);
			i = 0;
		}
		my_argv[i] = NULL;
		if (!(my_argv[i] = ft_wstrtstr(w_argv[i])))
			return (EXIT_FAILURE);
		i++;
	}
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
	if (ftmix.DIR_MUSIC_WPATH)
		free(ftmix.DIR_MUSIC_WPATH);
	if (ftmix.DIR_PIC_PATH)
		free(ftmix.DIR_PIC_PATH);
	return (ret);
}
