/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:30:43 by aboehm            #+#    #+#             */
/*   Updated: 2022/02/15 23:18:46 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->flag = 0;
	node->next = NULL;
	return (node);
}

void	ft_new_node(t_list **list, int content)
{
	t_list	*curr;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = content;
	new_node->flag = 0;
	new_node->next = NULL;
	curr = *list;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}
