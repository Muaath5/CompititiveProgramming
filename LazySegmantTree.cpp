namespace alg {

	const int N = 2e5 + 1;

	template<class _Ty>
	_Ty lazy_increment(_Ty original, _Ty update)
	{
		return original + update;
	}

	template<class _Ty>
	_Ty lazy_decrement(_Ty original, _Ty update)
	{
		return original - update;
	}

	template<class _Ty>
	_Ty lazy_set(_Ty original, _Ty update)
	{
		return update;
	}

	template<class _Ty>
	_Ty merge_sum(_Ty left, _Ty right)
	{
		return left + right;
	}

	template<class _Ty>
	_Ty merge_xor(_Ty left, _Ty right)
	{
		return left ^ right;
	}

	template<class _Ty>
	_Ty merge_max(_Ty left, _Ty right)
	{
		return max(left, right);
	}

	template<class _Ty>
	_Ty merge_min(_Ty left, _Ty right)
	{
		return min(left, right);
	}

	template <class _Ty = int, _Ty merge(_Ty left, _Ty right) = merge_sum, _Ty lazy_upd(_Ty original, _Ty update) = lazy_increment >
	class segmant_tree // <type, merge_function>
	{
	private:
		_Ty* tree = new _Ty[3 * N];
		_Ty* lazy = new _Ty[3 * N];

	public:
		segmant_tree() {
			memset(lazy, 0, N);
		}
		int INVALID = 0;
		int n;
		_Ty* values = new _Ty[N];

		_Ty get(int l, int r)
		{
			if (l > r) swap(l, r);
			return get_util(l, r, 0, n - 1);
		}

		void update(int index, _Ty val)
		{
			update_util(index, val, 0, n - 1);
		}

		void lazy_update(int l, int r, _Ty val)
		{
			lazy_update_util(l, r, 0, n - 1, val);
		}

		void build()
		{
			build_util(0, n - 1);
		}

	private:
		_Ty get_util(int from, int to, int s, int e, int pos = 1)
		{
			// Out of range
			if (e < from || s > to)
				return INVALID;

			if (s >= from && e <= to)
				return tree[pos];

			const int md = (s + e) / 2;
			const int left = pos * 2;
			const int right = left + 1;

			// Choices
			_Ty c1 = get_util(from, to, s, md, left);	// left
			_Ty c2 = get_util(from, to, md + 1, e, right);	// right
			return merge(c1, c2);
		}

		void expand_lazy(int pos, int l, int r)
		{
			if (lazy[pos]) {
				const int left = pos * 2;
				const int right = left + 1;

				tree[pos] = lazy_upd(tree[pos], lazy[pos]);
				if (r - l) {
					lazy[left] += lazy[pos];
					lazy[right] += lazy[pos];
				}

				lazy[pos] = 0;
			}
		}

		void lazy_update_util(int from, int to, int s, int e, _Ty upd, int pos = 1)
		{
			expand_lazy(pos, s, e);

			// Out of range
			if (e < from || s > to) return;

			if (s >= from && e <= to) {
				lazy[pos] += upd;
				expand_lazy(pos, s, e);
				return;
			}

			const int md = (s + e) / 2;
			const int left = pos * 2;
			const int right = left + 1;

			lazy_update_util(from, to, s, md, upd, left);
			lazy_update_util(from, to, md+1, e, upd, right);

			tree[pos] = merge(tree[left], tree[right]);
		}

		void update_util(int idx, _Ty value, int l, int r, int pos = 1)
		{
			if (l == r)
			{
				values[l] = value;
				tree[pos] = values[l];
				return;
			}

			const int md = (l + r) / 2;
			const int left = pos * 2;
			const int right = left + 1;

			if (idx <= md)
				update_util(idx, value, l, md, left);
			else
				update_util(idx, value, md + 1, r, right);

			tree[pos] = merge(tree[left], tree[right]);
		}

		void build_util(int l, int r, int pos = 1)
		{
			if (l == r)
			{
				tree[pos] = values[l];
				return;
			}
			const int md = (l + r) / 2;
			const int left = pos * 2;
			const int right = left + 1;
			build_util(l, md, left);
			build_util(md + 1, r, right);
			tree[pos] = merge(tree[left], tree[right]);
		}
	};

}
