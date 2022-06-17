/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdTools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:21:38 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:21:39 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	secure_close(int fd)
{
	if (fd > 1)
		close(fd);
}

void	close_std_streams(void)
{
	secure_close(0);
	secure_close(1);
}
