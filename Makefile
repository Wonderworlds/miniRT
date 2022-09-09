# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/12 14:25:17 by fmauguin          #+#    #+#              #
#    Updated: 2022/09/09 12:33:06 by amahla           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SHELL				=	/bin/sh

PROGNAME			:=	miniRT

PROGNAME_BONUS		:=	miniRT_bonus

LIBFT				:=	libft/libft.a

MLX					:=	minilibx-linux/libmlx_Linux.a

INCLUDEDIR			:=	includes libft/includes minilibx-linux
SRCDIR				:=	srcs

OBJDIR				:=	./obj
DEBUGDIR			:=	./debugobj

COMMONSRCS			:=	$(addprefix mandatory/,	$(addprefix common/,	$(addprefix main/,		main.c				\
																								start_and_leave.c)	\
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
																		$(addprefix volume/,	inside_vol.c		\
																								bounds.c			\
																								bounds_total.c)		\
																		$(addprefix bvh/,		bvh_construction.c	\
																								sort_bvh.c			\
																								print_bvh.c			\
																								bvh_utils.c)		\
																		$(addprefix raycast/,	hit_manager.c		\
																								ray_print.c			\
																								create_hit.c		\
																								ray_volume_hit.c	\
																								ray_cylinder_hit.c	\
																								ray_cylinder_hit2.c)\
																		$(addprefix menu/,		graphic_menu.c		\
																								build_menu.c		\
																								bp_utils.c			\
																								event_menu.c		\
																								copy_img.c			\
																								add_dec_menu.c		\
																								add_dec_menu2.c		\
																								add_dec_menu3.c		\
																								fill_menu.c			\
																								fill_menu2.c)		\
																		$(addprefix lights/,	lights.c)			\
																		)											\
												)

BONUSSRCS			:=	$(addprefix bonus/,		$(addprefix common/,	$(addprefix main/,		main.c				\
																								start_and_leave.c)	\
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
																		$(addprefix volume/,	inside_vol.c		\
																								bounds.c			\
																								bounds_total.c)		\
																		$(addprefix bvh/,		bvh_construction.c	\
																								sort_bvh.c			\
																								print_bvh.c			\
																								bvh_utils.c)		\
																		$(addprefix raycast/,	hit_manager.c		\
																								ray_print.c			\
																								create_hit.c		\
																								ray_volume_hit.c	\
																								ray_cylinder_hit.c	\
																								ray_cylinder_hit2.c)\
																		$(addprefix menu/,		graphic_menu.c		\
																								build_menu.c		\
																								bp_utils.c			\
																								event_menu.c		\
																								copy_img.c			\
																								add_dec_menu.c		\
																								add_dec_menu2.c		\
																								add_dec_menu3.c		\
																								fill_menu.c			\
																								fill_menu2.c)		\
																		$(addprefix lights/,	lights.c)			\
																		)											\
												)

UTILSSRC			:=	$(addprefix utils/,		ft_gnl_rt.c				\
												error_msg.c				\
												vector_math.c			\
												vector_math2.c			\
												vector_math3.c			\
												struct_utils.c			\
												color_utils.c			\
												bbox_utils.c			\
												ft_itoa_custom.c		\
												ft_ftoa_custom.c		\
												debug.c					\
												quicksort_lst_custom.c	\
												)


AMIRSRC				:=	$(addprefix amir/,			 					\
												)

FLORANSRC			:=	$(addprefix floran/,	main_floran.c					\
												)

CC					:=	cc
RM					:=	rm

CCFLAGS				:=	-Wall -Wextra -Werror
LIBFLAGS			:=	-lXext -lX11 -lm -lbsd
OPTFLAG				:=

NAME				:=	$(PROGNAME)
BONUS				:=	$(PROGNAME_BONUS)
FLORAN				:=	floran
AMIR				:=	amir

OUTDIR				:=	$(OBJDIR)

DEBUGNAME			:=	$(addsuffix .debug,$(PROGNAME))
BONUSDEBUGNAME		:=	$(addsuffix .debug,$(PROGNAME_BONUS))
FLORANNAME			:=	$(addsuffix .prog,$(FLORAN))

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

$(NAME)				:	$(addprefix $(OUTDIR)/,$(COMMONSRCS:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(NAME) $(addprefix $(OUTDIR)/,$(COMMONSRCS:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX) $(LIBFLAGS)

$(BONUS)		:	$(addprefix $(OUTDIR)/,$(BONUSSRCS:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(BONUS) $(addprefix $(OUTDIR)/,$(BONUSSRCS:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX) $(LIBFLAGS)

$(AMIR)				:	$(addprefix $(OUTDIR)/,$(COMMONSRCS:.c=.o)) $(addprefix $(OUTDIR)/,$(AMIRSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(NAME) $(addprefix $(OUTDIR)/,$(COMMONSRCS:.c=.o)) $(addprefix $(OUTDIR)/,$(AMIRSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX) $(LIBFLAGS)

$(FLORAN)			:	$(addprefix $(OUTDIR)/,$(COMMONSRCS:.c=.o)) $(addprefix $(OUTDIR)/,$(FLORANSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(FLORANNAME) $(addprefix $(OUTDIR)/,$(COMMONSRCS:.c=.o)) $(addprefix $(OUTDIR)/,$(FLORANSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(MLX) $(LIBFLAGS)

all					:	$(NAME)

bonus				:	$(BONUS)

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
	$(RM) -f $(PROGNAME) $(PROGNAME_BONUS) $(DEBUGNAME) $(BONUSDEBUGNAME) $(FLORANNAME)

re					:	fclean
	$(MAKE) $(NAME)

.PHONY				:	all bonus clean fclean re debug

-include	$(addprefix $(OUTDIR)/,$(COMMONSRCS:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(BONUSSRCS:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(AMIRSRC:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(FLORANSRC:.c=.d))
