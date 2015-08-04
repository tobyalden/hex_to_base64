#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <math.h>

const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[])
{
  const char *hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

  // hex to decimal
  mpz_t decimal;
  mpz_init_set_str (decimal, hex, 16);
  gmp_printf ("DECIMAL VALUE: %Zd\n", decimal);

  // decimal to base64
  mpz_t base;
  mpz_init_set_ui(base, 64);
  mpz_t place_value;
  mpz_init(place_value);
  long power = 0;
  mpz_pow_ui(place_value, base, power);
  while(mpz_cmp(decimal, place_value) > 0) {
    power++;
    mpz_pow_ui(place_value, base, power);
  }

  long length = power;
  char base64[length];

  if(power > 0) {
    power--;
  }

  while(power >= 0) {
    mpz_pow_ui(place_value, base, power);
    mpz_t quotient;
    mpz_init(quotient);
    mpz_fdiv_q(quotient, decimal, place_value);
    unsigned long quotient_ui = mpz_get_ui(quotient);
    char place_char = base64_table[quotient_ui];
    base64[(length - 1) - power] = place_char;
    printf("Fill in cell #%ld with %c\n", power, place_char);
    mpz_t decrement;
    mpz_init(decrement);
    mpz_mul_ui(decrement, place_value, quotient_ui);
    mpz_sub(decimal, decimal, decrement);
    power--;
  }

  printf("BASE64 VALUE: ");
  for (int i = 0; i < length; i++) {
    printf("%c", base64[i]);
  }
  printf("\n");

}
