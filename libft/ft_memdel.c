/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsharipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 09:16:38 by rsharipo          #+#    #+#             */
/*   Updated: 2018/09/27 10:26:56 by rsharipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_memdel(void **ap)
{
	if (ap && *ap)
	{
		LIBFT_FREE(*ap);
		*ap = NULL;
	}
}
