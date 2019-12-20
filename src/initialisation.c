


int		check_res(int width, int height)
{
/*	int		x;
	int		y;

	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);
*/
	if (width >= 1920 || height >= 1080)
		return (1);
	return (0);
}

