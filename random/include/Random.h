/*
 * Random.h
 *
 *  Created on: Sep 18, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_RANDOM_H_
#define INCLUDE_RANDOM_H_

#ifdef __cplusplus
extern"C"{
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

///
//The implementation of Random here is according to the LCLib Random Specification
//The implementation is defined by Oracle, under java.util.Random, which is adopted
// as standard by LCLib.
//The implementation is according to https://docs.oracle.com/javase/8/docs/api/java/util/Random.html
// Pursuant to that documentation, this code comes with the following warnings
//
/// Thread-safety
// If this file is compiled with the macro TIGAME_MULTITHREAD_SUPPORT,
// then instances of Random are thread safe. However, use of
// a single instance of Random across multiple threads may
// encounter contention, and therefore is disabled.
// If thread-safety is not required, the macro can be left undefined,
// and use of Random will be generally faster.
//
/// Security
// This Random Number Generator is NOT Cryptographically Strong and should NOT be used
// for Security Purposes.
typedef struct Random Random;




/**
 * Creates a new, uninitialized Pseudo-random Number Generator according to the LCLib Random Specification.
 * The Random Instance, will be given a unique seed, as though by `Random_seed(rand)` the first time its used, if neither Random_seed nor Random_setSeed is called on it prior.
 * Random_new allocates the instance via a call to malloc. If malloc fails, Random_new returns NULL.
 * However, it may make additional allocations or initializations.
 * If these additional allocations or initializations fail,
 *  any which are completed are deallocated and/or deinitialized in the reverse order,
 *  then the instance is deallocated using free, and the call returns NULL.
 * The instance must be destroyed using Random_free. If the instance is freed in any other way, the behavior is undefined.
 */
Random* Random_new();

/**
 * Destroys the given instance of Random.
 * All allocations and initializations peformed by Random_new are reversed in the reverse order they were performed.
 * rand MUST be a valid random instance that was returned by Random_new() and has not been freed, or the behavior is undefined
 */
void Random_free(Random* rand);
void Random_seed(Random* rand);
void Random_setSeed(Random* rand,uint64_t seed);
int32_t Random_nextInt(Random* rand);
int32_t Random_nextIntb(Random* rand,int32_t bound);
int64_t Random_nextLong(Random* rand);
float Random_nextFloat(Random* rand);
double Random_nextDouble(Random* rand);
double Random_nextGaussian(Random* rand);
bool Random_nextBoolean(Random* rand);
void Random_nextBytes(Random* rand,void* out,size_t size);


#ifdef __cplusplus
};
#endif

#endif /* INCLUDE_RANDOM_H_ */
