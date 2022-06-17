/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apangraz <apangraz@42adel.org.au>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:22:45 by apangraz          #+#    #+#             */
/*   Updated: 2022/05/25 13:31:54 by apangraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	echo(t_cmd *cmd)
{
	int		i;
	bool	newline;

	newline = false;
	i = 1;
	if (cmd && strcmp(cmd->argv[i], "-n") == 0)
	{
		newline = true;
		i++;
	}
	while (cmd && cmd->argv[i])
	{
		printf("%s ", cmd->argv[i]);
		i++;
	}
	if (newline == false)
		printf("\n");
}
