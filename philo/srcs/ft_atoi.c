/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:41:43 by vgiordan          #+#    #+#             */
/*   Updated: 2023/05/03 17:13:23 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s++, fd);
	}
}

static long long	ft_signe(const char *str)
{
	int	i;

	i = 0;
	while ((!(str[i] >= '0' && str[i] <= '9')) && str[i] != '-'
		&& str[i] != '+')
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] <= '9' && str[i + 1] >= '0')
		{
			if (str[i] == '-')
				return (-1);
			return (1);
		}
		return (0);
	}
	return (1);
}

static int	check_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i]) < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoi(const char *str)
{
	long long	number;
	int			i;

	i = 0;
	number = 0;
	if (check_numeric(str) == 0)
		return (-1);
	while (!(str[i] >= '0' && str[i] <= '9') && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\f' && str[i] != '\v' && str[i] != '\r'
			&& str[i] != '+' && str[i] != '-')
			return (0);
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		number = number * 10 + str[i] - '0';
		i++;
	}
	if (number * ft_signe(str) > 2147483647 || number * ft_signe(str) < 0)
		return (-1);
	return (number * ft_signe(str));
}
