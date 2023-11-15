/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarside <jgarside@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:46:09 by jgarside          #+#    #+#             */
/*   Updated: 2023/11/10 18:46:12 by jgarside         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//CLIENT: sends a message as a series of signals to a specified PID.
//The message is converted char by char into a sequence of signals.
//(SIGUSR1 and SIGUSR2) and transmitted to the specified process. 
//When the message is complete it also sends a signal to end the message.
//if the server sends back the sigusr2 signal then it prints the msg_confirm.
#include "../include/minitalk_bonus.h"

void	confirm_msg(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("message recieved\n");
}

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
//It takes a char and sends a signal for each bit of that char (8 bits).
//If the bit is 1 it sends SIGURS1, if the bit is 0 it sends SIGURS2.
//'1 << current_bit': shifts the binary digit 1 to the left by 'current_bit'
//creating a mask with a 1 bit at the specified bit position 
//and 0 bits elsewhere.
//bitwise AND (&) between the char and the mask examines only
//the bit at the specified position in 'c'.
//it returns 1 if both bits are 1, if not it returns 0.
//usleep introduces a delay between sending the signals to regulate
//the transmission rate and ensure that the signals are not sent too fast
//and create signal overload and the receiving process can process such signals.

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
		signal(SIGUSR2, confirm_msg);
		char_to_signals(pid, '\0');
	}
	else
	{
		ft_printf("Error: the input must be like: ./client PID \"message\"\n");
		return (1);
	}
	return (0);
}
