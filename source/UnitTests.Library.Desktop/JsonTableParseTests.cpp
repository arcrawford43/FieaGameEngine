#include "pch.h"
#include "JsonTableParseHelper.h"
#include "ToStringSpecialization.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include <crtdbg.h>
#include "AttributedFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace UnitTestsLibraryDesktop
{
	TEST_CLASS(JsonTableParseTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
#if defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leak!");
			}
#endif
		}

		TEST_METHOD(SingleInt)
		{
			JsonTableParseHelper helper;
			Scope* scope = new Scope;
			JsonTableParseHelper::SharedData sharedData{ scope };
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "hero" : {
                    "integer": 1
                  }
            })";

			coor.Parse(json);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->BackInteger(), 1);
			delete scope;
		}

		TEST_METHOD(DoubleIntArray)
		{
			JsonTableParseHelper helper;
			Scope scope;
			JsonTableParseHelper::SharedData sharedData{ &scope };
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "hero" : {
                    "table": [{
						"sword" : {
							"integer" : [1, 2, 3]
						}
					},
					{"shield" : {
						"integer" : [1, 2, 3]
					}
					
					}]
                  }
            })";

			coor.Parse(json);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable()->Find("sword")->GetInteger(), 1);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable()->Find("sword")->GetInteger(1), 2);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable()->Find("sword")->GetInteger(2), 3);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable(1)->Find("shield")->GetInteger(), 1);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable(1)->Find("shield")->GetInteger(1), 2);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable(1)->Find("shield")->GetInteger(2), 3);
		}


		TEST_METHOD(BigTest)
		{
			JsonTableParseHelper helper;
			Scope scope;
			JsonTableParseHelper::SharedData sharedData{ &scope };
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
  "Name": {
	"string" : "Test"
  },
  "Health": {
	"integer" : 100
  },
  "Damage": {
	"float" : 100.0
  },
  "Direction": {
    "vector" : "vec4(1,0,0,1) "
		},
			"Transform": {
				"matrix" : "mat4x4((1,0,0,0),(0,1,0,0),(0,0,1,0),(0,0,0,1)) "
			},
				"Aliases" : {
					"string" : ["Bob", "Jim", "Fred"]
				},
					"Address" : {
						"table" : {
							"Street": {
								"string" : "123 Anystreet St."
							},
								"City" : {
									"string" : "Orlando"
								},
									"Postal Code" : {
										"table" : {
											"Zip Code": {
												"integer" : 12345
											},
												"Zip Code+4" : {
													"integer" : 6789
												}
										}
									}
						}
					}
	} )";

			coor.Parse(json);
			Assert::AreEqual(sharedData._rootScope->Find("Name")->BackString(), "Test"s);
			Assert::AreEqual(sharedData._rootScope->Find("Health")->BackInteger(), 100);
			Assert::AreEqual(sharedData._rootScope->Find("Damage")->BackFloat(), 100.0f);
			Assert::AreEqual(sharedData._rootScope->Find("Direction")->BackVector(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
			Assert::AreEqual(sharedData._rootScope->Find("Transform")->BackMatrix(), glm::mat4(1.0f));
			Assert::AreEqual(sharedData._rootScope->Find("Aliases")->GetString(), "Bob"s);
			Assert::AreEqual(sharedData._rootScope->Find("Aliases")->GetString(1), "Jim"s);
			Assert::AreEqual(sharedData._rootScope->Find("Aliases")->GetString(2), "Fred"s);
			Assert::AreEqual(sharedData._rootScope->Find("Address")->GetTable()->Find("Street")->GetString(), "123 Anystreet St."s);
			Assert::AreEqual(sharedData._rootScope->Find("Address")->GetTable()->Find("City")->GetString(), "Orlando"s);
			Assert::AreEqual(sharedData._rootScope->Find("Address")->GetTable()->Find("Postal Code")->GetTable()->Find("Zip Code")->GetInteger(), 12345);
			Assert::AreEqual(sharedData._rootScope->Find("Address")->GetTable()->Find("Postal Code")->GetTable()->Find("Zip Code+4")->GetInteger(), 6789);
		}

		TEST_METHOD(Clone)
		{
			JsonTableParseHelper helper;
			Scope scope;
			JsonTableParseHelper::SharedData sharedData{ &scope };
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
  "Name": {
	"string" : "Test"
  },
  "Health": {
	"integer" : 100
  },
  "Damage": {
	"float" : 100.0
  },
  "Direction": {
    "vector" : "vec4(1,0,0,1) "
		},
			"Transform": {
				"matrix" : "mat4x4((1,0,0,0),(0,1,0,0),(0,0,1,0),(0,0,0,1)) "
			},
				"Aliases" : {
					"string" : ["Bob", "Jim", "Fred"]
				},
					"Address" : {
						"table" : {
							"Street": {
								"string" : "123 Anystreet St."
							},
								"City" : {
									"string" : "Orlando"
								},
									"Postal Code" : {
										"table" : {
											"Zip Code": {
												"integer" : 12345
											},
												"Zip Code+4" : {
													"integer" : 6789
												}
										}
									}
						}
					}
	} )";

			JsonParseCoordinator* clone = coor.Clone();
			clone->GetSharedData().As< JsonTableParseHelper::SharedData>()->SetRootScope(&scope);

			clone->Parse(json);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Name")->BackString(), "Test"s);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Health")->BackInteger(), 100);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Damage")->BackFloat(), 100.0f);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Direction")->BackVector(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Transform")->BackMatrix(), glm::mat4(1.0f));
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Aliases")->GetString(), "Bob"s);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Aliases")->GetString(1), "Jim"s);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Aliases")->GetString(2), "Fred"s);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Address")->GetTable()->Find("Street")->GetString(), "123 Anystreet St."s);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Address")->GetTable()->Find("City")->GetString(), "Orlando"s);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Address")->GetTable()->Find("Postal Code")->GetTable()->Find("Zip Code")->GetInteger(), 12345);
			Assert::AreEqual(clone->GetSharedData().As<JsonTableParseHelper::SharedData>()->_rootScope->Find("Address")->GetTable()->Find("Postal Code")->GetTable()->Find("Zip Code+4")->GetInteger(), 6789);

			delete clone;
		}

		TEST_METHOD(EmptyArray)
		{
			JsonTableParseHelper helper;
			Scope scope;
			JsonTableParseHelper::SharedData sharedData{ &scope };
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "hero" : {
                    "table": []
                  },
				"villian" : {
					"string" : "Evil"
			}
            })";

			coor.Parse(json);
			auto Func = [&] {sharedData._rootScope->Find("hero")->GetTable()->operator[](0); };
			Assert::ExpectException<std::out_of_range>(Func);
			Assert::AreEqual(sharedData._rootScope->Find("villian")->BackString(), "Evil"s);
		}

		TEST_METHOD(Class)
		{

			JsonTableParseHelper helper;
			Scope scope;
			JsonTableParseHelper::SharedData sharedData{ &scope };
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "hero" : {
                    "table": [{
						"class" : 1,
						"sword" : {
							"integer" : [1, 2, 3]
						},
						"Int" : {
							"integer" : 1
						},
						"IntArray" : {
							"integer" : [1, 2, 3, 4, 5]
						}
					},
					{"class" : "Scope",
					"shield" : {
						"integer" : [1, 2, 3]
					}
					
					}]
                  }
            })";

			Assert::ExpectException<std::runtime_error>([&] {coor.Parse(json); });

			json = R"({
                 "hero" : {
                    "table": [{
						"class" : "AttributedFoo",
						"sword" : {
							"integer" : [1, 2, 3]
						},
						"Int" : {
							"integer" : 1
						},
						"IntArray" : {
							"integer" : [1, 2, 3, 4, 5]
						},
						"Float" : {
							"float" : 1.0
						},	
						"Str" : {
							"string" : "Hello World"
						},
						"NestedScope" : {
							"table" : {
								"hi" : {
								"string" : "Hello"
								}
							}
						},
						"NestedScopeArray" : {
							"table" : [{
								"table1" : {
								"string" : "Hello1"
								}
							},
								{"class" : "AttributedFoo",
								"table2" : {
								"string" : "Hello2"
								}
							}]
						},

					},
					{"class" : "Scope",
					"shield" : {
						"integer" : [1, 2, 3]
					}
					
					}]
                  }
            })";
			Assert::ExpectException<std::runtime_error>([&] {coor.Parse(json); });
			coor;
			AttributedFooFactory attributedFooFactory;
			coor.Parse(json);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable()->Find("sword")->GetInteger(), 1);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable()->Find("sword")->GetInteger(1), 2);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable()->Find("sword")->GetInteger(2), 3);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable(1)->Find("shield")->GetInteger(), 1);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable(1)->Find("shield")->GetInteger(1), 2);
			Assert::AreEqual(sharedData._rootScope->Find("hero")->GetTable(1)->Find("shield")->GetInteger(2), 3);

			AttributedFoo* attributedFoo = sharedData._rootScope->Find("hero")->GetTable()->As<AttributedFoo>();
			Assert::IsNotNull(attributedFoo);

			AttributedFoo* notAttributedFoo = sharedData._rootScope->Find("hero")->GetTable(1)->As<AttributedFoo>();
			Assert::IsNull(notAttributedFoo);

			Assert::IsTrue(attributedFoo->IsAuxiliaryAttribute("sword"));
			Assert::AreEqual(attributedFoo->Find("sword")->GetInteger(), 1);
			Assert::AreEqual(attributedFoo->Int, 1);

			Assert::AreEqual(attributedFoo->IntArray[0], 1);
			Assert::AreEqual(attributedFoo->IntArray[1], 2);
			Assert::AreEqual(attributedFoo->IntArray[2], 3);

			Assert::AreEqual(attributedFoo->Float, 1.0f);

			Assert::AreEqual(attributedFoo->Find("NestedScope")->GetTable()->operator[]("hi").GetString(), "Hello"s);
			Assert::AreEqual(attributedFoo->Find("NestedScopeArray")->GetTable()->operator[]("table1").GetString(), "Hello1"s);

			Assert::AreEqual(attributedFoo->Str, "Hello World"s);

			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("this"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("Int"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("Float"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("Str"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("Vec"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("Mat"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("IntArray"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("FloatArray"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("StrArray"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("VecArray"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("MatArray"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(attributedFoo->IsPrescribedAttribute("NestedScopeArray"));
		}

	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState JsonTableParseTests::_startMemState;
}