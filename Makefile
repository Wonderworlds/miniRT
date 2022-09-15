# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/12 14:25:17 by fmauguin          #+#    #+#              #
#    Updated: 2022/09/15 18:53:50 by fmauguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SHELL				=	/bin/sh

PROGNAME			:=	miniRT
PROGNAME_BONUS		:=	$(PROGNAME)_bonus

LIBFT				:=	libft/libft.a

MLX					:=	minilibx-linux/libmlx_Linux.a

MANDATORYDIR		:=	./mandatory
BONUSDIR			:=	./bonus

MANDATORYSRCDIR		:=	$(addprefix $(MANDATORYDIR)/, srcs)
BONUSSRCDIR			:=	$(addprefix $(BONUSDIR)/, srcs)

INCLUDEDIR			:=	libft/includes minilibx-linux
MINCLUDEDIR			:=	$(INCLUDEDIR) $(addprefix $(MANDATORYDIR)/, includes)
BINCLUDEDIR			:=	$(INCLUDEDIR) $(addprefix $(BONUSDIR)/, includes)

OBJDIR				:=	./obj
BONUSOBJDIR			:=	$(OBJDIR)_bonus
DEBUGDIR			:=	./debugobj

MANDATORYSRCS		:=	$(addprefix main/,		main.c					\
												start_and_leave.c)		\
						$(addprefix graphics/,	graphic_process.c		\
												error_mlx.c				\
												graphic_hook.c			\
												graphic_render.c)		\
						$(addprefix parse/,		parse_rt.c				\
												format_data.c			\
												parse_volume.c			\
												parse_light.c			\
												parse_camera.c			\
												set_variables.c)		\
						$(addprefix volume/,	inside_vol.c			\
												bounds.c				\
												bounds_total.c)			\
						$(addprefix bvh/,		bvh_construction.c		\
												sort_bvh.c				\
												print_bvh.c				\
												bvh_utils.c)			\
						$(addprefix raycast/,	hit_manager.c			\
												ray_print.c				\
												create_hit.c			\
												ray_volume_hit.c		\
												ray_cylinder_hit.c		\
												ray_cylinder_hit2.c)	\
						$(addprefix menu/,		graphic_menu.c			\
												build_menu.c			\
												bp_utils.c				\
												event_menu.c			\
												copy_img.c				\
												add_dec_menu.c			\
												add_dec_menu2.c			\
												add_dec_menu3.c			\
												fill_menu.c				\
												fill_menu2.c)			\
						$(addprefix lights/,	lights.c)				\
						$(addprefix utils/,		ft_gnl_rt.c				\
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

BONUSSRCS			:=	$(addprefix main/,		main.c					\
												start_and_leave.c)		\
						$(addprefix graphics/,	graphic_process.c		\
												error_mlx.c				\
												graphic_hook.c			\
												graphic_render.c)		\
						$(addprefix parse/,		parse_rt.c				\
												format_data.c			\
												parse_volume.c			\
												parse_light.c			\
												parse_texture.c			\
												parse_texture2.c		\
												parse_camera.c		\
												parse_volume2.c		\
												parse_resolution.c	\
												set_variables.c)	\
						$(addprefix volume/,	inside_vol.c		\
												bounds.c			\
												bounds2.c			\
												bounds_total.c)		\
						$(addprefix bvh/,		bvh_construction.c	\
												sort_bvh.c			\
												print_bvh.c			\
												bvh_utils.c)		\
						$(addprefix raycast/,	hit_manager.c		\
												ray_print.c			\
												create_hit.c		\
												ray_volume_hit.c	\
												ray_triangle_hit.c	\
												ray_cone_hit.c		\
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
						$(addprefix lights/,	lights.c			\
												get_uv.c			\
												disruption.c		\
												texture_col.c		\
												phong_reflection.c)	\
						$(addprefix utils/,		ft_gnl_rt.c			\
												ft_strlen_rt.c			\
												error_msg.c				\
												vector_math.c			\
												vector_math2.c			\
												vector_math3.c			\
												struct_utils.c			\
												struct_utils2.c			\
												color_utils.c			\
												color_utils2.c			\
												bbox_utils.c			\
												ft_itoa_custom.c		\
												ft_ftoa_custom.c		\
												debug.c					\
												quicksort_lst_custom.c	\
												bmp_export.c			\
												)

CC					:=	cc
RM					:=	rm

CCFLAGS				:=	-Wall -Wextra -Werror
LIBFLAGS			:=	-lXext -lX11 -lm -lbsd
OPTFLAG				:=

NAME				:=	$(PROGNAME)
BONUS				:=	$(PROGNAME_BONUS)

OUTDIR				:=	$(OBJDIR)
BONUSOUTDIR			:=	$(BONUSOBJDIR)

DEBUGNAME			:=	$(addsuffix .debug,$(PROGNAME))
BONUSDEBUGNAME		:=	$(addsuffix .debug,$(PROGNAME_BONUS))

ifdef DEBUG
	OPTFLAG 		:=	-g
	LIBFT			:=	$(addsuffix .debug,$(LIBFT))
	NAME			:=	$(DEBUGNAME)
	BONUS			:=	$(BONUSDEBUGNAME)
	OUTDIR			:=	$(DEBUGDIR)
endif

$(OUTDIR)/%.o		:	$(MANDATORYSRCDIR)/%.c | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CC) -c -MMD -MP $(CCFLAGS) $(OPTFLAG) $(addprefix -I ,$(MINCLUDEDIR)) $< -o $@

$(BONUSOUTDIR)/%.o	:	$(BONUSSRCDIR)/%.c | $(BONUSOUTDIR)
	@mkdir -p $(dir $@)
	$(CC) -c -MMD -MP $(CCFLAGS) $(OPTFLAG) $(addprefix -I ,$(BINCLUDEDIR)) $< -o $@

$(NAME)				:	$(addprefix $(OUTDIR)/,$(MANDATORYSRCS:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(NAME) $(addprefix $(OUTDIR)/,$(MANDATORYSRCS:.c=.o)) $(LIBFT) $(MLX) $(LIBFLAGS)

$(BONUS)			:	$(addprefix $(BONUSOUTDIR)/,$(BONUSSRCS:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(BONUS) $(addprefix $(BONUSOUTDIR)/,$(BONUSSRCS:.c=.o)) $(LIBFT) $(MLX) $(LIBFLAGS)

all					:	$(NAME)

bonus				:	$(BONUS)

$(DEBUGNAME)		:
ifndef DEBUG
	$(MAKE) $(DEBUGNAME) DEBUG=1
endif

$(BONUSDEBUGNAME)		:
ifndef DEBUG
	$(MAKE) $(BONUSDEBUGNAME) DEBUG=1
endif

ifdef DEBUG
$(PROGNAME)			:	$(NAME)
$(PROGNAME_BONUS)	:	$(BONUSNAME)
endif

debug				:
ifndef DEBUG
	$(MAKE) $(BONUSDEBUGNAME) DEBUG=1
endif

ifdef LIBFT
$(LIBFT)			:
	$(MAKE) -j -C $(dir $(LIBFT))
endif

ifdef MLX
$(MLX)				:
	$(MAKE) -j -C $(dir $(MLX))
endif

$(OUTDIR)			:
	mkdir $(OUTDIR)

$(BONUSOUTDIR)		:
	mkdir $(BONUSOUTDIR)

clean				:
ifdef LIBFT
	$(MAKE) -C $(dir $(LIBFT)) fclean
endif
ifdef MLX
	$(MAKE) -C $(dir $(MLX)) clean
endif
	$(RM) -rf $(OBJDIR) $(BONUSOUTDIR) $(DEBUGDIR)

fclean				:	clean
	$(RM) -f $(PROGNAME) $(PROGNAME_BONUS) $(DEBUGNAME) $(BONUSDEBUGNAME) $(FLORANNAME)

re					:	fclean
	$(MAKE) $(NAME)

.PHONY				:	all bonus clean fclean re debug

-include	$(addprefix $(OUTDIR)/,$(MANDATORYSRCS:.c=.d))
-include	$(addprefix $(BONUSOUTDIR)/,$(BONUSSRCS:.c=.d))
