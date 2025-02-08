#ifndef GET_OR_MAKE_H
#define GET_OR_MAKE_H

#include <memory>
#include <string>
#include <map>
#include <unordered_map>

template <typename V, typename K, typename Key, typename Func>
std::shared_ptr<V> get_or_make(std::map<K, std::weak_ptr<V>>& map, const Key &key, Func make) {
    std::weak_ptr<V> &wp = map[key];
    std::shared_ptr<V> sp = wp.lock();
    if (sp) {
        return sp;
    }
    wp = sp = make();
    return sp;
}
template <typename V, typename K, typename Key, typename Func>
std::shared_ptr<V> get_or_make(std::map<K, std::shared_ptr<V>>& map, const Key &key, Func make) {
    std::shared_ptr<V> &sp = map[key];
    if (!sp) 
    {
        sp = make();
    }
    return sp;
}
template <typename V, typename K, typename Key, typename Func>
std::shared_ptr<V> get_or_make(std::unordered_map<K, std::weak_ptr<V>>& map, const Key &key, Func make) {
    std::weak_ptr<V> &wp = map[key];
    std::shared_ptr<V> sp = wp.lock();
    if (sp) {
        return sp;
    }
    wp = sp = make();
    return sp;
}
template <typename V, typename K, typename Key, typename Func>
std::shared_ptr<V> get_or_make(std::unordered_map<K, std::shared_ptr<V>>& map, const Key &key, Func make) {
    std::shared_ptr<V> &sp = map[key];
    if (!sp) 
    {
        sp = make();
    }
    return sp;
}
template <typename V, typename K, typename Key, typename Func>
V& get_or_make(std::unordered_map<K, V>& map, const Key& key, Func make) {
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    auto [new_it, inserted] = map.emplace(key, make());
    return new_it->second;
}


#endif