/*
 * rta-dmac stream cipher with Mac and Device class  
 * Copyright (c) 2015, Joe.yang <yangzc@szhittech.com>
 * 
 *
*/

#include <stdio.h>
#include <string.h>
#include "crypto.h"
#include "type.h"

#define S_SWAP(a,b) do{ u8 t = S[a];S[a] = S[b];S[b] = t; } while(0)

int ratDmac_GetKey(const u8 *DMac, const u8 *seed,u8 *key)
{
  u32 i,j=0;
  for(i = 0;i < 8;i++)
  {
    key[j] = DMac[i];
    j += 2;
  }
  j = 1;
  for(i = 0; i < 4;i++)
  {
    key[j] = seed[i];
    j +=2;
  }
  key[9] = 0x5a;
  key[11] =0xa5;
  key[13] = 0x55;
  return 0;
}
 
int ratDmac_skip(const u8 *key, size_t keylen, size_t skip, u8 *data, size_t data_len)
{
  u32 i,j,k;
  u8 S[256],*pos;
  size_t kpos;
  /* Setup RC4 state */
 for (i = 0; i < 256; i++)
     S[i] = i;
  j=0;
  kpos = 0;
  for (i = 0;i < 256; i++)
  {
    j = (j + S[i] +key[kpos])&0xff;
    kpos++;
   if(kpos >=keylen)
     kpos = 0;
   S_SWAP(i,j);
  }

/*Skip the start of the stream */
  i=j=0;
  for (k = 0; k < skip; k++)
  {
    i = (i+1) & 0xff;
    j = (j + S[i]) & 0xff;
    S_SWAP(i,j);
  }
  /*Apply RC4 to data */
   pos = data;
  for(k =0 ; k< data_len; k++)
  {
    i = (i + 1) & 0xff;
    j = (j + S[i]) & 0xff;
    S_SWAP(i, j);
    *pos++ ^=S[(S[i] +S[j]) & 0xff];
  }
  return 0;
}


