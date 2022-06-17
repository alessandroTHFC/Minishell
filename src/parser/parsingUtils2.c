/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingUtils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:00 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:29:01 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_temp(void)
{
	int	fd;

	unlink("/tmp/tmp_file");
	fd = open("/tmp/tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		printf("ERROR TEMP FD FAILED\n");
	return (fd);
}

void	exit_heredoc(int signal)
{
	(void) signal;
	write(1, "/n", 1);
	exit(0);
}
