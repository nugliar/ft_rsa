/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 09:12:22 by exam              #+#    #+#             */
/*   Updated: 2018/12/04 09:50:21 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lst_append(t_node **lst, t_node *node)
{
	t_node	*tmp;

	tmp = *lst;
	if ((NULL == tmp) || (NULL == node))
	{
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = node;
}

void	ft_lst_prepend(t_node **lst, t_node *node)
{
	if ((NULL == lst) || (NULL == node))
	{
		return ;
	}
	node->next = *lst;
	*lst = node;
}

void	ft_lst_del_first(t_node **lst, void (*f_del)(t_node *))
{
	t_node	*tmp;

	if ((NULL == lst) || (NULL == *lst))
	{
		return ;
	}
	tmp = *lst;
	*lst = (*lst)->next;
	ft_node_del(tmp, f_del);
}

void	ft_lst_del_last(t_node **lst, void (*f_del)(t_node *))
{
	t_node	*cur;
	t_node	*prev;

	if ((NULL == lst) || (NULL == *lst))
	{
		return ;
	}
	prev = NULL;
	cur = *lst;
	while (cur->next)
	{
		prev = cur;
		cur = cur->next;
	}
	if (NULL == prev)
	{
		*lst = NULL;
	}
	else
	{
		prev->next = NULL;
	}
	ft_node_del(cur, f_del);
}

void	ft_lst_del_one(t_node **lst, t_node *node, void (*f_del)(t_node *))
{
	t_node	*cur;
	t_node	*prev;

	if ((NULL == *lst) || (NULL == node))
	{
		return ;
	}
	prev = NULL;
	cur = *lst;
	while ((NULL != cur) && (node != cur))
	{
		prev = cur;
		cur = cur->next;
	}
	if (NULL == cur)
	{
		return ;
	}
	if (NULL == prev)
	{
		*lst = cur->next;
	}
	else
	{
		prev->next = cur->next;
	}
	ft_node_del(cur, f_del);
}

int	ft_lst_size(t_node *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	ft_lst_del(t_node *lst, void (*f_del)(t_node *))
{
	t_node	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_node_del(tmp, f_del);
	}
}

void	ft_lst_map(t_node *lst, void *farg, void (*f)(t_node *, void *))
{
	while (lst)
	{
		f(lst, farg);
		lst = lst->next;
	}
}

t_htbl	*ft_lst_htable(t_node *lst)
{
	t_htbl	*htbl;

	if (NULL == lst)
	{
		return (NULL);
	}
	htbl = ft_htbl_init(ft_lst_size(lst));
	while (lst)
	{
		ft_htbl_add(htbl, lst->key, lst->content);
		lst = lst->next;
	}
	return (htbl);
}
