namespace alg {
	using std::max;
	using std::min;
	const int maxSG = 2e5 + 1;

	struct range {
		range(int idx) : left(idx), right(idx) {}
		range(int l, int r) : left(l), right(r) {}
		int left, right;
		int size() { return right - left + 1; }
		int mid() { return (left + right) / 2; }
		bool out(range q) {
			return (q.left > right || q.right < left);
		}
		bool nested(range q) {
			return (left <= q.left && q.right <= right);
		}
		range lhalf() { return range(left, mid()); }
		range rhalf() { return range(mid() + 1, right); }

		std::istream& operator >> (range& rg) {
			return (std::cin >> rg.left >> rg.right);
		}
	};

	template<class Type, class _UpdTy>
	Type lazy_increment_sum(Type original, _UpdTy update, range r)
	{
		return original + (r.size() * update);
	}

	template<class Type, class _UpdTy>
	Type lazy_increment(Type original, _UpdTy update, range r)
	{
		return original + update;
	}

	template<class Type, class _UpdTy>
	Type lazy_set(Type original, _UpdTy update, range r)
	{
		return update;
	}

	template<class Type>
	Type merge_sum(Type l, Type r)
	{
		return l + r;
	}

	template<class Type>
	Type merge_xor(Type l, Type r)
	{
		return l ^ r;
	}

	template<class Type>
	Type merge_max(Type l, Type r)
	{
		return max(l, r);
	}

	template<class Type>
	Type merge_min(Type l, Type r)
	{
		return min(l, r);
	}
	template<class UpdType>
	UpdType expand_lazy_inc(UpdType lazy, UpdType upd)
	{
		return lazy + upd;
	}

	template<class UpdType>
	UpdType expand_lazy_new(UpdType lazy, UpdType upd)
	{
		return upd;
	}

	template <class Type = int,
		Type merge(Type l, Type r) = merge_sum,
		class UpdType = int,
		Type lazy_upd(Type original, UpdType update, range r) = lazy_increment,
		UpdType expand_lazy(UpdType lazy, UpdType upd) = expand_lazy_inc
	>
	class segmant_tree // <type, merge_function>
	{
	public:
		Type values[maxSG];
		void clear()
		{
			for (int i = 0; i < maxSG; i++)
				tree[i] = values[i] = OUT;
			for (int i = 0; i < maxSG; i++)
				lazy[i] = OUTUPD;
			n = 0;
		}
		void resize(int sz)
		{
			clear();
			n = sz;
		}
		void set_out(Type outside)
		{
			OUT = outside;
		}
		void set_out_update(UpdType outside)
		{
			OUTUPD = outside;
		}
		int size()
		{
			return n;
		}
		range all()
		{
			return range(0, n - 1);
		}
		void build()
		{
			build_util(all());
		}
		Type get(range r)
		{
			return get_util(r, all());
		}
		void update(int index, Type value)
		{
			update_util(index, value, all());
		}
		void lazy_update(range r, UpdType value)
		{
			lazy_update_util(r, all(), value);
		}

	private:
		int n;
		Type OUT, OUTUPD;
		Type tree[4 * maxSG];
		UpdType lazy[4 * maxSG];

		void expand_lazy_util(int pos, range arr)
		{
			if (lazy[pos] != OUTUPD) {
				tree[pos] = lazy_upd(tree[pos], lazy[pos], arr);
				if (arr.size() == 1) {
					values[arr.left] = tree[pos];
				}
				else {
					lazy[pos * 2] = expand_lazy(lazy[pos * 2], lazy[pos]);
					lazy[pos * 2 + 1] = expand_lazy(lazy[pos * 2 + 1], lazy[pos]);
				}
				lazy[pos] = OUTUPD;
			}
		}

		Type get_util(range q, range arr, int pos = 1)
		{
			// Out of range
			if (q.out(arr))
				return OUT;

			expand_lazy_util(pos, arr);

			if (q.nested(arr))
				return tree[pos];

			// Choices
			Type c1 = get_util(q, arr.lhalf(), pos * 2);
			Type c2 = get_util(q, arr.rhalf(), pos * 2 + 1);
			return merge(c1, c2);
		}

		void lazy_update_util(range q, range arr, UpdType upd, int pos = 1)
		{
			expand_lazy_util(pos, arr);

			// Out of range
			if (q.out(arr)) return;

			if (q.nested(arr))
			{
				lazy[pos] = expand_lazy(lazy[pos], upd);
				expand_lazy_util(pos, arr);
				return;
			}

			// Choices
			lazy_update_util(q, arr.lhalf(), upd, pos * 2);
			lazy_update_util(q, arr.rhalf(), upd, pos * 2 + 1);
			tree[pos] = merge(tree[pos * 2], tree[pos * 2 + 1]);
		}

		void update_util(int idx, Type value, range arr, int pos = 1)
		{
			if (arr.left == arr.right)
			{
				values[arr.left] = value;
				tree[pos] = values[arr.left];
				return;
			}

			if (idx <= arr.mid())
				update_util(idx, value, arr.lhalf(), pos * 2);
			else
				update_util(idx, value, arr.rhalf(), pos * 2 + 1);

			tree[pos] = merge(tree[pos * 2], tree[pos * 2 + 1]);
		}

		void build_util(range arr, int pos = 1)
		{
			if (arr.left == arr.right)
			{
				tree[pos] = values[arr.left];
				return;
			}
			build_util(arr.lhalf(), pos * 2);
			build_util(arr.rhalf(), pos * 2 + 1);
			tree[pos] = merge(tree[pos * 2], tree[pos * 2 + 1]);
		}
	};
}
