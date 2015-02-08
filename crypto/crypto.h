#ifndef CRYPTO_H
#define CRYPTO_H
#include "type.h"
/**
* ratDmac_GetKey - Create the seed of key 
 * @DMac: Type of Device + Mac Address,the length is 12 bytes.
 * @seed: The given random seed from the server 
 * @key: number of bytes to skip from the beginning of the RC4 stream
 * Returns: 0 on success, -1 on failure
 *
 * Generate RC4 pseudo random stream for the given key from the server
*/
int ratDmac_GetKey(const u8 *DMac, const u8 *seed,u8 *key);

/**
 * ratDmac_skip - XOR RC4 stream to given data with skip-stream-start
 * @key: RC4 key (16 bytes)
 * @keylen: RC4 key length
 * @skip: number of bytes to skip from the beginning of the RC4 stream
 * @data: data to be XOR'ed with RC4 stream
 * @data_len: buf length
 * Returns: 0 on success, -1 on failure
 *
 * Generate RC4 pseudo random stream for the given key, skip beginning of the
 * stream, and XOR the end result with the data buffer to perform RC4
 * encryption/decryption.
 */
int ratDmac_skip(const u8 *key, size_t keylen, size_t skip,
	     u8 *data, size_t data_len);
	     
#endif /* CRYPTO_H */
