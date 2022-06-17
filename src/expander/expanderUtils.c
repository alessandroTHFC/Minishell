/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanderUtils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:22:17 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:30:57 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**split_in_two(const char *string, char c)
{
	char	**splited_strings;
	char	*c_ptr;

	splited_strings = (char **)malloc(3 * sizeof(char *));
	c_ptr = ft_strchr(string, c);
	splited_strings[0] = ft_substr(string, 0, (c_ptr - string));
	splited_strings[1] = ft_substr((c_ptr + 1), 0, ft_strlen(c_ptr));
	splited_strings[2] = NULL;
	return (splited_strings);
}

char	**split_in_two_by_pointer(const char *string, char *c_ptr)
{
	char	**splited_strings;

	splited_strings = (char **)malloc(3 * sizeof(char *));
	splited_strings[0] = ft_substr(string, 0, (c_ptr - string));
	splited_strings[1] = ft_substr((c_ptr + 1), 0, ft_strlen(c_ptr));
	splited_strings[2] = NULL;
	return (splited_strings);
}

char	*search_var(char *value, int *i)
{
	while (value[*i] != '\0')
	{
		if (value[*i] == '$')
			return (&value[*i]);
		*i += 1;
	}
	return (NULL);
}

int	get_var_size(const char *var, int *index)
{
	int	i;

	i = 0;
	while ((var[i + 1] != ' ') && (var[i + 1] != '\0') && (var[i + 1] != '$'))
		i++;
	i++;
	*index += i;
	return (i);
}

void	handle_var_single_quote(t_var *var, char **value, int i)
{
	char	**splited_string;
	char	*temp;
	char	*aux;

	splited_string = ft_split(var->value, T_SINGLE_QUOTES);
	free((void **)var->value);
	var->value = ft_strdup(splited_string[0]);
	if (splited_string[1])
		temp = ft_strjoin("\'", splited_string[1]);
	else
		temp = ft_strdup("\'");
	aux = ft_substr(*value, i, (ft_strlen(*value) - i));
	var->after = ft_strjoin(temp, aux);
	free(temp);
	free(aux);
	free2d_array((void **) splited_string);
}
