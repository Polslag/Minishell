#include "test.h"
#include <stdio.h>

int	ft_env(t_env *envi, int env_len)
{
	int	i;

	i = 0;
	while (i < env_len)
	{
		printf("%s=%s\n", envi->key, envi->value);
		envi = envi->next;
		i++;
	}
	return (0);
}