
// include once this file
#include "Test.h"
#include "Member.h"
#include "Log.h"
#include "Entity.h"
#include "Wire.h"
#include "DataAccess.h"
#include "Container.h"

#include <memory> // for unique_ptr
using namespace Nodable;

int  Test::s_testCount        = 0;
int  Test::s_testSucceedCount = 0;

void Test::ResetCounters()
{
	s_testCount        = 0;
	s_testSucceedCount = 0;
}

void Test::DisplayResults()
{
	LOG_MSG("---------------------------------------------------------------\n");
	if(s_testSucceedCount != s_testCount)
		LOG_MSG("   Some tests failed. Passed : %d / %d\n", s_testSucceedCount, s_testCount);
	else
		LOG_MSG("   All tests are OK : %d / %d\n", s_testSucceedCount, s_testCount);

	LOG_MSG("---------------------------------------------------------------\n");
}

bool Test::RunAll()
{
	LOG_MSG("---------------------------------------------------------------\n");
	LOG_MSG("--                   Testing Nodable                         --\n");
	LOG_MSG("---------------------------------------------------------------\n");
	LOG_MSG("-- Info: note that these tests do NOT cover all the code     --\n");
	LOG_MSG("---------------------------------------------------------------\n");
	ResetCounters();

	LOG_MSG("Running Test for Member class: \n");

	LOG_MSG(" - Connection Flags...\n");

	{
		std::unique_ptr<Member> v(new Member);

		v->setConnectionFlags(ConnectionFlags_InputOnly);

		if (!v->allows(ConnectionFlags_OutputOnly)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-1a : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(ConnectionFlags_InputAndOutput)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-1b : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(ConnectionFlags_InputOnly)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-1c : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(ConnectionFlags_None)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-1d : FAILED !\n");
		}
		s_testCount++;
	}


	{
		std::unique_ptr<Member> v(new Member);

		v->setConnectionFlags(ConnectionFlags_OutputOnly);

		if (v->allows(ConnectionFlags_OutputOnly)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-2a : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(ConnectionFlags_InputAndOutput)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-2b : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(ConnectionFlags_InputOnly)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-2c : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(ConnectionFlags_None)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-2d : FAILED !\n");
		}
		s_testCount++;
	}

	{
		std::unique_ptr<Member> v(new Member);

		v->setConnectionFlags(ConnectionFlags_None);

		if (!v->allows(ConnectionFlags_OutputOnly)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-3a : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(ConnectionFlags_InputAndOutput)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-3b : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(ConnectionFlags_InputOnly)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-3c : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(ConnectionFlags_None)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-3d : FAILED !\n");
		}
		s_testCount++;
	}


	{
		std::unique_ptr<Member> v(new Member);

		v->setConnectionFlags(ConnectionFlags_InputAndOutput);

		if (v->allows(ConnectionFlags_OutputOnly)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-4a : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(ConnectionFlags_InputAndOutput)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-4b : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(ConnectionFlags_InputOnly)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-4c : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(ConnectionFlags_None)){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°0-4d : FAILED !\n");
		}
		s_testCount++;
	}


	// Test 01 - Set/Get a boolean
	//----------------------------

	LOG_MSG(" - Get/Set (Boolean)...\n");

	{
		std::unique_ptr<Member> v(new Member);
		v->setValue(true);		

		if (v->getValueAsBoolean()){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°1a : FAILED !\n");
		}
		s_testCount++;
		
		if (v->getType() == ::Type_Boolean){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°1b : FAILED !\n");
		}
		s_testCount++;

		v->setValue(false);
		if (!v->getValueAsBoolean()){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°1c : FAILED !\n");
		}
		s_testCount++;

		if (v->isSet()){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°1d : FAILED !\n");
		}
		s_testCount++;
	}

	// Test 02 - Set/Get a string
	//---------------------------

	LOG_MSG(" - Get/Set (String)...\n");

	{
		std::unique_ptr<Member> v(new Member);
		v->setValue("Hello world !");
		std::string str = "Hello world !";
		if (v->getValueAsString() == str){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°2a : FAILED !\n");
		}
		s_testCount++;

		if (v->getValueAsBoolean() == true){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°2b : FAILED !\n");
		}
		s_testCount++;

		if (v->getType() == ::Type_String){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°2c : FAILED !\n");
		}
		s_testCount++;

		if (v->getValueAsNumber() == str.length() ){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°2d : FAILED !\n");
		}
		s_testCount++;

		if (v->isSet()){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°2e : FAILED !\n");
		}
		s_testCount++;
	}

	// Test 03 - Set/Get a number (double)
	//------------------------------------

	LOG_MSG(" - Get/Set (Number)...\n");

	{
		std::unique_ptr<Member> v(new Member);
		v->setValue(50.0F);

		if (v->getValueAsNumber() == 50.0F){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°3a : FAILED !\n");
		}
		s_testCount++;

		if (v->getType() == ::Type_Number){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°3b : FAILED !\n");
		}
		s_testCount++;

		if (v->isSet()){
			s_testSucceedCount++;
		}else{
			LOG_MSG("Test n°3c : FAILED !\n");
		}
		s_testCount++;
	}

	LOG_MSG("Running Test for Entity class...\n");

	{
		// Test 4 : set/get a node member :
		//---------------------------------

		std::unique_ptr<Entity> a(new Entity);
		a->addMember("v");
		a->setMember("v", double(100));
		
		if( a->getMember("v")->getValueAsNumber()  == double(100))
			s_testSucceedCount++;
		else
			LOG_MSG("Test n°4 : FAILED !\n");
		s_testCount++;

	}

	LOG_MSG("Running integration Tests for Wire and Entity class...\n");

	{
		// Test 5a : connect two nodes (creates a wire)
		//---------------------------------------------

		std::unique_ptr<Entity> a(new Entity);
		a->addMember("output");

		std::unique_ptr<Entity> b(new Entity);
		b->addMember("input");
		
		std::unique_ptr<Wire> wire(new Wire);
		Entity::Connect(wire.get(), a->getMember("output"), b->getMember("input"));

		if ( 	wire->getSource() 		== a->getMember("output") && 
				wire->getTarget() 		== b->getMember("input")
			)
			s_testSucceedCount++;
		else
			LOG_MSG("Test n°5a : FAILED !\n");
		s_testCount++;

		// Test 5b : disconnect a wire
		//----------------------------

		Entity::Disconnect(wire.get());
		if(wire->getSource() == nullptr && wire->getTarget() == nullptr )
			s_testSucceedCount++;
		else
			LOG_MSG("Test n°5b : FAILED !\n");
		s_testCount++;

	}

	LOG_MSG("Running tests for DataAccess...\n");
	{
		std::unique_ptr<Container>           container(new Container);
		Entity* entity = container->createNodeAdd();
		std::unique_ptr<DataAccess> dataAccessComponent(new DataAccess);

		entity->setMember("name", "UnitTestEntity");
		entity->addComponent("dataAccess", dataAccessComponent.get());

		entity->addMember("BOOL");
		entity->setMember("BOOL", false);

		entity->addMember("STRING");
		entity->setMember("STRING", "hello world!");

		entity->addMember("NUMBER");
		entity->setMember("NUMBER", double(3.14));

		dataAccessComponent->update();
		entity->removeComponent("dataAccess");
	}

	DisplayResults();

	return s_testSucceedCount == s_testCount;
}
