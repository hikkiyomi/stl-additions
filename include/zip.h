#pragma once

#include <cinttypes>
#include <iterator>
#include <utility>

namespace lab {
    template<
        class FirstContainer,
        class SecondContainer
    > class ZipIterator {
    public:
        using T                 = typename FirstContainer::value_type;
        using U                 = typename SecondContainer::value_type;
        using first_iter        = typename FirstContainer::iterator;
        using second_iter       = typename SecondContainer::iterator;
        using value_type        = std::pair<T, U>;
        using reference         = value_type&;
        using size_type         = size_t;
        using pointer           = value_type*;
        using difference_type   = ptrdiff_t;
        using iterator_category = std::input_iterator_tag;
    public:
        ZipIterator(const first_iter& it1, const second_iter& it2)
            : it1_(it1)
            , it2_(it2)
        {}
    public:
        bool operator==(const ZipIterator& other) const {
            return it1_ == other.it1_ || it2_ == other.it2_;
        }
        
        bool operator!=(const ZipIterator& other) const {
            return !(*this == other);
        }

        std::pair<T, U> operator*() {
            return {*it1_, *it2_};
        }

        ZipIterator& operator->() {
            return *this;
        }

        ZipIterator& operator++() {
            ++it1_;
            ++it2_;
            
            return *this;
        }

        ZipIterator operator++(int) {
            ZipIterator res = *this;
            ++(*this);

            return res;
        }
    private:
        first_iter it1_;
        second_iter it2_;
    };

    template<
        class FirstContainer,
        class SecondContainer
    > class zip {
    public:
        using T                 = typename FirstContainer::value_type;
        using U                 = typename SecondContainer::value_type;
        using iterator          = ZipIterator<FirstContainer, SecondContainer>;
        using value_type        = std::pair<T, U>;
        using reference         = value_type&;
        using size_type         = size_t;
        using pointer           = value_type*;
        using difference_type   = ptrdiff_t;
    public:
        zip(FirstContainer& cont1, SecondContainer& cont2)
            : cont1_(cont1)
            , cont2_(cont2)
        {}
    public:
        iterator begin() {
            return iterator(cont1_.begin(), cont2_.begin());
        }

        iterator end() {
            return iterator(cont1_.end(), cont2_.end());
        }
    private:
        FirstContainer& cont1_;
        SecondContainer& cont2_;
    };
};
