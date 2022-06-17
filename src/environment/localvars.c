/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localvars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:21:58 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:21:59 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	local_search(char *key, t_env *env_local)
{
	unsigned long	hashindex;

	hashindex = hash(key, LOCAL_ENV_SIZE);
	while (env_local[hashindex].key != NULL)
	{
		if (!ft_strncmp(env_local[hashindex].key, key, ft_strlen(key)))
			return (env_local[hashindex]);
		++hashindex;
		hashindex %= LOCAL_ENV_SIZE;
	}
	return (env_local[hashindex]);
}

void	local_insert(char *key, char *data, t_env *env_local)
{
	unsigned long	hashindex;

	hashindex = hash(key, LOCAL_ENV_SIZE);
	while (env_local[hashindex].key != NULL
		&& (!ft_strncmp(env_local[hashindex].key, "-1", 2)))
	{
		++hashindex;
		hashindex %= LOCAL_ENV_SIZE;
	}
	env_local[hashindex].key = key;
	env_local[hashindex].data = data;
}
