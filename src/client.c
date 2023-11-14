/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarside <jgarside@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:46:21 by jgarside          #+#    #+#             */
/*   Updated: 2023/11/10 18:46:24 by jgarside         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	char_to_signals(int pid, char c)
{
	int	current_bit;

	current_bit = 0;
	while (current_bit < 8)
	{
		if ((c & (1 << current_bit)))
		{
			if (kill(pid, SIGUSR1) == -1)
				return (1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (2);
		}
		usleep(100);
		current_bit++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		i = 0;
		while (argv[2][i] != '\0')
		{
			char_to_signals(pid, argv[2][i]);
			i++;
		}
		if (argv[2][i] == '\0')
		{
			char_to_signals(pid, '\n');
		}
	}
	else
	{
		ft_printf("Error: the input must be like: ./client PID \"message\"\n");
		return (1);
	}
	return (0);
}
