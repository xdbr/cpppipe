#ifndef PIPE_HPP_E3BC3NG5
#define PIPE_HPP_E3BC3NG5

#include <functional>
#include <algorithm>

namespace ext {
    
template<class T>
class pipe {
    T _;
public:
    typedef T value_type;
    typedef std::function< typename T::value_type( typename T::value_type ) > function_type;

    explicit pipe(const value_type & t) : _{t} {}
    operator T() const { return _; }
    inline pipe<T> operator|(const function_type & f) {
        std::transform(_.begin(), _.end(), _.begin(), f);
        return pipe<T>{_};
    }
    inline auto operator==(const pipe<T> & rhs) const
    ->decltype(this->_ == rhs._) {
        return this->_ == rhs._;
    }
    inline auto begin() -> decltype(_.begin()) { return _.begin(); }
    inline auto end() -> decltype(_.end()) { return _.end(); }
};

template<class T> pipe<T> make_pipe(T & t) { return pipe<T>(t); }

} /* ext */

#endif /* end of include guard: PIPE_HPP_E3BC3NG5 */
