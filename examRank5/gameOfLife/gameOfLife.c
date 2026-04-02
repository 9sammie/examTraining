#include "life.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_cell_index(int x, int y, int largeur)
{
	return (y * largeur + x);
}

static void	make_cell_alive(char *map, int x, int y, int largeur)
{
	map[get_cell_index(x, y, largeur)] = 1;
}

static void	read_initial_map(char *map, int largeur, int hauteur)
{
	t_pen	pen;
	char	car;

	pen.x = 0;
	pen.y = 0;
	pen.down = 0;
	while (read(0, &car, 1) > 0)
	{
		if (car == 'x')
		{
			pen.down = !pen.down;
			if (pen.down)
				make_cell_alive(map, pen.x, pen.y, largeur);
		}
		else if (car == 'w')
		{
			if (pen.y > 0)
			{
				pen.y--;
				if (pen.down)
					make_cell_alive(map, pen.x, pen.y, largeur);
			}
		}
		else if (car == 'a')
		{
			if (pen.x > 0)
			{
				pen.x--;
				if (pen.down)
					make_cell_alive(map, pen.x, pen.y, largeur);
			}
		}
		else if (car == 's')
		{
			if (pen.y + 1 < hauteur)
			{
				pen.y++;
				if (pen.down)
					make_cell_alive(map, pen.x, pen.y, largeur);
			}
		}
		else if (car == 'd')
		{
			if (pen.x + 1 < largeur)
			{
				pen.x++;
				if (pen.down)
					make_cell_alive(map, pen.x, pen.y, largeur);
			}
		}
	}
}

static int	compter_voisines_vivantes(char *map, int x, int y, int largeur, int hauteur)
{
	int	nombre_voisines_vivantes;
	int	voisine_x;
	int	voisine_y;

	nombre_voisines_vivantes = 0;
	voisine_x = x - 1;
	voisine_y = y - 1;
	if (voisine_x >= 0 && voisine_x < largeur && voisine_y >= 0 && voisine_y < hauteur)
		nombre_voisines_vivantes += map[get_cell_index(voisine_x, voisine_y, largeur)];
	voisine_x = x;
	voisine_y = y - 1;
	if (voisine_x >= 0 && voisine_x < largeur && voisine_y >= 0 && voisine_y < hauteur)
		nombre_voisines_vivantes += map[get_cell_index(voisine_x, voisine_y, largeur)];
	voisine_x = x + 1;
	voisine_y = y - 1;
	if (voisine_x >= 0 && voisine_x < largeur && voisine_y >= 0 && voisine_y < hauteur)
		nombre_voisines_vivantes += map[get_cell_index(voisine_x, voisine_y, largeur)];
	voisine_x = x - 1;
	voisine_y = y;
	if (voisine_x >= 0 && voisine_x < largeur && voisine_y >= 0 && voisine_y < hauteur)
		nombre_voisines_vivantes += map[get_cell_index(voisine_x, voisine_y, largeur)];
	voisine_x = x + 1;
	voisine_y = y;
	if (voisine_x >= 0 && voisine_x < largeur && voisine_y >= 0 && voisine_y < hauteur)
		nombre_voisines_vivantes += map[get_cell_index(voisine_x, voisine_y, largeur)];
	voisine_x = x - 1;
	voisine_y = y + 1;
	if (voisine_x >= 0 && voisine_x < largeur && voisine_y >= 0 && voisine_y < hauteur)
		nombre_voisines_vivantes += map[get_cell_index(voisine_x, voisine_y, largeur)];
	voisine_x = x;
	voisine_y = y + 1;
	if (voisine_x >= 0 && voisine_x < largeur && voisine_y >= 0 && voisine_y < hauteur)
		nombre_voisines_vivantes += map[get_cell_index(voisine_x, voisine_y, largeur)];
	voisine_x = x + 1;
	voisine_y = y + 1;
	if (voisine_x >= 0 && voisine_x < largeur && voisine_y >= 0 && voisine_y < hauteur)
		nombre_voisines_vivantes += map[get_cell_index(voisine_x, voisine_y, largeur)];
	return (nombre_voisines_vivantes);
}

static void	next_generation(char *map, char *next_map, int largeur, int hauteur)
{
	int	x;
	int	y;
	int	nombre_voisines;
	int	cellule_vivante;

	y = 0;
	while (y < hauteur)
	{
		x = 0;
		while (x < largeur)
		{
			nombre_voisines = compter_voisines_vivantes(map, x, y, largeur, hauteur);
			cellule_vivante = map[get_cell_index(x, y, largeur)];
			if (cellule_vivante)
			{
				if (nombre_voisines < 2 || nombre_voisines > 3)
					next_map[get_cell_index(x, y, largeur)] = 0;
				else
					next_map[get_cell_index(x, y, largeur)] = 1;
			}
			else
			{
				if (nombre_voisines == 3)
					next_map[get_cell_index(x, y, largeur)] = 1;
				else
					next_map[get_cell_index(x, y, largeur)] = 0;
			}
			x++;
		}
		y++;
	}
}

static void	print_map(char *map, int largeur, int hauteur)
{
	int	x;
	int	y;

	y = 0;
	while (y < hauteur)
	{
		x = 0;
		while (x < largeur)
		{
			if (map[get_cell_index(x, y, largeur)])
				putchar('O');
			else
				putchar(' ');
			x++;
		}
		putchar('\n');
		y++;
	}
}

int	main(int argc, char **argv)
{
	int		largeur;
	int		hauteur;
	int		iterations;
	size_t	total;
	int		i;
	char	*map;
	char	*next_map;
	char	*tmp;

	if (argc != 4)
		return (1);
	largeur = atoi(argv[1]);
	hauteur = atoi(argv[2]);
	iterations = atoi(argv[3]);
	if (largeur <= 0 || hauteur <= 0 || iterations < 0)
		return (1);
	total = (size_t)largeur * (size_t)hauteur;
	if (total / (size_t)largeur != (size_t)hauteur)
		return (1);
	map = calloc(total, 1);
	if (!map)
		return (1);
	next_map = calloc(total, 1);
	if (!next_map)
		return (free(map), 1);
	read_initial_map(map, largeur, hauteur);
	i = 0;
	while (i < iterations)
	{
		next_generation(map, next_map, largeur, hauteur);
		tmp = map;
		map = next_map;
		next_map = tmp;
		i++;
	}
	print_map(map, largeur, hauteur);
	free(map);
	free(next_map);
	return (0);
}