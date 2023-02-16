/**
 * Author: chilli
 * Date: 2019-04-25
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Higher precision FFT, can be used for convolutions modulo arbitrary integers
 * as long as $N\log_2N\cdot \text{mod} < 8.6 \cdot 10^{14}$ (in practice $10^{16}$ or higher).
 * Inputs must be in $[0, \text{mod})$.
 * Time: O(N \log N), where $N = |A|+|B|$ (twice as slow as NTT or FFT)
 * Status: stress-tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

#include "FastFourierTransform.h"

void dft(int *a,int n,int *ans)
{
	for (int i=0;i<n;i++) ans[i]=a[bitrev[i]];
	for (int i=1,len=n>>1;i<n;i<<=1,len>>=1)
		for (int j=0;j<n;j+=(i<<1))
			for (int k=0,p=0;k<i;k++,p+=len)
			{
				int u=ans[j+k],v=ll(ans[j+k+i])*w[p]%fft_m;
				ans[j+k]=(u+v)%fft_m;ans[j+k+i]=(u-v+fft_m)%fft_m;
			}
}

void fft(int *a,int n,int *b,int m,int *ans)
{
	int len=1;while (len<=n+m) len<<=1;
	for (int i=n+1;i<len;i++) a[i]=0;
	for (int i=m+1;i<len;i++) b[i]=0;
	bitrev[0]=0;
	for (int i=1;i<len;i<<=1)
		for (int j=0;j<i;j++)
			bitrev[j+i]=bitrev[j]+(len>>1)/i;
	int wm=power(fft_g,(fft_m-1)/len,fft_m);
	w[0]=1;for (int i=1;i<len;i++) w[i]=ll(w[i-1])*wm%fft_m;
	dft(a,len,c);dft(b,len,ans);
	for (int i=1;i<len/2;i++) swap(w[i],w[len-i]);
	for (int i=0;i<len;i++) c[i]=ll(c[i])*ans[i]%fft_m;
	dft(c,len,ans);wm=power(len,fft_m-2,fft_m);
	for (int i=0;i<=n+m;i++) ans[i]=ll(ans[i])*wm%fft_m;
}
