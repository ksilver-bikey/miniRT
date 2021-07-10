NAME = miniRT

ARIF = norm/mRT/arithmetic/

OBJE = norm/mRT/objects/

OPTI = norm/mRT/optic/

UIf = norm/mRT/UI/

.PHONY: all
all: $(NAME)
	
$(NAME): norm/libft/libft.a libmlx.dylib
	@gcc -Wall -Wextra -Werror -o miniRT \
	$(ARIF)common_utils_one.c $(ARIF)common_utils_two.c \
	$(ARIF)gaus_ex.c $(ARIF)gaus_utils.c $(ARIF)lines.c \
	$(ARIF)plain_two.c $(ARIF)plain.c $(ARIF)vectors.c \
	$(ARIF)vectors_two.c $(OBJE)cylinders_four.c $(OBJE)plane.c \
	$(OBJE)cylinders_three.c $(OBJE)cylinders_two.c \
	$(OBJE)cylinders.c $(OBJE)obj_camera.c $(OBJE)obj_camera_two.c \
	$(OBJE)sphere_two.c $(OBJE)sphere.c $(OBJE)square_two.c \
	$(OBJE)square.c $(OBJE)triangle.c $(OPTI)light.c $(OPTI)dot_light.c \
	$(UIf)creat_bmp.c $(UIf)minirt_utils.c $(UIf)mrt_pars_and_errs.c \
	$(UIf)minirt.c $(UIf)mrt_reader.c $(UIf)mrt_reading_three.c \
	$(UIf)mrt_reading_two.c $(UIf)mrt_reading.c \
	$(UIf)reading_utils_two.c $(UIf)reading_utils.c $(UIf)window.c \
	norm/libft/libft.a \
	-lmlx -framework OpenGL -framework AppKit -L. libmlx.dylib 
	
norm/libft/libft.a:
	make -C norm/libft
	
libmlx.dylib:
	make -C minilibx/
	@cp minilibx/libmlx.dylib libmlx.dylib
	@@cp minilibx/libmlx.dylib Tests/libmlx.dylib

.PHONY: clean
clean:
	make fclean -C norm/libft
	make clean -C minilibx

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -f libmlx.dylib
	rm -f Tests/libmlx.dylib

.PHONY: re
re: fclean all
