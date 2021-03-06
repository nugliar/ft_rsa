/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsharipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 17:13:02 by rsharipo          #+#    #+#             */
/*   Updated: 2018/09/11 17:15:14 by rsharipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_strup(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		if (*s >= 'a' && *s <= 'z')
			*s = *s - 32;
		s++;
	}
}
