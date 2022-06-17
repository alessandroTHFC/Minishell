/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 20:36:51 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 14:55:17 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, const char *src, unsigned int nb)
{
	unsigned int	desti;
	unsigned int	srci;

	desti = 0;
	srci = 0;
	while (dest[desti] != '\0')
		desti++;
	while (desti < nb && src[srci])
	{
		dest[desti] = src[srci];
		srci++;
		desti++;
	}
	dest[desti] = '\0';
	return (dest);
}
