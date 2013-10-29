//
//  mojitoTests.m
//  mojitoTests
//
//  Created by simsea on 10/29/13.
//  Copyright (c) 2013 simsea. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "Mojito.h"

using namespace mojito;

// -----------------------------------------------------------------------------

class TestComponent : public Component
{
public:
	DECLARE_COMPONENT(TestComponent, Component);
	
	TestComponent()
	: m_life(0.0f)
	{
	}
	
	void increment(float dt) { m_life += dt; }
	float getLife() const { return m_life; }
	
private:
	float m_life;
};

typedef std::shared_ptr<TestComponent> SharedTestComponent;

DEFINE_COMPONENT(TestComponent);

// -----------------------------------------------------------------------------

class TestTickProcessor : public EntityProcessor
{
public:
	TestTickProcessor()
	: EntityProcessor(Filter().all({ TestComponent::TypeId }))
	{
	}
	
	void processEntity(float dt, SharedEntity entity)
	{
		SharedTestComponent comp = entity->getComponent<TestComponent>();
		comp->increment(dt);
		
		printf("%d tick now: %f\n", entity->getId(), comp->getLife());
	}
};

// -----------------------------------------------------------------------------


@interface mojitoTests : XCTestCase
{
	EntityManager* m_manager;
}
@end

@implementation mojitoTests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
	
	m_manager = new EntityManager();
}

- (void)tearDown
{
	delete m_manager;
	
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample
{
	// setup the entities
	SharedEntity entity0 = m_manager->createEntity();
	SharedEntity entity1 = m_manager->createEntity();
	SharedEntity entity2 = m_manager->createEntity();
	
	// add the test processor
	m_manager->addProcessor(new TestTickProcessor());
	
	// add components
	entity0->addComponent<TestComponent>();
	entity2->addComponent<TestComponent>();
	
	// update a few times
	for (int i = 0; i < 10; ++i)
	{
		m_manager->update(0.2f);
		usleep(100 * 1000);
	}
	
	// check the entities
	SharedTestComponent test = entity0->getComponent<TestComponent>();
	
	XCTAssertEqualWithAccuracy(test->getLife(), 2.0f, EPSILON, "entity0 test component time should be 2.0, but got %f", test->getLife());
}

@end
