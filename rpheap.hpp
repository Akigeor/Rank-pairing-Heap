#include <algorithm>
#include <list>
namespace sjtu {
	template<class T, class Compare = std::less<T>>
	class rpheap {
		class error {};
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
		node *link(node *&a, node *&b) {
			if (Compare()(a -> key, b -> key)) {
				std::swap(a, b);
			}
			a -> child[1] = b -> child[0];
			b -> child[0] -> parent = a;
			b -> child[0] = a;
			a -> parent = b;
			b -> rank ++;
			return b;
		}
	public:
		/*(1)class iterator {void decrease_key(const T &new_key) {}};
		  (2)iterator push(const T &key) {} (3)bool empty() {}*/
		/*(1)void pop() {} (2)T& top() {} (3)size_t size() {}*/
		/*(1)test (2)operator = (3)copy constructor*/
		class iterator{
			friend rpheap;
			private:
				rpheap* which;
				node* it;
			public:
				iterator(){
					which = nullptr;
					it = nullptr;
				}
				iterator(rpheap* _which,node* _it){
					which = _which;
					it = _it;
				}
				T& operator*() const {
					return it->key;
				}
				void decrease_key(const T &new_key){
					it->key = new_key;
					if (it->parent == null){
						if (Compare()(it->key,(*which->min_root)->key)){
							for (which->min_root = (which->roots).begin();*(which->min_root) != it;which->min_root ++);
						}
						return;
					}
					node *u = it->parent;
					node *y = it->child[1];
					it->child[1] = null;
					it->parent = null;
					if (u->child[1] == it) u->child[1] = y; else u->child[0] = y;
					y->parent = u;
					(which->roots).push_back(it);
					if (Compare()(it->key,(*which->min_root)->key)){
						which->min_root = -- (which->roots).end();
					}
					while (1){
						if (u->parent == null){
							u->rank = u->child[0]->rank + 1;
							break;
						}
						node *v = u->child[0];
						node *w = u->child[1];
						int k;
						if (v->rank > w->rank) k = v->rank; else k = w->rank;
						if (v->rank == w->rank) ++ k;
						if (k >= u->rank) break;
						u->rank = k;
						u = u->parent;
					}
				}
		};
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
		const T & top() {
			if (_size == 0) throw error();
			return (*min_root) -> key;
		}
		size_t size() {
			return _size;
		}
		bool empty(){
			return _size == 0;
		}
		iterator push(const T &key){
			node* now = new node(key,null,null,null);
			roots.push_back(now);
			if (Compare()(key,(*min_root)->key)){
				min_root = roots.end();
				-- min_root;
			}
			++ _size;
			return iterator(this,now);
		}
		void pop() {
			if (_size == 0) throw error();
			-- _size; 
			node* cur_node = (*min_root) -> child[0];
			while (cur_node != null) {
				node *tmp = cur_node -> child[1];
				cur_node -> child[1] = null;
				cur_node -> parent = null;
				roots.push_back(cur_node);
				cur_node = tmp;
			}
			delete *min_root;
			roots.erase(min_root);
			int max_size = 0;
			for (auto it = roots.begin(); it != roots.end(); it ++) {
				max_size = std::max(max_size, (*it) -> rank);
			}
			std::vector<node*> *count = new std::vector<node*> [max_size + 2];
			for (auto it = roots.begin(); it != roots.end(); it ++) {
				count[(*it) -> rank].push_back(*it);
			}
			int max_num = 0, pos = 0;
			for (int i = 0; i <= max_size; i ++) {
				if (max_num < count[i].size()) {
					max_num = count[i].size();
					pos = i;
				}
			}
			while (count[pos].size() > 1) {
				node *tmp = count[pos].back();
				count[pos].pop_back();
				node *result = link(count[pos].back(), tmp);
				count[pos].pop_back();
				count[pos + 1].push_back(result);
			}
			roots.clear();
			roots.resize(0);
			for (int i = 0; i <= max_size + 1; i ++) {
				if (count[i].size() > 0) {
					for (auto x : count[i]) {
						roots.push_back(x);
					}
				}
			}
			min_root = roots.end();
			for (typename std::list<node*>::iterator i = roots.begin(); i != roots.end(); ++ i) {
				if (min_root == roots.end() || Compare()((*i)->key, (*min_root)->key)) {
					min_root = i;
				}
			}
		}
	};
};
