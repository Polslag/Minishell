#include "libft-pilagach/libft.h"
#include "minishell.h"

static const char	*redir_symbol(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	return (">>");
}

void	debug(t_command *cmd)
{
	int		i;
	t_redir	*redir;

	while (cmd)
	{
		i = 0;
		printf("---- command ----\n");
		while (cmd->argv && cmd->argv[i])
		{
			printf("argv[%d] = %s\n", i, cmd->argv[i]);
			i++;
		}
		redir = cmd->redir;
		while (redir)
		{
			printf("redir %s %s\n", redir_symbol(redir->type), redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
