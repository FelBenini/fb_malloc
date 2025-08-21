/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fb_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:29:58 by fbenini-          #+#    #+#             */
/*   Updated: 2025/08/20 14:13:44 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_MALLOC_H
# define FB_MALLOC_H

# include <stddef.h>
# include <unistd.h>
# include <assert.h>

typedef struct s_allocated_block {
	struct s_allocated_block	*prev;
	struct s_allocated_block	*next;
	size_t						size;
	int							is_freed;
}	t_allocated_block;

typedef struct s_heap_region {
	struct s_heap_region		*prev;
	struct s_heap_region		*next;
	int							total_size;
	int							free_size;
}	t_heap_region;

void	*fb_malloc(size_t size);
void	fb_free(void *ptr);
void	log_list(t_allocated_block	**lst);

#endif
