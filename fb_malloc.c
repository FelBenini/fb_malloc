/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fb_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:29:16 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/20 14:31:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fb_malloc.h"

t_allocated_block	*split_block(t_allocated_block **block_to_split,
								size_t size)
{
	t_allocated_block	*block;
	t_allocated_block	*new_block;

	block = *block_to_split;
	if (block->size > size + sizeof(t_allocated_block))
	{
		new_block = (t_allocated_block *)((char *)(block + 1) + size);
		new_block->size = block->size - size - sizeof(t_allocated_block);
		new_block->is_freed = 1;
		new_block->next = block->next;
		new_block->prev = block;
		block->size = size;
		block->next = new_block;
		if (new_block->next)
			new_block->next->prev = new_block;
		return (block);
	}
	return (block);
}

void	join_free_blocks(t_allocated_block **block_to_join)
{
    t_allocated_block	*current_block;
    t_allocated_block	*next_block;
	t_allocated_block	*prev_block;

    current_block = *block_to_join;
    if (!current_block || !current_block->is_freed)
        return ;
    next_block = current_block->next;
	prev_block = current_block->prev;
    if (next_block && next_block->is_freed)
    {
        current_block->size += next_block->size + sizeof(t_allocated_block);
        current_block->next = next_block->next;
        if (current_block->next)
            current_block->next->prev = current_block;
    }
	if (prev_block && prev_block->is_freed)
	{
		current_block->size += prev_block->size + sizeof(t_allocated_block);
		current_block->prev = prev_block->prev;
		if (current_block->prev)
			current_block->prev->next = current_block;
	}
}

t_allocated_block	*find_free_space(t_allocated_block **head,
									size_t requested_space)
{
	t_allocated_block	*block;

	if (!*head)
		return (NULL);
	block = *head;
	while (block)
	{
		if (block->is_freed && block->size >= requested_space)
			return (split_block(&block, requested_space));
		block = block->next;
	}
	return (NULL);
}

t_allocated_block	*request_space(t_allocated_block **head,
									size_t requested_space)
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

t_allocated_block	**get_head_of_list(void)
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
	res->is_freed = 0;
	if (!*head)
		*head = res;
	return (res + 1);
}

void	fb_free(void *ptr)
{
	t_allocated_block	*block;
	t_allocated_block	**head;

	block = (t_allocated_block *)ptr - 1;
	block->is_freed = 1;
	join_free_blocks(&block);
	while (block->prev)
		block = block->prev;
	head = get_head_of_list();
	*head = block;
}
