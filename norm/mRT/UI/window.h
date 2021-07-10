/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:36:00 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 13:36:04 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# include "../minirt.h"

typedef struct			s_cam_buf
{
	struct s_cam_buf	*next;
	char				*line;
}						t_cam_buf;

typedef struct			s_ambient
{
	unsigned char		color[4];
	double				intense;
}						t_ambient;

typedef struct			s_normaly
{
	struct s_normaly	*next;
	char				*wrong_str;
	char				*right_str;
}						t_normaly;

typedef struct			s_pixel_step
{
	double				len;
	double				point[3];
	double				cos;
	int					a_c_answer;
}						t_pixel_step;

typedef struct			s_window
{
	char				*name;
	void				*prcs;
	void				*win;
	int					x;
	int					y;
	char				save;
	char				res_amb[2];
	char				auto_normalization;
	char				amb_act;
	struct s_cam_buf	*cam_buf;
	struct s_normaly	*normaly_buff;
	struct s_ambient	a_light;
	struct s_obj_camera	*camera;
	struct s_obj_camera	*act_cam;
	struct s_mrt_object	*objects;
	struct s_light		*lights;
}						t_window;

void					looping(void);
void					mrt_no_res_cam_buff(char *line);
void					mrt_color_null(unsigned char *color);
int						mrt_int_color(unsigned char color[4]);
void					mrt_copy_color(unsigned char color[4],\
													unsigned char field[4]);
void					bmp_rev(void);
int						ftf_point_copy(t_pixel_step *memory, t_pixel_step *new);
void					res_checking(void);
void					scene_activate(void);
void					mrt_abnormal_vecs(void);
int						some_button(int id);
void					mrt_painting(t_obj_cam *cam);
void					mrt_triangle_read(char *line);
void					walk_through_the_field(t_obj_cam *cam);
void					fill_the_field(t_obj_cam *cam, char in_out, t_mro *act,\
																	t_mro *mem);
void					mrt_parcer(char *line);
void					first_input_check(int argc, char **argv);
void					mrt_light_read(char *line);
void					mrt_res_read(char *line);
void					mrt_sphere_read(char *line);
void					mrt_square_read(char *line);
void					mrt_plane_read(char *line);
void					mrt_dot_light_read(char *line);
void					obj_add_to_scene(t_mro *obj);
void					mrt_add_read(char *line);
void					mrt_cylinder_read(char *line);
void					mrt_ambient_light_read(char *line);
int						win_close(void);
void					mrt_obj_cleaner(void);
int						mrt_read_color(char *data, unsigned char color[4]);
void					mrt_reading_data_clean(char **data);
void					mrt_camera_read(char *line);
int						mrt_read_block(char *line);
void					window_open(int x, int y);
t_window				*fg_win(void);
void					mrt_norm_vec(double norm_vec[3], char *line);
void					mrt_input_error(char code, char *line);
int						mrt_read_coords(char *data, double crds[3]);
void					mrt_norm_vec(double norm_vec[3], char *line);
void					mrt_input_error(char code, char *line);

#endif
