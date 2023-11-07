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
#include <stdio.h>

// ft_conversion(va_list vl, const char format):
// This function is responsible for handling different format specifiers
// and printing the corresponding data to the standard output.
// It uses va_arg to retrieve the next argument from the variable argument list
//(va_list vl)
// based on the format specifier provided in the format parameter.
// It then calls the corresponding helper functions
//(ft_putchar, ft_putstr, ft_putptr, ft_putnbr, ft_putunsigned, ft_puthex)
// to handle the specific format specifier.
// The function returns the total number of characters printed.
// ft_printf(const char *format, ...):
// It takes a format string and a variable number of arguments.
// It uses va_list (vl) to access the variable arguments.
// The function iterates through the format string character by character.
// When it encounters a '%' character, it calls ft_conversion
// to handle the format specifier and corresponding argument.
// Otherwise, it simply calls ft_putchar to print regular characters.
// The function returns the total number of characters printed.

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_conversion(va_list vl, const char format)
{
	int	char_printed;

	char_printed = 0;
	if (format == 'c')
		char_printed += ft_putchar(va_arg(vl, int));
	else if (format == 's')
		char_printed += ft_putstr(va_arg(vl, char *));
	else if (format == 'p')
		char_printed += ft_putptr(va_arg(vl, uintptr_t));
	else if (format == 'd' || format == 'i')
		char_printed += ft_putnbr(va_arg(vl, int));
	else if (format == 'u')
		char_printed += ft_putunsigned(va_arg(vl, unsigned int));
	else if (format == 'x' || format == 'X')
		char_printed += ft_puthex(va_arg(vl, unsigned int), format);
	else if (format == '%')
		char_printed += ft_putchar('%');
	return (char_printed);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	vl;
	int		char_printed;

	if (format == NULL)
	{
		return (-1);
	}
	i = 0;
	char_printed = 0;
	va_start(vl, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			char_printed += ft_conversion(vl, format[i + 1]);
			i++;
		}
		else
			char_printed += ft_putchar(format[i]);
		i++;
	}
	va_end(vl);
	return (char_printed);
}
/*
int	main(void)
{
	ft_printf(0);
	printf(0);
	printf(" %p %p\n", 0, 0);
	ft_printf(" %p %p\n", 0, 0);
	ft_printf("Hello, %s!\n", "John");
	ft_printf("My age is %d.\n", 25);
	ft_printf("My pointer address is %p.\n", &main);
	ft_printf("This is a character: %c\n", 'A');
	ft_printf("Unsigned integer: %u\n", 42);
	ft_printf("Hexadecimal (lowercase): %x\n", 255);
	ft_printf("Hexadecimal (uppercase): %X\n", 255);
	ft_printf("Print a percentage sign: %%\n");
	return (0);
}
*/
