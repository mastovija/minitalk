/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarside <jgarside@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:46:32 by jgarside          #+#    #+#             */
/*   Updated: 2023/11/10 18:46:34 by jgarside         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//SERVER: receives and interprets signals (SIGUSR1 and SIGUSR2)
//sent by the client.
//It translates those signals into chars and 
//reconstruct the transmitted message.

//'1 << current_bit': shifts the binary digit 1 to the left by 'current_bit'
//creating a mask with a 1 bit at the specified bit position 
//and 0 bits elsewhere.
//bitwise OR (|): compares bits of two numbers and if at least one bit is 1, the
//resulting bit is set to 1, otherwise it is 0.
//because I use it like |= we compound the bits. 
//when current_bit is 8 then prints the char
//if c == 0 means that is the end of the message '/0' and sends back
//SIGUSR2 to the client to confirm the message

#include "../include/minitalk_bonus.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	current_bit;
	static int	c;

	(void)context;
	if (signal == SIGUSR1)
		c |= (1 << current_bit);
	current_bit++;
	if (current_bit == 8)
	{
		if (c == 0)
		{
			if (kill(info->si_pid, SIGUSR2) == -1)
				ft_printf("Error confirming the message\n");
		}
		ft_printf("%c", c);
		current_bit = 0;
		c = 0;
	}
}

//sigaction is used to modify the action to be taken when a specific
//signal occurs.
//We call the function signal_handler when the signal is received.
//sigemptyset: ensures that no signals are blocked 
//(an empty set) during the execution of the signal handler.
//sigaddset: indicates that when the signal handler is running,
//SIGUSR1 and 2 will be blocked from interrupting its execution
//SA_SIGINFO: I use this to get the PID from the client to send the confirmation

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: input must be: ./server");
		return (1);
	}
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
