# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/31 13:12:01 by eduwer            #+#    #+#              #
#    Updated: 2020/03/04 15:20:35 by eduwer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c \
	helpers/helpers.c \
	helpers/reverse_bits.c \
	hash/hash_parse_args.c \
	hash/hash_process.c \
	hash/md5/md5.c \
	hash/md5/digest.c \
	hash/md5/rounds.c \
	hash/sha256/sha256.c \
	hash/sha256/exposed_sha256.c \
	hash/sha256/sha256_helpers.c \
	hash/sha512/sha512.c \
	hash/sha512/sha512_helpers.c \
	hash/sha384/sha384.c \
	cipher/base64/enc_base64.c \
	cipher/base64/dec_base64.c \
	cipher/base64/base64_parse_args.c \
	cipher/base64/get_enc_char.c \
	cipher/base64/get_dec_char.c \
	cipher/pbkdf2/pbkdf2.c \
	cipher/pbkdf2/hmac/hmac_sha256.c

NAME = ft_ssl

CC = gcc

CFLAGS = -I./include -I./libft/include -Wall -Wextra -Wno-unused-result -g

SRCF = ./srcs/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.c=.o))

LFT = libft/libft.a

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L./libft -lft -g

$(LFT):
	make -C ./libft

$(OBJF)%.o: $(SRCF)%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $(addprefix $(SRCF), $*.c)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
