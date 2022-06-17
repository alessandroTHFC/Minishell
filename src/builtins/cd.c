/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:22:45 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:31:54 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	change_dir_to_oldpwd(char *current_path)
{
	char	*tmp;

	tmp = search("OLDPWD").data;
	insert("OLDPWD", current_path);
	chdir(tmp);
}

static void	cd_home(void)
{
	insert("OLDPWD", ft_strdup(search("PWD").data));
	chdir(search("HOME").data);
}

static void	change_dir_to_path(const char *current_path)
{
	char	*wd;
	char	*abspath;
	int		len;

	wd = search("PWD").data;
	{
		len = ft_strlen(wd) + ft_strlen(current_path) + 1;
		insert(ft_strdup("OLDPWD"), ft_strdup(wd));
		if (current_path[0] == '/')
		{
			abspath = ft_calloc(len, sizeof(char));
			ft_strncat(abspath, wd, len);
			ft_strncat(abspath, "/", len);
			ft_strncat(abspath, current_path, len);
		}
		else
			abspath = ft_strdup(current_path);
		if (chdir(abspath))
			free(abspath);
		else
			insert(ft_strdup("PWD"), abspath);
	}
}

/* if the string is just ~ or ~/, calls cd_home
  * if it's -, assigns the PWD to the OLDPWD and calls
  * change_dir_to_oldpwd
  * else calls change_dir_to_path */
void	cd(t_cmd *cmd)
{
	char	*path;
	char	*current_path;

	path = cmd->argv[1];
	if ((!path) || ft_strncmp(path, "~", 2) == 0
		|| ft_strncmp(path, "~/", 3) == 0)
		return (cd_home());
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		current_path = ft_strdup(search("OLDPWD").data);
		if (current_path == NULL)
		{
			printf("cd [Error]");
			return ;
		}
		insert("OLDPWD", ft_strdup(search("PWD").data));
		change_dir_to_oldpwd(current_path);
	}
	else
	{
		current_path = ft_strdup(path);
		change_dir_to_path(current_path);
	}
	free(current_path);
}
