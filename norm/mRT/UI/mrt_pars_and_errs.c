/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_pars_and_errs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:24:11 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 13:24:13 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	input_errs_three(char code, char *line)
{
	if (code == 11)
	{
		ft_putstr_fd("Wrong color\n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 12)
	{
		ft_putstr_fd("Wrong FOV:\n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 14)
	{
		ft_putstr_fd("Wrong diameter:\n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 15)
		ft_putstr_fd("Something going wrong: camera is losed\n", 1);
	else if (code == 16)
		ft_putstr_fd("Cant't create .bmp file\n", 1);
	else if (code == 17)
	{
		ft_putstr_fd("Wrong light intence\n", 1);
		ft_putendl_fd(line, 1);
	}
}

void	input_errs_two(char code, char *line)
{
	if (code == 7)
	{
		ft_putstr_fd("Double ambient light lines:\n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 8)
	{
		ft_putstr_fd("Wrong ambient light ratio\n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 9)
	{
		ft_putstr_fd("Wrong coordinates\n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 10)
	{
		ft_putstr_fd("Wrong vector\n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 13)
		ft_putstr_fd("No ambience light\n", 1);
	else
		input_errs_three(code, line);
}

void	mrt_input_error(char code, char *line)
{
	ft_putstr_fd("Error\n", 1);
	if (code == 0)
		ft_putstr_fd("Wrong extention of input file\n", 1);
	else if (code == 1)
		ft_putstr_fd("Wrong input: there are no file\n", 1);
	else if (code == 2)
		ft_putstr_fd("Wrong input: more arguments then expected\n", 1);
	else if (code == 3)
	{
		ft_putstr_fd("File can't be open: \n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 4)
		ft_putstr_fd("Wrong resolution\n", 1);
	else if (code == 5)
	{
		ft_putstr_fd("Line is wrong:\n", 1);
		ft_putendl_fd(line, 1);
	}
	else if (code == 6)
		ft_putstr_fd("Double resolution lines\n", 1);
	else
		input_errs_two(code, line);
	win_close();
}

void	mrt_parcer(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		mrt_res_read(line);
	else if (line[0] == 'A' && line[1] == ' ')
		mrt_ambient_light_read(line);
	else if (line[0] == 'c' && line[1] == ' ')
		mrt_camera_read(line);
	else if (line[0] == 'l' && line[1] == ' ')
		mrt_light_read(line);
	else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		mrt_sphere_read(line);
	else if (line[0] == 't' && line[1] == 'r' && line[2] == ' ')
		mrt_triangle_read(line);
	else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		mrt_plane_read(line);
	else if (line[0] == 's' && line[1] == 'q' && line[2] == ' ')
		mrt_square_read(line);
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		mrt_cylinder_read(line);
	else if (line[0] == 'd' && line[1] == 'l' && line[2] == ' ')
		mrt_dot_light_read(line);
	else if (ft_strlen(line) == 0 || line[0] == '/')
		;
	else
		mrt_input_error(5, line);
	free_gc(line);
}
