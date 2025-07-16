#ifndef INC_4FSC0PF003_SUMMATIVE_ASSET_MANAGER_H
#define INC_4FSC0PF003_SUMMATIVE_ASSET_MANAGER_H

#include <span>
#include <format>
#include <string>
#include <array>

namespace texture_manager {

template<size_t N>
struct StringLiteral {
  constexpr StringLiteral(const char (&arg)[N]) {
    std::copy_n(arg, N, str);
  }
  char str[N];
};

template<typename TAsset, size_t TAssetSize, StringLiteral folderPath>

class TextureManager {
public:

  void LoadAssets(std::span<const std::string_view> assetsPaths) {
    for (size_t i = 0; i < assets_.size(); ++i) {
      assets_[i] = TAsset(std::format("{}/{}", folderPath.str, assetsPaths[i]));
    }
  }

  const TAsset& GetAsset(size_t asset_index) {
    if (asset_index  >= assets_.size()) {
      throw std::out_of_range("Invalid index");
    }
    return assets_[asset_index];
  }
private:
  std::array<TAsset, TAssetSize> assets_{};
};

}

#endif // INC_4FSC0PF003_SUMMATIVE_ASSET_MANAGER_H