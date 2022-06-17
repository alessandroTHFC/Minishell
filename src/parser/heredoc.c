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

static int	get_var_len(char *line, const int *i)
{
	int	var_len;
	int	c;

	c = *i;
	c++;
	var_len = 0;
	if (ft_isalpha(line[c]))
	{
		while (ft_isalpha(line[c]) && line[c] != ' ' && line[c] != '\0')
		{
			var_len++;
			c++;
		}
		return (var_len);
	}
	return (0);
}

static int	heredoc_var(char *line, int *i, int tmp_file)
{
	char	*temp;
	int		j;
	int		c;
	int		len;

	j = 0;
	c = *i;
	c++;
	len = get_var_len(line, i);
	temp = (char *) malloc(sizeof(len + 1));
	if (ft_isalpha(line[c]))
	{
		while (line[c] != ' ' && line[c])
		{
			temp[j] = line[c];
			c++;
			j++;
		}
		temp[j] = '\0';
		expand(&temp, false);
		ft_putstr_fd(temp, tmp_file);
	}
	return (len);
}

void	line_loop(int has_quotes, int tmp_file, char *line)
{
	int		i;
	int		skip_var_name;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && has_quotes == 0)
		{
			skip_var_name = heredoc_var(line, &i, tmp_file);
			i += skip_var_name;
		}
		else
			ft_putchar_fd(line[i], tmp_file);
		i++;
	}
}

void	read_n_write(char *delim, int has_quotes, int tmp_file)
{
	char	*line;

	signal(SIGINT, exit_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(tmp_file);
			exit(0);
		}
		if (line[0] == '\n')
			continue ;
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
		{
			close(tmp_file);
			exit(0);
		}
		line_loop(has_quotes, tmp_file, line);
		ft_putchar_fd('\n', tmp_file);
	}
}

void	heredoc(char *delimiter)
{
	int	temp_fd;
	int	pid;
	int	has_quotes;
	int	status;

	has_quotes = 0;
	temp_fd = open_temp();
	if (delimiter[0] == '\'' || delimiter[0] == '"')
	{
		has_quotes = 1;
		delimiter = ft_strtrim(delimiter, "\"'");
	}
	pid = fork();
	if (pid == 0)
		read_n_write(delimiter, has_quotes, temp_fd);
	close(temp_fd);
	waitpid(pid, &status, 0);
	if (!WIFEXITED(status))
		printf("error PID status\n");
}
