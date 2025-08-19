/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fb_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:29:16 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/19 15:32:27 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fb_malloc.h"

t_allocated_block	*find_free_space(t_allocated_block **head, size_t requested_space)
{
	t_allocated_block	*block;

	if (!*head)
		return (NULL);
	block = *head;
	while (block)
	{
		if (block->is_freed && block->size >= requested_space)
			return (block);
		block = block->next;
	}
	return (NULL);
}

t_allocated_block	*request_space(t_allocated_block **head, size_t requested_space)
{
	t_allocated_block	*block;
	t_allocated_block	*last;
	void				*req;

	block = sbrk(0);
	if (block == (void *)-1)
		return (NULL);
	req = sbrk(sizeof(t_allocated_block) + requested_space);
	if (req == (void *)-1)
		return (NULL);
	last = *head;
	if (last)
	{
		while (last->next)
			last = last->next;
		last->next = block;
	}
	block->is_freed = 0;
	block->prev = last;
	block->next = NULL;
	block->size = requested_space;
	return (block);
}

t_allocated_block	**get_head_of_list()
{
	static t_allocated_block	*head;

	return (&head);
}

void	*fb_malloc(size_t size)
{
	t_allocated_block	**head;
	t_allocated_block	*res;

	head = get_head_of_list();
	if (size <= 0)
		return (NULL);
	res = find_free_space(head, size);
	if (!res)
		res = request_space(head, size);
	if (!res)
		return (NULL);
	if (!*head)
		*head = res;
	return (res + 1);
}

void	fb_free(void *ptr)
{
	t_allocated_block	*block;

	block = (t_allocated_block *)ptr - 1;
	block->is_freed = 1;
}
