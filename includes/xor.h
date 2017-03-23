/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 23:27:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/22 23:27:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XOR_H
# define XOR_H

# ifdef XOR_PROG

#  include <printf.h>
#  include <libft.h>

# endif

# define XOR_KEY "JGUYET"

char		*crypt_string_to_xor(char *msg);
char		*uncrypt_xor_to_string(char *crypted);
char		*print_crypted(char *crypted);

#endif
