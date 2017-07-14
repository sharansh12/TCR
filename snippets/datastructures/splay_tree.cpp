#include "../header.h"
#include "./binary_tree_node.cpp"
template <typename T, typename R> // R is kept in root nodes
struct splay_tree_node : binary_tree_node<splay_tree_node<T, R>> {
	using node = splay_tree_node;
	using node_pr = std::pair<node *, node *>;
	using base = binary_tree_node<splay_tree_node>;
	using base::isleft, base::isright, base::l, base::r, base::p;
	T val;
	R pp;
	splay_tree_node(T _v, R _rv = {}) : val(_v), pp(_rv) {}
	node *rotate(bool right) { // return root of rotation
		node *p = this, x = p->child(!right);
		assert(x);
		p->link(!right, x->child(right));
		x->link(right, p);
		x->p = p->p;
		if(x->p) (x->p->l == p ? x->p->l : x->p->r) = x;
		if(x->p == nullptr) x->pp = p->pp;
		return x;
	}
	node *splay() { // return new root
		node *x = this;
		if(x->isroot()) return x;
		if(x->p->isroot()) return x->p->rotate(x->isleft());
		if(x->isleft() == x->p->isleft())
			return x->p->p->rotate(isleft())->rotate(isleft())->splay();
		if(x->isright() != x->p->isleft())
			return x->p->rotate(isleft())->p->rotate(isright())->splay();
		assert(false);
	}
	static node *merge(node *s, node *t) { // s++t, both roots
		return s->max()->splay()->right(t);
	}
	template <typename... Ts>
	node *merge(node *l, Ts... nodes) {
		return merge(l, merge(nodes...));
	}
	node_pr split() { return {splay()->unleft(), this}; }      // ..|x..
	node_pr splitleft() { return {this, splay()->unright()}; } // ..x|..
};