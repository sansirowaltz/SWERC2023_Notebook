/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

void push(int k,int x,int y,int c)
{
	e[k].to=y;e[k].cap=c;e[k].flow=0;e[k].next=head[x];head[x]=k;
}

void addedge(int x,int y,int c)
{
	push(edgecnt++,x,y,c);
	push(edgecnt++,y,x,0);
}

bool bfs(int S,int T)
{
	for (int i=1;i<=N;i++) d[i]=N;d[T]=0;
	int f=1,r=1;q[1]=T;
	while (f<=r&&d[S]==N)
	{
		int p=head[q[f]];
		while (p!=-1)
		{
			if (e[p^1].cap>e[p^1].flow&&d[e[p].to]==N)
			{
				q[++r]=e[p].to;d[q[r]]=d[q[f]]+1;
			}
			p=e[p].next;
		}
		f++;
	}
	for (int i=1;i<=N;i++) cur[i]=head[i];
	return d[S]<N;
}

int dfs(int k,int T,int flow)
{
	if (k==T) return flow;
	int Tflow=0;
	while (cur[k]!=-1)
	{
		int x=cur[k];
		if (e[x].cap>e[x].flow&&d[e[x].to]+1==d[k])
		{
			int tmp=dfs(e[x].to,T,min(flow,e[x].cap-e[x].flow));
			e[x].flow+=tmp;e[x^1].flow-=tmp;
			Tflow+=tmp;flow-=tmp;
			if (!flow) return Tflow;
		}
		cur[k]=e[x].next;
	}
	return Tflow;
}

int dinic(int S,int T)
{
	int flow=0;
	while (bfs(S,T)) flow+=dfs(S,T,inf);
	return flow;
}
