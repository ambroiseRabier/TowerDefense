#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP
#include "GameEngine/GameObject.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		//todo: test, will active a centralised memory for gameobjects and enable weak_ptr
		class Scene
		{
		public:
			static std::list<std::shared_ptr<GameObject>> game_object_list;
			static void init();
			template<typename T, typename... ParamTypes>
			static std::shared_ptr<T> instanciate(ParamTypes... params);

			static void destroy(GameObject& game_object);
		};

		template <typename T, typename ... ParamTypes>
		std::shared_ptr<T> Scene::instanciate(ParamTypes... params)
		{
			// force GameObject type: https://stackoverflow.com/questions/874298/c-templates-that-accept-only-certain-types#874337
			// but need BOOST :/
			std::shared_ptr<T> my_ptr = std::make_shared<T>(params...);
			std::shared_ptr<GameObject> my_ptr_game_object = std::move(static_cast<std::shared_ptr<GameObject>>(my_ptr));
			assert(my_ptr_game_object);
			game_object_list.push_front(std::move(my_ptr_game_object));
			return game_object_list.front();
			// tester retourne bien un share_ptr avec bon type,
			// créer bien obj
			// tester delete (faire un reset ici et sur devrait suffire, ou max 2 reset devrait créer erreur si pas enlever de d'affichage.
			// tester front()
		}


	}
}
#endif
