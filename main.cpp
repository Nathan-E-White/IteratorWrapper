#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <bitset>
#include <functional>
#include <numeric>
#include <utility>
#include <ctime>
#include <cassert>
#include <complex>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <memory>
#include <new>
#include <limits>
#include <climits>
#include <cfloat>
#include <cstdint>
#include <tuple>
#include <initializer_list>
#include <type_traits>
#include <cstddef>
#include <cstdarg>
#include <variant>
#include <optional>
#include <ranges>
#include <string_view>

#if __cpp_lib_ranges_stride >= 202207L
#include <ranges>
#endif





template<std::size_t P, std::size_t Q>
struct CliffordAlgebra {

};


template<typename T, std::size_t Dim>
class Point {
    std::array<T, Dim> data = {reinterpret_cast<T>(0)};

public:
    constexpr Point() = default;

    constexpr explicit Point(const std::array<T, Dim> &data) : data(data) {}

    constexpr explicit Point(std::array<T, Dim> &&data) : data(std::move(data)) {}

    template<typename... Args>
    constexpr explicit Point(Args... args) : data({args...}) {}

    T &operator[](std::size_t i) { return data[i]; }

    const T &operator[](std::size_t i) const { return data[i]; }

    static constexpr std::size_t dimension() { return Dim; }

};

#define ND [[nodiscard]]
#define MU [[maybe_unused]]
#define NR [[noreturn]]
#define DE [[deprecated]]
#define AT [[nodiscard]] auto
#define CT [[nodiscard]] constexpr auto


template<class C>
class Begin {

protected:
    constexpr Begin() noexcept = default;

    constexpr Begin(Begin const &) noexcept = default;

    constexpr Begin(Begin &&) noexcept = default;

    constexpr auto operator=(Begin const &) noexcept -> Begin & = default;

    constexpr auto operator=(Begin &&) noexcept -> Begin & = default;

    constexpr virtual ~Begin() noexcept = default;

public:
    ND MU virtual constexpr auto begin(C &c) -> decltype(c.begin()) { return c.begin(); }

    ND MU virtual constexpr auto begin(const C &c) -> decltype(c.begin()) { return c.begin(); }

    ND MU virtual constexpr auto operator()(C &c) -> decltype(c.begin()) { return c.begin(); }

    ND MU virtual constexpr auto operator()(const C &c) -> decltype(c.begin()) { return c.begin(); }

};

#define REF(X) std::reference_wrapper<X>

template<typename T, template<typename...> class C, std::size_t N = 0>
class End {
private:

    using type = std::conditional_t<N == 0, T, C<T, N>>;
    using ref_type = std::conditional_t<N == 0, REF(T), REF(C<T, N>)>;
    using const_ref_type = std::conditional_t<N == 0, REF(const T), REF(const C<T, N>)>;

    template<typename Ptr>
    using reference = std::common_reference_t<Ptr>;

    template<typename Ptr>
    using const_reference = std::add_const_t<std::common_reference_t<Ptr>>;

    template<typename Ptr>
    using value_type = std::remove_all_extents_t<std::remove_reference_t<Ptr>>;

    template<typename Ptr>
    using pointer = std::add_pointer_t<value_type<Ptr>>;

    template<typename Ptr>
    using const_pointer = std::add_const_t<pointer<Ptr>>;

protected:
    constexpr End() noexcept = default;

    constexpr End(End<T, C, N> const &) noexcept = default;

    constexpr End(End<T, C, N> &&) noexcept = default;

    constexpr auto
    operator=(End<T, C, N> const &) noexcept -> reference<End> = default; // NOLINT(misc-unconventional-assign-operator)

    constexpr auto operator=(End<T, C, N> &&) noexcept -> End & = default;

    constexpr virtual ~End() noexcept = default;

public:
    ND MU virtual constexpr auto end(C<T> &c) -> decltype(c.end()) { return c.end(); }

    ND MU virtual constexpr auto end(const C<T> &c) const -> decltype(c.end()) { return c.end(); }

    ND MU virtual constexpr auto end(T (&array)[N]) noexcept -> T * { return std::array<T, N>::end(); }

    ND MU virtual constexpr auto end(const T (&array)[N]) const noexcept -> T * { return std::array<T, N>::end(); }

    ND MU virtual constexpr auto operator()(C<T> &c) -> decltype(c.end()) { return c.end(); }

    ND MU virtual constexpr auto operator()(const C<T> &c) -> decltype(c.end()) { return c.end(); }
};

template<class C>
class CBegin {

protected:
    constexpr CBegin() noexcept = default;

    constexpr CBegin(CBegin const &) noexcept = default;

    constexpr CBegin(CBegin &&) noexcept = default;

    constexpr auto operator=(CBegin const &) noexcept -> CBegin<C> & = default;

    constexpr auto operator=(CBegin &&) noexcept -> CBegin<C> = default;

    constexpr virtual ~CBegin() noexcept = default;

public:

    ND MU virtual constexpr auto cbegin(const C &c) noexcept(noexcept(begin(c))) -> decltype(begin(c)) {
        return this->begin(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(CBegin<C>::cbegin(c))) -> decltype(cbegin(c)) {
        return CBegin<C>::cbegin(c);
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(CBegin<C>::cbegin(c))) -> decltype(cbegin(c)) {
        return CBegin<C>::cbegin(c);
    }

};

template<class C>
class CEnd {

protected:
    constexpr CEnd() noexcept = default;

    constexpr CEnd(CEnd const &) noexcept = default;

    constexpr CEnd(CEnd &&) noexcept = default;

    constexpr auto operator=(CEnd const &) noexcept -> CEnd<C> & = default;

    constexpr auto operator=(CEnd &&) noexcept -> CEnd<C> & = default;

    constexpr virtual ~CEnd() noexcept = default;

public:
    ND MU virtual constexpr auto cend(const C &c) noexcept(noexcept(end(c))) -> decltype(end(c)) {
        return this->end(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(CEnd<C>::cend(c))) -> decltype(cend(c)) {
        return CEnd<C>::cend(c);
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(CEnd<C>::cend(c))) -> decltype(cend(c)) {
        return CEnd<C>::cend(c);
    }
};


template<class C>
class RBegin {

protected:
    constexpr RBegin() noexcept = default;

    constexpr RBegin(RBegin const &) noexcept = default;

    constexpr RBegin(RBegin &&) noexcept = default;

    constexpr auto operator=(RBegin const &) noexcept -> RBegin<C> & = default;

    constexpr auto operator=(RBegin &&) noexcept -> RBegin<C> & = default;

    constexpr virtual ~RBegin() noexcept = default;

public:
    ND MU virtual constexpr auto rbegin(C &c) noexcept(noexcept(c.rbegin())) -> decltype(c.rbegin()) {
        return c.rbegin();
    }

    ND MU virtual constexpr auto rbegin(const C &c) noexcept(noexcept(c.rbegin())) -> decltype(c.rbegin()) {
        return c.rbegin();
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(RBegin<C>::rbegin(c))) -> decltype(rbegin(c)) {
        return RBegin<C>::rbegin(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(RBegin<C>::rbegin(c))) -> decltype(rbegin(c)) {
        return RBegin<C>::rbegin(c);
    }
};

template<class C>
class REnd {

protected:
    constexpr REnd() noexcept = default;

    constexpr REnd(REnd const &) noexcept = default;

    constexpr REnd(REnd &&) noexcept = default;

    constexpr auto operator=(REnd const &) noexcept -> REnd<C> & = default;

    constexpr auto operator=(REnd &&) noexcept -> REnd<C> & = default;

    constexpr virtual ~REnd() noexcept = default;

public:
    ND MU virtual constexpr auto rend(C &c) noexcept(noexcept(c.rend())) -> decltype(c.rend()) {
        return c.rend();
    }

    ND MU virtual constexpr auto rend(const C &c) noexcept(noexcept(c.rend())) -> decltype(c.rend()) {
        return c.rend();
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(REnd<C>::rend(c))) -> decltype(rend(c)) {
        return REnd<C>::rend(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(REnd<C>::rend(c))) -> decltype(rend(c)) {
        return REnd<C>::rend(c);
    }
};

template<class C>
class CRBegin {

protected:
    constexpr CRBegin() noexcept = default;

    constexpr CRBegin(CRBegin const &) noexcept = default;

    constexpr CRBegin(CRBegin &&) noexcept = default;

    constexpr auto operator=(CRBegin const &) noexcept -> CRBegin<C> & = default;

    constexpr auto operator=(CRBegin &&) noexcept -> CRBegin<C> & = default;

    constexpr virtual ~CRBegin() noexcept = default;

public:
    ND MU virtual constexpr auto crbegin(const C &c) noexcept(noexcept(rbegin(c))) -> decltype(rbegin(c)) {
        return this->rbegin(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(CRBegin<C>::crbegin(c))) -> decltype(crbegin(c)) {
        return CRBegin<C>::crbegin(c);
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(CRBegin<C>::crbegin(c))) -> decltype(crbegin(c)) {
        return CRBegin<C>::crbegin(c);
    }
};

template<class C>
class CREnd {

protected:
    constexpr CREnd() noexcept = default;

    constexpr CREnd(CREnd const &) noexcept = default;

    constexpr CREnd(CREnd &&) noexcept = default;

    constexpr auto operator=(CREnd const &) noexcept -> CREnd<C> & = default;

    constexpr auto operator=(CREnd &&) noexcept -> CREnd<C> & = default;

    constexpr virtual ~CREnd() noexcept = default;

public:
    ND MU virtual constexpr auto crend(const C &c) noexcept(noexcept(rend(c))) -> decltype(rend(c)) {
        return this->rend(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(CREnd<C>::crend(c))) -> decltype(crend(c)) {
        return CREnd<C>::crend(c);
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(CREnd<C>::crend(c))) -> decltype(crend(c)) {
        return CREnd<C>::crend(c);
    }
};

template<class C>
class Size {

protected:
    constexpr Size() noexcept = default;

    constexpr Size(Size const &) noexcept = default;

    constexpr Size(Size &&) noexcept = default;

    constexpr auto operator=(Size const &) noexcept -> Size<C> & = default;

    constexpr auto operator=(Size &&) noexcept -> Size<C> & = default;

    constexpr virtual ~Size() noexcept = default;

public:
    ND MU virtual constexpr auto size(const C &c) noexcept(noexcept(c.size())) -> decltype(c.size()) {
        return c.size();
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(Size<C>::size(c))) -> decltype(size(c)) {
        return Size<C>::size(c);
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(Size<C>::size(c))) -> decltype(size(c)) {
        return Size<C>::size(c);
    }
};


template<class C>
class Empty {
protected:
    constexpr Empty() noexcept = default;

    constexpr Empty(Empty const &) noexcept = default;

    constexpr Empty(Empty &&) noexcept = default;

    constexpr auto operator=(Empty const &) noexcept -> Empty<C> & = default;

    constexpr auto operator=(Empty &&) noexcept -> Empty<C> & = default;

    constexpr virtual ~Empty() noexcept = default;

public:
    ND MU virtual constexpr auto empty(const C &c) noexcept(noexcept(c.empty())) -> decltype(c.empty()) {
        return c.empty();
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(Empty<C>::empty(c))) -> decltype(empty(c)) {
        return Empty<C>::empty(c);
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(Empty<C>::empty(c))) -> decltype(empty(c)) {
        return Empty<C>::empty(c);
    }
};

template<class C>
class Data {
protected:
    constexpr Data() noexcept = default;

    constexpr Data(Data const &) noexcept = default;

    constexpr Data(Data &&) noexcept = default;

    constexpr auto operator=(Data const &) noexcept -> Data<C> & = default;

    constexpr auto operator=(Data &&) noexcept -> Data<C> & = default;

    constexpr virtual ~Data() noexcept = default;

public:
    ND MU virtual constexpr auto data(C &c) noexcept(noexcept(c.data())) -> decltype(c.data()) {
        return c.data();
    }

    ND MU virtual constexpr auto data(const C &c) noexcept(noexcept(c.data())) -> decltype(c.data()) {
        return c.data();
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(Data<C>::data(c))) -> decltype(data(c)) {
        return Data<C>::data(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(Data<C>::data(c))) -> decltype(data(c)) {
        return Data<C>::data(c);
    }
};


template<class C>
class Front {
protected:
    constexpr Front() noexcept = default;

    constexpr Front(Front const &) noexcept = default;

    constexpr Front(Front &&) noexcept = default;

    constexpr auto operator=(Front const &) noexcept -> Front<C> & = default;

    constexpr auto operator=(Front &&) noexcept -> Front<C> & = default;

    constexpr virtual ~Front() noexcept = default;

public:
    ND MU virtual constexpr auto front(C &c) noexcept(noexcept(c.front())) -> decltype(c.front()) {
        return c.front();
    }

    ND MU virtual constexpr auto front(const C &c) noexcept(noexcept(c.front())) -> decltype(c.front()) {
        return c.front();
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(Front<C>::front(c))) -> decltype(front(c)) {
        return Front<C>::front(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(Front<C>::front(c))) -> decltype(front(c)) {
        return Front<C>::front(c);
    }
};

template<class C>
class Back {
protected:
    constexpr Back() noexcept = default;

    constexpr Back(Back const &) noexcept = default;

    constexpr Back(Back &&) noexcept = default;

    constexpr auto operator=(Back const &) noexcept -> Back<C> & = default;

    constexpr auto operator=(Back &&) noexcept -> Back<C> & = default;

    constexpr virtual ~Back() noexcept = default;

public:
    ND MU virtual constexpr auto back(C &c) noexcept(noexcept(c.back())) -> decltype(c.back()) {
        return c.back();
    }

    ND MU virtual constexpr auto back(const C &c) noexcept(noexcept(c.back())) -> decltype(c.back()) {
        return c.back();
    }

    ND MU constexpr auto operator()(C &c) noexcept(noexcept(Back<C>::back(c))) -> decltype(back(c)) {
        return Back<C>::back(c);
    }

    ND MU constexpr auto operator()(const C &c) noexcept(noexcept(Back<C>::back(c))) -> decltype(back(c)) {
        return Back<C>::back(c);
    }
};

template<class C>
class At {
protected:
    constexpr At() noexcept = default;

    constexpr At(At const &) noexcept = default;

    constexpr At(At &&) noexcept = default;

    constexpr auto operator=(At const &) noexcept -> At<C> & = default;

    constexpr auto operator=(At &&) noexcept -> At<C> & = default;

    constexpr virtual ~At() noexcept = default;

public:
    ND MU virtual constexpr auto at(C &c, std::size_t i) noexcept(noexcept(c.at(i))) -> decltype(c.at(i)) {
        return c.at(i);
    }

    ND MU virtual constexpr auto at(const C &c, std::size_t i) noexcept(noexcept(c.at(i))) -> decltype(c.at(i)) {
        return c.at(i);
    }

    ND MU constexpr auto operator()(C &c, std::size_t i) noexcept(noexcept(At<C>::at(c, i))) -> decltype(at(c, i)) {
        return At<C>::at(c, i);
    }

    ND MU constexpr auto
    operator()(const C &c, std::size_t i) noexcept(noexcept(At<C>::at(c, i))) -> decltype(at(c, i)) {
        return At<C>::at(c, i);
    }
};


template<class C>
class MatrixIterator : public std::iterator<std::random_access_iterator_tag, typename C::value_type> {

    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename C::value_type;
    using difference_type = typename C::difference_type;
    using pointer = typename C::pointer;
    using reference = typename C::reference;

    // TODO: change to std::shared_ptr
    C *container;
    std::size_t index = 0x0;

protected:
    constexpr MatrixIterator() noexcept = default;

    constexpr MatrixIterator(MatrixIterator const &) noexcept = default;

    constexpr MatrixIterator(MatrixIterator &&) noexcept = default;

    constexpr auto operator=(MatrixIterator const &) noexcept -> MatrixIterator<C> & = default;

    constexpr auto operator=(MatrixIterator &&) noexcept -> MatrixIterator<C> & = default;

    constexpr virtual ~MatrixIterator() noexcept = default;

public:

    constexpr MatrixIterator(C &c, std::size_t i) noexcept: container(&c), index(i) {}

    constexpr MatrixIterator(const C &c, std::size_t i) noexcept: container(&c), index(i) {}

    constexpr auto operator*() noexcept(noexcept((*container)[index])) -> decltype((*container)[index]) {
        return (*container)[index];
    }

    constexpr auto operator*() const noexcept(noexcept((*container)[index])) -> decltype((*container)[index]) {
        return (*container)[index];
    }

    constexpr auto operator->() noexcept(noexcept(&(*container)[index])) -> decltype(&(*container)[index]) {
        return &(*container)[index];
    }

    constexpr auto operator->() const noexcept(noexcept(&(*container)[index])) -> decltype(&(*container)[index]) {
        return &(*container)[index];
    }

    constexpr auto
    operator[](std::size_t i) noexcept(noexcept((*container)[index + i])) -> decltype((*container)[index + i]) {
        return (*container)[index + i];
    }

    constexpr auto
    operator[](std::size_t i) const noexcept(noexcept((*container)[index + i])) -> decltype((*container)[index + i]) {
        return (*container)[index + i];
    }

    constexpr auto operator++() noexcept -> MatrixIterator<C> & {
        ++index;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> MatrixIterator<C> {
        MatrixIterator<C> it(*this);
        ++index;
        return it;
    }

    constexpr auto operator--() noexcept -> MatrixIterator<C> & {
        --index;
        return *this;
    }

    constexpr auto operator--(int) noexcept -> MatrixIterator<C> {
        MatrixIterator<C> it(*this);
        --index;
        return it;
    }

    constexpr auto operator+=(std::size_t i) noexcept -> MatrixIterator<C> & {
        index += i;
        return *this;
    }

    constexpr auto operator-=(std::size_t i) noexcept -> MatrixIterator<C> & {
        index -= i;
        return *this;
    }

    constexpr auto operator+(std::size_t i) const noexcept -> MatrixIterator<C> {
        return MatrixIterator<C>(*container, index + i);
    }

    constexpr auto operator-(std::size_t i) const noexcept -> MatrixIterator<C> {
        return MatrixIterator<C>(*container, index - i);
    }

    constexpr auto operator-(const MatrixIterator<C> &it) const noexcept -> std::size_t {
        return index - it.index;
    }

    constexpr auto operator==(const MatrixIterator<C> &it) const noexcept -> bool {
        return container == it.container && index == it.index;
    }

    constexpr auto operator!=(const MatrixIterator<C> &it) const noexcept -> bool {
        return container != it.container || index != it.index;
    }

    constexpr auto operator<(const MatrixIterator<C> &it) const noexcept -> bool {
        return container == it.container && index < it.index;
    }

    constexpr auto operator>(const MatrixIterator<C> &it) const noexcept -> bool {
        return container == it.container && index > it.index;
    }

    constexpr auto operator<=(const MatrixIterator<C> &it) const noexcept -> bool {
        return container == it.container && index <= it.index;
    }

    constexpr auto operator>=(const MatrixIterator<C> &it) const noexcept -> bool {
        return container == it.container && index >= it.index;
    }

    constexpr auto operator+(const MatrixIterator<C> &&it) const noexcept -> MatrixIterator<C> {
        return MatrixIterator<C>(*container, index + it.index);
    }

    constexpr auto operator-(const MatrixIterator<C> &&it) const noexcept -> MatrixIterator<C> {
        return MatrixIterator<C>(*container, index - it.index);
    }

    constexpr auto operator+=(const MatrixIterator<C> &&it) noexcept -> MatrixIterator<C> & {
        index += it.index;
        return *this;
    }

    constexpr auto operator-=(const MatrixIterator<C> &&it) noexcept -> MatrixIterator<C> & {
        index -= it.index;
        return *this;
    }

    constexpr auto operator==(const MatrixIterator<C> &&it) const noexcept -> bool {
        return container == it.container && index == it.index;
    }

    constexpr auto operator!=(const MatrixIterator<C> &&it) const noexcept -> bool {
        return container != it.container || index != it.index;
    }

    constexpr auto operator<(const MatrixIterator<C> &&it) const noexcept -> bool {
        return container == it.container && index < it.index;
    }

    constexpr auto operator>(const MatrixIterator<C> &&it) const noexcept -> bool {
        return container == it.container && index > it.index;
    }

    constexpr auto operator<=(const MatrixIterator<C> &&it) const noexcept -> bool {
        return container == it.container && index <= it.index;
    }

    constexpr auto operator>=(const MatrixIterator<C> &&it) const noexcept -> bool {
        return container == it.container && index >= it.index;
    }

};


template<typename T, template<typename...> class C, std::size_t N, std::size_t M>
class ColumnIterator :
        std::iterator<std::random_access_iterator_tag, T, std::ptrdiff_t, T *, T &> {
private:
    /* The purpose of thie class is to provide a column iterator for a matrix. */
    /* The column iterator is a random access iterator. */
    /* The column iterator is a bidirectional iterator. */
    /* The column iterator is a input iterator. */
    /* The column iterator is a output iterator. */
    /* The column iterator is meant to select a column from a matrix. */
    /* The column iterator is meant to be used with the Matrix class. */

    C<T> *container = nullptr;

    Begin<C<T>> begin_ = nullptr;
    End<T, C, N> end_ = nullptr;

    CBegin<C<T>> cbegin_ = nullptr;
    CEnd<C<T>> cend_ = nullptr;

    RBegin<C<T>> rbegin_ = nullptr;
    REnd<C<T>> rend_ = nullptr;

    CRBegin<C<T>> crbegin_ = nullptr;
    CREnd<C<T>> crend_ = nullptr;

    std::size_t index = static_cast<std::size_t>(0x0);

private:


public:

    constexpr ColumnIterator() noexcept = default;

    constexpr ColumnIterator(C<T> &container, std::size_t index) noexcept:
            container(&container), index(index) {}

    constexpr ColumnIterator(const ColumnIterator<C, T, N, M> &it) noexcept:
            container(it.container), index(it.index) {}

    constexpr ColumnIterator(ColumnIterator<C, T, N, M> &&it) noexcept:
            container(it.container), index(it.index) {}

    constexpr auto operator=(const ColumnIterator<C, T, N, M> &it) noexcept -> ColumnIterator<T, C, N, M> & {
        container = it.container;
        index = it.index;
        return *this;
    }

    constexpr auto operator=(ColumnIterator<C, T, N, M> &&it) noexcept -> ColumnIterator<T, C, N, M> & {
        container = it.container;
        index = it.index;
        return *this;
    }

    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    constexpr ColumnIterator(const C<T> &container, std::size_t index) noexcept: container(&container), index(index) {}

    constexpr explicit ColumnIterator(const ColumnIterator<T, C, N, M> &it) noexcept: container(it.container),
                                                                                      index(it.index) {}

    ND MU
    constexpr explicit
    ColumnIterator(ColumnIterator<T, C, N, M> &&it) noexcept: container(it.container), index(it.index) {}

    ND MU
    constexpr auto
    operator=(const ColumnIterator<T, C, N, M> &it) noexcept -> ColumnIterator<T, C, N, M> & {
        container = it.container;
        index = it.index;
        return *this;
    }

    ND MU
    constexpr auto
    operator=(ColumnIterator<T, C, N, M> &&it) noexcept -> ColumnIterator<T, C, N, M> & {
        container = it.container;
        index = it.index;
        return *this;
    }

    ND MU
    constexpr auto
    operator*() noexcept(noexcept((*container)[index])) -> decltype((*container)[index]) {
        return (*container)[index];
    }

    ND MU
    constexpr auto
    operator*() const noexcept(noexcept((*container)[index])) -> decltype((*container)[index]) {
        return (*container)[index];
    }

    ND MU
    constexpr auto
    operator->() noexcept(noexcept(&(*container)[index])) -> decltype(&(*container)[index]) {
        return &(*container)[index];
    }

    ND MU
    constexpr auto
    operator->() const noexcept(noexcept(&(*container)[index])) -> decltype(&(*container)[index]) {
        return &(*container)[index];
    }

    ND MU
    constexpr auto
    operator[](std::size_t i)
    noexcept(noexcept((*container)[index + i])) ->
    decltype((*container)[index + i]) {
        return (*container)[index + i];
    }

    ND MU
    constexpr auto
    operator[](std::size_t i)
    const noexcept(noexcept((*container)[index + i])) ->
    decltype((*container)[index + i]) {
        return (*container)[index + i];
    }

public:

    ND MU
    constexpr auto rbegin()
    noexcept -> decltype(rbegin_(container)) {
        return rbegin_(container);
    }

    ND MU
    constexpr auto rbegin()
    const noexcept -> decltype(rbegin_(container)) {
        return rbegin_(container);
    }

    ND MU
    constexpr auto crbegin()
    noexcept -> decltype(crbegin_(container)) {
        return crbegin_(container);
    }

    constexpr auto crbegin() const noexcept -> decltype(crbegin_(container)) {
        return crbegin_(container);
    }

    constexpr auto rend() noexcept -> decltype(rend_(container)) {
        return rend_(container);
    }

    constexpr auto rend() const noexcept -> decltype(rend_(container)) {
        return rend_(container);
    }

    constexpr auto crend() noexcept -> decltype(crend_(container)) {
        return crend_(container);
    }

    constexpr auto crend() const noexcept -> decltype(crend_(container)) {
        return crend_(container);
    }

    constexpr auto begin() noexcept -> decltype(begin_(container)) {
        return begin_(container);
    }

    constexpr auto begin() const noexcept -> decltype(begin_(container)) {
        return begin_(container);
    }

    constexpr auto cbegin() noexcept -> decltype(cbegin_(container)) {
        return cbegin_(container);
    }

    constexpr auto cbegin() const noexcept -> decltype(cbegin_(container)) {
        return cbegin_(container);
    }

    constexpr auto end() noexcept -> decltype(end_(container)) {
        return end_(container);
    }

    constexpr auto end() const noexcept -> decltype(end_(container)) {
        return end_(container);
    }

    constexpr auto cend() noexcept -> decltype(cend_(container)) {
        return cend_(container);
    }

    constexpr auto cend() const noexcept -> decltype(cend_(container)) {
        return cend_(container);
    }

    constexpr auto operator[](const std::size_t &i) noexcept -> decltype((*container)[i][index]) {
        return (*container)[i][index];
    }

    constexpr auto operator[](const std::size_t &i) const noexcept -> decltype((*container)[i][index]) {
        return (*container)[i][index];
    }

};


template<typename T, std::size_t N, std::size_t M>
class RMatrix {
private:

    std::array<T, N * M> data;

    std::array<std::ranges::take_view<std::array<T, N * M>>, M> m_tv_columns{data | std::views::take(N)};
    std::array<std::ranges::take_view<std::array<T, N * M>>, N> m_tv_rows{data | std::views::take(M)};

    std::array<std::ranges::ref_view<std::ranges::take_view<std::array<T, N * M>>>, M> m_rv_columns{m_tv_columns};
    std::array<std::ranges::ref_view<std::ranges::take_view<std::array<T, N * M>>>, N> m_rv_rows{m_tv_rows};

    /* Set up a stride view */
    std::ranges::stride_view

    void set_tvs() {
        /* Set the column take views */
        for (std::size_t i = 0; i < M; ++i) {
            m_tv_columns[i] = data | std::views::drop(i * N) | std::views::take(N);
        }
        /* Set the row take views */
        for (std::size_t i = 0; i < N; ++i) {
            m_tv_rows[i] = data | std::views::drop(i * M) | std::views::take(M);
        }
    }

    void set_rvs() {
        /* Set the column ref views */
        for (std::size_t i = 0; i < M; ++i) {
            m_rv_columns[i] = m_tv_columns[i];
        }
        /* Set the row ref views */
        for (std::size_t i = 0; i < N; ++i) {
            m_rv_rows[i] = m_tv_rows[i];
        }
    }



public:

        RMatrix() = default;

        RMatrix(const RMatrix &m) = default;

        RMatrix(RMatrix &&m) = default;

        RMatrix &operator=(const RMatrix &m) = default;

        RMatrix &operator=(RMatrix &&m) = default;

        RMatrix(const std::array<T, N * M> &data) : data(data) {
            set_tvs();
            set_rvs();
        }

        RMatrix(std::array<T, N * M> &&data) : data(std::move(data)) {
            set_tvs();
            set_rvs();
        }

        RMatrix(const std::array<std::array<T, M>, N> &data) {
            for (std::size_t i = 0; i < N; ++i) {
                for (std::size_t j = 0; j < M; ++j) {
                    this->data[i * M + j] = data[i][j];
                }
            }
            set_tvs();
            set_rvs();
        }

        RMatrix(std::array<std::array<T, M>, N> &&data) {
            for (std::size_t i = 0; i < N; ++i) {
                for (std::size_t j = 0; j < M; ++j) {
                    this->data[i * M + j] = std::move(data[i][j]);
                }
            }
            set_tvs();
            set_rvs();
        }

        RMatrix(const std::initializer_list<std::initializer_list<T>> &data) {
            std::size_t i = 0;
            for (const auto &row : data) {
                std::size_t j = 0;
                for (const auto &col : row) {
                    this->data[i * M + j] = col;
                    ++j;
                }
                ++i;
            }
            set_tvs();
            set_rvs();
        }

        RMatrix(std::initializer_list<std::initializer_list<T>> &&data) {
            std::size_t i = 0;
            for (auto &row : data) {
                std::size_t j = 0;
                for (auto &col : row) {
                    this->data[i * M + j] = std::move(col);
                    ++j;
                }
                ++i;
            }
            set_tvs();
            set_rvs();
        }

};


template<typename T, std::size_t M, std::size_t N>
class ND MU Matrix {


private: /* Private Types */
    using Row = std::array<T, N>;
    using Col = std::array<T, M>;
    using ColMajorData = std::array<Row, M>;
    using RowMajorData = std::array<Col, N>;

private:    /* Private Data */
    std::variant<ColMajorData, RowMajorData> data = ColMajorData{reinterpret_cast<Row>(0)};
    std::ranges::view_interface<Matrix> col_view = std::ranges::view_interface<Matrix>(data);
    std::ranges::view_interface<Matrix> row_view = std::ranges::view_interface<Matrix>(data);


public: /* Public Types */
    using value_type = T;
    using reference = std::common_reference<T>;
    using const_reference = std::add_const_t<std::common_reference<T>>;
    using pointer = std::add_pointer_t<std::common_reference<T>>;
    using const_pointer = std::add_const_t<std::add_pointer_t<std::common_reference<T>>>;
    using iterator = typename ColMajorData::iterator;
    using const_iterator = typename ColMajorData::const_iterator;
    using reverse_iterator = typename ColMajorData::reverse_iterator;
    using const_reverse_iterator = typename ColMajorData::const_reverse_iterator;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

public: /* Public Constructors */
    constexpr Matrix() = default;

    constexpr Matrix(const Matrix &other) = default;

    constexpr Matrix(Matrix &&other) noexcept = default;


    ND MU constexpr explicit Matrix(const ColMajorData &data) : data(data) {}

    ND MU constexpr explicit Matrix(ColMajorData &&data) : data(std::move(data)) {}

    ND MU constexpr explicit Matrix(const RowMajorData &data) : data(data) {}

    ND MU constexpr explicit Matrix(RowMajorData &&data) : data(std::move(data)) {}

    template<typename... Args>
    ND MU constexpr explicit Matrix(Args... args) : data({args...}) {}

    template<typename... Args>
    ND MU constexpr explicit Matrix(const std::array<Args, N> &... args) : data({args...}) {}

    template<typename... Args>
    ND MU constexpr explicit Matrix(std::array<Args, N> &&... args) : data({std::move(args)...}) {}

    ND MU constexpr explicit Matrix(const std::array<T, M * N> &data) {
        std::copy(data.begin(), data.end(), this->data.begin());
    }

    MU constexpr virtual ~Matrix() = default;


    constexpr Matrix &operator=(const Matrix &other) = default;

    constexpr Matrix &operator=(Matrix &&other) noexcept = default;

    template<typename U>
    constexpr explicit Matrix(Matrix<U, M, N> const &other) noexcept {
        std::copy(other.begin(), other.end(), this->data.begin());
    }

    template<typename U>
    constexpr explicit Matrix(Matrix<U, M, N> &&other) noexcept {
        std::move(other.begin(), other.end(), this->data.begin());
    }

    template<typename U>
    constexpr Matrix &operator=(const Matrix<U, M, N> &other) {
        std::copy(other.begin(), other.end(), this->data.begin());
        return *this;
    }


public: /* Public Member Functions */

    static constexpr std::size_t rows() { return M; }

    static constexpr std::size_t cols() { return N; }


    constexpr reference operator()(std::size_t i, std::size_t j) {
        return std::get<ColMajorData>(data)[i][j];
    }

    constexpr const_reference operator()(std::size_t i, std::size_t j) const {
        return std::get<ColMajorData>(data)[i][j];
    }

    constexpr reference operator[](std::size_t i) {
        return std::get<ColMajorData>(data)[i];
    }

    constexpr const_reference operator[](std::size_t i) const {
        return std::get<ColMajorData>(data)[i];
    }


    /* Iterators */
    // constexpr iterator begin() noexcept { return std::get<ColMajorData>(data).begin(); }
    // constexpr const_iterator begin() const noexcept { return std::get<ColMajorData>(data).begin(); }

    constexpr iterator end() noexcept { return std::get<ColMajorData>(data).end(); }

    constexpr const_iterator end() const noexcept { return std::get<ColMajorData>(data).end(); }

    constexpr reference at(std::size_t i, std::size_t j) {
        return std::get<ColMajorData>(data).at(i).at(j);
    }

    constexpr const_reference at(std::size_t i, std::size_t j) const {
        return std::get<ColMajorData>(data).at(i).at(j);
    }

    constexpr reference at(std::size_t i) {
        return std::get<ColMajorData>(data).at(i);
    }

    constexpr const_reference at(std::size_t i) const {
        return std::get<ColMajorData>(data).at(i);
    }

    constexpr reference front() {
        return std::get<ColMajorData>(data).front();
    }

    constexpr const_reference front() const {
        return std::get<ColMajorData>(data).front();
    }

    constexpr reference back() {
        return std::get<ColMajorData>(data).back();
    }

    constexpr const_reference back() const {
        return std::get<ColMajorData>(data).back();
    }

public:

    // friend std::begin
    friend constexpr auto begin(Matrix &m) noexcept -> iterator {
        return std::begin(m.data);
    }

    friend constexpr auto begin(const Matrix &m) noexcept -> const_iterator {
        // TODO(Is this correct?)
        return std::begin(Matrix<T, M, N>::Begin::begin(m));
    }

    friend constexpr auto begin(std::size_t i, Matrix &m) noexcept -> iterator {
        return std::begin(m.data[i]);
    }

    // friend std::end
    friend constexpr auto end(Matrix &m) noexcept -> iterator {
        return std::end(m.data);
    }

    friend constexpr auto end(const Matrix &m) noexcept -> const_iterator {
        return std::end(m.data);
    }


};


class MeshCell {

public:
    MeshCell() {
        std::cout << "MeshCell constructor" << std::endl;
    }

    ~MeshCell() {
        std::cout << "MeshCell destructor" << std::endl;
    }
};


class Mesh {
private:
    MeshCell *cells;
    int nCells;
public:
    Mesh(int nCells) : nCells(nCells) {
        std::cout << "Mesh constructor" << std::endl;
        cells = new MeshCell[nCells];
    }

    ~Mesh() {
        std::cout << "Mesh destructor" << std::endl;
        delete[] cells;
    }
};


template<typename T, std::size_t Dim>
class Particle {
private: /* Types */
    using Point3D = Point<T, 0x3UL>;
    using Point2D = Point<T, 0x2UL>;
    using Point1D = Point<T, 0x1UL>;

private: /* Fields */



    /* Position, Velocity */
    std::variant<Point3D, Point2D, Point1D> m_lin_pos;
    std::variant<Point3D, Point2D, Point1D> m_lin_vel;
    std::variant<Point3D, Point2D, Point1D> m_lin_acc;

    /* The rotational displacement, angular velocity, and angular acceleration */
    std::variant<Point3D, Point2D, Point1D> m_rot_pos;
    std::variant<Point3D, Point2D, Point1D> m_rot_vel;
    std::variant<Point3D, Point2D, Point1D> m_rot_acc;

    /* The mass of the particle */
    T m_mass;

    /* The inverse of the mass of the particle */
    T m_inv_mass;

    /* The inertia tensor of the particle */

/* The inverse of the inertia tensor of the particle */


public:

};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
