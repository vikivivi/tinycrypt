/**
  Copyright © 2017 Odzhan. All Rights Reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  3. The name of the author may not be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY AUTHORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#define R(v,n)(((v)>>(n))|((v)<<(32-(n))))
#define F(n)for(i=0;i<n;i++)
  
void chaskey(void *mk, void *data) {
    unsigned int i,*x=data,*k=mk;

    // add 128-bit key
    F(4)x[i]^=k[i];
    // apply 16 rounds
    F(16)
      x[0]+=x[1],
      x[1]=R(x[1],27)^x[0],
      x[2]+=x[3],
      x[3]=R(x[3],24)^x[2],
      x[2]+=x[1],
      x[0]=R(x[0],16)+x[3],
      x[3]=R(x[3],19)^x[0],
      x[1]=R(x[1],25)^x[2],
      x[2]=R(x[2],16);
    // add 128-bit key
    F(4)x[i]^=k[i];
}
