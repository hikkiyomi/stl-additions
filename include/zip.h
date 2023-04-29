#pragma once

#include <utility>

namespace lab {
    template<
        class FirstContainer,
        class SecondContainer
    > class ZipIterator {
    public:
        using T = typename FirstContainer::value_type;
        using U = typename SecondContainer::value_type;
        using FirstIter = typename FirstContainer::iterator;
        using SecondIter = typename SecondContainer::iterator;
    public:
        ZipIterator(const FirstIter& it1, const SecondIter& it2)
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
        FirstIter it1_;
        SecondIter it2_;
    };

    template<
        class FirstContainer,
        class SecondContainer
    > class zip {
    public:
        using T = typename FirstContainer::value_type;
        using U = typename SecondContainer::value_type;
        using iterator = ZipIterator<FirstContainer, SecondContainer>;
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
