#include <stdlib.h>
#include <stdio.h>
#include "test.h"

// COPIE DES VARIABLES ENVIRONNEMENT DANS UNE LISTE CHAINEE

// typedef	struct s_env
// {
// 		char			*key;
// 		char			*value;
// 		struct s_env	*next;
// }				t_env;


int	ft_pwd(void);
int	ft_cd(char *s, t_env *envi);
int	ft_env(t_env *envi, int env_len);

int	ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return i;
}

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_inienv(t_env **list)
{
	(*list)->key = NULL;
	(*list)->value = NULL;
	(*list)->next = NULL;
}

t_env	*ft_lstlast(t_env **list)
{
	t_env	*node;

	node = (*list);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

int	ft_find_poschr(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}

char	*ft_split_key(char **env, int i)
{
	char 	*ret;
	int 	j;
	int		sep;

	j = 0;
	sep = ft_find_poschr(env[i], '=');
	if (sep < 0)
		return (NULL);
	ret = malloc(sizeof(char) * (sep + 1));
	if (!ret)
		return (NULL);
	while (j < sep)
	{
		ret[j] = env[i][j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_split_value(char **env, int i)
{
	char 	*ret;
	int		len_max;
	int		j;
	int		sep;

	j = 0;
	len_max = ft_strlen(env[i]);
	sep = ft_find_poschr(env[i], '=') + 1;
	if (sep < 0)
		return (NULL);
	ret = malloc(sizeof(char) * (len_max - sep + 1));
	if (!ret)
		return (NULL);
	while (env[i][j + sep])
	{
		ret[j] = env[i][j + sep];
		j++;
	}
	return (ret);
}

void	ft_addenv(t_env **list, char **env, int i)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	ft_inienv(&new);
	if (!(*list))
	{
		new->key = ft_split_key(env, i);
		new->value = ft_split_value(env, i);
		(*list) = new;
		return ;
	}
	last = ft_lstlast(list);
	new->key = ft_split_key(env, i);
	new->value = ft_split_value(env, i);
	last->next = new;
	return ;
}

void	ft_envsetup(t_env **envi, int env_len, char **env)
{
	int	i;

	i = 0;
	while (i < env_len)
	{
		ft_addenv(envi, env, i);
		i++;
	}
}

void	ft_freeenv(t_env **envi, int env_len)
{
	int		i;
	t_env	*bob;

	i = 0;
	while (i < env_len)
	{
		bob = (*envi)->next;
		free((*envi));
		(*envi) = bob;
		i++;
	}
	free((*envi));
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	// (void)av;
	t_env	*envi;

	envi = NULL;
	// envi = malloc(sizeof(t_env));
	// ft_inienv(&envi);
	ft_envsetup(&envi, ft_tablen(env), env);
	ft_cd(av[1], envi);
	ft_pwd();
	ft_env(envi, ft_tablen(env));
	ft_freeenv(&envi, ft_tablen(env));
	return 0;
}