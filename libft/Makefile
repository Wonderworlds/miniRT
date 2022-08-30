# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 14:23:03 by fmauguin          #+#    #+#              #
#    Updated: 2022/08/29 18:50:35 by fmauguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL				=	/bin/sh

PROGNAME			:=	libft.a

INCLUDEDIR			:=	includes
SRCDIR				:=	srcs

OBJDIR				:=	./obj
DEBUGDIR			:=	./debugobj

LIBFTSRC			:=	ft_atoi.c 				\
						ft_atoi_err.c			\
						ft_atof.c				\
						ft_bzero.c 				\
						ft_calloc.c 			\
						ft_gnl.c 				\
						ft_int_len.c 			\
						ft_isalnum.c			\
						ft_isalpha.c			\
						ft_isascii.c			\
						ft_isdigit.c			\
						ft_isprint.c			\
						ft_itoa.c				\
						ft_lstadd_back.c 		\
						ft_lstadd_front.c 		\
						ft_lstclear.c 			\
						ft_lstdelone.c 			\
						ft_lstiter.c 			\
						ft_lstlast.c 			\
						ft_lstmap.c 			\
						ft_lstnew.c 			\
						ft_lstsize.c 			\
						ft_lst_at.c 			\
						ft_max.c				\
						ft_memchr.c 			\
						ft_memcmp.c 			\
						ft_memcpy.c 			\
						ft_memmove.c 			\
						ft_memset.c 			\
						ft_min.c				\
						ft_printf_buffer.c 		\
						ft_printf.c 			\
						ft_fprintf.c 			\
						ft_printf_char.c 		\
						ft_printf_format.c 		\
						ft_printf_hex.c 		\
						ft_printf_int.c 		\
						ft_printf_padding.c 	\
						ft_printf_precision.c 	\
						ft_printf_ptr.c 		\
						ft_printf_str.c 		\
						ft_printf_uint.c 		\
						ft_putchar_fd.c 		\
						ft_putendl_fd.c 		\
						ft_putnbr_fd.c 			\
						ft_putstr_fd.c 			\
						ft_split.c 				\
						ft_strchr.c 			\
						ft_strdup.c 			\
						ft_striteri.c 			\
						ft_strjoin.c 			\
						ft_strlcat.c 			\
						ft_strlcpy.c 			\
						ft_strlen.c 			\
						ft_strmapi.c 			\
						ft_strncmp.c 			\
						ft_strnlen.c 			\
						ft_strnstr.c 			\
						ft_strrchr.c 			\
						ft_strtrim.c 			\
						ft_substr.c 			\
						ft_tolower.c 			\
						ft_toupper.c 			\
						ft_uint_len_base.c


CC					:=	cc
RM					:=	rm

CCFLAGS				:=	-Wall -Wextra -Werror
LIBFLAGS			:=
OPTFLAG				:=

NAME				:=	$(PROGNAME)

OUTDIR				:=	$(OBJDIR)

DEBUGNAME			:= $(addsuffix .debug,$(PROGNAME))

ifdef DEBUG
	OPTFLAG 		:=	-g
	LIBFT			:=	$(addsuffix .debug,$(LIBFT))
	NAME			:=	$(DEBUGNAME)
	BONUSNAME		:=	$(BONUSDEBUGNAME)
	OUTDIR			:=	$(DEBUGDIR)
endif

$(OUTDIR)/%.o		:	$(SRCDIR)/%.c | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CC) -c -MMD -MP $(CCFLAGS) $(OPTFLAG) $(addprefix -I ,$(INCLUDEDIR)) $< -o $@

$(NAME)				:	$(addprefix $(OUTDIR)/,$(LIBFTSRC:.c=.o))
	ar rcs $@ $(addprefix $(OUTDIR)/,$(LIBFTSRC:.c=.o))

all					:	$(NAME)

$(DEBUGNAME)		:
ifndef DEBUG
	$(MAKE) $(DEBUGNAME) DEBUG=1
endif

ifdef DEBUG
$(PROGNAME)			:	$(NAME)
endif

debug				:
ifndef DEBUG
	$(MAKE) DEBUG=1
endif

$(OUTDIR)			:
	mkdir $(OUTDIR)

clean				:
	$(RM) -rf $(OBJDIR) $(DEBUGDIR)

fclean				:	clean
	$(RM) -f $(PROGNAME) $(DEBUGNAME)

re					:	fclean
	$(MAKE) $(NAME)

.PHONY				:	all bonus clean fclean re

-include	$(addprefix $(OUTDIR)/,$(LIBFTSRC:.c=.d))

###-----------------------------------git------------------------------------###

update				:
	git pull
