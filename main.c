#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <math.h>

void print_array(char array[], long length);
long hex_to_base64(char *hex, char **base64);

const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[])
{
  printf("HEX INPUT: %s\n", argv[1]);
  char *base64;
  long length = hex_to_base64(argv[1], &base64);
  printf("BASE64 OUTPUT: ");
  print_array(base64, length);
}

long hex_to_base64(char *hex, char **base64) {
  mpz_t decimal;
  mpz_init_set_str (decimal, hex, 16);
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
  // char base64_arr[length];
  char *base64_arr;
  base64_arr = (char *) malloc(length);

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
    base64_arr[(length - 1) - power] = place_char;
    mpz_t decrement;
    mpz_init(decrement);
    mpz_mul_ui(decrement, place_value, quotient_ui);
    mpz_sub(decimal, decimal, decrement);
    power--;
  }

  *base64 = &base64_arr[0];
  return length;
}

void print_array(char *array, long length) {
  // printf("firstchar: %c\n", array[0]);
  for (long i = 0; i < length; i++) {
    printf("%c", array[i]);
  }
  printf("\n");
}
