/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

     memset(rankcnt,0,sizeof(rankcnt));
    for (int i=1;i<=len;i++) rankcnt[a[i]]++;
    for (int i=98;i<123;i++) rankcnt[i]+=rankcnt[i-1];
    for (int i=1;i<=len;i++) rank[i]=rankcnt[a[i]];
    int l=1;
    while (l<len)
    {
        for (int i=1;i<=len;i++)
        {
            rank1[i]=rank[i];
            if (i+l<=len) rank2[i]=rank[i+l]; else rank2[i]=0;
        }
        memset(rankcnt,0,sizeof(rankcnt));
        for (int i=1;i<=len;i++) rankcnt[rank2[i]]++;
        for (int i=1;i<=len;i++) rankcnt[i]+=rankcnt[i-1];
        for (int i=len;i;i--)
        {
            tmpsa[rankcnt[rank2[i]]]=i;rankcnt[rank2[i]]--;
        }
        memset(rankcnt,0,sizeof(rankcnt));
        for (int i=1;i<=len;i++) rankcnt[rank1[i]]++;
        for (int i=1;i<=len;i++) rankcnt[i]+=rankcnt[i-1];
        for (int i=len;i;i--)
        {
            sa[rankcnt[rank1[tmpsa[i]]]]=tmpsa[i];rankcnt[rank1[tmpsa[i]]]--;
        }
        rank[sa[1]]=1;
        for (int i=2;i<=len;i++)
        {
            rank[sa[i]]=rank[sa[i-1]];
            if ((rank1[sa[i]]!=rank1[sa[i-1]])||(rank2[sa[i]]!=rank2[sa[i-1]])) rank[sa[i]]++;
        }
        if (rank[sa[len]]==len) break;
        l<<=1;
    }
    l=0;
    for (int i=1;i<=len;i++)
        if (rank[i]>1)
        {
            int j=sa[rank[i]-1];
            while ((i+l<=len)&&(j+l<=len)&&(a[i+l]==a[j+l])) l++;
            height[rank[i]]=l;if (l) l--;
        }
