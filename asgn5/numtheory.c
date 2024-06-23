#include <stdbool.h>
#include "numtheory.h"
#include "randstate.h"

void gcd(mpz_t d, mpz_t a, mpz_t b) {
	mpz_t for_a; // temporary variables so the actual a & b aren't changed
	mpz_t for_b;
	
	mpz_init_set(for_a , a);
	mpz_init_set(for_b , b);
	
	while (mpz_cmp_ui(for_b, 0) != 0) {
		mpz_set(d,for_b);
		mpz_mod(for_b, for_a, for_b);
		mpz_set(for_a, d);
	}
	mpz_set (d, for_a);

	mpz_clear(for_a);
	mpz_clear(for_b);
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
	
	// cannot do numbers that are zero, so we need to put this in
	if (mpz_cmp_ui(a, 0) == 0 || mpz_cmp_ui(n, 0) == 0) {
		mpz_set_ui(a,0);
		mpz_set_ui(n,0);
		mpz_set_ui(o,0);
		return;
	}
		
	mpz_t r;
	mpz_t r_prime;
	mpz_t for_r; // temporary variables so the actual r aren't changed
	
	mpz_t t;
	mpz_t t_prime;
	mpz_t for_t; // temporary variables so the actual t aren't changed
	
	mpz_t q;
	mpz_t product;
	mpz_t difference;
	
	mpz_init_set(r , n);
	mpz_init_set(r_prime , a);
	mpz_init_set_ui(t ,0);
	mpz_init_set_ui(t_prime , 1); // constant means variable
	mpz_init(for_r);
	mpz_init(for_t);
	mpz_init(product);
	mpz_init(difference);
	mpz_init (q);
	
	while (mpz_cmp_ui(r_prime, 0) != 0) { // while (r_prime != 0) 
		mpz_fdiv_q(q, r, r_prime); // q = r/r_prime
		
		mpz_set(for_r, r); // need to save r
		
		mpz_mul(product, q, r_prime); // q * r_prime	
		mpz_set(r, r_prime);
		mpz_sub(difference, for_r , product); // r - q * r_prime
		mpz_set(r_prime, difference); // r_prime = r - q * r_prime;
		
		
		mpz_set(for_t, t);
		
		mpz_mul(product, q, t_prime); 	
		mpz_set(t, t_prime);	
		mpz_sub(difference, for_t , product); 
		mpz_set(t_prime, difference);
	} // end of while-loop
	
	if (mpz_cmp_ui(r, 1) > 0) {
		mpz_set(t , 0);
	}
	
	if (mpz_cmp_ui(t, 0) < 0) {
		mpz_add(t, t, n);
	}
	
	mpz_set(o,t);
	
	mpz_clear(r);
	mpz_clear(r_prime);
	mpz_clear(t);
	mpz_clear(t_prime);
	mpz_clear (for_r); 
	mpz_clear (for_t); 
	mpz_clear (q);
	mpz_clear (product);
	mpz_clear (difference);
}



void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
	
	mpz_t v;
	mpz_t p;
	mpz_t v_temp;
	mpz_t d_temp; // don't want to change d
	
	mpz_init_set(p, a);
	mpz_init_set_ui(v, 1);
	mpz_init(v_temp);
	mpz_init_set(d_temp, d);
	
	while (mpz_cmp_ui(d_temp, 0) > 0) {
		if (mpz_odd_p(d_temp) != 0) {
			mpz_mul(v_temp, v , p);
			mpz_mod(v , v_temp, n);
		} // end of first if-statement
		mpz_mul(v_temp, p, p);
		mpz_mod(p, v_temp, n);
		
		mpz_fdiv_q_ui(d_temp, d_temp, 2);
	}
	mpz_set(o, v);
	
	mpz_clear(v_temp);
	mpz_clear(d_temp);
	mpz_clear(v);
	mpz_clear (p); 

}

bool is_prime(mpz_t n, uint64_t iters) {
	
	// we must also check for small prime numbers (0,1,2,3)
	if (mpz_cmp_ui(n, 0) == 0 || mpz_cmp_ui(n, 1) == 0) {
		return false;
	}
	else if (mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0) {
		return true;
	}

	mpz_t random;
	mpz_t compare; 
	mpz_t s;
	mpz_t y;
	mpz_t r;
	mpz_t r_again;
	mpz_t j;
	mpz_t two_power;
	mpz_t subtract_one;

	mpz_init(compare);
	mpz_init(r);
	mpz_init(y);
	mpz_init_set (r_again, r);
	mpz_init(random);
	mpz_init(two_power);
	mpz_init(subtract_one);
	mpz_init_set_ui (j,0);
	mpz_init_set_ui(s,0);

	mpz_sub_ui(compare, n, 1); //compare = n - 1
	mpz_sub_ui(subtract_one, n, 1); //subtract_one = n - 1
	
	while ((mpz_even_p(compare) != 0) && (mpz_cmp_ui(compare, 0) != 0)) {
		mpz_fdiv_q_ui(compare, compare, 2); 
		mpz_add_ui(s, s, 1);
	}

	mpz_set(r, compare); // write n−1= 2srsuch that r is odd 

	for (uint64_t i = 0; i < iters; i ++) {
		// choose random a∈{2,3,...,n−2}
		mpz_sub_ui(compare, n, 3); // n - 3
		mpz_urandomm(random, state, compare);
		mpz_add_ui(random, random, 2);

		pow_mod(y, random, r, n);
		mpz_sub_ui(compare, n, 1); // compare = n - 1

		if (mpz_cmp_d (y, 1) != 0 && mpz_cmp(y, compare) != 0) { 
			mpz_set_ui(j, 1);
			mpz_sub_ui(subtract_one, s, 1); // subtract_one = s - 1
			// while ((j <= s - 1) and (y != n - 1)) 
			while ((mpz_cmp(j, subtract_one) < 0 || mpz_cmp(j, subtract_one) == 0) && mpz_cmp(y, compare) != 0) {
				mpz_set_ui(two_power, 2);
				pow_mod(y, y, two_power, n);

				if (mpz_cmp_d (y, 1) == 0) {
				// clear all mpz_t
					mpz_clear (random);
					mpz_clear (compare); 
					mpz_clear (s);
					mpz_clear (y);
					mpz_clear (r);
					mpz_clear (j);
					mpz_clear (two_power);
					mpz_clear (subtract_one);
					return false;
				} // end of if-statement

			mpz_add_ui(j, j, 1);
			} // end of while-statement

		// compare...	
		// if (y != n -1)
		if (mpz_cmp(y, compare) != 0) {
			mpz_clear (random);
			mpz_clear (compare); 
			mpz_clear (s);
			mpz_clear (y);
			mpz_clear (r);
			mpz_clear (j);
			mpz_clear (two_power);
			mpz_clear (subtract_one);
			return false;
		}
			
		} // end of if-statement
	}
	mpz_clear (random);
	mpz_clear (compare); 
	mpz_clear (s);
	mpz_clear (y);
	mpz_clear (r);
	mpz_clear (j);
	mpz_clear (two_power);
	mpz_clear (subtract_one);
	return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {

	
	bool if_prime = false;
	
	while (if_prime == false || mpz_sizeinbase(p, 2) < bits) {
		if_prime = false;
		mpz_urandomb(p, state, bits);
		if (is_prime (p, iters) == true) {
				if_prime = true;
				}
	}
}
