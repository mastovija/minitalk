    #include "../include/minitalk_bonus.h"

    void	confirm_msg(int signal)
    {
	    if (signal == SIGUSR2)
		    ft_printf("message recieved\n");
    }

    int ft_atoi(char* str)
    {
        int i = 0;
        int sign = 1;
        int result = 0;
        
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
    int char_to_signals(int pid, char c)
    {
        int	current_bit;

        current_bit = 0;
        while (current_bit < 8)
        {
            if ((c & (1 << current_bit)))
            {
                if(kill(pid, SIGUSR1) == -1)
                    return (1);
            }
            else
            {
                if(kill(pid, SIGUSR2) == -1)
                    return (2);
            }
            usleep(500);
            current_bit++;
        }
        return (0);
    }

    int main (int argc, char** argv)
    {
        if (argc == 3)
        {
            int pid = ft_atoi(argv [1]);

            int i = 0;

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
