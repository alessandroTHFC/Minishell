/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:10:00 by aboehm            #+#    #+#             */
/*   Updated: 2022/02/15 23:17:21 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst,	t_list *new_lst)
{
	if (new_lst == NULL)
		return ;
	new_lst->next = *lst;
	*lst = new_lst;
	return ;
}
