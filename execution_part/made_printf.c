/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:06:48 by sfellahi          #+#    #+#             */
/*   Updated: 2024/09/17 12:48:56 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	printstring(const char *text, int *charcount)
{
	if (!text)
		text = "(null)";
	while (*text)
		*charcount += write(1, text++, 1);
}

void	printnumber(long long value, int base, int *charcount)
{
	char	*digits;

	digits = "0123456789abcdef";
	if (value < 0)
	{
		value = -value;
		*charcount += write(1, "-", 1);
	}
	if (value >= base)
		printnumber(value / base, base, charcount);
	*charcount += write(1, &digits[value % base], 1);
}

int	made_printf(const char *format, ...)
{
	int		charcount;
	va_list	args;

	charcount = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && (*(format + 1) == 's' || *(format + 1) == 'd'))
		{
			format++;
			if (*format == 's')
				printstring(va_arg(args, const char *), &charcount);
			else if (*format == 'd')
				printnumber(va_arg(args, int), 10, &charcount);
		}
		else
			charcount += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (charcount);
}
