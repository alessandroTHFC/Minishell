/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashTable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:52:49 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 22:16:08 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Djb2 hash function
u_int64_t	hash(char *str, int envlen)
{
	u_int64_t	hash;

	hash = 5381L;
	while (*str++)
		hash = ((hash << 5) + hash) + (*str - 1);
	return (hash % envlen);
}

//returns an environmariable from a key
t_env	search(char *key)
{
	unsigned long	hashindex;

	hashindex = hash(key, ENV_SIZE);
	while (g_env_table[hashindex].key != NULL)
	{
		if (!ft_strncmp(g_env_table[hashindex].key, key, ft_strlen(key)))
			return (g_env_table[hashindex]);
		++hashindex;
		hashindex %= ENV_SIZE;
	}
	return (g_env_table[hashindex]);
}

//insert a key-value pair into the hashtable
void	insert(char *key, char *data)
{
	unsigned long	hashindex;

	hashindex = hash(key, ENV_SIZE);
	while (g_env_table[hashindex].key != NULL
		&& ft_strncmp(key, g_env_table[hashindex].key, ft_strlen(key)))
	{
		++hashindex;
		hashindex %= ENV_SIZE;
	}
	if (g_env_table[hashindex].key)
	{
		free(g_env_table[hashindex].key);
		free(g_env_table[hashindex].data);
	}
	g_env_table[hashindex].key = key;
	g_env_table[hashindex].data = data;
}

//return a list of env vars to the terminal
void	display(t_cmd *cmd)
{
	int		i;

	(void)cmd;
	i = 0;
	while (i < ENV_SIZE)
	{
		if (g_env_table[i].key != NULL)
			printf("%s=%s\n", g_env_table[i].key, g_env_table[i].data);
		i++;
	}
}

char	**get_env(t_env *envtab)
{
	int		i;
	char	*tmp;
	char	**env;
	int		len;

	len = 0;
	i = 0;
	while (i < ENV_SIZE)
		if (envtab[i++].key)
			len++;
	env = (char **)ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (++i < ENV_SIZE)
	{
		if (envtab[i].key)
		{
			tmp = ft_strjoin(envtab[i].key, "=");
			*env = ft_strjoin(tmp, envtab[i].data);
			free(tmp);
			(*env)++;
		}
	}
	return (env);
}
