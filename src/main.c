/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:34:15 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 22:23:39 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/global.h"
#include "../inc/minishell.h"

//copy the environment variables from *env into hashtable entries
void	init_g_env_table(char **env)
{
	char	**var;
	int		i;

	i = 0;
	while (i < ENV_SIZE)
	{
		g_env_table[i].key = NULL;
		g_env_table[i].data = NULL;
		i++;
	}
	i = 2;
	while (*env)
	{
		var = ft_split(*env++, '=');
		if (var[0] && var[1])
			insert(ft_strdup(var[0]), ft_strdup(var[1]));
		free2d_array((void **)var);
	}
}

void	free_env(void)
{
	int	i;

	i = 0;
	while (i < ENV_SIZE)
	{
		if (g_env_table[i].key)
			free(g_env_table[i].key);
		if (g_env_table[i].data)
			free(g_env_table[i].data);
		g_env_table[i].data = NULL;
		g_env_table[i].key = NULL;
		i++;
	}
}

void	safe_exit(int status)
{
	rl_clear_history();
	free_env();
	exit(status);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	init_g_env_table(env);
	loop_shell();
	safe_exit(0);
}
