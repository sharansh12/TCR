#include "../header.h"
struct HLD {
	int V; vvi &graph;
	vi p, pr, d, heavy; // parents, path-root; heavy child, depth
	HLD(vvi &graph, int root = 0) : V(graph.size()), graph(graph),
	p(V,-1), pr(V,-1), d(V,0), heavy(V,-1) { dfs(root);
		for(int i=0; i<V; ++i) if (p[i]==-1 || heavy[p[i]]!=i)
			for (int j=i; j!=-1; j=heavy[j]) pr[j] = i;
	}
	int dfs(int u){
		ii best; int s=1, ss;	// best, size (of subtree)
		for(auto &v : graph[u]) if(u!=p[v])
			d[v]=d[u]+1, p[v]=u, s += ss=dfs(v), best = max(best,{ss,v});
		heavy[u] = best.second; return s;
	}
	int lca(int u, int v){
		for(; pr[u]!=pr[v]; v=p[pr[u]]) if(d[pr[u]] > d[pr[v]]) swap(u,v);
		return d[u] < d[v] ? u : v;
	}
};
