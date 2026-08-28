#include <unistd.h>
#include <stdlib.h>
#include "../test.h"

char	*ft_strjoin(char const *s1, char const *s2);

char	*get_home(t_env *envi)
{
	int		i;
	char	*home;

	home = "HOME";
	while (envi->next != NULL)
	{
		i = 0;
		while (envi->key[i] == home[i] && home[i])
			i++;
		if (!home[i])
			return (envi->value);
		envi = envi->next;
	}
	i = 0;
	while (envi->key[i] == home[i] && home[i])
		i++;
	if (!home[i])
		return (envi->value);
	return (NULL);
}

char	*ft_establish_path(char *s)
{
	char	*pwd;
	char	*ret;

	if (s[0] == '/')
		return (s);
	ret = getcwd(NULL, 0);
	pwd = ft_strjoin(ret, "/");
	free(ret);
	ret = ft_strjoin(pwd, s);
	return (ret);
}

int	ft_cd(char *s, t_env *envi)
{
	char	*path;

	if (!s)
		path = get_home(envi);
	else
		path = ft_establish_path(s);
	if (!path)
		return (1);
	if (chdir(path) < 0)
		return (1);
	return (0);
}