//
// Created by sebas on 07/07/2025.
//

#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H
#include <random>
#include <SFML/Graphics.hpp>
#include "texture_manager.h"

// Classe Sprite personnalisée

class GameSprite {

  sf::Vector2f position_;
  float alpha_;
  float fade_speed_;
  bool is_active_;
  sf::Color base_color_;
  sf::Color current_color_;
  float scale_;
  int texture_idx_;

  // Générateur de nombres aléatoires
  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_int_distribution<> color_dist_;
  std::uniform_int_distribution<> texture_idx_dist_;
  std::uniform_real_distribution<float> fade_dist_;
  std::uniform_real_distribution<float> scale_dist_;

  //number_of_splash_sprites to be set in the code, difficult to be done in constructor
  static constexpr size_t number_of_splash_sprites=36;
  texture_manager::TextureManager<sf::Texture, number_of_splash_sprites, "_assets/splats"> textures_;

  static constexpr std::string_view splat_files[static_cast<size_t>(number_of_splash_sprites)] = {
      "splat00.png", "splat01.png", "splat02.png", "splat03.png", "splat04.png",
      "splat05.png", "splat06.png", "splat07.png", "splat08.png", "splat09.png",
      "splat10.png", "splat11.png", "splat12.png", "splat13.png", "splat14.png",
      "splat15.png", "splat16.png", "splat17.png", "splat18.png", "splat19.png",
      "splat20.png", "splat21.png", "splat22.png", "splat23.png", "splat24.png",
      "splat25.png", "splat26.png", "splat27.png", "splat28.png", "splat29.png",
      "splat30.png", "splat31.png", "splat32.png", "splat33.png", "splat34.png",
      "splat35.png"
  };
//std::string_view splat_files[static_cast<size_t>(number_of_splash_sprites)];


public:
  explicit GameSprite(sf::Vector2f pos);

  void Update(float deltaTime);
  void Draw(sf::RenderWindow& window);

  [[nodiscard]] bool is_active() const ;
  [[nodiscard]] sf::Vector2f position() const;
  [[nodiscard]] float alpha() const;
  //std::string static constexpr get_splat_png(int splash_idx);

};

#endif //GAME_SPRITE_H