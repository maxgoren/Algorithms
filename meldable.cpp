#include <iostream>
using namespace std;

struct Edge {
	int v;
	int wt;
	Edge* next;
	Edge(int v_, int wt_, Edge* next_) {
		v = v_; wt = wt_; next = next_;
	}
};

class Graph {
	Edge** adjlist;
	int _V;
	int _E;
	public:
		Graph(int numv)
		{
			_V = numv;
			_E = 0;
			adjlist = new Edge*[numv];
			for (int i = 0; i < numv; i++)
				adjlist[i] = nullptr;
		}
		void addEdge(int v, int u, int wt)
		{
			for (auto it = adjlist[v]; it != nullptr; it = it->next)
				if (it->v == u)
					return;
			adjlist[v] = new Edge(u, wt, adjlist[v]);
			adjlist[u] = new Edge(v, wt, adjlist[u]);
			_E++;
		}
		int V() const {
			return _V;
		}
		int E() const {
			return _E;
		}
		Edge* adj(int v) {
			return adjlist[v];
		}
		void showGraph()
		{
			for (int i = 0; i < _V; i++) {
				cout<<i<<": ";
				for (auto it = adjlist[i]; it != nullptr; it = it->next)
					cout<<it->v<<"{"<<it->wt<<"} ";
				cout<<endl;
			}
		}
};

template <typename T>
class PQ {
	private:
		struct node {
			node* left;
			node* right;
			node* parent;
			T info;
			node(T info_)
			{
				info = info_;
				left = right = parent = nullptr;
			}
		};
		node* root;
		int n;
		node* merge(node* h1, node* h2)
		{
			if (h1 == nullptr) return h2;
			if (h2 == nullptr) return h1;
			if (h2->info < h1->info) return merge(h2, h1);
			if (rand() % 2 == 0) {
				h1->left = merge(h1->left, h2);
				h1->left->parent = h1;
			} else {
				h1->right = merge(h1->right, h2);
				h1->right->parent = h1;
			}
			return h1;
		}
	public:
		PQ()
		{
			n = 0;
			root = nullptr;
		}
		int size() const {
			return n;
		}
		bool empty() const {
			return root == nullptr;
		}
		void push(T info) {
			node* t = new node(info);
			root = merge(t, root);
			root->parent = nullptr;
			n++;
		}
		T top() {
			return root->info;
		}
		T pop()
		{
			T ret = root->info;
			node* t = root;
			root = merge(root->left, root->right);
			delete t;
			if (root != nullptr) root->parent = nullptr;
			n--;
			return ret;
		}
};

void dijkstra(Graph G, int start)
{
	PQ<pair<int, int>> pq;
	int *cost = new int[G.V()];
	int *pred = new int[G.V()];
	for (int i = 0; i < G.V(); i++) {
		cost[i] = 0x39393939;
		pred[i] = -1;
	}
	cost[start] = 0;
	pred[start] = start;
	pq.push(make_pair(0, start));
	while (!pq.empty()) {
		int curr = pq.pop().second;
		cout<<"Visiting: "<<curr<<"\n";
		for (auto it = G.adj(curr); it != nullptr; it = it->next) {
			int nc = cost[curr] + it->wt;
			if (nc < cost[it->v]) {
				cost[it->v] = nc;
				pred[it->v] = curr;
				pq.push(make_pair(nc, it->v));
			}
		}
	}
	for (int i = 0; i < G.V(); i++)
	{
		if (cost[i] < 0x39393939) {
			cout<<i<<": cost: "<<cost[i]<<"   Shortest path: ";
			for (int crawl = i; crawl != start; crawl = pred[crawl]) {
				cout<<crawl<<" <- ";
			}
			cout<<start<<"\n";
		}
	}
}

int main()
{
	Graph G(7);
	for (int i = 0; i < 14; i++)
	{
		int v = rand() % 7;
		int u = rand() % 7;
		int wt = rand() % 43;
		if (v != u)
			G.addEdge(v, u, wt);
		else
			i--;
	}
	dijkstra(G, 0);
	G.showGraph();
	return 0;
}