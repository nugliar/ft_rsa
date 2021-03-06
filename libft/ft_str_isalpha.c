/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsharipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:32:56 by rsharipo          #+#    #+#             */
/*   Updated: 2018/09/10 10:36:08 by rsharipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_str_isalpha(const char *s)
{
	if (s == NULL)
		return (-1);
	while (*s)
		if (!ft_isalpha(*s++))
			return (0);
	return (1);
}
