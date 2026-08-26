#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_pwd(void)
{
	char *buf;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (!buf)
		return (EXIT_FAILURE);
	printf("%s\n", buf);
	free(buf);
	return (EXIT_SUCCESS);
}