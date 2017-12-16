#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include <new> 
#include <string> 
#include <stdlib.h>
#include "SFML/Audio.hpp"


#include "Globals/Globals.h"
#include "Factory/Factory.h"
#include "UserComponents/UserComponents.h"
#include "Entity/Entity.h"
#include "Manager/Manager.h"


// create fl namespace


// Takeaways 
// - InterEntity: pull out controls to central class/manager. Create connection manager, use it to register wtih contact manager; Still have connection components
// Connection manager takes registration; has methods like InCtonactWith, and GetPairedEntity. Connection manager registers with contact manager
// - IntraEntity: Messaging, create base messaging class, create specific message classes (in a library). Use strings as names for referencing message type.
// - Entity Creation: Create heirarchy of user components, such that controls conpoments can know about other types. // Scratch that
// Make spawn component that can spawn other entities. Create interface for attaching spawn entiteis, if needed, but make entity library all the same and
// make it easy for everyone else to create entities.




//multiple windows; consider

// make some way to check entity has been reigstered before refereing
//figure out difference between at and [] for vectors

//consider changing itemType to partType


// Get better way to attach user data to bodies;



// GOALS
//
// Pop balloons
// Destory vehicle and character (health)
// Fuel for vehicle (inventory)
// Inventory for character
// Character hold on to balloon and float
// Make homing missle with splash damage


//TODO Character body still in game after entering vehicle

// Create debugging setup, so that asserts tell useful info
// let character jump // on all object, not just ground
// sensor collisions
// get center of mass working again // seems to be working... for the time being // generalize use
// use bullets
// decide character's velocity when exiting vehicle
// full screen gun doesn't work // decide how to scale game, or if you can
// create AI component
// Gun collides with walls first, causing it to move the joint // Consider masking it out, make uncollidable

typedef std::vector<Part*> Parts;




void MakeRocket(Entity &entity, Item **item);
void MakeGun(Entity &entity, Item **item);
void MakePlatform(Entity &entity, Item **item);
void MakeBorder(Entity &entity, Item **item);
void MakeCar(Entity &entity, Item **item);
void MakeCharacter(Entity &entity, Item **item);
void MakeBalloon(Entity &entity, Item **item);
void MakeBackground(Entity &entity, Item **item);
void MakeWheel1(Entity &entity, Item **item);
void MakeWheel2(Entity &entity, Item **item);
void MakeTree(Entity &entity, Item **item);
void MakeString(Entity &entity, Item **item);
void MakeRope(Entity &entity, Item **item);



int main()
{
	//------------------------
	// Init
	//------------------------

	Globals::entFactoryInterface = new EntityFactory;
	sf::Clock deltaClock;
	sf::Music music;
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	if (!music.openFromFile(MUSIC(BestGameEverMaster.wav))) {
		return -1;
	}
	music.setLoop(true);
	//music.play();


	//------------------------
	// Create Entites/Items
	//------------------------

	Entity background_ent("Background"); Item* background = 0;
	MakeBackground(background_ent,& background);

	Entity platform_ent("Platform_Ent"); Item *platform = 0;
	MakePlatform(platform_ent, &platform);
	Entity tree_ent[10]; Item *tree[10];
	for (int i = 0; i < 10; i++) {
		MakeTree(tree_ent[i], &tree[i]);
	}

	Entity character_ent("Character_Ent"); Item * character = 0;
	MakeCharacter(character_ent, &character);

	Entity border_ent("Border_Ent"); Item *border = 0;
	MakeBorder(border_ent, &border);

	Entity balloon_ent("Balloon_Ent"); Item* balloon;
	MakeBalloon(balloon_ent, &balloon);
	
	Entity rocket_ent("Rocket_Ent"); Item *rocket = 0;
	MakeRocket(rocket_ent, &rocket);

	Entity gun_ent("Gunt_Ent"); Item *gun=0;
	MakeGun(gun_ent, &gun);	

	Entity car_ent("Car_ent"); Item *car = 0;
	MakeCar(car_ent, &car);

	Entity wheel1_ent; Item *wheel1 = 0;
	MakeWheel1(wheel1_ent, &wheel1);

	Entity wheel2_ent; Item *wheel2 = 0;
	MakeWheel2(wheel2_ent, &wheel2);
	
	Entity stringSegs[5]; Item *balloonStrings[5]; std::vector<Item*> balloonString;
	for (int i = 0; i < 5; i++) {
		MakeString(stringSegs[i], &balloonStrings[i]);
		balloonString.push_back(balloonStrings[i]);
	}

	Entity ropeSegs[5]; Item *ropeArray[5]; std::vector<Item*> rope;
	for (int i = 0; i < 5; i++) {
		MakeRope(ropeSegs[i], &ropeArray[i]);
		rope.push_back(ropeArray[i]);
	}

	std::vector<uint32_t> tempVec;
	tempVec.resize(CharacterConnectionComponent::NUM_CONNECTION);
	tempVec[CharacterConnectionComponent::BALLOON_CONNECTION] = balloon_ent.GetID();
	tempVec[CharacterConnectionComponent::ROCKET_CONNECTION] = rocket_ent.GetID();
	tempVec[CharacterConnectionComponent::GUN_CONNECTION] = gun_ent.GetID();
	tempVec[CharacterConnectionComponent::CAR_CONNECTION] = car_ent.GetID();
	tempVec[CharacterConnectionComponent::SEGMENT_CONNECTION] = stringSegs[4].GetID();
	character_ent.AddComponent({ new CharacterConnectionComponent(tempVec) });

	//------------------------
	// Create Joints
	//------------------------


	RevoluteJointConfig stringConfig;
	stringConfig.collide = false;
	for (int i = 0; i < 4; i++) {
		stringConfig.coordsA.push_back(b2Vec2(0, .25));
		stringConfig.coordsB.push_back(b2Vec2(0, -.25));
	}
	stringConfig.coordsA.insert(stringConfig.coordsA.begin(), b2Vec2(0, .25));
	stringConfig.coordsB.insert(stringConfig.coordsB.begin(), b2Vec2(0, -.25));
	balloonString.insert(balloonString.begin(), balloon);
	Factory::CreateJoints(balloonString, stringConfig);
	

	RevoluteJointConfig config;
	config.collide = false;
	for (int i = 0; i < 4; i++) {
		config.coordsA.push_back(b2Vec2(0, .75));
		config.coordsB.push_back(b2Vec2(0, -.75));
	}
	config.coordsA.insert(config.coordsA.begin(), b2Vec2(0, .25));
	config.coordsB.insert(config.coordsB.begin(), b2Vec2(0, -.75));
	rope.insert(rope.begin(), platform);
	Factory::CreateJoints(rope, config);
	
	
	RevoluteJointConfig rocketConfig;
	rocketConfig.collide = false;
	rocketConfig.coordsA.push_back(b2Vec2(0,-1));
	rocketConfig.coordsB.push_back(b2Vec2(0,.25));
	Factory::CreateJoints({ rocket, gun}, rocketConfig);


	WheelJointConfig wheelConfig;
	wheelConfig.collide = false;
	wheelConfig.axis = b2Vec2(0, 1);
	wheelConfig.coordsA = b2Vec2(-1.5, 1.5);
	wheelConfig.coordsB = b2Vec2(0, 0);
	Factory::CreateJoints(car, wheel1, wheelConfig);
	wheelConfig.coordsA = b2Vec2(1.5, 1.5);
	Factory::CreateJoints(car, wheel2, wheelConfig);




	//------------------------
	// Create Connections
	//------------------------
	
	/*
	Entity connection_ent;
	connection_ent.Init(
	{
		new ConnectionControlsComponent(),
		new VehicleConnectionComponent(rocket_ent->GetID(), character_ent->GetID(), gun_ent->GetID()) }
	);
	
	EntityManager::RegisterEntity(&connection_ent);
	
	Entity temp_ent;
	temp_ent.Init(
	{
		new TempControlsComponent(),
		new GroundConnectionComponent(character_ent->GetID(), {platform_ent->GetID(), border_ent->GetID()}) }
	);
	EntityManager::RegisterEntity(&temp_ent);
	
	

	
	Entity balloonConnect_ent;
	balloonConnect_ent.Init(
	{
		new ConnectionControlsComponent(), 
		new BalloonConnectionComponent(balloon_ent->GetID(), character_ent->GetID(), stringSegs[4]->GetID()) }
	);
	EntityManager::RegisterEntity(&balloonConnect_ent);
	
	

	Entity carConnect_ent;
	carConnect_ent.Init(
	{
		new ConnectionControlsComponent(), 
		new VehicleConnectionComponent(car_ent->GetID(), character_ent->GetID(), gun_ent->GetID())}
	);

	EntityManager::RegisterEntity(&carConnect_ent);
	
	*/
	
	//------------------------
	// Main Loop
	//------------------------

	//ContactManager contactManager;
	//contactManager.RegisterContact(&character_ent);
	//contactManager.RegisterContact(&connection_ent);
	//contactManager.RegisterContact(&temp_ent);
	//contactManager.RegisterContact(&carConnect_ent);
	//contactManager.RegisterContact(&balloonConnect_ent);
	//contactManager.RegisterFilter({ character_ent.GetID(), rocket_ent.GetID(), gun_ent.GetID(), balloon_ent.GetID(), car_ent.GetID() });
	//Globals::world.SetContactListener(&contactManager);

	Globals::window.setFramerateLimit(60);

	while (Globals::window.isOpen())
	{
		Globals::window.clear();
		Globals::IncrTimer();
		EventManager::GetEvents(Globals::window);
		EntityManager::Update(Globals::window);
		Globals::world.Step(timeStep, velocityIterations, positionIterations);
		EventManager::ClearEvents();
		Globals::window.display();

	}

	return 0;
}









void MakeRope(Entity &entity, Item  **item) {

	Parts * segmentParts = new Parts({
		Factory::CreatePart<Box>(b2Vec2(0,0),b2Vec2(.5,1.5)),
	});
	*item = Factory::CreateItem(*segmentParts, DYNAMIC_BODY);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(300), SF_2_BOX(300)), 0);
	entity.AddComponent(
	{
		new BasicGraphicsComponent(&Globals::window, *item),
		new BasicPhysicsComponent(*item) }
	);
	EntityManager::RegisterEntity(&entity);
	
}




void MakeString(Entity &entity, Item **item) {

	Parts segmentParts{
		Factory::CreatePart<Box>(b2Vec2(0,0), b2Vec2(.1,.5))
	};
	*item = Factory::CreateItem(segmentParts, DYNAMIC_BODY);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(600), SF_2_BOX(500)), 0);



	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(200), SF_2_BOX(200)), 0);
	(*item)->body->GetFixtureList()->SetSensor(true);
	entity.AddComponent(
	{
		new BasicGraphicsComponent(&Globals::window, *item),
		new BasicPhysicsComponent(*item) }
	);
	EntityManager::RegisterEntity(&entity);
}



void MakeTree(Entity &entity, Item **item) {

	Parts treeParts{
		Factory::CreatePart<Tree>(b2Vec2(SF_2_BOX(( 100) + 50),SF_2_BOX(550)), b2Vec2(1,2))
	};
	(*item) = Factory::CreateItem(treeParts);
	entity.AddComponent(
	{
		new BasicGraphicsComponent(&Globals::window, *item)
	}
	);
	EntityManager::RegisterEntity(&entity);
	
}






void MakeWheel1(Entity &entity, Item **item) {



	Parts wheel1Parts{
		Factory::CreatePart<Tire>(b2Vec2(0,0), b2Vec2(1,1))
	};
	(*item) = Factory::CreateItem(wheel1Parts, DYNAMIC_BODY);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(600), SF_2_BOX(500)), 0);

	entity.AddComponent(
	{
		new BasicPhysicsComponent(*item),
		new BasicGraphicsComponent(&Globals::window, *item),
	}
	);
	(*item)->body->SetUserData(&entity);
	EntityManager::RegisterEntity(&entity);

}


void MakeWheel2(Entity &entity, Item **item) {


	Parts wheel2Parts{
		Factory::CreatePart<Tire>(b2Vec2(0,0), b2Vec2(1,1))
	};
	(*item) = Factory::CreateItem(wheel2Parts, DYNAMIC_BODY);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(600), SF_2_BOX(500)), 0);

	entity.AddComponent(
	{
		new BasicPhysicsComponent(*item),
		new BasicGraphicsComponent(&Globals::window, *item),
	}
	);
	(*item)->body->SetUserData(&entity);
	EntityManager::RegisterEntity(&entity);
}


 void MakeCharacter(Entity &entity, Item **item) {
	std::vector<Part*> characterParts{
		Factory::CreatePart<Character>(b2Vec2(0,0), b2Vec2(1,1))
	};
	(*item) = Factory::CreateItem(characterParts, DYNAMIC_BODY);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(400), SF_2_BOX(400)), 0);
	(*item)->body->SetFixedRotation(true);

	entity.AddComponent(
	{
		new BasicGraphicsComponent(&Globals::window, *item),
		new CharacterPhysicsComponent(*item),
		new CharacterControlsComponent() }
	);
	(*item)->body->SetUserData(&entity);
	EntityManager::RegisterEntity(&entity);
}

 void MakeRocket(Entity &entity, Item **item) {

	std::vector<Part*> rocketParts{
		Factory::CreatePart<Rocket>(b2Vec2(0,0), b2Vec2(1,2.5)),
		//Factory::CreatePart<Box>(b2Vec2(0,1), b2Vec2(2,2), DEGREES_2_RAD(45)),
		//Factory::CreatePart<Tire>(b2Vec2(0,-1), b2Vec2(1.5,1.5))
	};
	(*item) = Factory::CreateItem(rocketParts, DYNAMIC_BODY);
	(*item)->body->SetAngularDamping(3);
	(*item)->body->SetLinearDamping(0);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(200), SF_2_BOX(200)), 0);


	entity.AddComponent(
	{
		new RocketControlsComponent(),
		new BasicGraphicsComponent(&Globals::window, *item),
		new BasicPhysicsComponent(*item) }
	);

	(*item)->body->SetUserData(&entity);
	EntityManager::RegisterEntity(&entity);
}

 void MakeCar(Entity &entity, Item **item) {

	Parts carParts{
		Factory::CreatePart<Car>(b2Vec2(0,0), b2Vec2(5,1.75))
	};
	(*item) = Factory::CreateItem(carParts, DYNAMIC_BODY);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(600), SF_2_BOX(500)), 0);

	entity.AddComponent(
	{
		new RocketControlsComponent(),
		new BasicPhysicsComponent(*item),
		new BasicGraphicsComponent(&Globals::window, *item),

	}
	);
	(*item)->body->SetUserData(&entity);
	EntityManager::RegisterEntity(&entity);


}


 void MakeGun(Entity &entity, Item **item) {

	std::vector<Part*> gunParts{
		Factory::CreatePart<Cannon>(b2Vec2(0,0), b2Vec2(.35,1)),
	};
	(*item) = Factory::CreateItem(gunParts, DYNAMIC_BODY);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(200), SF_2_BOX(200)), 0);


	entity.AddComponent(
	{
		new GunControlsComponent(),
		new BasicGraphicsComponent(&Globals::window, *item),
		new GunPhysicsComponent(*item, &Globals::window) }
	);

	(*item)->body->SetUserData(&entity); //use entity id instead of reference
	EntityManager::RegisterEntity(&entity);
}

 void MakeBackground(Entity &entity, Item **item) {

	std::vector<Part*> backgroundParts{
		Factory::CreatePart<Background>(b2Vec2(SF_2_BOX(400),SF_2_BOX(300)), b2Vec2(SF_2_BOX(800),SF_2_BOX(600)))
	};
	(*item) = Factory::CreateItem(backgroundParts);

	entity.AddComponent(
	{
		new BasicGraphicsComponent(&Globals::window, *item)
	}
	);

	EntityManager::RegisterEntity(&entity);
}


 void MakeBox(Entity &entity, Item **item) {

	std::vector<Part*> boxParts{
		Factory::CreatePart<Box>(b2Vec2(0,0), b2Vec2(2,2))
	};
	(*item) = Factory::CreateItem(boxParts, DYNAMIC_BODY);
	(*item)->body->SetAngularDamping(2);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(300), SF_2_BOX(300)), DEGREES_2_RAD(0));


	entity.AddComponent(
	{
		new BasicGraphicsComponent(&Globals::window, *item),
		new BasicPhysicsComponent(*item) }
	);

	EntityManager::RegisterEntity(&entity);

}



 void MakeBalloon(Entity &entity, Item **item) {

	std::vector<Part*> balloonParts{
		Factory::CreatePart<Balloon>(b2Vec2(0,0), b2Vec2(1,2))
	};
	(*item) = Factory::CreateItem(balloonParts, DYNAMIC_BODY);
	(*item)->body->SetGravityScale(2);
	(*item)->body->SetLinearDamping(1);
	(*item)->body->SetAngularDamping(1);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(300), SF_2_BOX(300)), 0);
	//balloon->SetCenterMass(b2Vec2(0, -.5));



	entity.AddComponent(
	{
		new BasicGraphicsComponent(&Globals::window, *item),
		new BasicPhysicsComponent(*item) }
	);
	(*item)->body->SetUserData(&entity);
	EntityManager::RegisterEntity(&entity);

}

 void MakePlatform(Entity &entity, Item **item) {

	Parts platformParts{
		Factory::CreatePart<Platform>(b2Vec2(0,0), b2Vec2(8,1))
	};
	(*item) = Factory::CreateItem(platformParts, STATIC_BODY);
	(*item)->body->SetTransform(b2Vec2(SF_2_BOX(400), SF_2_BOX(200)), 0);



	entity.AddComponent(
	{
		new BasicPhysicsComponent(*item),
		new BasicGraphicsComponent(&Globals::window, *item),
	}
	);
	(*item)->body->SetUserData(&entity);
	EntityManager::RegisterEntity(&entity);



}

 void MakeBorder(Entity &entity, Item **item) {
	Parts borderParts{
		Factory::CreatePart<Border>(b2Vec2(SF_2_BOX(400),SF_2_BOX(300)),b2Vec2(SF_2_BOX(800),SF_2_BOX(600)))
	};
	(*item) = Factory::CreateItem(borderParts, STATIC_BODY);


	entity.AddComponent(
	{
		new BasicPhysicsComponent(*item)
	}
	);
	(*item)->body->SetUserData(&entity);
	EntityManager::RegisterEntity(&entity);
}