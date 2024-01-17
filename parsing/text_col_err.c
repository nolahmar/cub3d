/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_col_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:15:56 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/17 15:02:30 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_err(char *ptr)
{
	if (ft_strncmp(ptr, "NO ", 3) != 0 && ft_strncmp(ptr, "WE ", 3) != 0
		&& ft_strncmp(ptr, "EA ", 3) != 0 && ft_strncmp(ptr, "SO ", 3) != 0
		&& ft_strncmp(ptr, "C ", 2) != 0 && ft_strncmp(ptr, "F ", 2) != 0
		&& ptr[0] != ' ' && ptr[0] != '\n')
		print_error("Error:\nbad argument!\n", 1);
}

void	format_c_eror(char *line)
{
	if (ft_strncmp(line, "C", 1) != 0)
		print_error("Erreur :\nformat de ligne invalide (ceil) !\n", 1);
}

void	format_f_eror(char *line)
{
	if (ft_strncmp(line, "F ", 2) != 0)
		print_error("Erreur :\nformat de ligne invalide (sol) !\n", 1);
}

void	print_error(char *error, int exit_code)
{
	ft_putstr_fd(error, 2);
	exit(exit_code);
}
