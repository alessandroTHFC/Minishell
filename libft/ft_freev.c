/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:38:58 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 14:51:59 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//freev(ptr, N, TRUE); /* if known length */
//freev(ptr, -1, TRUE); /* if NULL-terminated */
//freev(ptr, -1, FALSE); /* to keep array */

void	ft_freev(void **ptr, int len, bool free_seg)
{
	if (len < 0)
	{
		while (*ptr)
		{
			free(*ptr);
			*ptr++ = NULL;
		}
	}
	else
	{
		while (len)
		{
			free(ptr[len]);
			ptr[len--] = NULL;
		}
	}
	if (free_seg)
		free(ptr);
}

void	free2d_array(void **arry)
{
	int	i;

	i = 0;
	while (arry[i])
		free(arry[i++]);
	free(arry);
}
