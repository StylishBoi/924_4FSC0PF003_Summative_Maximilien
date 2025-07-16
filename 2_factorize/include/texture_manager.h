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

template<typename TAsset, typename TAssetType, StringLiteral folderPath>
  requires std::is_enum_v<TAssetType> && requires
{
  {static_cast<size_t>(TAssetType::kLength)};
}
class TextureManager {
public:

  void LoadAssets(std::span<const std::string_view> assetsPaths) {
    for (size_t i = 0; i < assets_.size(); ++i) {
      assets_[i] = TAsset(std::format("{}/{}", folderPath.str, assetsPaths[i]));
    }
  }

  const TAsset &GetAsset(TAssetType asset_index) {
    const auto index = static_cast<int64_t>(asset_index);
    if (index < 0 || index >= std::ssize(assets_)) {
      throw std::out_of_range("Invalid index");
    }
    return assets_[index];
  }
private:
  std::array<TAsset, static_cast<size_t>(TAssetType::kLength)> assets_{};
};

}

#endif // INC_4FSC0PF003_SUMMATIVE_ASSET_MANAGER_H
