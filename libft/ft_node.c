/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsharipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 09:35:41 by rsharipo          #+#    #+#             */
/*   Updated: 2018/09/27 10:18:24 by rsharipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_node	*ft_node_init(void)
{
	t_node	*node;

	LIBFT_ALLOC(node, sizeof(t_node));
	if (NULL == node)
		return (NULL);
	ft_bzero(node, sizeof(t_node));
	return (node);
}

t_node	*ft_node_new(const char *key, void *content, size_t size)
{
	t_node	*node;

	node = ft_node_init();
	if (NULL == node)
		return (NULL);
	node->key = ft_strdup(key);
	node->content = content;
	node->size = size;
	return (node);
}

void 	ft_node_del(t_node *node, void (*f_del)(t_node *))
{
	if (NULL == node)
		return ;
	if (NULL != f_del)
	{
		f_del(node);
	}
}
