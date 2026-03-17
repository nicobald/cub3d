/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parse_type.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nbaldes <nbaldes@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/15 19:38:53 by utilisateur	   #+#	#+#			 */
/*   Updated: 2026/03/16 17:47:44 by nbaldes		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <cub3D.h>

int	map_type(char *line, int len)
{
	int	fchar;
	int	lchar;

	fchar = 0;
	lchar = len - 2;
	if (lchar < 0)
		return (0);
	while (line[fchar] == ' ' || line[fchar] == '	')
		fchar++;
	while ((line[lchar] == ' ' && lchar > 0)
		|| (line[lchar] == '	' && lchar > 0))
		lchar--;
	if (line[fchar] != '1' || line[lchar] != '1')
		return (0);
	while (fchar < lchar)
	{
		if (line[fchar] != '0' && line[fchar] != '1'
			&& line[fchar] != 'N' && line[fchar] != 'S'
			&& line[fchar] != 'E' && line[fchar] != 'W' && line[fchar] != ' ')
			return (0);
		fchar++;
	}
	return (1);
}

int	texture_type(char *line, char *type, int len)
{
	char	*extention;

	len = len - 2;
	if (len < 0)
		return (0);
	while ((line[len] == ' ' && len > 0) || (line[len] == '	' && len > 0))
		len--;
	extention = &line[len - 3];
	if (count_words(line) != 2)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strnstr(line, type, 2) == NULL
		|| (*(line + 2) != ' ' && *(line + 2) != '	'))
		return (0);
	if (ft_strnstr(extention, ".xpm", 4) == NULL)
		return (0);
	return (1);
}

int	color_type(char *line, char *type)
{
	int	i;
	int	nb_coma;

	i = 0;
	nb_coma = 0;
	if (count_words(line) != 2)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strnstr(line, type, 1) == NULL
		|| (*(line + 1) != ' ' && *(line + 1) != '	'))
		return (0);
	while (line[i])
	{
		if (line[i] == ',')
			nb_coma++;
		i++;
	}
	if (nb_coma != 2)
		return (0);
	if (split_check_color(line) == 0)
		return (0);
	return (1);
}

int	str_type(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\t' && line[i] != ' '
			&& line[i] != '\n' && line[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	parse_type(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (texture_type(line, "NO", len) == 1)
		return (NO);
	else if (texture_type(line, "SO", len) == 1)
		return (SO);
	else if (texture_type(line, "WE", len) == 1)
		return (WE);
	else if (texture_type(line, "EA", len) == 1)
		return (EA);
	else if (color_type(line, "F") == 1)
		return (F);
	else if (color_type(line, "C") == 1)
		return (C);
	else if (map_type(line, len) == 1)
		return (MAP);
	else if (str_type(line) == 1)
		return (STR);
	return (EMP);
}
