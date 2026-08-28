
#include "minishell.h"

void	ft_error_output(t_data *data, char *title, char *content)
{
	if (title)
	{
		// write(data->cmd->fd_out, RD, ft_strlen(RD));
		write(data->cmd->fd_out, title, ft_strlen(title));
		// write(data->cmd->fd_out, WH, ft_strlen(WH));	
	}
	// write(data->cmd->fd_out, color, ft_strlen(color));
	write(data->cmd->fd_out, content, ft_strlen(content));
	// write(data->cmd->fd_out, WH, ft_strlen(WH));
}
