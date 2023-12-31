#pragma once

#include <cinttypes>
#include <iterator>
#include <stdexcept>

namespace lab {
    template<typename T>
    class XRangeIterator {
    public:
        using value_type        = typename T::value_type;
        using reference         = value_type&;
        using size_type         = typename T::size_type;
        using pointer           = value_type*;
        using difference_type   = typename T::difference_type;
        using iterator_category = std::input_iterator_tag;
    public:
        XRangeIterator(value_type value, value_type end_value, value_type step)
            : value_(value)
            , end_value_(end_value)
            , step_(step)
        {
            if (step_ == 0) {
                throw std::runtime_error("Third argument of xrange cannot be zero.");
            }

            if ((step_ < 0 && value_ < end_value_) || (step_ > 0 && value_ > end_value_)) {
                value_ = end_value_;
            }
        }
    public:
        bool operator==(const XRangeIterator<T>& other) const {
            return value_ == other.value_;
        }

        bool operator!=(const XRangeIterator<T>& other) const {
            return !(*this == other);
        }

        value_type& operator*() {
            return value_;
        }

        XRangeIterator& operator->() {
            return *this;
        }
        
        XRangeIterator& operator++() {
            value_ += step_;

            if (!IsBordersOk()) {
                value_ = end_value_;
            }

            return *this;
        }

        XRangeIterator operator++(int) {
            XRangeIterator res = *this;
            ++(*this);

            return res;
        }
    private:
        value_type value_;
        value_type end_value_;
        value_type step_;
    private:
        inline bool IsBordersOk() const noexcept {
            if (step_ > 0) {
                return value_ < end_value_;
            }

            return value_ > end_value_;
        }
    };

    template<typename T>
    class xrange {
    public:
        using value_type      = T;
        using reference       = T&;
        using const_reference = const T&;
        using iterator        = XRangeIterator<xrange<T>>;
        using const_iterator  = XRangeIterator<const xrange<T>>;
        using difference_type = ptrdiff_t;
        using size_type       = size_t;
    public:
        xrange(T end)
            : start_(0)
            , end_(end)
            , step_(1)
        {}
        
        xrange(T start, T end)
            : start_(start)
            , end_(end)
            , step_(1)
        {}

        xrange(T start, T end, T step)
            : start_(start)
            , end_(end)
            , step_(step)
        {}
    public:
        iterator begin() {
            return iterator(start_, end_, step_);
        }

        iterator end() {
            return iterator(end_, end_, step_);
        }
    private:
        T start_;
        T end_;
        T step_;
    };
};
