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
  //Makes string array of files empty at start, will be filled in constructor
  std::string test_splat_files[static_cast<size_t>(number_of_splash_sprites)];


public:
  explicit GameSprite(sf::Vector2f pos);

  void Update(float deltaTime);
  void Draw(sf::RenderWindow& window);

  [[nodiscard]] bool is_active() const ;
  [[nodiscard]] sf::Vector2f position() const;
  [[nodiscard]] float alpha() const;
  [[nodiscard]] std::string get_splat_png(int splash_idx) const;

};

#endif //GAME_SPRITE_H