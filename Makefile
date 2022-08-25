# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/12 14:25:17 by fmauguin          #+#    #+#              #
#    Updated: 2022/08/25 19:10:22 by amahla           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SHELL				=	/bin/sh

PROGNAME			:=	miniRT

LIBFT				:=	libft/libft.a

MLX					:=	minilibx-linux/libmlx_Linux.a

INCLUDEDIR			:=	includes libft/includes minilibx-linux
SRCDIR				:=	srcs

OBJDIR				:=	./obj
DEBUGDIR			:=	./debugobj

COMMONSRCS			:=

UTILSSRC			:=	$(addprefix utils/,		ft_gnl_rt.c		\
												error_msg.c		\
												vector_math.c	\
												)


AMIRSRC				:=	$(addprefix amir/,		main.c 			\
												$(addprefix graphics/,	graphic_process.c	\
																		error_mlx.c			\
																		graphic_hook.c		\
																		graphic_render.c)	\
												$(addprefix parse/,		parse_rt.c			\
																		format_data.c		\
																		parse_volume.c		\
																		parse_light.c		\
																		parse_camera.c		\
																		set_variables.c)	\
												$(addprefix volume/,	bounds.c			\
																		inside_vol.c)		\
																		)

FLORANSRC			:=	$(addprefix floran/,	main.c 			\
												$(addprefix volume/,	inside_vol.c)		\
																				)

CC					:=	cc
RM					:=	rm

CCFLAGS				:=	-Wall -Wextra -Werror
LIBFLAGS			:=	-lXext -lX11 -lm -lbsd
OPTFLAG				:=

NAME				:=	$(PROGNAME)
FLORAN				:=	floran

OUTDIR				:=	$(OBJDIR)

DEBUGNAME			:=	$(addsuffix .debug,$(PROGNAME))

ifdef DEBUG
	OPTFLAG 		:=	-g
	LIBFT			:=	$(addsuffix .debug,$(LIBFT))
	NAME			:=	$(DEBUGNAME)
	BONUSNAME		:=	$(BONUSDEBUGNAME)
	OUTDIR			:=	$(DEBUGDIR)
endif

$(OUTDIR)/%.o		:	$(SRCDIR)/%.c | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CC) -c -MMD -MP $(CCFLAGS) $(OPTFLAG) $(addprefix -I ,$(INCLUDEDIR)) $(addprefix -I ,$(dir $(LIBFT))) $(addprefix -I ,$(dir $(MLX))) $< -o $@

$(NAME)				:	$(addprefix $(OUTDIR)/,$(AMIRSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(NAME) $(addprefix $(OUTDIR)/,$(AMIRSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX) $(LIBFLAGS)

$(FLORAN)			:	$(addprefix $(OUTDIR)/,$(FLORANSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(FLORAN) $(addprefix $(OUTDIR)/,$(FLORANSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX) $(LIBFLAGS)

all					:	$(NAME) $(BONUSNAME)

$(DEBUGNAME)		:
ifndef DEBUG
	$(MAKE) $(DEBUGNAME) DEBUG=1
endif

ifdef DEBUG
$(PROGNAME)			:	$(NAME)
$(PROGNAME_BONUS)	:	$(BONUSNAME)
endif

debug				:
ifndef DEBUG
	$(MAKE) DEBUG=1
endif

ifdef LIBFT
$(LIBFT)			:
	$(MAKE) -j -C $(dir $(LIBFT))
endif

ifdef MLX
$(MLX)			:
	$(MAKE) -j -C $(dir $(MLX))
endif

$(OUTDIR)			:
	mkdir $(OUTDIR)

clean				:
ifdef LIBFT
	$(MAKE) -C $(dir $(LIBFT)) fclean
endif
ifdef MLX
	$(MAKE) -C $(dir $(MLX)) clean
endif
	$(RM) -rf $(OBJDIR) $(DEBUGDIR)

fclean				:	clean
	$(RM) -f $(PROGNAME) $(PROGNAME_BONUS) $(DEBUGNAME) $(BONUSDEBUGNAME)

re					:	fclean
	$(MAKE) $(NAME)

.PHONY				:	all bonus clean fclean re debug

-include	$(addprefix $(OUTDIR)/,$(COMMONSRCS:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(AMIRSRC:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(FLORANSRC:.c=.d))
