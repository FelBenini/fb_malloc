# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenini- <your@mail.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 15:26:13 by fbenini-          #+#    #+#              #
#    Updated: 2025/08/19 15:31:50 by fbenini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fb_malloc.a

SRCS = fb_malloc.c logger.c

CFLAGS = -Wall -Wextra -Werror

HDRS = fb_malloc.h

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I.$(HDRS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all re clean fclean
