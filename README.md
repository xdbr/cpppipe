cpppipe
=======

cpppipe – unix like pipes for containers

Usage
-----

Assume:

```
int plusone(int i) { return i+1; }
int addone(int i) { return i+1; }

std::vector<int> v{ 0, 2, 4 };
```

Then:

```
// result will be of type vector<int>
std::vector<int> result = ext::pipe<decltype(v)>{v} | plusone | addone;
```

Or:

```
ext::pipe<decltype(v)> pipe{ v };

// result will be of type pipe<T>
auto result = pipe | plusone | addone;
```

Or:

```
// result will be of type pipe<T>
auto result = ext::make_pipe(v) | plusone | addone;
```

Or:

```
(ext::make_pipe(v) | plusone | addone) > result;
```

About
-----

This is a pure `-Ofun`-project. It might still turn out useful some day – who knows?

Tests
-----

To run the tests, type:
```
rake clean && rake
```

License
-------

WTFPL