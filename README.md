# What are these?
These are C++ pre-definded structures

# Lazy Segmant Tree
## How to use?
### Declaration
The syntax
```c++
alg::segmant_tree<$DataType$, $MergeFunction$, $LazyUpdateMerge$> $Name$;
```

### Available merge functions
- **`merge_sum`**: Summation
- **`merge_xor`**: Bitwise XOR
- **`merge_max`**: Maximum element
- **`merge_min`**: Minimum element

### Variables
- **`INVALID`**: the value that is out of range
- **`n`**: The size of the array
- **`values`**: The array

### Functions
- **`build()`**: To build the segmant tree
- **`get(l, r)`**: To get a range
- **`update(idx, upd)`**: To update a single element
- **`lazy_update(l, r, upd)`**: To update a range

## Example
```c++
int q;
alg::segmant_tree<ll> sg;
cin >> sg.n >> q;
for (int i = 0; i < sg.n; i++) cin >> sg.values[i];
sg.build();
while (q--)
{
	int l, r;
	cin >> l >> r;
	sg.get(l, r);
}
```

# Disjoint union set (DSU)
## How to use?
### Declaration
The syntax
```c++
alg::dsu $Name$;
```

## Avaliable methods
- `initialize()`: Initialize arrays to default values based on `dsu.n`
- `link(x, y)`: Union two `x` and `y` nodes, returns false if they were connected before, otherwise returns true
- `root(x)`: Get the root node for the component of node `x`
- `get_components()`: Returns components count
- `same_component(x, y)`: Checks if nodes `x` and `y` are on the same component
