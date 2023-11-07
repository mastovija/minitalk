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
//'ft_printf_number_hex.c'
// handles the printing of hexadecimal numbers in 'ft_printf'.
//'ft_hex_len': calculates the length of a hexadecimal number.
//'ft_print_hex': recursive function responsible for printing a hex number
// in reverse order.
// Depending on the format ('x' or 'X'), it prints the digit in lowercase
//('a' to 'f') or uppercase ('A' to 'F').
//'ft_puthex': this is the main function of this file. 
//It is used to print a hexadecimal number using the ft_print_hex function.

int	ft_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len ++;
		num = num / 16;
	}
	return (len);
}

void	ft_print_hex(unsigned int num, const char format)
{
	if (num >= 16)
	{
		ft_print_hex(num / 16, format);
		ft_print_hex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar((num + '0'));
		else
		{
			if (format == 'x')
				ft_putchar((num - 10 + 'a'));
			if (format == 'X')
				ft_putchar((num - 10 + 'A'));
		}
	}
}

int	ft_puthex(unsigned int num, const char format)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_print_hex(num, format);
	return (ft_hex_len(num));
}
