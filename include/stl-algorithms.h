#pragma once

#include <iterator>
#include <type_traits>

namespace lab {
    template<typename T>
    using RequireIter = typename 
        std::enable_if<
            !std::is_same<
                typename std::iterator_traits<T>::value_type,
                void
            >::value
        >::type;

    template<typename Iter>
    using RequireInputIter = typename
        std::enable_if<
            std::is_convertible<
                typename std::iterator_traits<Iter>::iterator_category,
                std::input_iterator_tag
            >::value
        >::type;

    template<typename Iter>
    using RequireFwdIter = typename
        std::enable_if<
            std::is_convertible<
                typename std::iterator_traits<Iter>::iterator_category,
                std::forward_iterator_tag
            >::value
        >::type;

    template<typename Iter>
    using RequireBidirIter = typename
        std::enable_if<
            std::is_convertible<
                typename std::iterator_traits<Iter>::iterator_category,
                std::bidirectional_iterator_tag
            >::value
        >::type;

    template<typename Compare>
    struct IteratorComparator {
        Compare comp_;

        explicit constexpr
        IteratorComparator(Compare comp)
            : comp_(std::move(comp))
        {}

        template<typename Iter1, typename Iter2>
        bool operator()(Iter1 it1, Iter2 it2) {
            return bool(comp_(*it1, *it2));
        }
    };

    namespace base {
        struct BaseComparator {
            template<typename Iter1, typename Iter2>
            bool operator()(Iter1 it1, Iter2 it2) {
                return *it1 < *it2;
            }
        };

        template<typename T>
        struct BaseFindPredicate {
            T x;
            
            explicit constexpr
            BaseFindPredicate(T _x)
                : x(std::move(_x))
            {}

            template<typename U>
            bool operator()(U a) {
                return a == x;
            }
        };

        struct BasePalindromePredicate {
            template<
                typename T,
                typename U
            > bool operator()(T x, U y) {
                return x == y;
            }
        };

#if __cplusplus == 201103L
        template<
            class ForwardIt,
            class Compare,
            typename = RequireFwdIter<ForwardIt>
        > bool is_sorted_base(ForwardIt first, ForwardIt last, Compare comp) {
            if (first == last) {
                return true;
            }

            ForwardIt next = first;
            
            for (++next; next != last; first = next, ++next) {
                if (!comp(first, next)) {
                    return false;
                }
            }

            return true;
        }
#else
        template<
            class ForwardIt,
            class Compare,
            typename = RequireFwdIter<ForwardIt>
        > constexpr bool is_sorted_base(ForwardIt first, ForwardIt last, Compare comp) {
            if (first == last) {
                return true;
            }

            ForwardIt next = first;
            
            for (++next; next != last; first = next, ++next) {
                if (!comp(first, next)) {
                    return false;
                }
            }

            return true;
        }
#endif
    };

#if __cplusplus >= 202002L

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > constexpr bool all_of(InputIt first, InputIt last, Predicate p) {
        return last == find_if_not(first, last, p);
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > constexpr bool any_of(InputIt first, InputIt last, Predicate p) {
        return !none_of(first, last, p);
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > constexpr bool none_of(InputIt first, InputIt last, Predicate p) {
        return last == find_if(first, last, p);
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > constexpr bool one_of(InputIt first, InputIt last, Predicate p) {
        bool exist = false;

        for (; first != last; ++first) {
            if (p(*first)) {
                if (exist) {
                    return false;
                }

                exist = true;
            }
        }

        return exist;
    }

    template<
        class ForwardIt,
        typename = RequireFwdIter<ForwardIt>
    > constexpr bool is_sorted(ForwardIt first, ForwardIt last) {
        return base::is_sorted_base(first, last, base::BaseComparator());
    }

    template<
        class ForwardIt,
        class Compare,
        typename = RequireFwdIter<ForwardIt>
    > constexpr bool is_sorted(ForwardIt first, ForwardIt last, Compare compare) {
        return base::is_sorted_base(first, last, IteratorComparator(compare));
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > constexpr bool is_partitioned(InputIt first, InputIt last, Predicate p) {
        for (; first != last; ++first) {
            if (!p(*first)) {
                break;
            }
        }

        for (; first != last; ++first) {
            if (p(*first)) {
                return false;
            }
        }

        return true;
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > constexpr InputIt find_if(InputIt first, InputIt last, Predicate p) {
        for (; first != last; ++first) {
            if (p(*first)) {
                return first;
            }
        }

        return last;
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > constexpr InputIt find_if_not(InputIt first, InputIt last, Predicate p) {
        for (; first != last; ++first) {
            if (!p(*first)) {
                return first;
            }
        }

        return last;
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > constexpr InputIt find_last(InputIt first, InputIt last, Predicate p) {
        InputIt res = last;

        for (; first != last; ++first) {
            if (p(*first)) {
                res = first;
            }
        }

        return res;
    }

    template<
        class InputIt,
        typename T,
        typename = RequireInputIter<InputIt>
    > constexpr InputIt find_not(InputIt first, InputIt last, T x) {
        return lab::find_if_not(first, last, base::BaseFindPredicate<T>(x));
    }

    template<
        class InputIt,
        typename T,
        typename = RequireInputIter<InputIt>
    > constexpr InputIt find_backward(InputIt first, InputIt last, T x) {
        return find_last(first, last, base::BaseFindPredicate<T>(x));
    }

    template<
        class BidirIt,
        class Predicate,
        typename = RequireBidirIter<BidirIt>
    > constexpr bool is_palindrome(BidirIt first, BidirIt last, Predicate p) {
        if (first == last) {
            return true;
        }

        BidirIt prev = last;

        for (--prev; first != prev; ++first, --prev) {
            if (!p(*first, *prev)) {
                return false;
            }
        }

        return true;
    }

    template<
        class BidirIt,
        typename = RequireBidirIter<BidirIt>
    > constexpr bool is_palindrome(BidirIt first, BidirIt last) {
        return is_palindrome(first, last, base::BasePalindromePredicate());
    }

#elif __cplusplus >= 201103L

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > bool all_of(InputIt first, InputIt last, Predicate p) {
        return last == find_if_not(first, last, p);
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > bool any_of(InputIt first, InputIt last, Predicate p) {
        return !none_of(first, last, p);
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > bool none_of(InputIt first, InputIt last, Predicate p) {
        return last == find_if(first, last, p);
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > bool one_of(InputIt first, InputIt last, Predicate p) {
        bool exist = false;

        for (; first != last; ++first) {
            if (p(*first)) {
                if (exist) {
                    return false;
                }

                exist = true;
            }
        }

        return exist;
    }

    template<
        class ForwardIt,
        typename = RequireFwdIter<ForwardIt>
    > bool is_sorted(ForwardIt first, ForwardIt last) {
        return base::is_sorted_base(first, last, base::BaseComparator());
    }

    template<
        class ForwardIt,
        class Compare,
        typename = RequireFwdIter<ForwardIt>
    > bool is_sorted(ForwardIt first, ForwardIt last, Compare compare) {
        return base::is_sorted_base(first, last, IteratorComparator<Compare>(compare));
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > bool is_partitioned(InputIt first, InputIt last, Predicate p) {
        for (; first != last; ++first) {
            if (!p(*first)) {
                break;
            }
        }

        for (; first != last; ++first) {
            if (p(*first)) {
                return false;
            }
        }

        return true;
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > InputIt find_if(InputIt first, InputIt last, Predicate p) {
        for (; first != last; ++first) {
            if (p(*first)) {
                return first;
            }
        }

        return last;
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > InputIt find_if_not(InputIt first, InputIt last, Predicate p) {
        for (; first != last; ++first) {
            if (!p(*first)) {
                return first;
            }
        }

        return last;
    }

    template<
        class InputIt,
        class Predicate,
        typename = RequireInputIter<InputIt>
    > InputIt find_last(InputIt first, InputIt last, Predicate p) {
        InputIt res = last;

        for (; first != last; ++first) {
            if (p(*first)) {
                res = first;
            }
        }

        return res;
    }

    template<
        class InputIt,
        typename T,
        typename = RequireInputIter<InputIt>
    > InputIt find_not(InputIt first, InputIt last, T x) {
        return lab::find_if_not(first, last, base::BaseFindPredicate<T>(x));
    }

    template<
        class InputIt,
        typename T,
        typename = RequireInputIter<InputIt>
    > InputIt find_backward(InputIt first, InputIt last, T x) {
        return find_last(first, last, base::BaseFindPredicate<T>(x));
    }

    template<
        class BidirIt,
        class Predicate,
        typename = RequireBidirIter<BidirIt>
    > bool is_palindrome(BidirIt first, BidirIt last, Predicate p) {
        if (first == last) {
            return true;
        }

        BidirIt prev = last;

        for (--prev; first != prev; ++first, --prev) {
            if (!p(*first, *prev)) {
                return false;
            }
        }

        return true;
    }

    template<
        class BidirIt,
        typename = RequireBidirIter<BidirIt>
    > bool is_palindrome(BidirIt first, BidirIt last) {
        return is_palindrome(first, last, base::BasePalindromePredicate());
    }

#endif
};
