/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarside <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:47:15 by jgarside          #+#    #+#             */
/*   Updated: 2023/07/27 12:47:20 by jgarside         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//'ft_printf_int_decimal.c'
//handles the printing of decimal numbers in our 'ft_printf'.
//'ft_char': 
//is a utility function used by ft_itoa to convert an unsigned int to a string.
//'ft_len': calculates the length of an integer.
//'ft_itoa': converts an integer to a string.
//'ft_putnbr': this is the main function of this file.
//It is used to print an integer 'n' to the standard output.
//First calls 'ft_itoa' to convert the integer 'n' to a string 
//and stores the result in the string 'num'.
//Then calls 'ft_putstr' (defined in 'ft_printf.c') to print the string
//to the standard output and retrieves 
//the length of the printed string in the variable 'len'.
//After printing, it frees the memory allocated for the string
//representation using 'free'.
//Finally, it returns the length of the printed string.

char	*ft_char(char *s, unsigned int number, int len)
{
	while (number > 0)
	{
		s[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (s);
}

int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char				*s;
	int					len;
	unsigned int		number;
	int					sign;

	sign = 1;
	len = ft_len(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!(s))
		return (NULL);
	s[len--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		sign *= -1;
		number = n * -1;
		s[0] = '-';
	}
	else
		number = n;
	s = ft_char(s, number, len);
	return (s);
}

int	ft_putnbr(int n)
{
	int		len;
	char	*num;

	num = ft_itoa(n);
	len = ft_putstr(num);
	free(num);
	return (len);
}
