#include <algorithm>
#include <list>
namespace sjtu {
	template<class T, class Compare = std::less<T>>
	class rpheap {
		class node {
			friend class rpheap;
			T key;
			node *child[2], *parent;
			int rank;
			node() : key(), rank(-1) {
				child[0] = child[1] = parent = nullptr;
			}
			node(const T &key, node *l, node *r, node *par) : key(key), rank(0) {
				child[0] = l; child[1] = r;
				parent = par;
			}
			void destory() {
				for (int i = 0; i < 2; ++ i) {
					if (child[i] -> rank != -1) {
						child[i] -> destory();
						delete child[i];
					}
				}
			}
		};
		std::list<node*> roots;
		typename std::list<node*>::iterator min_root;
		size_t _size;
		node *null;
	public:
		void merge(rpheap &other) {
			if (&other == this) return;
			roots.splice(roots.end(), other.roots);
			if (other._size && Compare()((*other.min_root) -> key, (*min_root) -> key)) min_root = other.min_root;
			other.clear();
		}
		void clear() {
			for (auto x : roots) {
				x -> destory();
				delete x;
			}
			roots.clear();
			min_root = roots.end();
			_size = 0;
		}
		rpheap() {
			_size = 0;
			null = new node();
			roots.clear();
			min_root = roots.end();
		}
		~rpheap() {
			clear();
			delete null;
		}
	};
};

