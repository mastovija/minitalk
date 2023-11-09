#include "../include/minitalk_bonus.h"


void signal_handler (int signal, siginfo_t *info, void *context)
{
    static int current_bit;
    static int c;

    (void)context;
    if (signal == SIGUSR1)
        c |= (1 << current_bit);
    current_bit++;
    if(current_bit == 8)
    {
        if (c == 0)
        {
            if(kill(info->si_pid, SIGUSR2) == -1)
                ft_printf("Error confirming the message\n");
        }
        ft_printf("%c", c);
        current_bit = 0;
        c = 0;
    }
}

int main (int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        ft_printf("Error: input must be: ./server");
        return (1);
    }
        
    struct sigaction sa;
    int pid = getpid();
    
    ft_printf("PID: %d\n", pid);

    
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1) 
    {
        pause();
    }   

    return (0);
}   
