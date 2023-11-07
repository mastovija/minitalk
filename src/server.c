#include "../include/minitalk.h"


void signal_handler (int signal)
{
    static int current_bit;
    static char c;

    if (signal == SIGUSR1)
        c |= (1 << current_bit);
    current_bit++;
    if(current_bit == 8)
    {
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

    
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);


    while (1) {
        pause();
    }   

    return (0);
}   
