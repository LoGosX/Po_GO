#pragma once
#include <unordered_map>
#include <memory>
#include <string>

template<typename T>
class AssetManager
{
    std::unordered_map<std::string, std::unique_ptr<T>> _assets;

public:

    /**
     * @brief Get the Asset object associated with the key
     * 
     * @param key Key associated with the asset
     * @return T* Pointer to asset if found, nullptr otherwise
     */
    T* getAsset(const std::string& key);

    /**
     * @brief Gives this AssetManager ownership of asset
     * 
     * @param key Key associated with asset
     * @param asset Pointer to asset that needs to be stored inside AssetManager
     */
    void addAsset(const std::string& key, T* asset);

    /**
     * @brief The same as addAsset(const std::string&, T*) but accepts rvalue reference instead
     */
    void addAsset(const std::string& key, T&& asset);
};

template<typename T>
T* AssetManager<T>::getAsset(const std::string& key) {
    auto res = _assets.find(key);
    if(!res.first)
        return nullptr;
    return res.second->get();
}

template<typename T>
void AssetManager<T>::addAsset(const std::string& key, T&& asset) {
    _assets.emplace(key, std::unique_ptr(std::forward<T>(asset)));
}

template<typename T>
void AssetManager<T>::addAsset(const std::string& key, T* asset) {
    _assets.emplace(key, std::unique_ptr(asset));
}