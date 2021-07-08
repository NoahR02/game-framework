#include "Player.h"
#include "../ECS/Camera.h"

Player::Player(Scene* scene) : Entity(scene) {
  addComponent<Sprite>();
  addComponent<PlayerEntityID>();
  addComponent<Camera>(0, 0);

  auto& body = addBody();
  body.setType(Body::BodyType::DYNAMIC_BODY);
}

void Player::construct() {

}


void playerMoveLeft(Player& entity) {
  //cameraMoveLeft(entity);
  auto& sprite = entity.getComponent<Sprite>();
  auto& body = entity.getComponent<Body>();

  body.setLinearVelocity({body.getLinearVelocity().x - entity.speed, body.getLinearVelocity().y});
}

void playerMoveRight(Player& entity) {
  //cameraMoveRight(entity);
  auto& sprite = entity.getComponent<Sprite>();
  auto& body = entity.getComponent<Body>();

  body.setLinearVelocity({body.getLinearVelocity().x + entity.speed, body.getLinearVelocity().y});
}

void playerMoveUp(Player& entity) {
  //cameraMoveUp(entity);
  auto& sprite = entity.getComponent<Sprite>();
  auto& body = entity.getComponent<Body>();

  body.setLinearVelocity({body.getLinearVelocity().x, body.getLinearVelocity().y - entity.speed});
}

void playerMoveDown(Player& entity) {
  //cameraMoveDown(entity);
  auto& sprite = entity.getComponent<Sprite>();
  auto& body = entity.getComponent<Body>();

  body.setLinearVelocity({body.getLinearVelocity().x, body.getLinearVelocity().y + entity.speed});
}
