#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include <memory>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <list>

template <typename T>
class SetAbstract {
  public:
    virtual ~SetAbstract() = default;
    virtual size_t size() const = 0;
    virtual void add_elem(const T& elem) = 0;
    virtual void remove_elem(const T& elem) = 0;
    virtual bool is_contain(const T& elem) const = 0;
    virtual std::unique_ptr<SetAbstract> clone() const = 0;
    virtual std::unique_ptr<SetAbstract> get_union(const SetAbstract& other) const = 0;
    virtual std::unique_ptr<SetAbstract> get_intersection(const SetAbstract& other) const = 0;
    virtual std::vector<T> get_elements() const = 0;
};

template <typename T>
class SetList : public SetAbstract<T> {
    std::list<T> elements;

  public:
    SetList() = default;
    SetList(const std::initializer_list<T>& elems) {
        for (const auto& e : elems) {
            add_elem(e);
        }
    }

    size_t size() const override { return elements.size(); }

    void add_elem(const T& elem) override {
        if (!is_contain(elem)) {
            elements.push_back(elem);
        }
    }

    void remove_elem(const T& elem) override { elements.remove(elem); }

    bool is_contain(const T& elem) const override {
        return std::find(elements.begin(), elements.end(), elem) != elements.end();
    }

    std::unique_ptr<SetAbstract<T>> clone() const override {
        return std::make_unique<SetList>(*this);
    }

    std::unique_ptr<SetAbstract<T>> get_union(const SetAbstract<T>& other) const override {
        auto result = clone();
        for (const auto& e : other.get_elements()) {
            if (!is_contain(e)) result->add_elem(e);
        }
        return result;
    }

    std::unique_ptr<SetAbstract<T>> get_intersection(const SetAbstract<T>& other) const override {
        auto result = std::make_unique<SetList>();
        for (const auto& e : elements) {
            if (other.is_contain(e)) result->add_elem(e);
        }
        return result;
    }

    std::vector<T> get_elements() const override {
        return {elements.begin(), elements.end()};
    }
};

template <typename T>
class SetHash : public SetAbstract<T> {
    std::unordered_set<T> elements;

  public:
    SetHash() = default;
    SetHash(const std::initializer_list<T>& elems) : elements(elems) {}

    size_t size() const override { return elements.size(); }

    void add_elem(const T& elem) override {
        elements.insert(elem);
    }

    void remove_elem(const T& elem) override { elements.erase(elem); }

    bool is_contain(const T& elem) const override {
        return elements.count(elem) > 0;
    }

    std::unique_ptr<SetAbstract<T>> clone() const override {
        return std::make_unique<SetHash>(*this);
    }

    std::unique_ptr<SetAbstract<T>> get_union(const SetAbstract<T>& other) const override {
        auto result = clone();
        for (const auto& e : other.get_elements()) {
            result->add_elem(e);
        }
        return result;
    }

    std::unique_ptr<SetAbstract<T>> get_intersection(const SetAbstract<T>& other) const override {
        auto result = std::make_unique<SetHash>();
        for (const auto& e : elements) {
            if (other.is_contain(e)) result->add_elem(e);
        }
        return result;
    }

    std::vector<T> get_elements() const override {
        return {elements.begin(), elements.end()};
    }
};

template <typename T>
class Set {
    static constexpr size_t maxlen = 10;
    std::unique_ptr<SetAbstract<T>> impl;

    void check_and_switch_impl() {
        const size_t sz = impl->size();
        const bool is_list = dynamic_cast<SetList<T>*>(impl.get());
        if (is_list && sz > maxlen) {
            auto new_impl = std::make_unique<SetHash<T>>();
            for (const auto& e : impl->get_elements()) {
                new_impl->add_elem(e);
            }
            impl = std::move(new_impl);
        } else if (!is_list && sz <= maxlen) {
            auto new_impl = std::make_unique<SetList<T>>();
            for (const auto& e : impl->get_elements()) {
                new_impl->add_elem(e);
            }
            impl = std::move(new_impl);
        }
    }

  public:
    Set() : impl(std::make_unique<SetList<T>>()) {}
    Set(std::initializer_list<T> elems) {
        if (elems.size() > maxlen) {
            impl = std::make_unique<SetHash<T>>(elems);
        } else {
            impl = std::make_unique<SetList<T>>(elems);
        }
    }

    void add_elem(const T& elem) {
        impl->add_elem(elem);
        check_and_switch_impl();
    }

    void remove_elem(const T& elem) {
        impl->remove_elem(elem);
        check_and_switch_impl();
    }

    bool is_contain(const T& elem) const { return impl->is_contain(elem); }

    Set get_union(const Set& other) const {
        return Set(impl->get_union(*other.impl));
    }

    Set get_intersection(const Set& other) const {
        return Set(impl->get_intersection(*other.impl));
    }

    size_t size() const { return impl->size(); }
    std::vector<T> get_elements() const { return impl->get_elements(); }
    friend std::ostream& operator<<(std::ostream& os, const Set<T>& set) {
        const auto elements = set.get_elements();
        os << "{";
        for (size_t i = 0; i < elements.size(); ++i) {
            os << elements[i];
            if (i != elements.size() - 1) {
                os << ", ";
            }
        }
        os << "};";
        return os;
    }

  private:
    Set(std::unique_ptr<SetAbstract<T>> impl) : impl(std::move(impl)) {}
};

#endif