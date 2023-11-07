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

//'ft_printf_ptr.c' is responsible for printing the hexadecimal representation
// of a pointer address, along with the "0x" prefix, as part of ft_printf.
// 'ft_ptr_len': calculates the length of the hexadecimal representation
// of the pointer address (uintptr_t value).
// uintptr_t type is used to represent unsigned integer values that can store
// the numeric representation of a pointer address.
// 'ft_print_ptr': recursively prints the hexadecimal digits of the given 'nb'.
// 'ft_putptr': is the main function responsible for printing the hexadecimal
// representation of a pointer address with the "0x" prefix.

int	ft_ptr_len(uintptr_t nb)
{
	int	len;

	if (nb == 0)
		return (3);
	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	ft_print_ptr(uintptr_t nb)
{
	if (nb >= 16)
	{
		ft_print_ptr(nb / 16);
		ft_print_ptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_putchar((nb + '0'));
		else
			ft_putchar((nb - 10 + 'a'));
	}
}

int	ft_putptr(uintptr_t ptr)
{
	int	char_printed;

	char_printed = 0;
	if (ptr == 0)
	{
		char_printed += write(1, "(nil)", 5);
	}
	else
	{
		char_printed += write(1, "0x", 2);
		ft_print_ptr(ptr);
		char_printed += ft_ptr_len(ptr);
	}
	return (char_printed);
}
