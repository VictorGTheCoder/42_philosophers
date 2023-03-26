/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:41:43 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 10:36:13 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_signe(const char *str)
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

long	ft_atoi(const char *str)
{
	long	number;
	int	i;

	i = 0;
	number = 0;
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
